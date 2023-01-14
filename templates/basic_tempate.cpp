#include <bits/stdc++.h>

using namespace std;
using vInt = vector<int>;
using LL = long long;
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
#define cyes cout << "Yes" << '\n'
#define cno cout << "No" << '\n'
#define for0(i, n) for(int (i)=0; (i)<(n); (i)++)
#define for1(i, n) for(int (i)=1; (i)<=(n); (i)++) 
#define newInt(n) int n; cin >> n
#define newLL(n) LL n; cin >> n
#define newVInt(A, f, t) vInt A(t); for(int i=f; i<t; i++) cin >> A[i]
#define newVLL(A, f, t) vLL A(t); for(int i=f; i<t; i++) cin >> A[i]
#define endl '\n'
#define ff first
#define ss second

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

void solve(){
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    solve();

    return 0;
}
