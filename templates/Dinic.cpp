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

struct Dinic{
    struct Edge{
        int v, c, rev;
        Edge(int v, int c, int rev)
            : v(v), c(c), rev(rev) {}
    };
    const int INF = 1e9;

    int s, t, N;
    LL maxF = 0;
    vector<vector<Edge>> adjs;
    vInt lv, lst;

    Dinic(int s, int t, int N): s(s), t(t),  N(N){
        adjs = vector<vector<Edge>>(N);
        lv = vInt(N);
        lst = vInt(N);
    }

    void addEdge(int u, int v, int c){
        adjs[u].emplace_back(v, c, adjs[v].size());
        adjs[v].emplace_back(u, 0, adjs[u].size()-1);
    }

    bool bfs(){
        fill(all(lv), -1);
        queue<int> q;
        q.push(s);
        lv[s] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto [v, c, r]: adjs[u]){
                if(lv[v] != -1 || c <= 0) continue;
                lv[v] = lv[u]+1;
                q.push(v);
            }
        }
        return lv[t] != -1;
    }

    int dfs(int u, int f){
        if(u == t) return f;
        for(int& i = lst[u]; i!=adjs[u].size(); i++){
            Edge& e = adjs[u][i];
            if(lv[e.v] != lv[u]+1 || e.c <= 0) continue;
            int avail = dfs(e.v, min(f, e.c));
            if(avail <= 0) continue;
            e.c -= avail;
            adjs[e.v][e.rev].c += avail;
            return avail;
        }
        return 0;
    }

    void flow(){
        maxF = 0;
        while(bfs()){
            fill(all(lst), 0);
            while(true){
                int f = dfs(s, INF);
                if(f == 0) break;
                maxF += f;
            }
        }
    }
};