//
// Created by kibi on 2022/4/4.
//
#include <bits/stdc++.h>
using namespace std;
string txt, pat;
int dp[1000005][256];
int x;
int l1, l2;
int ans = -1;
int X[1000005];
int main(){
    cin >> txt >> pat;
    l1 = pat.length();
    l2 = txt.length();
    dp[0][pat[0]] = 1;
    for(int i = 1; i <= l1; i++){
        for(int j = 0; j < 256; j++){
            dp[i][j] = dp[x][j];
        }
        dp[i][pat[i]] = i+1;
        x = dp[x][pat[i]];
        X[i] = x;
        //        mxx = max(mxx,x);
    }
    int j = 0;
    for(int i = 0; i < l2; i++){
        j = dp[j][txt[i]];
        if(j == l1){
            ans = i - l1 + 2;
            printf("%d\n", ans);
        }
    }
    //    if(ans == -1){
    //        printf("-1\n");
    //    }
    //    printf("%d", mxx);
    for(int i = 0; i < l1; i++){
        printf("%d ", X[i]);
    }
}

// 23-11-10

/*
 *

 #include <bits/stdc++.h>
using namespace std;

int main(){
   auto read_str = [](vector<int> &x){
       auto judge = [](int c){return 'A' <= c && c <= 'Z';};
       int c = getchar();
       while(!judge(c)){
           c = getchar();
       }
       while(judge(c)){
           x.emplace_back(c);
           c = getchar();
       }
       x.shrink_to_fit();
   };

   vector<int> s1, s2, ss;
   read_str(s2), read_str(s1);

   for(auto &i : s1){
       ss.emplace_back(i);
   }
   ss.emplace_back('#');
   for(auto &i : s2){
       ss.emplace_back(i);
   }

   int pi[s1.size() + 1 + s2.size()];
   pi[0] = 0;
   for(int i = 1; i < ss.size(); i++){
       int j = pi[i - 1];
       while(j && ss[j] != ss[i]){
           j = pi[j - 1];
       }
       if(ss[i] == ss[j]){
           j++;
       }
       pi[i] = j;
   }


   for(int i = (int)s1.size() + 1; i < ss.size(); i++){
       if(pi[i] == s1.size()){
           printf("%d\n", (int)(i - 2 * s1.size() + 1));
       }
   }

   for(int i = 0; i < s1.size(); i++){
       printf("%d ", pi[i]);
   }
   printf("\n");
}

 *
 */