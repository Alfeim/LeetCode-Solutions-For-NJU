/********************************************
作者:Alfeim
题目:灯泡开关2
时间消耗:0ms
解题思路:所有灯泡状态仅仅取决于前三个灯泡的状态数
所以只需要遍历前三个灯泡的状态空间即可
********************************************/
class Solution {
public:
    int flipLights(int n, int m) {
        n = min(n,3);
        if(m == 0) return 1;
        if(m == 1) return n == 1 ? 2 : n == 2 ? 3 : 4;
        if(m == 2) return n == 1 ? 2 : n == 2 ? 4 : 7;
        return n == 1 ? 2 : n == 2 ? 4 : 8;
    }
};