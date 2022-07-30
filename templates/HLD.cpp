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

struct HLD{
    int N, root, num;
    vInt in, pars, depth, top, trSize;
    matInt tree;

    HLD(int N=1, int root = 1): N(N), root(root){
        in = vInt(N+1);
        pars = vInt(N+1);
        depth = vInt(N+1);
        top = vInt(N+1);
        trSize = vInt(N+1);
        tree = matInt(N+1);
        num = 0;
    }

    // get tree structure, parents, and depth
    void dfs1(int tar, int par, matInt& adjs){
        depth[tar] = depth[par] + 1;
        for(int nxt: adjs[tar]){
            if(nxt == par) continue;
            pars[nxt] = tar;
            tree[tar].push_back(nxt);
            dfs1(nxt, tar, adjs);
        }
    }

    // HLD preparation
    int dfs2(int tar){
        trSize[tar] = 1;
        for(int& nxt: tree[tar]){
            trSize[tar] += dfs2(nxt);
            if(trSize[nxt] > trSize[tree[tar][0]])
                swap(tree[tar][0], nxt);
        }
        return trSize[tar];
    }

    void dfs3(int tar){
        in[tar] = ++num;
        for(int nxt: tree[tar]){
            top[nxt] = (nxt == tree[tar][0]) ? top[tar] : nxt;
            dfs3(nxt);
        }
    }

    void run(matInt& adjs){
        dfs1(root, 0, adjs);
        dfs2(root);
        dfs3(root);
    }
};

////////////////////////////////////////////////////////////////////
// Example: 트리와 쿼리1 
// https://www.acmicpc.net/problem/13510

template <typename T>
struct Seg{
    int N;
    vector<T> seg;
    Seg(int N, T BASE_VAL = 0): N(N){
        int siz = 1;
        while(siz < 2*N) siz <<= 1;
        seg = vector<T>(siz+1);
    }
    T merge(T a, T b){
        return max(a, b);
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
    void update(int tar, int v, int idx, int s, int e){
        if(tar < s || tar > e) return;
        if(s == e){
            seg[idx] = v;
            return;
        }
        int m = s+e >> 1;
        update(tar, v, idx<<1, s, m);
        update(tar, v, idx<<1|1, m+1, e);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    T query(int l, int r, int idx, int s, int e){
        if(r < s || e < l) return 0;
        if(l <= s && e <= r) return seg[idx];
        int m = s+e >> 1;
        T ans = merge(query(l, r, idx<<1, s, m), query(l, r, idx<<1|1, m+1, e));
        return ans;
    }
};

int treeQuery(int u, int v, Seg<int>& seg, HLD& hld){
    vInt& in = hld.in;
    vInt& top = hld.top;
    vInt& depth = hld.depth;
    vInt& pars = hld.pars;

    if(depth[u] > depth[v]) swap(u, v);
    int ans = 0;

    while(top[u] != top[v]){
        if(depth[top[u]] < depth[top[v]]) swap(u, v);
        ans = max(ans, seg.query(in[top[u]], in[u], 1, 1, seg.N));
        u = pars[top[u]];
    }
    
    if(depth[u] > depth[v]) swap(u, v);
    if(u != v) ans = max(ans, seg.query(in[u]+1, in[v], 1, 1, seg.N));

    return ans;
}

void solve(){
    int N;
    cin >> N;

    matInt adjs(N+1);

    struct Node{
        int u, v, c;
    };

    vector<Node> eds(N+1);
    for(int i=1; i<N; i++){
        int u, v, c;
        cin >> u >> v >> c;
        if(u > v) swap(u, v);
        adjs[u].push_back(v);
        adjs[v].push_back(u);
        eds[i] = {u,v,c};
    }

    HLD hld(N);
    hld.run(adjs);

    vInt& in = hld.in;
    vInt& top = hld.top;
    vInt& depth = hld.depth;

    vInt cost(N+1);
    for(int i=1; i<N; i++){
        auto [u, v, c] = eds[i];
        if(depth[u] > depth[v]) swap(u, v);
        cost[in[v]] = c;
    }

    Seg<int> seg(N);
    seg.init(1, 1, N, cost);

    int Q;
    cin >> Q;
    for(int i=1; i<=Q; i++){
        int op; cin >> op;
        if(op == 1){
            int idx, c;
            cin >> idx >> c;
            auto [u, v, _] = eds[idx];
            if(depth[u] > depth[v]) swap(u, v);
            seg.update(in[v], c, 1, 1, N);
        }
        else{
            int u, v;
            cin >> u >> v;
            cout << treeQuery(u, v, seg, hld) << '\n';
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    solve();
    
    return 0;
}
