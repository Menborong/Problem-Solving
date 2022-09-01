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

struct LCP{
    string S;
    int N;
    vInt sa, isa, ra, nra, lcp;
    LCP(string& S): S(S){
        N = S.size();
        sa = isa = lcp = vInt(N);
        ra = nra = vInt(N*2);
    }
    void buildsa(){
        for(int i=0; i<N; i++){
            sa[i] = i;
            ra[i] = S[i];
        }
        for(int i=1; i<N; i*=2){
            auto cmp = [&](int& a, int& b)->bool{
                if(ra[a] != ra[b]) return ra[a] < ra[b];
                return ra[i+a] < ra[i+b];
            };
            sort(all(sa), cmp);
            nra[sa[0]] = 1;
            for(int j=1; j<N; j++)
                nra[sa[j]] = nra[sa[j-1]] + cmp(sa[j-1], sa[j]);
            swap(ra, nra);
            if(ra[N-1] == N) break;
        }
    }
    void buildlcp(){
        buildsa();
        for(int i=0; i<N; i++)
            isa[sa[i]] = i;
        int k = 0;
        for(int i=0; i<N; i++){
            if(isa[i]){
                int j = sa[isa[i]-1];
                while(i+k < N && j+k < N && S[i+k]==S[j+k])
                    k++;
                lcp[isa[i]] = (k ? k-- : 0);
            }
        }
    }
};
