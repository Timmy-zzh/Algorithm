#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * 给定两个 01 字符串 a 和 b ，请计算它们的和，并以二进制字符串的形式输出。
输入为 非空 字符串且只包含数字 1 和 0。

示例 1：
输入: a = "11", b = "10"
输出: "101"

示例 2：
输入: a = "1010", b = "1011"
输出: "10101"

提示：
每个字符串仅由字符 '0' 或 '1' 组成。
1 <= a.length, b.length <= 10^4
字符串如果不是 "0" ，就都不含前导零。
 */

/**
 * 1、审题：
 * - 输入两个二进制字符串，要求对将二进制进行相加，计算出二进制的结果
 * 2、思路：
 * - 遍历两个字符串，从末尾往前遍历，两两相加，超过了字符串长度的为0，
 * - 相加过程需要考虑进位情况
 * - 将相加后的结果，存在在字符串中，使用append增加单个字符，最后翻转字符串得到最终结果
 * 3、总结：
 * - 二进制运算要求从字符串的末尾字符开始相加，并注意进位处理
 * - 使用while循环不断获取字符串的字符，超过范围使用0替补，
 * - 字符串使用
 * -- 字符串获取字符内容，使用str[i],
 * -- 将数字转成字符串：to_string(num)
 * -- 字符串内容翻转：reverse(str.begin(),str.end())
 */
string addBinary(string a, string b)
{
    std::cout << "a:" << a << " ,b:" << b << std::endl;
    int aLen = a.length();
    int bLen = b.length();

    int i = a.length() - 1;
    int j = b.length() - 1;
    int space = 0; // 进位

    string result = "";
    while (i >= 0 || j >= 0)
    {
        int aNum = i < 0 ? 0 : a[i] - '0';
        int bNum = j < 0 ? 0 : b[j] - '0';
        int sum = aNum + bNum + space;
        space = sum / 2;
        sum = sum % 2;
        std::cout << "sum:" << sum << std::endl;

        result.append(std::to_string(sum));
        i--;
        j--;
    }
    if (space != 0)
    {
        result.append(std::to_string(space));
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    std::string res = addBinary("1010", "1011");
    std::cout << "res:" << res << std::endl;

    return 0;
}