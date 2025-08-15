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
给定一个字符串 s ，请计算这个字符串中有多少个回文子字符串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

示例 1：
输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"

示例 2：
输入：s = "aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

提示：
1 <= s.length <= 1000
s 由小写英文字母组成
 */

// 计算回文子串的个数
int countPalindorm(std::string s, int start, int end)
{
    int count = 0;
    while (start >= 0 && end < s.length())
    {
        if (s[start] != s[end])
        {
            break;
        }
        start--;
        end++;
        count++;
    }

    return count;
}

/**
 * 解法二：从中间向两端开始遍历
 * - 遍历原始字符串，在遍历的字符位置，开始分别向两端开始扩散，判断是否存在相同的字符，如果存在则说明遍历子区域是回文串，并添加回文串的个数
 * - 遍历的字符位置，分两种情况，一种是以当前字符为中心，一种是当前字符和后一个字符为中心
 */
int countSubstrings(string s)
{
    std::cout << "s:" << s << std::endl;
    int res = 0;
    for (int i = 0; i < s.length(); i++)
    {
        res += countPalindorm(s, i, i);
        res += countPalindorm(s, i, i + 1);
    }
    return res;
}

// 判断该子字符串是否是回文串
int isPalindrome(std::string s, int start, int end)
{
    while (start < end)
    {
        if (s[start] != s[end])
        {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}

/**
 * 1、审题：
 * - 输入一个字符串，该字符串有很多的子字符串，判断這些子字符串是否是回文串，返回是回文串的个数
 * 2、解法：暴力解法
 * - 双指针定义子字符串，然后判断子字符串是否是回文串
 */
int countSubstrings1(string s)
{
    std::cout << "s:" << s << std::endl;
    int start = 0;
    int end = 0;
    int res = 0;
    for (int i = 0; i < s.length(); i++)
    {
        start = i;
        end = s.length() - 1;
        while (start <= end)
        {
            res += isPalindrome(s, start, end);
            end--;
        }
    }
    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    auto res = countSubstrings("aaa");
    // auto res = countSubstrings("abc");

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