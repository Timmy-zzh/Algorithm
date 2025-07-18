#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/**
 * https://leetcode.cn/problems/w3tCBm/description/
    给定一个非负整数 n ，请计算 0 到 n 之间的每个数字的二进制表示中 1 的个数，并输出一个数组。

    示例 1:
    输入: n = 2
    输出: [0,1,1]
    解释:
    0 --> 0
    1 --> 1
    2 --> 10

    示例 2:
    输入: n = 5
    输出: [0,1,1,2,1,2]
    解释:
    0 --> 0
    1 --> 1
    2 --> 10
    3 --> 11
    4 --> 100
    5 --> 101

    说明 :
    0 <= n <= 105
 *
 * 总结：
 * 1、10进制转2进制方式
 * 2、vector数据结构添加元素方法push_back
 * 3、与位运算操作
 * 4、给vector数据结构添加默认值和长度 vector<int> res(n + 1, 0);
 */

/**
 * 1、解题思路：
 * 如果i为偶数，i的二进制1的个数，和i/2的二进制1的个数相同，因为i的结果等于i/2往左移动一位，i= i/2 << 1,
 * 如果i为奇数，是i/2的二进制往左移一位，并在最右边位数加上1，i = i/2 << 1 + 1
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
 * 1、解题思路：动态规划解法
 * 因为i的二进制1的个数，与i&(i-1)的二进制1的个数，要多1，
 * 根据这个规律得出推导公式：res[i] = res[i&(i-1)] + 1;
 */
vector<int> countBits3(int n)
{
    /**
     * 创建res数组，数组长度为n，数组中每个元素默认值为0
     * - 如果没有指定，这样 vector<int> res;
     * 直接使用去获取第一个源 res[0]会导致未定义报错（Segmentation fault）
     */
    vector<int> res(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        res[i] = res[i & (i - 1)] + 1;
    }

    return res;
}

/**
 * 1、解题思路：与运算
 * 与运算 i&(i-1) 会将i的二进制形式的最后一个1去除，最后将所有二进制的1去除得到0，计算的几次也就是二进制1的个数
 * 搞个例子出来：
 */
vector<int> countBits2(int n)
{
    vector<int> res;
    for (int i = 0; i <= n; i++)
    {
        int count = 0;
        int num = i;
        while (num != 0)
        {
            num = num & (num - 1);
            count++;
        }
        res.push_back(count);
    }

    return res;
}

/**
 * 1、审题：
 * 输入一个非负整数，求从0开始到n这几个整数，每个整数二进制形式中包含1的个数
 * 2、解题：
 * 暴力解法：从0到n进行遍历，求每个整数i的二进制个数，把10进制转成2进制，求1的个数
 * - 10进制转成2进制的方法，是将数字i不断除于2，得到商和余数，
 * -- 不断除于2，直到最后一定是商为0余数为1，将所得的余数加起来取反，就是最后的二进制结果
 * - 求二进制1的个数，也就是将余数为1的个数相加
 * 例子：10的二进制为1010
 * - 计算逻辑：
 * -- 10 /2 = 5 余 0
 * -- 5 /2 = 2 余 1
 * -- 2 /2 = 1 余 0
 * -- 1 /2 = 0 余 1
 * ==》当最后商为0时停止计算，将所有余数取反，就是对应二进制结果 1010
 *
 * 3、总结：
 * - 思路总结：10进制转2进制，通过将原数字不断除于2得到商和余数，直到最后商为0余数为1，得到的所有余数取反就是对应二进制
 * - vector数据结构添加元素使用方法push_back
 * - auto类型推导
 * - vector遍历
 */
vector<int> countBits1(int n)
{
    vector<int> res;
    for (int i = 0; i <= n; i++)
    {
        int count = 0;
        int num = i;
        while (num != 0)
        {
            int remaind = num % 2;
            if (remaind == 1)
            {
                count++;
            }
            num = num / 2;
        }
        res.push_back(count);
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    auto res = countBits(6);
    // 遍历res
    for (int element : res)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    return 0;
}