//
// Created by kibi on 24-10-5.
//
#include "mahjong.h"

#include <bits/stdc++.h>
using namespace std;

namespace
{
string its(int x)
{
	string res="";
	res+=(char)('0'+x%10);
	if(x<=9) res+='m';
	else if(x<=19) res+='p';
	else res+='s';
	return res;
}
int F[3][3][2],G[3][3][2];
void trans(int Cnt)
{
	memset(G,-1,sizeof(G));
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int l=0;l<2;l++) if(F[i][j][l]>=0)
	{
		for(int t=0;t<=min(i,Cnt);t++)
		{
			for(int d=0;d<=(Cnt-t>=2?1:0);d++)
			{
				for(int d2=0;d2<=(Cnt-t-2*d>=3?1:0);d2++)
				{
					int v=F[i][j][l]+d2+t;
					int r1=i+j-t,r2=Cnt-t-d*2-d2*3;
					for(int m=0;m<=min(r1,r2);m++) G[min(2,m)][min(2,r2-m)][l|d]=max(G[min(2,m)][min(2,r2-m)][l|d],min(v,4));
				}
			}
		}
	}
}
int cnt[35];
bool chk(vector <int> Vec)
{
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<Vec.size();i++)
	{
		cnt[Vec[i]]++;
		if(cnt[Vec[i]]>4) return 0;
	}
	memset(F,-1,sizeof(F)),memset(G,-1,sizeof(G));
	F[0][0][0]=0;
	for(int i=1;i<=30;i++)
	{
		trans(cnt[i]);
		swap(F,G);
	}
	int maxx=0;
	for(int i=0;i<3;i++) for(int j=0;j<3;j++) maxx=max(maxx,F[i][j][1]);
	return maxx>=4;
}
vector <string> inp;
unordered_map <string,int> ma,inpcnt;
vector <int> vec;
vector <string> cds;
int idx,cost=0;
int inpidx=0;
long long costs=0;
int ti=0;
void grader_init()
{
	vec.clear();
	cds.clear();
	inpcnt.clear();
	for(int i=1;i<=108;i++)
	{
		string s=inp[inpidx++];
		cds.push_back(s);
		inpcnt[s]++;
		if(inpcnt[s]>4)
		{
			cout<<"Invalid input [3]\n";
			exit(0);
		}
		if(i<=13)
		{
			int x=s[0]-'0';
			if(s[1]=='m') vec.push_back(x);
			else if(s[1]=='p') vec.push_back(10+x);
			else vec.push_back(20+x);
		}
	}
	ma.clear();
	int cntok=0;
	for(int i=1;i<=29;i++) if(i%10)
	{
		vec.push_back(i);
		if(chk(vec)) ma[its(i)]=1,cntok++,cout<<its(i)<<" ";
		vec.pop_back();
	}
	puts("");
	if(cntok<2)
	{
		cout<<"Invalid input [4]\n";
		exit(0);
	}
	vector <string> c30;
	c30.clear();
	for(int i=13;i<43;i++) c30.push_back(cds[i]);
	idx=43;
	ti=0;
	play_game(c30);
}

}

vector <string> guess(string str)
{
	ti++;
	cost++;
	if(cost>270000)
	{
		cout<<"Wrong Answer [0]\n";
		exit(0);
	}
	if(str[0]<'1'||str[0]>'9')
	{
		cout<<"Wrong Answer [1]\n";
		exit(0);
	}
	if(str[1]!='m'&&str[1]!='p'&&str[1]!='s')
	{
		cout<<"Wrong Answer [1]\n";
		exit(0);
	}
	vector <string> res;
	res.clear();
	if(ma[str])
	{
		res.push_back("CORRECT");
		return res;
	}
	for(int i=0;i<3;i++)
	{
		if(idx<108)
		{
			if(ma[cds[idx]]) res.push_back("-1");
			else res.push_back(cds[idx]);
			idx++;
		}
		else res.push_back("-1");
	}
	return res;
}

int main()
{
	freopen("mahjong.in","r",stdin);
	freopen("mahjong.out","w",stdout);
	int Tc;
	cin>>Tc;
	if(Tc>10000)
	{
		cout<<"Invalid input [0]\n";
		return 0;
	}
	string st;
	while(cin>>st)
	{
		inp.push_back(st);
		if(inp.size()==108*Tc) break;
	}
	if(inp.size()!=108*Tc)
	{
		cout<<"Invalid input [1]\n";
		return 0;
	}
	for(int i=0;i<inp.size();i++)
	{
		if(inp[i][0]<'1'||inp[i][0]>'9')
		{
			cout<<"Invalid input [2]\n";
			return 0;
		}
		if(inp[i][1]!='m'&&inp[i][1]!='p'&&inp[i][1]!='s')
		{
			cout<<"Invalid input [2]\n";
			return 0;
		}
	}

	while(Tc--) grader_init();
	double score=0.0;
	if(cost>270000) score=0.0;
	else if(cost>=140000) score=5.0;
	else if(cost>=50000) score=20.0;
	else if(cost>=45000) score=20.0+6.0*(double)(50000-cost)/5000.0;
	else score=min(100.0,26.0+(double)(cost-45000)*(double)(cost-45000)*0.00000541);
	printf("Accepted! Cost = %d. Score = %.2lf.\n",cost,score);
	return 0;
}
