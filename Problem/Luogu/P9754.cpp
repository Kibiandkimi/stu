//
// Created by kibi on 23-10-28.
//
#include <bits/stdc++.h>
using namespace std;

int main(){
    using ll = long long;

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

        static void read_ll(ll &x){
            ll s = 0, w = 1, c = getchar();
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

        static void read_(vector<int> &x){
            auto judge = [](int c){return c == '.' || ('a' <= c && c <= 'z');};
            int c = getchar();
            while(!judge(c)){
                c = getchar();
            }
            while(judge(c)){
                x.emplace_back(c);
                c = getchar();
            }
            x.shrink_to_fit();
        }

        static ll calc_padding(ll now, ll unit){
            ll res = (now / unit + (bool)(now % unit)) * unit;
            return res;
        }

        static void decompose(vector<int> &x, vector<vector<int>> &res){
            vector<int> t;
            for(auto &i : x){
                if(i != '.'){
                    t.emplace_back(i);
                }else{
                    t.shrink_to_fit();
                    res.emplace_back(t);
                    vector<int>{}.swap(t);
                }
            }
            t.shrink_to_fit();
            res.emplace_back(t);
        }

    };

    class BasicStruct{
    public:
        vector<int> name;
        int id{};
        ll siz{};
    };

    class Element{
    public:
        vector<int> name;
        int type, id;
        ll offset;

        Element(int type, int id, ll offset):type(type), id(id), offset(offset){}
    };

    class Struct: public BasicStruct{
    public:
        map<vector<int>, int> element;
        int num_of_ele{0}, unit_size{0};
        vector<Element> ele{Element{0, 0, 0}};

        Struct() = default;
        explicit Struct(const BasicStruct& a){
            id = a.id;
            siz = a.siz;
            unit_size = (int)a.siz;
            num_of_ele = 0;
        }
    };

    class Instance{
    public:
        vector<int> name;
        int type_of_struct, id;
        ll addr;

        Instance(int type, int id, ll addr):type_of_struct(type), id(id), addr(addr){}
    };

    auto read = Tools::read;
    auto read_ = Tools::read_;
    auto read_ll = Tools::read_ll;
    auto calc_padding = Tools::calc_padding;
    auto decompose = Tools::decompose;

    int n;
    read(n);

    map<vector<int>, int> struct_, instance; // map name->id
    int cnt_struct = 4, cnt_instance; // cnt

    BasicStruct myLong{{'l', 'o', 'n', 'g'}, 1, 8},
            myInt{{'i', 'n', 't'}, 2, 4},
            myShort{{'s', 'h', 'o', 'r', 't'}, 3, 2},
            myChar{{'b', 'y', 't', 'e'}, 4, 1}; // basic struct init
    struct_[{'l', 'o', 'n', 'g'}] = 1,
                            struct_[{'i', 'n', 't'}] = 2,
                            struct_[{'s', 'h', 'o', 'r', 't'}] = 3,
                            struct_[{'b', 'y', 't', 'e'}] = 4;

    vector<Struct> myStruct{Struct{} ,(Struct)myLong, (Struct)myInt, (Struct)myShort, (Struct)myChar}; // init struct
    vector<Element> myElement{Element{0, 0, 0}};
    vector<Instance> myInstance{Instance{0, 0, 0}};

    ll addr = 0; // addr

    while(n--){
        int opt;
        read(opt);

        if(opt == 1){
            Struct now;
            vector<int> name_struct;
            int k;
            read_(name_struct), read(k);
            now.id = ++cnt_struct; // init id
            now.num_of_ele = k; // init num of element
            struct_[name_struct] = now.id; // init map
            ll offset = 0; // offset
            int cnt_element = 0;
            while(k--){
                vector<int> type_element, name_element;
                read_(type_element), read_(name_element);
                now.element[name_element] = ++cnt_element; // init name map
                offset = calc_padding(offset, myStruct[struct_[type_element]].unit_size); // use function to calc offset

                /*
                offset = (offset / myStruct[struct_[type_element]].siz + // calc offset
                        (bool)(offset % myStruct[struct_[type_element]].siz))
                                * myStruct[struct_[type_element]].siz;
                */

                now.ele.emplace_back(struct_[type_element], now.element[name_element], offset); // init element
                now.ele.back().name = name_element;
                offset += myStruct[struct_[type_element]].siz;
                now.unit_size = max(now.unit_size, myStruct[struct_[type_element]].unit_size); // update unit size
            }

            now.siz = calc_padding(offset, now.unit_size); // use function to calc siz
            /*
            now.siz = (offset / now.unit_size + (bool)(offset % now.unit_size)) * now.unit_size; // init siz
            */
            now.name = name_struct;
            myStruct.emplace_back(now);
            printf("%lld %d\n", now.siz, now.unit_size);
        }else if(opt == 2){
            vector<int> type_instance, name_instance;
            read_(type_instance), read_(name_instance);
            addr = calc_padding(addr, myStruct[struct_[type_instance]].unit_size);
            //            if(!instance[name_instance]){
            //                instance[name_instance] = ++cnt_instance;
            //            }
            instance[name_instance] = ++cnt_instance;
            myInstance.emplace_back(struct_[type_instance], instance[name_instance], addr);
            myInstance.back().name = name_instance;
            printf("%lld\n", addr);
            addr += myStruct[struct_[type_instance]].siz;
        }else if(opt == 3){
            vector<int> raw_instance;
            vector<vector<int>> layer;
            read_(raw_instance);
            decompose(raw_instance, layer);
            if(layer.empty()){
                throw exception();
            }
            int now = myInstance[instance[layer[0]]].type_of_struct;
            ll offset = myInstance[instance[layer[0]]].addr;
            for(auto i = layer.begin() + 1; i != layer.end(); i++){
                offset += myStruct[now].ele[myStruct[now].element[*i]].offset;
                now = myStruct[now].ele[myStruct[now].element[*i]].type;
            }
            printf("%lld\n", offset);
        }else if(opt == 4){
            ll pos;
            read_ll(pos);
            int l = 1, r = cnt_instance, res = 1;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(myInstance[mid].addr > pos){
                    r = mid - 1;
                }else{
                    res = mid;
                    l = mid + 1;
                }
            }
            if(!cnt_instance){
                printf("ERR\n");
                continue;
            }
            int now = myInstance[res].type_of_struct;
            if(pos >= myInstance[res].addr + myStruct[myInstance[res].type_of_struct].siz){
                printf("ERR\n");
                continue;
            }
            vector<vector<int>> ans{myInstance[res].name};
            bool flag = true;
            ll offset = myInstance[res].addr;
            while(myStruct[now].num_of_ele != 0){
                l = 1, r = myStruct[now].num_of_ele, res = 1;
                while(l <= r){
                    int mid = (l + r) >> 1;
                    if(myStruct[now].ele[mid].offset + offset > pos){
                        r = mid - 1;
                    }else{
                        res = mid;
                        l = mid + 1;
                    }
                }
                offset += myStruct[now].ele[res].offset;
                if(pos >= offset + myStruct[myStruct[now].ele[res].type].siz){
                    flag = false;
                    break;
                }
                ans.emplace_back(myStruct[now].ele[res].name);
                now = myStruct[now].ele[res].type;
            }
            if(!flag){
                printf("ERR\n");
                continue;
            }
            for(auto i = ans.begin(); i + 1 != ans.end(); i++){
                for(auto &j : *i){
                    printf("%c", (char)j);
                }
                printf(".");
            }
            for(auto &j : ans.back()){
                printf("%c", (char)j);
            }
            printf("\n");
        }
        if(cnt_instance < 0 || cnt_struct < 0){
            throw exception();
        }
    }
}