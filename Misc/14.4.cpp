//
// Created by kibi on 2021/6/13.
//
#include <bits/stdc++.h>
using namespace std;
int prior(char op)
{
    if(op=='+'||op=='-')
        return 1;
    if(op=='*'||op=='/')
        return 2;
    return 0;
}
string middletolast(string middle)
{
    stack<char> op;
    string ans;
    bool bj = false;
    for(int i=0; i<middle.size(); i++)
    {
        char c=middle[i];
        if(c>='0'&&c<='9')
        {
            if(bj == false){
                ans.append(1,' ');
            }
            ans.append(1,c);
            bj = true;
        }
        else
        {
            bj = false;
            if(c=='(')
                op.push('(');
            else
            {
                if(c==')')
                {
                    while(op.top()!='(')
                    {
                        ans.append(1,op.top());
                        op.pop();
                    }
                    op.pop();
                }
                else
                {
                    if(op.empty())
                    {
                        op.push(c);
                    }
                    else
                    {
                        if(prior(c)>prior(op.top()))
                            op.push(c);
                        else
                        {
                            while(!op.empty()&&prior(c)<=prior(op.top()))
                            {
                                ans.append(1,op.top());
                                op.pop();
                            }
                            op.push(c);
                        }
                    }
                }
            }
        }
    }
    while(!op.empty())
    {
        ans.append(1,op.top());
        op.pop();
    }
    return ans;
}

int main()
{
    string mdata,res;
    cin>>mdata;
    res=middletolast(mdata);
    //    cout << res << endl;
    for(int i=1; i<res.size(); i++)
    {
        if((res[i]>='0'&&res[i]<='9')||res[i]==' ')
            cout<<res[i];
        else
            cout<<' '<<res[i];
    }
    cout<<endl;
    return 0;
}