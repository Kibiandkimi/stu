//
// Created by Lenovo on 24-4-14.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    //    freopen("temp.in", "r", stdin);

    vector<int> data;
    int c = getchar();
    while(c == 'G' || c == 'R'){
        data.emplace_back(c == 'G' ? 1 : -1);
        c = getchar();
    }

    map<int, int> mp;
    int sum[data.size()];
    sum[0] = data[0];
    mp[0] = -1;
    mp[sum[0]] = 0;
    for(int i = 1; i < data.size(); i++){
        sum[i] = sum[i - 1] + data[i];
        if(mp.find(sum[i]) == mp.end()){
            mp[sum[i]] = i;
        }
    }

    int ans = 0;
    for(int i = (int)data.size() - 1; i >= 0; i--){
        ans = max(ans, i - mp[sum[i]]);
    }
    printf("%d\n", ans);

    //    fclose(stdin);
}