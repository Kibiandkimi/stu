//
// Created by kibi on 23-11-4.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    class Tools {
    public:
        static void read(int &x) {
            int s = 0, w = 1, c = getchar();
            while (c < '0' || '9' < c) {
                if (c == '-') {
                    w = -1;
                }
                c = getchar();
            }
            while ('0' <= c && c <= '9') {
                s = s * 10 + c - '0';
                c = getchar();
            }
            x = s * w;
        }

        static void read_(initializer_list<int *> x) {
            for (auto &i : x) {
                read(*i);
            }
        }

        static void read_bool(bool &x) {
            static auto judge = [](int c) { return c == '.' || c == 'x'; };
            int c = getchar();
            while (!judge(c)) {
                c = getchar();
            }
            x = (c == '.');
        }
    };

    auto read_ = Tools::read_;// try initializer_list
    auto read_bool = Tools::read_bool;

    static int n, m;
    int x, y, k;
    //    read(n), read(m), read(x), read(y);
    read_({&n, &m, &x, &y, &k});

    bool raw_mp[n][m];
    for (auto &i : raw_mp) {
        for (auto &j : i) {
            read_bool(j);
        }
    }

    static int trans[2][5] = {{0, -1, 1, 0, 0},
                              {0, 0, 0, -1, 1}};

    //    int raw_f1[n][m], raw_f2[n][m];
    int f[n][m];
    memset(f, 0xc0, sizeof f);
    //    memset(raw_f1, 0xc0, sizeof raw_f1);
    //    memset(raw_f2, 0xc0, sizeof raw_f2);
    //    static auto f1 = raw_f1;
    //    static auto f2 = raw_f2;
    static auto mp = raw_mp;
    static int ans = 0;

    // TODO fix the two, not correct in ans, but should correct in grammar, can't be compile

    /*
    class Work{
    public:
        Work(int x, int y, int len, int d){
            deque<pair<int, int>> q;
            f1[x][y] = f2[x][y];
            for(int i = 1; x >= 0 && x < n && y >= 0 && y < m; i++, x += trans[0][d], y += trans[1][d]){
                if(!mp[x][y]){
                    q.clear();
                    continue;
                }

                while(!q.empty() && q.back().second + i - q.back().first < f1[x][y]){
                    q.pop_back();
                }
                q.emplace_back(i, f2[x][y]);
                while(!q.empty() && i - q.front().first > len){
                    q.pop_front();
                }
                f1[x][y] = q.front().second + i - q.front().first;

                ans = max(ans, f1[x][y]);
            }
        }
    };
     */

    /*
    static auto work = [](int x, int y, int len, int d){
        deque<pair<int, int>> q;
        f1[x][y] = f2[x][y];
        for(int i = 1; x >= 0 && x < n && y >= 0 && y < m; i++, x += trans[0][d], y += trans[1][d]){
            if(!mp[x][y]){
                q.clear();
                continue;
            }

            while(!q.empty() && q.back().second + i - q.back().first < f1[x][y]){
                q.pop_back();
            }
            q.emplace_back(i, f2[x][y]);
            while(!q.empty() && i - q.front().first > len){
                q.pop_front();
            }
            f1[x][y] = q.front().second + i - q.front().first;

            ans = max(ans, f1[x][y]);
        }
    };
     */

    //    f1[x - 1][y - 1] = 0;
    f[x - 1][y - 1] = 0;

    while (k--) {
        int s, t, d;
        read_({&s, &t, &d});
        //        swap(reinterpret_cast<exception_ptr &>(f1), reinterpret_cast<exception_ptr &>(f2));
        int a = d > 2 ? -1 : d == 1 ? n - 1
                                    : 0,
            b = d < 3 ? -1 : d == 3 ? m - 1
                                    : 0,
            mxi = d > 2 ? n : m, len = t - s + 1;
        for (int i = 0; i < mxi; i++) {
            //            work(a != -1 ? a : i, b != -1 ? b : i, len, d);
            //            Work{a != -1 ? a : i, b != -1 ? b : i, len, d};
            deque<pair<int, int>> q;
            int _x = a != -1 ? a : i, _y = b != -1 ? b : i;

            //            f1[x][y] = f2[x][y];
            for (int _i = 1; _x >= 0 && _x < n && _y >= 0 && _y < m; _i++, _x += trans[0][d], _y += trans[1][d]) {
                if (!mp[_x][_y]) {
                    q.clear();
                    continue;
                }

                while (!q.empty() && q.back().second + _i - q.back().first < f[_x][_y]) {
                    q.pop_back();
                }
                q.emplace_back(_i, f[_x][_y]);
                while (!q.empty() && _i - q.front().first > len) {
                    q.pop_front();
                }
                f[_x][_y] = q.front().second + _i - q.front().first;

                ans = max(ans, f[_x][_y]);
                //                printf("%d ", f[x][y]);
            }
        }
    }

    printf("%d\n", ans);

    /*
    for(auto &i : f){
        int s, t, d;
        // read(s), read(t), read(d);
        read_({&s, &t, &d});

        if(lst == i){
            i[x][y] = 0;
            int off_x = trans[0][d], off_y = trans[1][d];
            deque<pair<int, int>> dq;
            for(int p = x, q = y, time = 0; time < (t - s); time++){
                p += off_x, q += off_y;
                if(!mp[p][q] || p >= n || q >= m){
                    break;
                }
                i[p][q] = i[p - off_x][q - off_y] + 1;
            }
            continue;
        }

        lst = i;
    }
    */
}