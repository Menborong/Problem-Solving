#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()

struct SCC{
    vector<vector<int>> adjs;
    int N, id, sid;
    vector<int> ids, sids;
    stack<int> s;
    SCC() {}
    SCC(int N): N(N){
        adjs = vector<vector<int>>(N+1);
        sids = vector<int>(N+1);
        ids = vector<int>(N+1);
        id = sid = 0;
    }
    void addEdge(int u, int v){
        adjs[u].push_back(v);
    }
    int dfs(int tar){
        int ret = ids[tar] = ++id;
        s.push(tar);
        for(int nxt: adjs[tar]){
            if(!ids[nxt]) ret = min(ret, dfs(nxt));
            else if(!sids[nxt]) ret = min(ret, ids[nxt]);
        }
        if(ret == ids[tar]){
            sid++;
            while(true){
                int now = s.top();
                s.pop();
                sids[now] = sid;
                if(now == tar) break;
            }
        }
        return ret;
    }
    void run(){
        for(int i=1; i<=N; i++){
            if(ids[i]) continue;
            dfs(i);
        }
    }
};

struct SAT{
    SCC scc;
    vector<int> ans;
    int N;
    SAT() {}
    SAT(int N): N(N){
        scc = SCC(2*N);
        ans = vector<int>(N+1);
    }
    int NOT(int v){
        return 2*N+1-v;
    }
    // not u -> ~u
    void addEdge(int u, int v){
        if(u >> 31) u = NOT(~u);
        if(v >> 31) v = NOT(~v);
        scc.addEdge(NOT(u), v);
        scc.addEdge(NOT(v), u);
    }
    bool run(){
        scc.run();
        for(int i=1; i<=N; i++){
            if(scc.sids[i] == scc.sids[NOT(i)]) return 0;
            if(scc.sids[i] > scc.sids[NOT(i)]) ans[i] = 0;
            else ans[i] = 1;
        }
        return 1;
    }
};

void solve(){
    int N, M;
    cin >> N >> M;
    
    SAT sat(N);
    for(int i=1; i<=M; i++){
        int u, v;
        cin >> u >> v;
        if(u < 0) u--;
        if(v < 0) v--;
        sat.addEdge(u, v);
    }

    int res = sat.run();
    cout << res << '\n';
    if(!res) return;
    for(int i=1; i<=N; i++)
        cout << sat.ans[i] << ' ';
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    solve();
    
    return 0;
}
