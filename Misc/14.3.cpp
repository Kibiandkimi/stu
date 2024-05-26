//
// Created by kibi on 2021/6/13.
//
#include <bits/stdc++.h>
using namespace std;
string c;
stack<char> c1;
int ans;
int trans(char x)
{
    if(x=='*'||x=='/') return 3;
    else if(x=='+'||x=='-') return 2;
    else if(x=='^') return 4;
    else return 1;
}
int main()
{
    getline(cin,c);
    bool ywkg = false;
    for(int i = 0; i < c.size(); i++){
        if(c[i]>='0'&&c[i]<='9'){
            if(i == 0){
                c1.push(c[i]-'0');
            }else if(!ywkg){
                int t = c1.top();
                c1.pop();
                c1.push(c[i]-'0'+10*t);
            }else{
                c1.push(c[i]-'0');
            }
            ywkg = false;
        }else if(c[i]==' '){
            ywkg = true;
        }else{
            int a = 0, b = 0;
            a = c1.top();
            c1.pop();
            b = c1.top();
            c1.pop();
            switch(c[i]){
                case '+' :
                    c1.push(a+b);
                    break;
                    case '-':
                        c1.push(b-a);
                        break;
                        case '*':
                            c1.push(a*b);
                            break;
                            case '/':
                                c1.push(b/a);
                                break;
            }
        }
    }
    cout << int(c1.top());
    return 0;
}
