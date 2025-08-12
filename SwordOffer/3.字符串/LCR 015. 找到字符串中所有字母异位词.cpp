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
using namespace std;

/**
给定两个字符串 s 和 p，找到 s 中所有 p 的 变位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
变位词 指字母相同，但排列不同的字符串。

示例 1：
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的变位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的变位词。

 示例 2：
输入: s = "abab", p = "ab"
输出: [0,1,2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的变位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的变位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的变位词。
 */

bool isAllZero(std::vector<int> countMap)
{
    for (int count : countMap)
    {
        if (count != 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * 1、审题：
 * - 输入一个长字符串s和短字符串p，求p的变位词在长字符串s中的起始索引
 * 2、解题
 * - 和LCR14题一样的思路，采用双指针+哈希表解法
 * - 使用int[]数组保存字母出现的次数，然后使用双指针遍历长字符串的一个区域，然后判断是否存在这样变位词
 */
vector<int> findAnagrams(string s, string p)
{
    if (s.length() < p.length())
    {
        return {};
    }
    vector<int> res;
    vector<int> countMap(26, 0); // 字母出现的次数

    // 先遍历短字符串
    for (int i = 0; i < p.length(); i++)
    {
        countMap[p[i] - 'a']++;
        countMap[s[i] - 'a']--;
    }

    // 判断是否命中p变位词在字符串s中
    if (isAllZero(countMap))
    {
        res.push_back(0);
    }

    // 继续遍历长字符串
    for (int i = p.length(); i < s.length(); i++)
    {
        countMap[s[i] - 'a']--;
        countMap[s[i - p.length()] - 'a']++;
        if (isAllZero(countMap))
        {
            res.push_back(i - p.length() + 1);
        }
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    auto res = findAnagrams("cbaebabacd", "abc");
    // std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    for (int element : res)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

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