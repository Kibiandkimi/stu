P1117(待理解，后缀数组+st表 求 lcp+lcs)
P1903(想做)
P3939(这里有超快的快读fread)
P7914*
P1600(class Lca & class Graph)
hash -> unordered_map
类的静态成员变量一定要在全局里先声明！！！
Maths and Algorithm
有时间学习zkw树
和差角公式
泰勒展开式
make a read to read char
P3017 c++解包(支持array, tuple ...)
class的函数中的static元素也是由各实例共享的
priority_queue自定义排序见P2149, P6833
TODO 矩阵乘法
signal 4: SIGILL 有可能是printf()中类型错误，如果是printf("%d", func)，func返回类型为int但忘记return也会导致错误
TODO 数论
cmp中的类型要和数组保持一致，别 long long 变 int，而且这种情况没有警告
T365455 sort的cmp这样写竟然不会有问题，Question类继承Node，把cmp也继承了，cmp中类型是Node，Question排序用cmp，也可以排
重链剖分 Heavy path decomposition
重心 barycentre

'''
P1439*, P1025, P5020, P1941*, P1006, P1064, P1091, P5664*, P1880*, P1070**, P1140, P4310, P5017*, P8564*, P1052, P4138,
P5322, P6005, P2516, P1192, P2585(dp)
P1613(图上dp)
P2015, P1122(树上DP)
P1441*, P1896, P2704, P1433*, P1559, P2051, P1879, P2622, P3959*(状压dp)
P4170, P1220, P1040(区间dp)
P1018(dp+高精)
P2569*, P1776*(dp+单调队列)
P2671(线性结构)
P3939, P3017*(二分)
P1450*(背包+容斥)
P2827, P1886, P2034, P2627(单调队列)
P1070*, P3800(?dp+单调队列)
P7073(树形结构)
P2146, P3384, P2590, P3178, P4281(树链刨分)
P3919, P3834, P1383, P3567*, P2617*(主席树)
P1198, P2471, P4588, P1083, P1816, P2286, P1937, P2894, P7706, P4198, CF438D, P6812, P5522, P6587(线段树)
P1637*(树状数组+dp)
P1972, P3374, P5677, P5428(树状数组)
P5367(树状数组+康托展开)
P1801, P3369, P3391, P1503*, P1486, P2073, P6136, P3871(平衡树-fhq-treap)
P3870, P2357(分块)
P5049&P5022/the same code/(基环树)
P1453(基环树+dp)
P1314, P2280, P1311, P2882, P3397(前缀和)
P3805(Manacher求最大回文)
P1659(Manacher+一点点前缀和)
P6216(Manacher+KMP+前缀和)
P4555(Manacher+dp?,还得再看看)
P3808, P3796, P3966**(AC自动机)
P5357(AC自动机+(拓扑排序?或者别的))
P1345, P2055, P3376, P2756, P2763, P1894, P1129(网络流)
P1155(二分图)
P3386(二分图最大匹配——匈牙利(网络流似乎也可以))
P6577, P3967(二分图最佳匹配 即 二分图最大权完美匹配 —— KM算法)
P1983, P1113(拓扑排序)
P1341, P3520(欧拉回路和欧拉道路)
P3379(lca)
P3258, P1600*, P3128(差分+lca)
P2002, P2863, P2835(tarjan强连通分量和缩点)
P3627(tarjan缩点+dp)
P5058, P3469(求割点)
P6833, P4822, P1522, P3371(最短路)
P3884(dfs)
P1144, P1825(bfs)
P1119(某最短路)
P1550, P2212, P3073(最小生成树)
P4391, P3435(KMP)
P1168, P1090(优先队列)
P7915(双端队列)
P6033(队列+快读)
P5149(trie+逆序对)
P8306, P9364(trie)
P1525, P1621, P2700, P9565(并查集)
P3811*(线性求逆元)
P5656*(二元一次不定方程)
P5091*, P4139(扩展欧拉定理)
P5018, P4305, P1379(哈希)
P4035, P1337(模拟退火)
P5638, CF1073D, P9754(模拟)
P3467, CF817D(单调栈)
P1865(埃氏筛)
P1349, CF222E(矩阵加速)
P3868(中国剩余定理)
P2303*, P2568(欧拉函数)
P2183*(扩展Lucas定理)
P9209, CF1661D, P9378, P9378(贪心)
P6812(差分)
P4782(2-SAT)
CF1548B(ST表)
P5522(状态压缩)
P7482(分治)
'''

24-3-31 new Problem List
哈夫曼（Huffman Tree）：P2168
高精度:P1005

TODO P2303
TODO P2183

Warning: 
    - lambda函数在capture时，只会在声明时捕获一次而不会在每次调用时捕获。

24-4-11
单调队列: P1886
DP:
    -背包: P4158, P1282
    -树形: P2607
    -区间: P2466

图论:
    P3942
    -基环树: P2607
    -bfs: P1514, P2578, P4667
    -A*: P2901

数据结构:
    -树链剖分: P4092
    -平衡树: P3224
    -线段树: P2824, P1502
    -笛卡尔树: P5854

贪心:
    P2123, P1084
    -反悔: P4053

倍增:
    P1084, CF413E

二分:
    -二分答案: P1182, P2678, P2824

分治:
    CF1442D

哈希:
    P3370, P3498, P4503, P8085

字符串:
    -Manacher: P3501
    -KMP: P3065

语法:
不调用函数获取其返回值类型(typeof, decltype)?
定义define作用域(#undef)?
P4503 unique_ptr初探
P8085 MyString without unique_ptr
函数作为参数传递

英文:
DSU(Disjoint Set Union) 并查集

TODO:
https://www.luogu.com.cn/article/vix37anf 整数划分转移