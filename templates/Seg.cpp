#include <bits/stdc++.h>

using namespace std;
using vInt = vector<int>;
using matInt = vector<vInt>;
using pii = pair<int, int>;
using vPii = vector<pii>;
using matPii = vector<vPii>;
using LL = long long;
using vLL = vector<LL>;
using matLL = vector<vLL>;
using pLL = pair<LL, LL>;
using vPLL = vector<pLL>;
using vBool = vector<bool>;
using matBool = vector<vBool>;
using vStr = vector<string>;

#define all(x) (x).begin(), (x).end()

// SegTree: range sum

template <typename T>
struct Seg{
    int N;
    vector<T> seg;
    Seg(int N): N(N){
        int siz = 1;
        while(siz < 2*N) siz <<= 1;
        seg = vector<T>(siz+1);
    }
    T merge(T a, T b){
        // can be changed
        return a+b;
    }
    void init(int idx, int s, int e, vector<T>& A){
        if(s == e){
            seg[idx] = A[s];
            return;
        }
        int m = s+e >> 1;
        init(idx<<1, s, m, A);
        init(idx<<1|1, m+1, e, A);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    void update(int tar, T v, int idx, int s, int e){
        if(r < s || e < l) return;
        if(s == e){
            seg[idx] = v; // can be changed
            return;
        }
        int m = s+e >> 1;
        update(tar, v, idx<<1, s, m);
        update(tar, v, idx<<1|1, m+1, e);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    T query(int l, int r, int idx, int s, int e){
        if(r < s || e < l) return 0; // can be changed
        if(l <= s && e <= r) return seg[idx];
        int m = s+e >> 1;
        return merge(query(l, r, idx<<1, s, m), query(l, r, idx<<1|1, m+1, e));
    }
};
