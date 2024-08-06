//
// Created by kibi on 24-7-26.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using T = array<int, 9>;

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

    auto into_array = [](int a){
        T res;
        for(auto &i : res){
            i = a % 10;
            a /= 10;
        }
        reverse(res.begin(), res.end());
        return res;
    };

    auto into_num = [](T a){
        int res = 0;
        for(auto &i : a){
            res = res * 10 + i;
        }
        return res;
    };

    auto transfer = [](T u_arr)->tuple<T, T>{
        T u1_arr = {u_arr[3], u_arr[0], u_arr[1],
                    u_arr[6], u_arr[4], u_arr[2],
                    u_arr[7], u_arr[8], u_arr[5]},
          u2_arr = {u_arr[0], u_arr[1], u_arr[2],
                    u_arr[5], u_arr[3], u_arr[4],
                    u_arr[6], u_arr[7], u_arr[8]};
        return {u1_arr, u2_arr};
    };

    T a;
    for(auto &i : a){
        read(i);
    }

    auto st = into_num(a);

    map<int, int> mpu/*, mpv*/;

    auto get_ans = [&mpu/*, &mpv*/, into_array](){
        vector<int> ans;

        int pre = 12345678;

        ans.emplace_back(pre);
        while(mpu[pre] != -1){
            ans.emplace_back(mpu[pre]);
            pre = mpu[pre];
        }

        reverse(ans.begin(), ans.end());

        //        ans.emplace_back(suc);
        //        while(mpv[suc] != -1){
        //            ans.emplace_back(mpv[suc]);
        //            suc = mpv[suc];
        //        }

        printf("%d\n", (int)ans.size() - 1);

        for(auto &i : ans){
            auto tem = into_array(i);
            printf("%d %d %d\n%d %d %d\n%d %d %d\n\n", tem[0], tem[1], tem[2], tem[3], tem[4], tem[5], tem[6], tem[7], tem[8]);
        }
    };

    mpu[st] = -1;
    //    mpv[12345678] = -1;

    queue<int> q1/*, q2*/;

    q1.emplace(st)/*, q2.emplace(12345678)*/;

    while(!q1.empty()/* && !q2.empty()*/){
        auto u = q1.front()/*, v = q2.front()*/;
        q1.pop()/*, q2.pop()*/;

        auto u_arr = into_array(u);
        auto [u1_arr, u2_arr] = transfer(u_arr);
        auto u1_num = into_num(u1_arr), u2_num = into_num(u2_arr);

        if(mpu[u1_num] == 0){
            mpu[u1_num] = u;
            q1.emplace(u1_num);
            if(u1_num == 12345678){
                get_ans();
                return 0;
            }
        }

        if(mpu[u2_num] == 0){
            mpu[u2_num] = u;
            q1.emplace(u2_num);
            if(u2_num == 12345678){
                get_ans();
                return 0;
            }
        }

        /*auto v_arr = into_array(v);
        auto [v1_arr, v2_arr] = transfer(v_arr);
        auto v1_num = into_num(v1_arr), v2_num = into_num(v2_arr);

        if(mpv[v1_num] == 0){
            if(mpu.find(v1_num) != mpu.end()){
                get_ans(v1_num, v);
                return 0;
            }else {
                mpv[v1_num] = v;
                q2.emplace(v1_num);
            }
        }

        if(mpv[v2_num] == 0){
            if(mpu.find(v2_num) != mpu.end()){
                get_ans(v2_num, v);
                return 0;
            }else{
                mpv[v2_num] = v;
                q2.emplace(v2_num);
            }
        }*/
    }

}