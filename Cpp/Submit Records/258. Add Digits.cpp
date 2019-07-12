/********************************************
作者:Alfeim
题目:各位相加
时间消耗:4ms
解题思路:假设当前各位是abc,则可以表示为100a + 10b + c;
如果各位相加,与原数的差为99a + 9b;可以看到,差值是9的倍数,
所以只需要对原数对9取余即可,如果取余值为0就返回9,否则返回取余
的那个值
********************************************/
class Solution {
public:
    int addDigits(int num) {
        if(num < 10)
             return num;
        return num % 9 == 0 ? 9 : num%9;
    }
};