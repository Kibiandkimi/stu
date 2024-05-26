//
// Created by kibi on 2021/11/7.
//
#include <cstdio>
using namespace std;

long long a[205][205];
long long b[205][205];
long long fx[205][205];
long long fy[205][205];
int n;
long long lz(long long z){
    return z>0?z:z*-1;
}
//int main(){
//    int i,j;
//    printf("100\n");
//    for(i=1;i<=100;i++){
//        for(j=1;j<=100;j++){
//            printf("1000000 ");
//        }
//        puts("");
//    }
//    return 0;
//}
int main(){
    int i,j;
    long long a1,a2,x1,x2,b1,b2;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%lld",&b[i][j]);
        }
    }
    fx[1][1]=a[1][1];
    fy[1][1]=b[1][1];
    for(i=2;i<=n;i++){
        fx[1][i]=fx[1][i-1]+a[1][i];
        fy[1][i]=fy[1][i-1]+b[1][i];
        fx[i][1]=fx[i-1][1]+a[i][1];
        fy[i][1]=fy[i-1][1]+b[i][1];
    }
    for(i=2;i<=n;i++) {
        for(j=2;j<=n;j++){
            a1=fx[i-1][j];
            b1=fy[i-1][j];
            a2=fx[i][j-1];
            b2=fy[i][j-1];
            x1=a[i][j];
            x2=b[i][j];
            if((a1+x1)*(b1+x2)>(a2+x1)*(b2+x2)){
                fx[i][j]=a2+x1;
                fy[i][j]=b2+x2;
            }else if((a1+x1)*(b1+x2)==(a2+x1)*(b2+x2)){
                if(lz(a1+x1-b1-x2)>lz(a2+x1-b2+x2)) {
                    fx[i][j] = a1 + x1;
                    fy[i][j] = b1 + x2;
                }else{
                    fx[i][j]=a2+x1;
                    fy[i][j]=b2+x2;
                }
            }else{
                fx[i][j] = a1 + x1;
                fy[i][j] = b1 + x2;
            }
        }
    }
    printf("%lld\n",fx[n][n]*fy[n][n]);
    return 0;
}
/*
2
1 2
3 4
3 3
1 2
 */