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
#define ff first
#define ss second

struct CHT{
    deque<pLL> lines;
    LL f(pLL l, LL x){
        return l.ff * x + l.ss;
    }
    double meet(pLL a, pLL b){
        return (double)(b.ss - a.ss) / (a.ff - b.ff);
    }
    void insert(pLL l){
        while(lines.size() >= 2){
            double xtop = meet(lines[lines.size() - 2], lines[lines.size() - 1]);
            double xnew = meet(lines[lines.size() - 1], l);
            if(xtop <= xnew) break;
            lines.pop_back();
        }
        lines.push_back(l);
    }
    LL query(LL x){
        int s = 0;
        int e = lines.size() - 1;
        while(s+1 < e){
            int m = (s+e)/2;
            if(meet(lines[m], lines[m+1]) <= x) s = m;
            else e = m;
        }
        if(meet(lines[s], lines[e]) <= x) return f(lines[e], x);
        return f(lines[s], x);
    }
    LL query_lin(LL x){
        while(lines.size() >= 2){
            double xfront = meet(lines[0], lines[1]);
            if(x < xfront) break;
            lines.pop_front();
        }
        return f(lines[0], x);
    }
};

struct Lichao{
    const LL INF = 1e18;
    LL f(pLL l, LL x){
        return l.ff * x + l.ss;
    }
    struct Node{
        int l, r;
        pLL line;
    };
    vector<Node> nodes;
    int newNode(){
        int idx = nodes.size();
        nodes.push_back({-1, -1, {0, INF}});
        return idx;
    }
    void insert(pLL line, int idx, int s, int e){
        pLL low = line;
        pLL high = nodes[idx].line;
        if(f(low, s) > f(high, s)) swap(low, high);
        if(f(low, e) <= f(high, e)){
            nodes[idx].line = low;
            return;
        }
        int m = (s+e)/2;
        if(f(low, m) > f(high, m)){
            nodes[idx].line = high;
            if(nodes[idx].l == -1) nodes[idx].l = newNode();
            insert(low, nodes[idx].l, s, m);
        }
        else{
            nodes[idx].line = low;
            if(nodes[idx].r == -1) nodes[idx].r = newNode();
            insert(high, nodes[idx].r , m+1, e);
        }
    }
    LL query(LL x, int idx, int s, int e){
        if(idx == -1) return INF;
        LL fx = f(nodes[idx].line, x);
        int m = (s+e)/2;
        if(x <= m) return min(fx, query(x, nodes[idx].l, s, m));
        else return min(fx, query(x, nodes[idx].r, m+1, e));
    }
    Lichao(){
        newNode();
    }
};

// example: BOJ 4008 (https://www.acmicpc.net/problem/4008)
void solve(){
    int N;
    cin >> N;
    LL a, b, c;
    cin >> a >> b >> c;
    vLL A(N+1);
    for(int i=1; i<=N; i++){
        cin >> A[i];
    }
    for(int i=1; i<=N; i++) A[i] += A[i-1];

    // a A[N]^2 + b A[N] + c - dp[N] = min_{i<N} (2a*A[i]*A[N] - a*A[i]^2 + b*A[i] - dp[i])

    Lichao cht;
    cht.insert({0, 0}, 0, 0, 1e9);
    LL ndp;
    for(int i=1; i<=N; i++){
        LL v = cht.query(A[i], 0, 0, 1e9);
        ndp = a*A[i]*A[i] + b*A[i] + c - v;
        cht.insert({a*A[i]*2, -a*A[i]*A[i] + b*A[i] - ndp}, 0, 0, 1e9);
    }
    cout << ndp << '\n';

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    solve();
    
    return 0;
}
