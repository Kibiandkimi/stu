//
// Created by kibi on 23-10-3.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    class Tools{
    public:
        static void read(int &x){
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
        }
    };

    class List{
    public:
        int pos;
        List *pre, *nxt;

        List():pre(nullptr), nxt(nullptr){}
        List(int pos, List *pre, List *nxt):pos(pos), pre(pre), nxt(nxt){}
    };

    freopen("fastslow.in", "r", stdin);
    freopen("fastslow.out", "w", stdout);

    auto read = Tools::read;

    int n, m;
    read(n), read(m);

    List *head[n + 1], *end[n + 1];
    memset(head, 0, sizeof head);
    memset(end, 0, sizeof end);

    int raw_data[n], num = 0, cnt = 0;
    vector<int> vis;
    static map<int, int> mp, list_mp;
    for(int i = 0; i < n; i++){
        read(raw_data[i]);

        if(!list_mp[raw_data[i]]){
            list_mp[raw_data[i]] = ++cnt;
        }
        int id = list_mp[raw_data[i]];

        List *now = new List{i, end[id], nullptr};
        if(end[id]){
            end[id]->nxt = now;
        }
        end[id] = now;
        if(!head[id]){
            head[id] = now;
        }

        mp[raw_data[i]]++;
        if(mp[raw_data[i]] == 1000){
            num++;
            vis.emplace_back(raw_data[i]);
        }
    }

    map<int, int> mp_sum;
    int sum[num][n];
    for(int i = 0; i < num; i++){
        mp_sum[vis[i]] = i;
        sum[i][0] = (raw_data[0] == vis[i]);
        for(int j = 1; j < n; j++){
            sum[i][j] = sum[i][j - 1] + (raw_data[j] == vis[i]);
        }
    }

    map<pair<int, int>, long long> res;

    int tem[2 * 1000 + 5];
    while(m--){
        int x, y;
        read(x), read(y);

        if(res[{x, y}]){
            printf("%lld\n", res[{x, y}]);
            continue;
        }

        int mp_x = mp[x], mp_y = mp[y], id_x = list_mp[x], id_y = list_mp[y];
        long long ans = 0;

        if(x == y) {
            int sum_x = 0;
            if (mp_x >= 1000) {
                sum_x = sum[mp_sum[x]][n - 1];
            }else{
                for(auto i = head[id_x]; i; i = i->nxt){
                    sum_x++;
                }
            }
            ans = (sum_x / 2) * (sum_x - (sum_x / 2));
        }else if(mp_x >= 1000 && mp_x > mp_y){
            int sum_id = mp_sum[x];
            int cnt_of_y = 0;
            for(auto i = end[id_y]; i; i = i->pre){
                cnt_of_y++;
                if(!i->pos){
                    break;
                }
                ans = max(ans, (long long)cnt * sum[sum_id][i->pos - 1]);
            }
        }else if(mp_y >= 1000){
            int sum_id = mp_sum[y];
            int cnt_of_x = 0;
            for(auto i = head[id_x]; i; i = i->nxt){
                cnt_of_x++;
                if(i->pos == n - 1){
                    break;
                }
                ans = max(ans, (long long)cnt * (sum[sum_id][n - 1] - sum[sum_id][i->pos]));
            }
        }else{
            int cnt_of_tem = 0, sum_x = 0, sum_y = 0;
            for(auto i = head[id_x], j = head[id_y]; i || j;){
                if(j == nullptr || i != nullptr && i->pos < j->pos){
                    tem[cnt_of_tem++] = x;
                    sum_x++;
                    i = i->nxt;
                }else{
                    tem[cnt_of_tem++] = y;
                    sum_y++;
                    j = j->nxt;
                }
            }

            int cnt_of_x = 0, cnt_of_y = sum_y;
            ans = 0;
            for(int i = 0; i < cnt_of_tem; i++){
                if(tem[i] == x){
                    cnt_of_x++;
                    ans = max(ans, (long long)cnt_of_x * cnt_of_y);
                }else{
                    cnt_of_y--;
                }
            }
        }

        res[{x, y}] = ans;

        printf("%lld\n", ans);
    }

    fclose(stdin);
    fclose(stdout);

}