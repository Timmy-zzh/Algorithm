#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 */
using namespace std;

/**
给定一个非空字符串 s，请判断如果 最多 从字符串中删除一个字符能否得到一个回文字符串。

示例 1：
输入: s = "aba"
输出: true

示例 2：
输入: s = "abca"
输出: true
解释: 可以删除 "c" 字符 或者 "b" 字符

示例 3：
输入: s = "abc"
输出: false

提示：
1 <= s.length <= 105
s 由小写英文字母组成
 */

/**
 * 判断从start，end位置，往中间遍历，是否都存在相同的字符
 */
bool isPalindrome(std::string s, int start, int end)
{
    while (start < end)
    {
        if (s[start] != s[end])
        {
            break;
        }
        start++;
        end--;
    }
    return start >= end;
}

/**
 * 1、审题：
 * - 输入一个字符串，将字符串中的一个字符进行删除，删除完后剩下的字符串要求是回文串，如果存在这样的字符返回true
 * 2、解题：
 * - 双指针解法，从前后两端开始不断往中间遍历，如果遇到不相等的字符，则可以考虑将该字符删除继续进行判断是否是字符串
 * - 使用for循环遍历，先查找到不相等字符的位置，分别跳过该两个位置的字符，继续往中间遍历判断是否是回文串
 * - 如果输入的字符串就是回文串，则中间位置的删除一个字符，还是回文串
 * - 例子1： 回文字符串：abcdcba -> 删除中间字符-》abccba
 * - 例子2： 回文字符串：abccba  -> 删除中间字符-》abcba
 */
bool validPalindrome(string s)
{
    std::cout << "validPalindrome s:" << s << std::endl;
    int start = 0;
    int end = s.length() - 1;
    // 双指针分别从中间开始遍历，尝试找到不相等的字符
    for (; start < s.length() / 2; start++, end--)
    {
        if (s[start] != s[end])
        {
            break;
        }
    }

    return start == s.length() / 2 ||
           isPalindrome(s, start + 1, end) ||
           isPalindrome(s, start, end - 1);
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // auto res = validPalindrome("aba");
    auto res = validPalindrome("cbbcc");

    std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    // for (int element : res)
    // {
    //     std::cout << element << ",";
    // }
    // std::cout << std::endl;

    // 遍历2维数组
    // for (vector<int> ele : res)
    // {
    //     for (int element : ele)
    //     {
    //         std::cout << element << ",";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}