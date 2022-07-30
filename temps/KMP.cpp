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

struct KMP{
    string S, T;
    int N, M;
    vInt F;
    KMP(string& S, string& T): S(S), T(T){
        N = S.size();
        M = T.size();
        F = vInt(M+1);
    }
    void calF(){
        for(int i=2; i<=M; i++){
            int f = i-1;
            while(f){
                f = F[f];
                if(T[i-1] == T[f]){
                    F[i] = f+1;
                    break;
                }
            };
        }
    }
    vInt getIdx(){
        vInt ans;
        int i = 0, j = 0;
        while(i < N){
            while(j<M && S[i+j] == T[j])
                j++;
            if(j == M){
                ans.push_back(i);
            } 
            int f = F[j];
            i = max(i+j-f, i+1);
            j = f;
        }
        return ans;
    }
};

void solve(){
    string S, T;
    getline(cin ,S);
    getline(cin ,T);

    KMP kmp(S, T);
    kmp.calF();

    vInt ans = kmp.getIdx();
    cout << ans.size() << '\n';
    for(int i: ans){
        cout << i+1 << ' ';
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    solve();
    
    return 0;
}
