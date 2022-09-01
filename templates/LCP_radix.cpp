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
    int N, M;
    vInt ra, nra, sa, isa, lcp, idx, cnt;
    LCP(int N): N(N){
        ra = nra = vInt(2*N);
        sa = isa = lcp = idx = vInt(N);
        M = max(256, N) + 1;
        cnt = vInt(M);
    }
    void buildsa(string& S){
        for(int i=0; i<N; i++){
            sa[i] = i;
            ra[i] = S[i];
        }
        for(int d=1; d<N; d<<=1){
            auto cmp = [&](int a, int b)->bool{
                if(ra[a]!=ra[b]) return ra[a] < ra[b];
                return ra[a+d] < ra[b+d];
            };

            fill(all(cnt), 0);
            for(int i=0; i<N; i++) cnt[ra[d+i]]++;
            for(int i=1; i<M; i++) cnt[i] += cnt[i-1];
            for(int i=N-1; i>=0; i--) idx[--cnt[ra[i+d]]] = i;

            fill(all(cnt), 0);
            for(int i=0; i<N; i++) cnt[ra[i]]++;
            for(int i=1; i<M; i++) cnt[i] += cnt[i-1];
            for(int i=N-1; i>=0; i--) sa[--cnt[ra[idx[i]]]] = idx[i];

            nra[sa[0]] = 1;
            for(int i=1; i<N; i++)
                nra[sa[i]] = nra[sa[i-1]] + cmp(sa[i-1], sa[i]);

            swap(ra, nra);
            if(ra[N-1] == N) break;
        }
    }
};
