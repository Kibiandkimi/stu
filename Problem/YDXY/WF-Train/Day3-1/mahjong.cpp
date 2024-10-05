//
// Created by kibi on 24-10-5.
//
#include "mahjong.h"
#include <bits/stdc++.h>
void init(int T) {
    // nothing happened
}

enum Card{
    m1 = 1,
    m2,
    m3,
    m4,
    m5,
    m6,
    m7,
    m8,
    m9,
    p1 = 11,
    p2,
    p3,
    p4,
    p5,
    p6,
    p7,
    p8,
    p9,
    s1 = 21,
    s2,
    s3,
    s4,
    s5,
    s6,
    s7,
    s8,
    s9,
};

void play_game(vector<string> vec) {
    unordered_set<Card> st;
    {
        st.insert(s1);
        st.insert(s2);
        st.insert(s3);
        st.insert(s4);
        st.insert(s5);
        st.insert(s6);
        st.insert(s7);
        st.insert(s8);
        st.insert(s9);
        st.insert(p1);
        st.insert(p2);
        st.insert(p3);
        st.insert(p4);
        st.insert(p5);
        st.insert(p6);
        st.insert(p7);
        st.insert(p8);
        st.insert(p9);
        st.insert(m1);
        st.insert(m2);
        st.insert(m3);
        st.insert(m4);
        st.insert(m5);
        st.insert(m6);
        st.insert(m7);
        st.insert(m8);
        st.insert(m9);
    }
    [&st, &vec]{

    }();

    auto trans = [](Card a) -> string {
        switch (a) {
            case m1:
            return "m1";
            case m2:
            return "m2";
            case m3:
            return "m3";
            case m4:
            return "m4";
            case m5:
            return "m5";
            case m6:
            return "m6";
            case m7:
            return "m7";
            case m8:
            return "m8";
            case m9:
            return "m9";
            case s1:
            return "s1";
            case s2:
            return "s2";
            case s3:
            return "s3";
            case s4:
            return "s4";
            case s5:
            return "s5";
            case s6:
            return "s6";
            case s7:
            return "s7";
            case s8:
            return "s8";
            case s9:
            return "s9";
            case p1:
            return "p1";
            case p2:
            return "p2";
            case p3:
            return "p3";
            case p4:
            return "p4";
            case p5:
            return "p5";
            case p6:
            return "p6";
            case p7:
            return "p7";
            case p8:
            return "p8";
            case p9:
            return "p9";
        }
    };

    auto etrans = [](string a) -> Card {
            if (a == "m1"){
                return m1;
            }
            if (a == "m2"){
                return m2;
            }
            if (a == "m3"){
                return m3;
            }
            if (a == "m4"){
                return m4;
            }
            if (a == "m5"){
                return m5;
            }
            if (a == "m6"){
                return m6;
            }
            if (a == "m7"){
                return m7;
            }
            if (a == "m8"){
                return m8;
            }
            if (a == "m9"){
                return m9;
            }
            if(a == "s1"){
                return s1;
            }
            if(a == "s2"){
                return s2;
            }
            if(a == "s3"){
                return s3;
            }
            if(a == "s4"){
                return s4;
            }
            if(a == "s5"){
                return s5;
            }
            if(a == "s6"){
                return s6;
            }
            if(a == "s7"){
                return s7;
            }
            if(a == "s8"){
                return s8;
            }
            if(a == "s9"){
                return s9;
            }
            if(a == "p1"){
                return p1;
            }
            if(a == "p2"){
                return p2;
            }
            if(a == "p3"){
                return p3;
            }
            if(a == "p4"){
                return p4;
            }
            if(a == "p5"){
                return p5;
            }
            if(a == "p6"){
                return p6;
            }
            if(a == "p7"){
                return p7;
            }
            if(a == "p8"){
                return p8;
            }
            if(a == "p9"){
                return p9;
            }
    };

    while (true) {
        auto temp = trans(*st.begin());
        st.erase(st.begin());
        swap(temp[0], temp[1]);
        auto res = guess(temp);
        if (res.size() == 1) {
            return;
        }
        for (auto &i : res) {
            if (i == "-1") {
                continue;
            }
            temp = i;
            swap(temp[0], temp[1]);
            st.erase(etrans(temp));
        }
    }
}