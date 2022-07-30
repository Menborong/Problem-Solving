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

template <typename T>
struct Lazy{
    int N;
    vector<T> seg, lazy;
    Lazy(int N): N(N){
        int siz = 1;
        while(siz < 2*N) siz <<= 1;
        seg = vector<T>(siz+1);
        lazy = vector<T>(siz+1);
    }
    T merge(T a, T b){
        return max(a, b);
    }
    T bulk(int s, int e, T c){
        return c;
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
    void prop(int idx, int s, int e){
        int m = s+e >> 1;
        if(s != m) lazy[idx<<1] += lazy[idx];
        if(m+1 != e) lazy[idx<<1|1] += lazy[idx];
        seg[idx<<1] += bulk(s, m, lazy[idx]);
        seg[idx<<1|1] += bulk(m+1, e, lazy[idx]);
        lazy[idx] = 0;
    }
    void update(int l, int r, T v, int idx, int s, int e){
        if(r < s || e < l) return;
        if(l <= s && e <= r){
            seg[idx] += bulk(s, e, v);
            lazy[idx] += v;
            return;
        }
        int m = s+e >> 1;
        if(lazy[idx]) prop(idx, s, e);
        update(l, r, v, idx<<1, s, m);
        update(l, r, v, idx<<1|1, m+1, e);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    T query(int l, int r, int idx, int s, int e){
        if(r < s || e < l) return 0;
        if(l <= s && e <= r) return seg[idx];
        int m = s+e >> 1;
        if(lazy[idx]) prop(idx, s, e);
        return merge(query(l, r, idx<<1, s, m), query(l, r, idx<<1|1, m+1, e));
    }
};
