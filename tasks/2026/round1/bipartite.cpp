// @check-accepted: *
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <numeric>

namespace xnqs {

class dsu_rollback {
private:
	struct dsu_state_t {
		int a, old_sz, b, old_t, old_bip;
		dsu_state_t(int a, int old_sz, int b, int old_t, int old_bip):
			a(a), old_sz(old_sz), b(b), old_t(old_t), old_bip(old_bip) {}
	};

	int n;
	int bip;
	std::vector<int> t;
	std::vector<int> sz;
	std::vector<dsu_state_t> stk;
public:
	dsu_rollback() {
		bip = 1;
		t.assign(1, 0); std::iota(t.begin(), t.end(), 0);
		sz.assign(1, 1);
		stk.clear();
	}

	dsu_rollback(int n): n(n) {
		bip = 1;
		t.assign(2*n, 0); std::iota(t.begin(), t.end(), 0);
		sz.assign(2*n, 1);
		stk.clear();
	}

	int is_bipartite() {
		return bip;
	}

	int find(int k) {
		if (t[k] != k) return find(t[k]);
		return t[k];
	}

	void unite(int a, int b) {
		int ra = find(a);
		int rb = find(b);

		if (sz[ra] < sz[rb]) {
			std::swap(ra, rb);
		}
		
		stk.emplace_back(ra, sz[ra], rb, t[rb], bip);

		if (ra == rb) {
			return;
		}

		sz[ra] += sz[rb];
		t[rb] = ra;
	}

	void add_edge(int a, int b) {
		unite(a, b+n);
		bip &= find(a) != find(a+n);
		bip &= find(b) != find(b+n);
		unite(a+n, b);
		bip &= find(a) != find(a+n);
		bip &= find(b) != find(b+n);
	}

	void undo() {
		auto [a, old_sz, b, old_t, old_bip] = stk.back();
		stk.pop_back();

		sz[a] = old_sz;
		t[b] = old_t;
		bip = old_bip;
	}

	void remove_edge() {
		undo();
		undo();
	}
}; // class dsu_rollback

class dsu_queue {
private:
	struct update_t {
		int a, b, rev;
		update_t(int a, int b, int rev):
			a(a), b(b), rev(rev) {}
	};

	int n;
	std::size_t ready;
	std::vector<update_t> updates;
	dsu_rollback dsu;
public:
	dsu_queue(int n): n(n) {
		ready = 0;
		updates.clear();
		dsu = dsu_rollback(n);
	}

	bool is_bipartite() {
		return dsu.is_bipartite();
	}

	int find(int k) {
		return dsu.find(k);
	}

	void add_edge(int a, int b) {
		updates.emplace_back(a, b, 0);
		dsu.add_edge(a, b);
	}

	void remove_edge() {
		if (!ready) {
			for (std::size_t i = 0; i < updates.size(); i++) {
				dsu.remove_edge();
			}

			std::reverse(updates.begin(), updates.end());
			
			for (std::size_t i = 0; i < updates.size(); i++) {
				updates[i].rev = 1;
				dsu.add_edge(updates[i].a, updates[i].b);
			}

			updates.pop_back();
			dsu.remove_edge();

			ready = updates.size();
		}
		else {
			std::vector<update_t> tmp[2];

			while (!updates.back().rev) {
				tmp[0].emplace_back(updates.back());
				updates.pop_back();
				dsu.remove_edge();
			}

			std::size_t block = ready & (-ready);
			for (std::size_t i = 0; i < block; i++) {
				tmp[1].emplace_back(updates.back());
				updates.pop_back();
				dsu.remove_edge();
			}

			for (int i = 0; i < 2; i++) {
				std::reverse(tmp[i].begin(), tmp[i].end());
			}

			for (const auto& update : tmp[0]) {
				updates.emplace_back(update);
				dsu.add_edge(update.a, update.b);
			}
			
			for (const auto& update : tmp[1]) {
				updates.emplace_back(update);
				dsu.add_edge(update.a, update.b);
			}

			updates.pop_back();
			dsu.remove_edge();
			ready -= 1;
		}
	}
}; // class dsu_queue

}; // namespace xnqs

int gs, edg;
std::vector<std::pair<int,int>> edges;

void read_data() {
	std::cin >> gs >> edg;
	edges.reserve(edg);
	for (int i = 0, a, b; i < edg; i++) {
		std::cin >> a >> b; --a, --b;
		edges.emplace_back(a, b);
	}
}

void solve() {
	int64_t ret = 0;
	xnqs::dsu_queue dsu(gs);
	for (int l = 0, r = 0; r < edg; r++) {
		dsu.add_edge(edges[r].first, edges[r].second);
		while (l < r && !dsu.is_bipartite()) {
			dsu.remove_edge();
			++l;
		}

		ret += r-l+1;
	}

	std::cout << ret << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	read_data();
	solve();
}
