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
给定一个字符串 s ，验证 s 是否是 回文串 ，只考虑字母和数字字符，可以忽略字母的大小写。
本题中，将空字符串定义为有效的 回文串 。

示例 1：
输入: s = "A man, a plan, a canal: Panama"
输出: true
解释："amanaplanacanalpanama" 是回文串

示例 2：
输入: s = "race a car"
输出: false
解释："raceacar" 不是回文串

提示：
1 <= s.length <= 2 * 105
字符串 s 由 ASCII 字符组成
 */

bool isPalindrome(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = std::tolower(s[i]);
    }

    int left = 0;
    int right = s.length() - 1;

    while (left < right)
    {
        while (left < right && !std::isalnum(s[left]))
        {
            left++;
        }
        while (left < right && !std::isalnum(s[right]))
        {
            right--;
        }
        // 左右字符都转换成大写字母
        if (s[left] != s[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

/**
 * 1、审题：
 * - 输入一个字符串s，判断s是否是回文串，字符串由字母数组和符号空格组成，只判断数字和字母，忽略大小写
 * 2、解题：
 * - 回文串是字符串正读和反读都一样
 * - 在该题中，使用双指针解法，一个从左开始遍历，一个从最右端开始遍历，判断是否是数字和字母，不是的话，继续移动指针
 * - 是的话，判断两个指针指向的字符是否相等，不相等，直接返回false
 * 3、优化写法：
 * - 先遍历字符串中所有字符，转成小写
 * - 在while循环中，继续使用while循环过滤非字母和数字的字符，接着直接判断是否相等
 */
bool isPalindrome1(string s)
{
    int left = 0;
    int right = s.length() - 1;

    while (left < right)
    {
        char leftCh = s[left];
        if (!std::isalnum(leftCh))
        {
            left++;
            continue;
        }
        char rightCh = s[right];
        if (!std::isalnum(rightCh))
        {
            right--;
            continue;
        }
        // 左右字符都转换成大写字母
        if (std::toupper(leftCh) != std::toupper(rightCh))
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    auto res = isPalindrome("A man, a plan, a canal: Panama");
    // auto res = isPalindrome("race a car");

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