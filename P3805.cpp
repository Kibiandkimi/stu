//
// Created by kibi on 2022/7/8.
//
#include <bits/stdc++.h>
using namespace std;
char c[11000005];
int l, r, n;
int d1[11000005], d2[11000005];
int ans;
int main(){
    scanf("%s", c+1);
    for(int i = 1; c[i]!=0; i++){
        n++;
    }
    //    n = c.size();
    l = 0, r = -1;
    for(int i = 1; c[i]!=0; i++){
        if(i > r){
            int j;
            for(j = 0; (c[i-j]==c[i+j])&&(c[i+j]!=0); j++){
            }
            j--;
            if(j>=0) {
                l = i - j;
                r = i + j;
            }
            d1[i] = j+1;
        }else{
            if(d1[l+r-i]+i>r) {
                int j;
                for (j = 0; (c[r + j]==c[i - (r - i) - j]) && (c[r+j]!=0); j++) {
                }
                j--;
                d1[i] = r+j-i+1;
                if (j > 0) {
                    l = i - (r - i) - j;
                    r += j;
                }
                //                d1[i] = r - i + 1;
            }else{
                d1[i] = d1[l+r-i];
                if(i + d1[i] > n){
                    d1[i] = n-i;
                }
            }
        }
        ans = max(ans, d1[i]*2-1);
    }
    l = 0;
    r = -1;
    for(int i = 1; c[i+1]!=0; i++){
        if(i >= r){
            int j;
            for(j = 0; (c[i-j+1] == c[i+j]) && (c[i+j]!=0); j++){
            }
            j--;
            if(j > 0){
                r = i+j;
                l = i-j+1;
            }
            d2[i] = j;
        }else{
            if(d2[l+r-i-1]+i+1 > r){
                int j;
                for(j = 0; (c[r+j]==c[i-(r-i)+1-j]) && (c[r+j]!=0); j++){
                }
                j--;
                d2[i] = r+j-i;
                if(j > 0){
                    l = i-(r-i)+1-j;
                    r = r+j;
                }
                //                d2[i] = r-i;
            }else{
                d2[i] = d2[l+r-i-1];
                if(i + d2[i] > n){
                    d2[i] = n-i;
                }
            }
        }
        ans = max(ans, d2[i]*2);
    }
    printf("%d", ans);
}

namespace Second{
    using namespace std;

    int readStr(char *c);

    int main(){
        static char raw[24000005], str[46000005];
        static int len = readStr(raw+1), d[46000005], ans = 0;
        str[0] = '#';
        for(int i = 1; i <= len; i++){
            str[i*2] = raw[i];
            str[i*2 - 1] = '*';
        }
        str[len*2+1] = '*';
        len = len*2+1;
        for(int i = 1; i <= len; i++){
            static int mid = 0, r = 0;
            if(i <= r){
                d[i] = min(d[(mid<<1)-i], r-i+1);
            }
            while(str[i - d[i]] == str[i + d[i]] && i + d[i] <= len){
                ++d[i];
            }
            if(d[i] + i > r){
                r = d[i] + i - 1, mid = i;
            }
            if(d[i] > ans){
                ans = d[i];
            }
        }
        printf("%d", ans-1);
    }

    int readStr(char *c){
        int tem = getchar();
        while(tem < 'a' || 'z' < tem){
            tem =getchar();
        }
        static int i = 0;
        while('a' <= tem && tem <= 'z'){
            c[i++] = (char)tem;
            tem = getchar();
        }
        return i;
    }
}

// 23-11-11

/*
#include <bits/stdc++.h>
using namespace std;

int main(){
    auto read_str = [](vector<char> &x){
        auto judge = [](int c){
            return 'a' <= c && c <= 'z';
        };
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

    vector<char> raw, s;
    read_str(raw);

    s.reserve(2 * raw.size() + 1);

    s.emplace_back('#');
    for(auto &i : raw){
        s.emplace_back(i);
        s.emplace_back('#');
    }

    int d[s.size()], ans = 0;
    memset(d, 0, sizeof d);
    for(int i = 0, l = 0, r = -1; i < s.size(); i++){
        if(i > r){
            for(int j = 0; j <= min((int)s.size() - i - 1, i); j++){
                if(s[i - j] != s[i + j]){
                    break;
                }
                d[i] = j;
            }
        }else{
            int i_ = l + (r - i);
            if(i_ - d[i_] > l){
                d[i] = d[i_];
            }else{
                for(int j = r - i; j <= min((int)s.size() - i - 1, i); j++){
                    if(s[i - j] != s[i + j]){
                        break;
                    }
                    d[i] = j;
                }
            }
        }
        if(r < i + d[i]){
            r = i + d[i];
            l = i - d[i];
        }
        ans = max(ans, d[i]);
    }

    printf("%d\n", ans);
}
*/
