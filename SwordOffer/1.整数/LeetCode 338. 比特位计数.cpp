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
338. 比特位计数
https://leetcode.cn/problems/counting-bits/description/

给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans 作为答案。
不要使用内置函数来解决（例如，C++ 中的 __builtin_popcount）。

示例 1：
输入：n = 2
输出：[0,1,1]
解释：
0 --> 0
1 --> 1
2 --> 10

示例 2：
输入：n = 5
输出：[0,1,1,2,1,2]
解释：
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101

提示：
0 <= n <= 105
进阶：
很容易就能实现时间复杂度为 O(n log n) 的解决方案，你可以在线性时间复杂度 O(n) 内用一趟扫描解决此问题吗？
 */

/**
 * 位移操作解法：
 * - 整数i往左位移移位i>>1,对应结果为i/2，
 * - 如果i为偶数，他的最低位为0，往右位移一位，他的结果i/2,与i的二进制表示中1的个数一样。
 * - 如果i为奇数，他的最低位为1，往右移位移位，他的结果i/2，i中二进制1的个数比i/2多一，
 * - 所以可以采用动态规划的解法来实现
 */
vector<int> countBits(int n)
{
    vector<int> res(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        res[i] = res[i / 2] + (i & 1);
    }

    return res;
}

/**
 * 位运算&解法
 * - 位运算表达式 i&(i-1) 每次都会将数字i中二进制最右侧的1去除掉，
 * - 这样不断每次都去除掉二进制中的1，直到所有的1去除掉，结果值为0，记录的操作次数就是结果值
 */
vector<int> countBits2(int n)
{
    vector<int> res(n + 1, 0);

    for (int i = 0; i <= n; i++)
    {
        int num = i;
        while (num != 0)
        {
            num = num & (num - 1);
            res[i]++;
        }
    }

    return res;
}

/**
 * 1、审题：输入一个整数n，要求从数字0开始到数字n一共n+1个数字，每个数字对应二进制表示的数字1的个数。
 * 最后把这每个数字中二进制数字1个数组成的数组返回。
 * 2、解题：
 * 二进制转换法：
 * - 将每个整数i转成二进制，并记录二进制中1的个数
 * - 创建一个n+1的数组，用来保存二进制包含1的个数
 */
vector<int> countBits1(int n)
{
    vector<int> res(n + 1, 0);

    string binaryStr = ""; // 数字i对应的二进制结果值

    for (int i = 0; i <= n; i++)
    {
        int num = i;
        binaryStr = "";
        while (num != 0)
        {
            // 十进制数字num转换成二进制
            int remainder = num % 2; // 取余数
            int business = num / 2;  // 商

            if (remainder == 1)
            {
                res[i]++;
            }
            num = business;
            binaryStr = to_string(remainder) + binaryStr;
        }
        std::cout << i << " -- " << binaryStr << std::endl;
    }

    return res;
}

int main()
{
    std::cout << "《剑指》" << std::endl;
    auto res = countBits(6);
    // std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    for (auto ele : res)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

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