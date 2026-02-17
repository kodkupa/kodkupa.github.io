#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstdint>

struct SegTreeNode {
	int cnt = 0;
	int64_t sum = 0;
	SegTreeNode* l = nullptr;
	SegTreeNode* r = nullptr;
};

int mempool_cnt = 0;
SegTreeNode mempool[21000005];

SegTreeNode* new_node() {
	return mempool + mempool_cnt++;
}

inline SegTreeNode* get_lchild(SegTreeNode* node) {
	if (!node) {
		return nullptr;
	}
	return node->l;
}

inline SegTreeNode* get_rchild(SegTreeNode* node) {
	if (!node) {
		return nullptr;
	}
	return node->r;
}

inline int get_cnt(SegTreeNode* node) {
	if (!node) {
		return 0;
	}
	return node->cnt;
}

inline int64_t get_sum(SegTreeNode* node) {
	if (!node) {
		return 0;
	}
	return node->sum;
}

int n, m, q;
int arr1[500005];
int arr2[500005];
int sorted[1000005];
SegTreeNode* tree1[500005];
SegTreeNode* tree2[500005];

int norm(int val) {
	int l = 0, r = n+m-1;
	while (l <= r) {
		int m = (l+r) >> 1;
		if (sorted[m] == val) {
			return m;
		}
		else if (sorted[m] > val) {
			r = m-1;
		}
		else {
			l = m+1;
		}
	}
	return -1;
}

int norm_r(int val) {
	return sorted[val];
}

SegTreeNode* update_copy(SegTreeNode* tree, int l, int r, int pos, int add) {
	SegTreeNode* ret = new_node();
	ret->cnt = get_cnt(tree);
	ret->sum = get_sum(tree);
	ret->l = get_lchild(tree);
	ret->r = get_rchild(tree);
	if (l == r) {
		ret->cnt += 1;
		ret->sum += add;
		return ret;
	}

	int m = (l+r)>>1;
	if (pos <= m) {
		ret->l = update_copy(ret->l, l, m, pos, add);
	}
	else {
		ret->r = update_copy(ret->r, m+1, r, pos, add);
	}

	ret->cnt = get_cnt(ret->l) + get_cnt(ret->r);
	ret->sum = get_sum(ret->l) + get_sum(ret->r);
	return ret;
}

int query_kth(SegTreeNode* r1, SegTreeNode* l1, SegTreeNode* r2, SegTreeNode* l2, int l, int r, int k, int& cnt, int64_t& sum) {
	if (l == r) {
		cnt += get_cnt(r1) - get_cnt(l1) + get_cnt(r2) - get_cnt(l2);
		sum += get_sum(r1) - get_sum(l1) + get_sum(r2) - get_sum(l2);
		return l;
	}

	int m = (l+r)>>1;
	int new_k = k - get_cnt(get_rchild(r1)) + get_cnt(get_rchild(l1)) - get_cnt(get_rchild(r2)) + get_cnt(get_rchild(l2));
	if (new_k >= 0) {
		cnt += get_cnt(get_rchild(r1)) - get_cnt(get_rchild(l1)) + get_cnt(get_rchild(r2)) - get_cnt(get_rchild(l2));
		sum += get_sum(get_rchild(r1)) - get_sum(get_rchild(l1)) + get_sum(get_rchild(r2)) - get_sum(get_rchild(l2));
		return query_kth(get_lchild(r1), get_lchild(l1), get_lchild(r2), get_lchild(l2), l, m, new_k, cnt, sum);
	}
	else {
		return query_kth(get_rchild(r1), get_rchild(l1), get_rchild(r2), get_rchild(l2), m+1, r, k, cnt, sum);
	}
}

void read_arrays() {
	std::cin >> n >> m >> q;
	for (int i = 0; i < n; i++) {
		std::cin >> arr1[i];
		sorted[i] = arr1[i];
	}
	for (int i = 0; i < m; i++) {
		std::cin >> arr2[i];
		sorted[i+n] = arr2[i];
	}

	std::sort(sorted, sorted+n+m);
}

void build_pst() {
	for (int i = 0; i < n; i++) {
		tree1[i] = update_copy(((i-1>=0) ? tree1[i-1] : nullptr), 0, n+m-1, norm(arr1[i]), arr1[i]);
	}
	for (int i = 0; i < m; i++) {
		tree2[i] = update_copy(((i-1>=0) ? tree2[i-1] : nullptr), 0, n+m-1, norm(arr2[i]), arr2[i]);
	}
}

void answer_queries() {
	while (q--) {
		int l1, r1, l2, r2;
		std::cin >> l1 >> r1 >> l2 >> r2;

		int len = r1-l1+1 + r2-l2+1;
		int k = r1-l1+1;
		
		int cnt = 0;
		int64_t sum = 0;
		int kth = norm_r(query_kth(tree1[r1], ((l1-1>=0) ? tree1[l1-1] : nullptr),
		                           tree2[r2], ((l2-1>=0) ? tree2[l2-1] : nullptr),
		                           0, n+m-1, k, cnt, sum));

		if (cnt > k) {
			sum -= (cnt-k) * kth;
		}

		std::cout << sum << "\n";
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	read_arrays();
	build_pst();
	answer_queries();
}
