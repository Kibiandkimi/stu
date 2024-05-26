//
// Created by kibi on 23-8-8.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100000, MaxK = 1000000, MinK = -1000000, RangeK = 2000000, Dis = 1000001;

int main(){

    //    freopen("t.in", "r", stdin);

    class TreeArray{
        int data[RangeK + 5]{}, n;

    public:
        explicit TreeArray(int n) : n(n){};

        void add(int x, bool flag = true){
            if(x > MaxK + Dis){
                x = MaxK + Dis;
            }else if(x <= 0){
                x = MinK + Dis;
            }
            while(x <= n){
                flag ? data[x]++ : data[x]--;
                x += (x & -x);
            }
        }

        int query(int x){
            int res = 0;
            assert(x > 0 && x<= MaxK + Dis);
            while(x){
                res += data[x];
                x -= (x & -x);
            }
            return res;
        }
    };

    class Inequality{
    public:
        int a, b, c;
        bool on;
    };

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

        static void read_opt(int &x){
            int c = getchar();
            while(c != 'A' && c != 'Q' && c != 'D'){
                c = getchar();
            }
            x = (c == 'A' ? 1 : (c == 'D' ? 2 : 3));
        }

        static void add_inequality_to_tree(Inequality &iq, TreeArray *tr, bool flag = true){
            auto [a, b, c, on] = iq;
            if(a == 0){
                if(b > c){
                    tr->add(MinK + Dis, flag);
                }
            }else{
                // ax + b > c -> {x > (c-b)/a (a > 0), x < (c-b)/a (a < 0)}
                if(a > 0){ // x > floor((c-b)/a) -> (floor((c-b)/a), MaxK + Dis]
                    int l = (c-b)/a + ((c-b) >= 0 ? 1 : (((c-b)/a*a!=(c-b)) ? 0 : 1)) + Dis, r = MaxK + Dis;
                    if(l > r){
                        return;
                    }
                    tr->add(l, flag);
                }else{ // x < (c-b)/a -> [MinK + Dis, roof((c-b)/a))
                    int l = MinK + Dis, r = (c-b)/a + ((c-b) <= 0 ? (((c-b)/a*a!=(c-b)) ? 1 : 0) : 0) + Dis;
                    if(l >= r){
                        return;
                    }
                    tr->add(r, !flag);
                    tr->add(l, flag);
                }
            }
        }
    };

    int n;

    Tools::read(n);

    static TreeArray tree_array(MaxK + Dis);
    static Inequality inequality[N + 5];

    while(n--){
        int opt;
        Tools::read_opt(opt);
        int a, b, c, i, k;
        static int cnt_of_inequality = 0;
        switch(opt){
            case 1:
                Tools::read(a), Tools::read(b), Tools::read(c);
                inequality[++cnt_of_inequality] = {a, b, c, true};
                Tools::add_inequality_to_tree(inequality[cnt_of_inequality], &tree_array);
                break;
            case 2:
                Tools::read(i);
                if(!inequality[i].on){
                    break;
                }
                inequality[i].on = false;
                Tools::add_inequality_to_tree(inequality[i], &tree_array, false);
                break;
            case 3:
                Tools::read(k);
                printf("%d\n", tree_array.query(k + Dis));
                break;
            default:
                throw exception();
        }
    }

    //    fclose(stdin);
}