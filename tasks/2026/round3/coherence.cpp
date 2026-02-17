// @check-accepted: examples NQsmall NoUpd LineGraph NQlarge NQfull
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <unordered_set>

struct PairHasher {
	std::size_t operator() (const std::pair<int,int>& p) const {
		return 1000000ULL * p.first + p.second;
	}
};

int gs;
std::vector<std::unordered_set<int>> adj_list;
int tree[1200005];
int lazy[1200005];
std::vector<std::pair<int,int>> walk_stack;

void st_push(int node, int l, int r) {
	tree[node] += lazy[node];
	if (l != r) {
		lazy[node<<1] += lazy[node];
		lazy[node<<1|1] += lazy[node];
	}
	lazy[node] = 0;
}

void st_update(int node, int l, int r, int st, int fi, int add) {
	if (l > fi || r < st) {
		st_push(node, l, r);
		return;
	}
	if (st <= l && r <= fi) {
		lazy[node] += add;
		st_push(node, l, r);
		return;
	}
	
	st_push(node, l, r);
	int m = (l+r) >> 1;
	st_update(node<<1, l, m, st, fi, add);
	st_update(node<<1|1, m+1, r, st, fi, add);
	tree[node] = std::min(tree[node<<1], tree[node<<1|1]);
}

int st_query(int node, int l, int r, int st, int fi) {
	st_push(node, l, r);
	if (l > fi || r < st) {
		return 0x3f3f3f3f;
	}
	if (st <= l && r <= fi) {
		return tree[node];
	}

	int m = (l+r) >> 1;
	return std::min(st_query(node<<1, l, m, st, fi), st_query(node<<1|1, m+1, r, st, fi));
}

///////////////////////////////////////////////////////////////

void init_fastio() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
}

void read_tree() {
	std::cin >> gs;
	adj_list.resize(gs+1);
	for (int i = 0, a, b; i < gs-1; i++) {
		std::cin >> a >> b;
		adj_list[a].emplace(b);
		adj_list[b].emplace(a);
	}
}

void init_segtree() {
	for (int i = 1; i <= gs; i++) {
		st_update(1, 1, gs, i, gs, 1);
		for (int j : adj_list[i]) {
			if (i < j) {
				st_update(1, 1, gs, j, gs, -1);
			}
		}
	}
}

void swap_nodes(int a, int b) {
	if (a > b) {
		std::swap(a, b);
	}

	std::unordered_set<std::pair<int,int>, PairHasher> edges;
	for (auto x : {a, b}) for (const auto& i : adj_list[x]) {
		edges.emplace(std::min(x, i), std::max(x, i));
	}

	// undo each edges contribution
	for (const auto& [x, y] : edges) {
		adj_list[x].erase(y);
		adj_list[y].erase(x);
		st_update(1, 1, gs, std::max(x, y), gs, 1);
	}

	for (auto [x, y] : edges) {
		if (x == a) {
			x = b;
		}
		else if (x == b) {
			x = a;
		}
		if (y == a) {
			y = b;
		}
		else if (y == b) {
			y = a;
		}

		adj_list[x].emplace(y);
		adj_list[y].emplace(x);
		st_update(1, 1, gs, std::max(x, y), gs, -1);
	}
}

void answer_queries() {
	/*for (int i = 1; i <= gs; i++) {
		std::cout << st_query(1, 1, gs, i, i) << " ";
	}
	std::cout << "\n";*/

	int q = 0;
	std::cin >> q;
	while (q--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int a, b;
			std::cin >> a >> b;
			swap_nodes(a, b);

			/*for (int i = 1; i <= gs; i++) {
				std::cout << st_query(1, 1, gs, i, i) << " ";
			}
			std::cout << "\n";*/
		}
		else {
			int min_req;
			std::cin >> min_req;
			if (min_req == 1) {
				std::cout << "1\n";
			}
			else {
				int ans = gs;
				int l = min_req, r = gs;
				while (l <= r) {
					int m = (l+r) >> 1;
					if (st_query(1, 1, gs, min_req, m) == 1) {
						ans = m;
						r = m-1;
					}
					else {
						l = m+1;
					}
				}

				std::cout << ans << "\n";
			}
		}
	}
}

int main() {
	init_fastio();
	read_tree();
	init_segtree();
	answer_queries();
}
