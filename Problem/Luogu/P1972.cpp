//
// Created by kibi on 22-8-12.
//
#include <bits/stdc++.h>
using namespace std;
int n, a[1000005], m;
int lo[1000005];
int res[1000005];
int tr[4000005];
vector<pair<pair<int, int>, int> > q;

bool cmp(pair<pair<int, int>, int> ta,  pair<pair<int, int>, int> b){
    return ta.first.second < b.first.second;
}

void insert(int x, int v){
    for(int i = x; i <= n; i+=(i&-i)){
        tr[i] += v;
    }
}

int query(int x){
    int ans = 0;
    if(x == 0){
        return 0;
    }
    for(int i = x; i > 0; i-=(i&-i)){
        ans += tr[i];
    }
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++){
        int l, r;
        scanf("%d %d", &l, &r);
        q.push_back({{l,r}, i});
    }
    sort(q.begin(), q.end(), cmp);
    int sq = q.size(), last = 0;
    for(int i = 0; i < sq; i++){
        if(last != q[i].first.second){
            for(int j = last+1; j <= q[i].first.second; j++){
                if(lo[a[j]]){
                    insert(lo[a[j]], -1);
                }
                insert(j, 1);
                lo[a[j]] = j;
            }
        }
        last = q[i].first.second;
//        printf("%d\n", query(q[i].second) - query(q[i].first-1));
        res[q[i].second] = query(q[i].first.second) - query(q[i].first.first-1);
    }
    for(int i = 1; i <= m; i++){
        printf("%d\n", res[i]);
    }
}

// 2023/8/3

/*

#include <bits/stdc++.h>
using namespace std;

const int N = 1000000, M = 1000000;

void read(int&);

int main(){

    class TreeArray{
        int data[4 * N + 5]{}, n;
    public:

        explicit TreeArray(int n):n(n){};

        void insert(int x, int v){
            while(x <= n){
                data[x] += v;
                x += (x & -x);
            }
        }

        int query(int x){
            int ans = 0;
            while(x){
                ans += data[x];
                x -= (x&-x);
            }
            return ans;
        }
    };

    int n;
    read(n);
    static int a[N + 5];
    for(int i = 1; i <= n; i++){
        read(a[i]);
    }

    class Question{
    public:
        int id, l, r, ans;
        static bool cmp_with_r(const Question &a, const Question &b){
            return a.r < b.r;
        }
        static bool cmp_with_id(const Question &a, const Question &b){
            return  a.id < b.id;
        }
    };

    int m;
    read(m);

    static Question q[M + 5];

    for(int i = 1; i <= m; i++){
        q[i].id = i;
        read(q[i].l), read(q[i].r);
    }

    sort(q + 1, q + 1 + m, Question::cmp_with_r);

    static int last[N + 5], ans[M + 5];
    static TreeArray tree(n);

    for(int i = 1, j = 1; i <= n; i++){
        if(!last[a[i]]){
            tree.insert(i, 1);
            last[a[i]] = i;
        }else{
            tree.insert(last[a[i]], -1);
            tree.insert(i, 1);
            last[a[i]] = i;
        }
        while(q[j].r == i){
            q[j].ans = tree.query(q[j].r) - tree.query(q[j].l - 1);
//          printf("%d\n", );
            j++;
        }
    }

    sort(q + 1, q + 1 + m, Question::cmp_with_id);

    for(int i = 1; i <= m; i++){
        printf("%d\n", q[i].ans);
    }
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(c < '0' || '9' < c){
        if (c == '-'){
            w = -1;
        }
        c = getchar();
    }
    while('0' <= c && c <= '9'){
        s = s * 10 + c - '0';
        c = getchar();
    }
    x = s * w;
}

*/