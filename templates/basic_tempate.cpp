#include <bits/stdc++.h>

using namespace std;
using LL = long long;
#define int LL // check!!!!!!!


using vInt = vector<int>;
using vLL = vector<LL>;
using pLL = pair<LL, LL>;
using vPLL = vector<pLL>;
using pii = pair<int, int>;
using vPii = vector<pii>;
using matInt = vector<vInt>;
using matLL = vector<vLL>;
using vBool = vector<bool>;
using matBool = vector<vBool>;
using vStr = vector<string>;

#define all(x) (x).begin(), (x).end()
#define cyes cout << "YES" << '\n'
#define cno cout << "NO" << '\n'
#define for0(i, n) for(int (i)=0; (i)<(n); (i)++)
#define for1(i, n) for(int (i)=1; (i)<=(n); (i)++) 
#define newInt(n) int n; cin >> n
#define newLL(n) LL n; cin >> n
#define newVInt(A, f, t) vInt A(t); for(int i=f; i<t; i++) cin >> A[i]
#define newVLL(A, f, t) vLL A(t); for(int i=f; i<t; i++) cin >> A[i]
#define endl '\n'
#define ff first
#define ss second

/////////////////////////////////////////////////////////

const int MOD = 998244353;

int modAdd(LL a, LL b){
    return (a+b)%MOD;
}
int modMul(LL a, LL b){
    return (a*b)%MOD;
}
int modExp(LL a, int k){
    LL ans = 1;
    while(k){
        if(k&1) ans = modMul(ans, a);
        a = modMul(a, a);
        k >>= 1;
    }
    return ans;
}

vInt FACT, INVF;
void initFACT(int N){
    FACT = INVF = vInt(N+1);
    FACT[0] = 1;
    for(int i=1; i<=N; i++)
        FACT[i] = modMul(FACT[i-1], i);
    INVF[N] = modExp(FACT[N], MOD-2);
    for(int i=N-1; i>=0; i--)
        INVF[i] = modMul(INVF[i+1], i+1);
}

int getC(int N, int M){
    if(M < 0 || M > N) return 0;
    int ans = FACT[N];
    ans = modMul(ans, INVF[M]);
    ans = modMul(ans, INVF[N-M]);
    return ans;
}

/////////////////////////////////////////////////////////

struct SumSeg{
    int N;
    vInt seg;
    SumSeg(int N): N(N){
        int siz = 1;
        while(siz < 2*N) siz <<= 1;
        seg = vInt(siz+1);
    }
    int merge(int a, int b){
        // can be changed
        return a+b;
    }
    void init(int idx, int s, int e, vInt& A){
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
        if(tar > e || tar < s) return;
        if(s == e){
            seg[idx] = v; // can be changed
            return;
        }
        int m = s+e >> 1;
        update(tar, v, idx<<1, s, m);
        update(tar, v, idx<<1|1, m+1, e);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    int query(int l, int r, int idx, int s, int e){
        if(r < s || e < l) return 0; // can be changed
        if(l <= s && e <= r) return seg[idx];
        int m = s+e >> 1;
        return merge(query(l, r, idx<<1, s, m), query(l, r, idx<<1|1, m+1, e));
    }
};

/////////////////////////////////////////////////////////

struct RMQSeg{
    int N;
    vInt seg;
    RMQSeg(int N): N(N){
        int siz = 1;
        while(siz < 2*N) siz <<= 1;
        seg = vInt(siz+1, -1e18);
    }
    int merge(int a, int b){
        // can be changed
        return max(a, b);
    }
    void init(int idx, int s, int e, vInt& A){
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
        if(tar > e || tar < s) return;
        if(s == e){
            seg[idx] = v; // can be changed
            return;
        }
        int m = s+e >> 1;
        update(tar, v, idx<<1, s, m);
        update(tar, v, idx<<1|1, m+1, e);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    int query(int l, int r, int idx, int s, int e){
        if(r < s || e < l) return -1e18; // can be changed
        if(l <= s && e <= r) return seg[idx];
        int m = s+e >> 1;
        return merge(query(l, r, idx<<1, s, m), query(l, r, idx<<1|1, m+1, e));
    }
};

/////////////////////////////////////////////////////////

struct RMQIdxSeg{
    int N;
    vInt seg;
    vInt& A;
    RMQIdxSeg(int N, vInt& A): N(N), A(A){
        int siz = 1;
        while(siz < 2*N) siz <<= 1;
        seg = vInt(siz+1, -1);
    }
    int merge(int a, int b){
        // can be changed
        if(a == -1) return b;
        if(b == -1) return a;
        return A[a] < A[b] ? a : b;
    }
    void init(int idx, int s, int e, vInt& A){
        if(s == e){
            seg[idx] = s;
            return;
        }
        int m = s+e >> 1;
        init(idx<<1, s, m, A);
        init(idx<<1|1, m+1, e, A);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    void update(int tar, int v, int idx, int s, int e){
        if(tar > e || tar < s) return;
        if(s == e){
            seg[idx] = v; // can be changed
            return;
        }
        int m = s+e >> 1;
        update(tar, v, idx<<1, s, m);
        update(tar, v, idx<<1|1, m+1, e);
        seg[idx] = merge(seg[idx<<1], seg[idx<<1|1]);
    }
    int query(int l, int r, int idx, int s, int e){
        if(r < s || e < l) return -1; // can be changed
        if(l <= s && e <= r) return seg[idx];
        int m = s+e >> 1;
        return merge(query(l, r, idx<<1, s, m), query(l, r, idx<<1|1, m+1, e));
    }
};

/////////////////////////////////////////////////////////



struct Disj{
    vInt disj;
    vInt depth;
    Disj(int N=1){
        disj = vInt(N+1);
        depth = vInt(N+1);
        for(int i=1; i<=N; i++)
            disj[i] = i;
    }
    int disjF(int u){
        while(u != disj[u])
            u = disj[u];
        return u;
    }
    void disjU(int u, int v){
        u = disjF(u);
        v = disjF(v);
        if(u == v) return;
        if(depth[u] < depth[v])
            swap(u, v);
        if(depth[u] == depth[v])
            depth[u]++;
        disj[v] = u; 
    }
};


void solve(){
    
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T;
    cin >> T;
    while(T--)
        solve();

    return 0;
}
