#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <queue>
#include "src/bean.h"
#include <random>
#include <algorithm>
#include <unordered_set>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。写就是思考
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
29. 两数相除
https://leetcode.cn/problems/divide-two-integers/description/

给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用 乘法、除法和取余运算。
整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345 将被截断为 8 ，-2.7335 将被截断至 -2 。
返回被除数 dividend 除以除数 divisor 得到的 商 。
注意：假设我们的环境只能存储 32 位 有符号整数，其数值范围是 [−231,  231 − 1] 。本题中，如果商 严格大于 231 − 1 ，则返回 231 − 1 ；如果商 严格小于 -231 ，则返回 -231 。

示例 1:
输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = 3.33333.. ，向零截断后得到 3 。

示例 2:
输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = -2.33333.. ，向零截断后得到 -2 。

提示：
-231 <= dividend, divisor <= 231 - 1
divisor != 0
 */

/**
 * 1、之前的算法思路会导致超时，是因为在while循环中每次循环都是在除数 dividendL 的基础上减去被除数 divisorL 的值，
 * - 这样当除数很大，而被除数只是1的情况下，那这个while循环就需要循环很多次数，导致超时
 * 2、那现在的关键就是减少while的循环次数，让被除数不在只是累减处理，而是以2的倍数来累减计算值，在内层增加一个while循环来让被除数不断乘以2的阶乘
 * - 只要不超过除数，就可以一直增加这个阶乘值，直到超过，这样每次一次外层循环，减少的就是被除数的2的阶乘的个数，内层while循环不断计算出可以减少的被除数个数
 * - 忘记了不能用乘法
 * 3、总结：
 * - 要求除法结果，但是计算时不能用乘法和除法运算法
 * - 数据类型范围值越界，需要类型扩容int类型扩展至long类型
 * - 不能一个一个的不断的减少除数的个数，太耗时，改为一次减少多个，计算可以减少的个数 （这个逻辑是这道题的核心思路）
 */
int divide(int dividend, int divisor)
{
    long res = 0;
    int sign = 1; // 计算符号

    // 获取他的绝对值，先转成longlong类型，再转换符号
    long dividendL = dividend;
    long divisorL = divisor;
    // 获取绝对值
    if (dividend < 0)
    {
        dividendL = -dividendL;
    }
    if (divisor < 0)
    {
        divisorL = -divisorL;
    }

    // 获取正负数符号
    if ((dividend < 0 && divisor < 0) || (dividend >= 0 && divisor > 0))
    {
        sign = 1;
    }
    else
    {
        sign = -1;
    }

    // 使用阶乘方式来处理
    long temp = 0;
    long multi = 0; // 重复的阶乘个数
    while (dividendL >= divisorL)
    {
        multi = 1;
        temp = divisorL;
        while (dividendL > (temp << 1))
        {
            multi = multi << 1; // 往左移动
            temp = temp << 1;
        }
        dividendL -= temp;
        res += multi;
    }
    if (sign < 0)
    {
        res = -res;
    }

    if (res > INT32_MAX)
    {
        return INT32_MAX;
    }
    if (res < INT32_MIN)
    {
        return INT32_MIN;
    }
    return res;
}

/**
 * 1、审题：
 * - 题目输入两个整数，分别是被除数 dividend，和除数 divisor，现在要求不适用乘法除法取余这些运算符，来进行求除法运算的商
 * - 题目给出的要求是如果商大于2的31次方，则返回最大值2的31次方，最小值也是一样的返回逻辑
 * 2、解题：
 * - 题目限制不能用乘法、除法和取余运算符，可以考虑使用加法，减法，只是最基本的暴力运算方法实现
 * - 被除数每次不断减少除数的数值，他的结果值加1，直到小于除数，则返回结果值。
 * - 在相除前还需要判断正负数,如果为负数，则将他们转换成正数，并且使用一个值space来保存他们最后结果值商的正负数
 * - 对于最小数 负的2的31次方这个数，如果将他们转成正数2的31次方，则超过了int类型范围的最大值，所以需要使用long类型来承接数据
 * 3、通过while循环每次都减少一个除数的值，效率还是太慢了，需要进行优化解法
 * - 通过寻找整数的规律，采用位移的方式，将除数每次往左移动一位，他的结果就是两倍数值了。按照这个思路来
 */
int divide1(int dividend, int divisor)
{
    long res = 0;
    int space = 1;
    long dividendL = dividend;
    long divisorL = divisor;
    if (dividendL < 0)
    {
        space *= -1;
        dividendL *= -1;
    }
    if (divisorL < 0)
    {
        space *= -1;
        divisorL *= -1;
    }

    while (dividendL >= divisorL)
    {
        dividendL -= divisorL;
        res++;
    }
    res *= space;
    if (res > INT32_MAX)
    {
        return INT32_MAX;
    }
    if (res < INT32_MIN)
    {
        return INT32_MIN;
    }
    return res;
}

int main()
{
    std::cout << "《剑指》" << std::endl;
    auto res = divide(10, 3);
    std::cout << "res:" << res << std::endl;

    // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    // vector<string> words = {"tars", "rats", "arts", "star"};

    // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    // vector<vector<int>> prerequisites = {
    //     {1, 0},
    //     {2, 0},
    //     {3, 1},
    //     {3, 2},
    // };

    // vector<int> nums = {1, 2, 3};
    // vector<vector<int>> isConnected = {
    //     {1, 0, 0, 1},
    //     {0, 1, 1, 0},
    //     {0, 1, 1, 1},
    //     {1, 0, 1, 1},
    // };
    // vector<vector<int>> isConnected = {
    //     {1, 1, 0},
    //     {1, 1, 0},
    //     {0, 0, 1},
    // };

    // vector<int> nums = {100, 4, 200, 1, 3, 2};
    // vector<int> nums = {4, 0, -4, -2, 2, 5, 2, 0, -8, -8, -8, -8, -1, 7, 4, 5, 5, -4, 6, 6, -3};
    // auto res = longestConsecutive(nums);
    // std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    // for (auto ele : res)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    // 遍历2维数组
    // for (vector<int> ele : res)
    // {
    //   for (auto element : ele)
    //   {
    //     std::cout << element << ",";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "map +++++++++++++++ " << std::endl;
    // for (auto ele : map)
    // {
    //   std::cout << ele.first << " ---- nextNodes: " << std::endl;
    //   for (auto ele : ele.second)
    //   {
    //     std::cout << ele;
    //     std::cout << std::endl;
    //   }

    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "inDegreeMap ============ " << std::endl;
    // for (auto ele : inDegreeMap)
    // {
    //   std::cout << ele.first << " ---- " << ele.second;
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}