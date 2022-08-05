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

// 추가적인 수정이 필요할지 모릅니다...
struct Hopcroft{
    int N, M;
    matInt adjs;
    vInt CHK, BTA, LVL, LST;

    const int INF = 1e9;

    Hopcroft(int N, int M): N(N), M(M){
        adjs = matInt(N+1);
        CHK = vInt(N+1);
        BTA = vInt(M+1);
        LVL = vInt(N+1);
        LST = vInt(N+1);
    }

    void addEdge(int u, int v){
        adjs[u].push_back(v);
    }

    void bfs(){
        queue<int> q;
        for(int i=1; i<=N; i++){
            if(CHK[i]) LVL[i] = INF;
            else{
                LVL[i] = 0;
                q.push(i);
            }
        }
        while(!q.empty()){
            int tar = q.front();
            q.pop();
            for(int b: adjs[tar]){
                int nxt = BTA[b];
                if(!nxt || LVL[nxt] != INF) continue;
                LVL[nxt] = LVL[tar]+1;
                q.push(nxt);
            }
        }
    }

    bool dfs(int tar){
        for(int& i=LST[tar]; i<adjs[tar].size(); i++){
            int b = adjs[tar][i];
            if(!BTA[b] || LVL[BTA[b]] == LVL[tar]+1 && dfs(BTA[b])){
                CHK[tar] = true;
                BTA[b] = tar;
                return true; 
            }
        }
        return false;
    }

    int numM;
    int match(){
        numM = 0;
        while(true){
            bfs();
            fill(all(LST), 0);
            int tmp = 0;
            for(int i=1; i<=N; i++){
                if(!CHK[i] && dfs(i)) tmp++;
            }
            if(!tmp) break;
            numM += tmp;
        }
        return numM;
    }

    vBool VSA, VSB;
    void mvsDfs(int tar){
        VSA[tar] = true;
        for(int b: adjs[tar]){
            if(BTA[b] && !VSB[b] && !VSA[BTA[b]]){
                VSB[b] = true;
                mvsDfs(BTA[b]);
            }
        }
    }

    void minVertexSet(){
        VSA = vBool(N+1);
        VSB = vBool(M+1);
        for(int i=1; i<=N; i++){
            if(!CHK[i]) mvsDfs(i);
        }
        for(int i=1; i<=N; i++)
            VSA[i] = !VSA[i];
    }

};