### KMP

字符串匹配算法，在txt中寻找pat。

````cpp
class KMP {
    class Pat {
        const size_t len, n;
        const vector<int> str;
        vector<vector<int>> nxt;

        class Res {
        public:
            int num{0};
            vector<int> pos{vector<int>(0)};
        };

    public:
        Pat(vector<int> str, int n) : str(str),
                                      n(n),
                                      len(str.size()),
                                      nxt(len + 1, vector<int>(n)) {
            if (str.empty()) {
                throw runtime_error("ErrorSize!");
            }

            int pre = 0;
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < n; j++) {
                    nxt[i][j] = nxt[pre][j];
                }
                nxt[i][str[i]] = i + 1;
                pre = nxt[pre][str[i]];
            }
            for (int j = 0; j < n; j++) {
                nxt[len][j] = nxt[pre][j];
            }
        }

        Res search(vector<int> txt) {
            size_t len_txt = txt.size();
            int stat = 0;
            Res res;
            for (int i = 0; i < len_txt; i++) {
                if (txt[i] >= n) {
                    stat = 0;
                } else {
                    stat = nxt[stat][txt[i]];
                    if (stat == len) {
                        res.num++;
                        res.pos.emplace_back(i);
                    }
                }
            }
            return res;
        }
    };
};
````



重点在nxt数组的构造，pre是具有与当前状态相同后缀的位置（以前看文章上写前缀，就半天没懂）。

当前的nxt通过pre转移，pre也通过pre转移。由于具有相同后缀，所以nxt可以通过pre转移。

不知道怎么写note
