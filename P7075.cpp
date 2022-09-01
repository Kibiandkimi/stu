//
// Created by kibi on 2022/9/1.
//
#include <bits/stdc++.h>
static const int r4 = 1461, r400 = 146097, r100 = 36524;
using namespace std;

/*公元前共1178个闰年，开始时间4713，1，1，为闰年。共1721423(058)天？。四年一周期共1461天
 * 1582,10,4 395个闰年，577460（1581，12，31），577737（）
 * 400 146097 100 36524?
 * */

struct node{
    int day, month;
};

bool getType(int c);
void read(int &x);
void read(long long &x);
node queryMonthsAndDays(int x, bool f = false);
void dealR4(long long int r, int y, int &year, int &month, int &day);

int main(){
    int Q;
    long long r;
    read(Q);
    while(Q--){
        bool bc = false;
        read(r);
        ++r;//因为第零天为1日？
        int year, month, day;
        if(r <= 1721423){
            bc = true;
            int round4 = r% r4, y = r/ r4;
            if(round4 <= 366){
                node res = queryMonthsAndDays(round4, true);
                month = res.month, day = res.day, year = 4713-y*4;
            }else{
                round4 -= 366;
                y*=4;
                y++;
                y += (round4-1) / 365;
                round4 = ((round4-1) % 365) + 1;
                node res = queryMonthsAndDays(round4);
                month = res.month, day = res.day, year = 4713-y;
            }
        }else{
            r -= 1721423;
            if(r <= 577733){
                int round4 = r% r4, y = r/ r4;
                y*=4;
                y++;
                if(round4 > 1095){
                    round4 -= 1095;
                    y += 3;
                    node res = queryMonthsAndDays(round4, true);
                    month = res.month, day = res.day, year = y;
                }else{
                    y += (round4-1)/365;
                    round4 = ((round4-1)%365);
                    node res = queryMonthsAndDays(round4);
                    month = res.month, day = res.day, year = y;
                }
            }else{
                r -= 577733;
                //                10.15日为1
                r += 10;
                int y = 1582;
                if(r <= 17){
                    month = 10, day = r, year = 1582;
                }else if(r <= 78){
                    r -= 17;
                    if(r <= 30){
                        month = 11, day = r, year = 1582;
                    }else{
                        month = 12, day = r-30, year = 1582;
                    }
                }else{
                    r -= 78;
                    r -= 13;
                    y++;
                    if(r <= 365){
                        node res = queryMonthsAndDays(r);
                        month = res.month, day = res.day, year = y;
                    }else{
                        r -= 365;
                        if(r <= 6210){
                            dealR4(r, y, year, month, day);
                        }else {
                            r -= 6210;
                            y += 17;
                            int round4 = r % r400, ty = r / r400;
                            ty *= 400;
                            if((round4-1)/r100>3){
                                round4 -= 3*r100;
                                ty += 300;
                                dealR4(round4, ty+y, year, month, day);
                            }else{
                                ty += ((round4-1)/r100)*100;
                                round4 = (round4-1)%r100;
                                if((round4 + 365)>r100){
                                    round4 = round4 - r100 + 366;
                                    ty += 100;
                                    node res = queryMonthsAndDays(round4, true);
                                    month = res.month, day = res.day, year = ty+y;
                                }else{
                                    dealR4(round4, ty+y, year, month, day);
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("%d %d %d ", day, month, year);
        if(bc) {
            printf("BC");
        }
        printf("\n");
    }
}

void dealR4(long long int r, int y, int &year, int &month, int &day) {
    int round4 = r % r4, ty = r / r4;
    ty *= 4;
    if (round4 <= 366) {
        ty++;
        node res = queryMonthsAndDays(round4, true);
        month = res.month, day = res.day, year = ty + y;
    } else {
        round4 -= 366;
        ty++;
        ty += (round4 - 1) / 365;
        round4 = (round4 - 1) % 365 + 1;
        node res = queryMonthsAndDays(round4);
        month = res.month, day = res.day, year = ty + y;
    }
}

bool getType(int c){
    return c<'0'||'9'<c;
}

void read(int &x){
    int s = 0, w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

void read(long long &x){
    long long s = 0;
    int w = 1, c = getchar();
    while(getType(c)){
        if(c == '-'){
            w *= -1;
        }
        c = getchar();
    }
    while(!getType(c)){
        s = s*10+c-'0';
        c = getchar();
    }
    x = s*w;
}

node queryMonthsAndDays(int x, bool f){
    int mon[13] = {0, 31, 28+f, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(x > 366){
        throw "error days";
    }
    int month, day;
    for(int i = 1; i <= 12; i++){
        if(x > mon[i]){
            x -= mon[i];
        }else{
            month = i, day = x;
            return {day, month};
        }
    }
    throw "error days";
}