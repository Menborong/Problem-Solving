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

struct Aho{
    struct Node{
        int fail, ch[26];
        bool ed;
        Node(){
            fail = 0;
            ed = false;
            for(int i=0; i<26; i++) ch[i] = 0;
        }
    };
    vector<Node> nds;
    int getNew(){
        int idx = nds.size();
        nds.push_back(Node());
        return idx;
    }
    Aho(){
        getNew();
    }
    void add(int tar, int idx, string& S){
        if(idx == S.size()){
            nds[tar].ed = true;
            return;
        }
        int nv = S[idx] - 'a';
        if(!nds[tar].ch[nv]) nds[tar].ch[nv] = getNew();
        add(nds[tar].ch[nv], idx+1, S);
    }
    void makeF(){
        queue<int> q;
        q.push(0);
        while(!q.empty()){
            int tar = q.front();
            q.pop();
            for(int i=0; i<26; i++){
                int nxt = nds[tar].ch[i];
                if(!nxt) continue;
                int f = nds[tar].fail;
                while(f && !nds[f].ch[i])
                    f = nds[f].fail;
                if(tar && nds[f].ch[i]) f = nds[f].ch[i];
                nds[nxt].fail = f;
                nds[nxt].ed |= nds[f].ed;
                q.push(nxt);
            }
        }
    }
    void search(string& S, vInt& ans){
        int tar = 0;
        for(int i=0; i<S.size(); i++){
            int nv = S[i] - 'a';
            while(tar && !nds[tar].ch[nv])
                tar = nds[tar].fail;
            if(nds[tar].ch[nv]) tar = nds[tar].ch[nv];
            if(nds[tar].ed) ans.push_back(i);
        }
    }
};

void solve(){
    int N;
    cin >> N;

    Aho aho;
    for(int i=0; i<N; i++){
        string S;
        cin >> S;
        aho.add(0, 0, S);
    }
    aho.makeF();

    int Q;
    cin >> Q;
    for(int i=0; i<Q; i++){
        string S;
        cin >> S;
        vInt ans;
        aho.search(S, ans);
        if(ans.size()) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    solve();
    
    return 0;
}
