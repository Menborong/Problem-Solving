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

struct Po{
    int x, y, idx;
    bool operator<(Po& b){
        if(x != b.x) return x < b.x;
        else if (y != b.y) return y < b.y;
        return idx < b.idx;
    }
};

struct ConvexHull{
    bool is_lin;
    vector<Po> ps;
    ConvexHull(vector<Po>& ps): ps(ps){
        is_lin = false;
    }
    LL ccw(Po& p1, Po& p2, Po& p3, Po& p4){
        LL ans = 0;
        ans += (LL)(p2.x-p1.x)*(p4.y-p3.y);
        ans -= (LL)(p2.y-p1.y)*(p4.x-p3.x);
        return ans;
    }
    LL ccw(Po& p1, Po& p2, Po& p3){
        LL ans = 0;
        ans += (LL)(p2.x-p1.x)*(p3.y-p2.y);
        ans -= (LL)(p2.y-p1.y)*(p3.x-p2.x);
        return ans;
    }
    LL sqDist(Po& p1, Po& p2){
        LL ans = 0;
        ans += (LL)(p2.x-p1.x)*(p2.x-p1.x);
        ans += (LL)(p2.y-p1.y)*(p2.y-p1.y);
        return ans;
    }

    void run(bool ok_lin = false){
        auto minE = min_element(all(ps));
        swap(ps.front(), *minE);
        
        sort(1+all(ps), [this](Po& a, Po& b)->bool{
            LL rot = ccw(ps[0], a, b);
            if(rot) return rot > 0;
            else return sqDist(ps[0], a) > sqDist(ps[0], b);
        });
        ps.push_back(ps[0]);

        is_lin = true;
        for(int i=0; i<ps.size()-3; i++){
            if(ccw(ps[i], ps[i+1], ps[i+2])){
                is_lin = false;
                break;
            }
        }

        if(is_lin){
            if(!ok_lin) ps.resize(2);
            return;
        }

        if(ok_lin){
            int s = 2, e = 2;
            while(e < ps.size()){
                if(ccw(ps[0], ps[1], ps[e]) ==  0) e++;
                else break;
            }
            reverse(ps.begin()+1, ps.begin()+e);
        }

        int l = 1;
        for(int r=2; r<ps.size(); r++){
            while(ccw(ps[l-1], ps[l], ps[r]) < 0)
                l--;
            if(!ok_lin && ccw(ps[l-1], ps[l], ps[r]) == 0){
                if(sqDist(ps[l-1], ps[r]) > sqDist(ps[l-1], ps[l]))
                    ps[l] = ps[r];
                continue;
            }
            ps[++l] = ps[r];
        }

        ps.resize(l);
    }

    pii getLongest(){
        int a = 0; int b = 1;
        int a_opt = a;
        int b_opt = b;
        int numP = ps.size();

        while(true){
            int an = (a+1)%numP;
            int bn = (b+1)%numP;
            if(ccw(ps[a], ps[an], ps[b], ps[bn]) > 0)
                b = bn;
            else{
                a = an;
                if(a == 0) break;
            }
            if(sqDist(ps[a_opt], ps[b_opt]) < sqDist(ps[a], ps[b])){
                a_opt = a;
                b_opt = b;
            }
        }
        return {a_opt, b_opt};
    }
};

void solve(){
    int N;
    cin >> N;
    vector<Po> PS(N);
    for(int i=0; i<N; i++){
        int x, y;
        cin >> x >> y;
        PS[i] = {x, y, i};
    }
    ConvexHull ch(PS);
    ch.run();
    cout << ch.ps.size() << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    solve();
    
    return 0;
}
