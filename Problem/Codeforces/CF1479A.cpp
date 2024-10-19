//
// Created by kibi on 24-7-30.
//
#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(random_device{}());

int main(){

    using uint = unsigned int;

    auto read = [](){
        uint s = 0, c = getchar();
        while(c < '0' || '9' < c){
            c = getchar();
        }
        while('0' <= c && c <= '9'){
            s = s * 10 + c - '0';
            c = getchar();
        }
        return s;
    };

    // auto n = read();
    uint n;
    cin >> n;

    // uint l = 1e9, r = 1e9;
    uint lp = 0, rp = n + 1;

    uint pmid = rnd() % n + 1;
    cout << "? " << pmid << endl;
    // uint vmid = read();
    uint vmid;
    cin >> vmid;

    while(pmid - lp > 1){
        uniform_int_distribution<uint> dist(lp + 1, pmid - 1);
        uint genp = dist(rnd);
        cout << "? " << genp << endl;
        // uint genv = read();
        uint genv;
        cin >> genv;
        if(genv > vmid){
            lp = genp;
        }else{
            rp = pmid;
            pmid = genp;
            vmid = genv;
        }
    }

    while(rp - pmid > 1){
        uniform_int_distribution<uint> dist(pmid + 1, rp - 1);
        uint genp = dist(rnd);
        cout << "? " << genp << endl;
        // uint genv = read();
        uint genv;
        cin >> genv;
        if(genv > vmid){
            rp = genp;
        }else{
            lp = pmid;
            pmid = genp;
            vmid = genv;
        }
    }

    cout << "! " << pmid << endl;

    return 0;
}