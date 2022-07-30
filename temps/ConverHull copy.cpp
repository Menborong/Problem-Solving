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

LL ccw(Po& a, Po& b, Po& c){
    return (LL)(b.x-a.x)*(c.y-b.y) - (LL)(b.y-a.y)*(c.x-b.x);
}

LL ccw(Po& a, Po& b, Po& c, Po& d){
    return (LL)(b.x-a.x)*(d.y-c.y) - (LL)(b.y-a.y)*(d.x-c.x);
}

LL sqDist(Po& a, Po& b){
    return (LL)(b.x-a.x)*(b.x-a.x) + (LL)(b.y-a.y)*(b.y-a.y);
}

struct ConvexHull{
    vector<Po> ps;
    vector<Po> hull;
    ConvexHull(vector<Po>& ps): ps(ps){}
    
    void run(bool on_line = false){
        if(ps.size() <= 1){
            hull = ps;
            return;
        }
        swap(ps.front(), *min_element(all(ps)));

        sort(1+all(ps), [&](Po& a, Po& b)->bool{
            LL rot = ccw(ps[0], a, b);
            if(rot) return rot > 0;
            return sqDist(ps[0], a) < sqDist(ps[0], b);
        });
        
        if(on_line){
            int e;
            for(e = ps.size()-2; e >= 1; e--){
                if(ccw(ps[0], ps[e], ps[e+1])) break;
            }
            if(e) reverse(1+e+all(ps));
        }
        
        for(auto p: ps){
            while(hull.size() >= 2){
                LL tmp = ccw(*(hull.end()-2), *(hull.end()-1), p);
                if(tmp < 0 || (!on_line && tmp == 0)) hull.pop_back();
                else break;
            }
            hull.push_back(p);
        }
        
    }

    pii getLongest(){
        int a = 0; int b = 1;
        int a_opt = a;
        int b_opt = b;
        int numP = hull.size();

        while(true){
            int an = (a+1)%numP;
            int bn = (b+1)%numP;
            if(ccw(hull[a], hull[an], hull[b], hull[bn]) > 0)
                b = bn;
            else{
                a = an;
                if(a == 0) break;
            }
            if(sqDist(hull[a_opt], hull[b_opt]) < sqDist(hull[a], hull[b])){
                a_opt = a;
                b_opt = b;
            }
        }
        return {a_opt, b_opt};
    }

    bool is_in(Po& p){
        if(hull.size() <= 2) return false;
        for(int i=0; i<hull.size(); i++){
            LL res = ccw(hull[i], hull[(i+1)%hull.size()], p);
            if(res <= 0) return false; 
        }
        return true;
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
