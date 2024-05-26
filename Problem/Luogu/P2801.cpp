//
// Created by kibi on 2022/6/12.
//
//O2
#include <bits/stdc++.h>
using namespace std;
int n,q,sq;
int a[1000005], st[1005], nd[1005], bel[1000005], mark[1005];
vector<int> v[1005];

bool cmp(int a, int b){
    return a<b;
}

void update(int b){
    for(int i = st[b]; i <= nd[b]; i++){
        v[b][i-st[b]] = a[i];
    }
    sort(v[b].begin(), v[b].end(), cmp);
}

int main(){
    scanf("%d %d", &n, &q);
    sq = sqrt(n);
    for(int i = 1; i <= sq; i++){
        st[i] = n/sq*(i-1)+1;
        nd[i] = n/sq*i;
    }
    nd[sq] = n;

    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }

    for(int i = 1; i <= sq; i++){
        for(int j = st[i]; j <= nd[i]; j++){
            bel[j] = i;
            v[i].push_back(a[j]);
        }
        sort(v[i].begin(),v[i].end(),cmp);
    }


    while(q--){
        char t;
        scanf("%s", &t);
        int l,r,k;
        scanf("%d %d %d", &l, &r, &k);
        if(t == 'M'){
            if(bel[l] == bel[r]){
                for(int i = l; i <= r; i++){
                    a[i] += k;
                }
                update(bel[l]);
            }else{
                for(int i = l; i <= nd[bel[l]]; i++){
                    a[i] += k;
                }
                update(bel[l]);
                for(int i = st[bel[r]]; i <= r; i++){
                    a[i] += k;
                }
                update(bel[r]);
                for(int i = bel[l] + 1; i < bel[r]; i++){
                    mark[i] += k;
                }
            }
        }else{
            int s = 0;
            if(bel[l] == bel[r]){
                for(int i = l; i <= r; i++){
                    s += (a[i]+mark[bel[i]] >= k);
                }
            }else{
                for(int i = l; i <= nd[bel[l]]; i++){
                    s += (a[i]+mark[bel[i]] >= k);
                }
                for(int i = st[bel[r]]; i <= r; i++){
                    s += (a[i]+mark[bel[i]] >= k);
                }
                for(int i = bel[l] + 1; i < bel[r]; i++){
                    s += v[i].end() - lower_bound(v[i].begin(), v[i].end(), k-mark[i]);
                }
            }
            printf("%d\n", s);
        }
    }

    return 0;
}

/*
 *
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read = [](initializer_list<int*> x){
        auto read = [](int &x){
            int s = 0, w = 1, c = getchar();
            while(c < '0' || '9' < c){
                if(c == '-'){
                    w = -1;
                }
                c = getchar();
            }
            while('0' <= c && c <= '9'){
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        };

        for(auto &i : x){
            read(*i);
        }
    };

    auto read_str = [](int &x){
        auto judge = [](int c){
            return c == 'M' || c == 'A';
        };
        int c = getchar();
        while(!judge(c)){
            c = getchar();
        }
        x = c;
    };

    int n, q;
    read({&n, &q});

    int val[n];
    for(auto &i : val){
        read({&i});
    }

    int b[n], siz = (int)sqrt(n);
    int tag[siz + 1];
    memcpy(b, val, sizeof b);
    memset(tag, 0, sizeof tag);
    for(int i = 0, cnt = 0; i < n; i += siz){
        sort(b + cnt * siz, b + cnt * siz + siz);
        cnt++;
    }
    if(siz * siz < n) {
        sort(b + siz * siz, b + n);
    }

    while(q--){
        int opt, l, r, v, ans, ll, rr;
        read_str(opt);
        read({&l, &r, &v});
        l--, r--;
        switch(opt){
            case 'M':
                ll = l, rr = min((l / siz + 1) * siz, r + 1) - 1;
                if((l + 1) % siz != 0){
                    for(int i = ll; i <= rr; i++){
                        val[i] += v;
                    }
                    for(int i = (l / siz) * siz; i < min((l / siz + 1) * siz, n); i++){
                        b[i] = val[i];
                    }
                    sort(b + (l / siz) * siz, b + min((l / siz + 1) * siz, n));
                    ll = rr + 1;
                }
                for(int i = ll; i + siz <= r + 1; i += siz){
                    tag[i / siz] += v;
                    ll += siz;
                }
                if(ll <= r){
                    for(int i = ll; i <= r; i++){
                        val[i] += v;
                    }
                    rr = min(n, ll + siz);
                    for(int i = ll; i < rr; i++){
                        b[i] = val[i];
                    }
                    sort(b + ll, b + rr);
                }
                break;
            case 'A':
                ll = l, rr = min((l / siz + 1) * siz, r + 1) - 1, ans = 0;
                if((l + 1) % siz != 0){
                    for(int i = ll; i <= rr; i++){
                        val[i] + tag[i / siz] >= v ? ans++ : ans;
                    }
                    ll = rr + 1;
                }
                for(int i = ll; i + siz <= r + 1; i += siz){
                    int lll = i, rrr = min(n - 1, i + siz - 1);
                    int res = rrr + 1;
                    while(lll <= rrr){
                        int mid = (lll + rrr) >> 1;
                        if(v <= b[mid] + tag[i / siz]){
                            res = mid;
                            rrr = mid - 1;
                        }else{
                            lll = mid + 1;
                        }
                    }
                    ans += min(n - 1, i + siz - 1) - res + 1;
                    ll += siz;
                }
                if(ll <= r){
                    for(int i = ll; i <= r; i++){
                        val[i] + tag[i / siz] >= v ? ans++ : ans;
                    }
                }
                printf("%d\n", ans);
                break;
            default:
                throw runtime_error("Error operation!");
        }
    }
}
 *
 * */