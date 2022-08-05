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

struct MCMF{
    struct Edge{
        int v, c, d, rev;
        Edge(int v, int c, int d, int rev)
            : v(v), c(c), d(d), rev(rev) {}
    };

    const int INF = 1e9;
    int s, t, N;
    vector<vector<Edge>> adjs;
    vInt dist;
    vPii prev;
    vBool chk;

    LL minC, maxF;

    MCMF(int s, int t, int N): s(s), t(t), N(N){
        adjs = vector<vector<Edge>>(N);
        dist = vInt(N, INF);
        prev = vPii(N);
        chk = vBool(N);
    }

    void addEdge(int u, int v, int c, int d){
        adjs[u].emplace_back(v, c, d, adjs[v].size());
        adjs[v].emplace_back(u, 0, -d, adjs[u].size()-1);
    }

    bool SPFA(){
        fill(all(dist), INF);
        fill(all(prev), pii(-1, -1));
        fill(all(chk), false);
        
        queue<int> q;
        q.push(s);
        chk[s] = true;
        dist[s] = 0;

        while(!q.empty()){
            int tar = q.front();
            q.pop();
            chk[tar] = false;
            for(int i=0; i<adjs[tar].size(); i++){
                Edge& e = adjs[tar][i];
                if(e.c <= 0) continue;
                if(dist[e.v] <= dist[tar] + e.d) continue;
                dist[e.v] = dist[tar] + e.d;
                prev[e.v] = {tar, i};
                if(!chk[e.v]){
                    q.push(e.v);
                    chk[e.v] = true;
                }
            }
        }
        
        if(prev[t].first == -1) return false;
        return true;
    }

    void flow(){
        minC = 0;
        maxF = 0;
        while(SPFA()){
            int f = INF;
            for(int i=t; i!=s; i=prev[i].first){
                f = min(f, adjs[prev[i].first][prev[i].second].c);
            }
            maxF += f;
            for(int i=t; i!=s; i=prev[i].first){
                Edge& e = adjs[prev[i].first][prev[i].second];
                Edge& re = adjs[i][e.rev];
                minC += (LL)e.d * f;
                e.c -= f;
                re.c += f;
            }
        }
    }
};