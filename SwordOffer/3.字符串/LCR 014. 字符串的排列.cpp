#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 */
using namespace std;
using namespace std;

/**
 给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的某个变位词。
换句话说，第一个字符串的排列之一是第二个字符串的 子串 。

示例 1：
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2 包含 s1 的排列之一 ("ba").

示例 2：
输入: s1= "ab" s2 = "eidboaoo"
输出: False
 */
bool allZero(std::vector<int> countArr)
{
    for (int count : countArr)
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
 * - 输入两个字符串，短字符串s1，和长字符串s2，求长字符串s2中是否包含端字符串s1的变位词
 * 什么是变位词？
 * - 就是单词长度和包含的字母个数都相同的字符串
 * 2、解题：双指针加哈希表解法
 * - 使用哈希表保存字符串中每个字符出现的次数，由于字母一共有26个，所以使用int[]数组结构作为哈希表
 * - 刚开始int[]中所有元素都为0；遍历端字符串s1的所有字符，记录字母出现的次数，记录的哈希表作为后面比对的基准值
 * - 接着遍历长字符串s2的字符，长字符串的比对采用双指针定位字符串子数组，并且在遍历的过程中，注意区域前后字符的增加和删除
 * - 每一次遍历增减后，都判断一下当前哈希表中的字符个数，是否全部等于0；全部等于0则说明命中题目中的变位词
 */
bool checkInclusion(string s1, string s2)
{
    std::cout << "s1:" << s1 << " ,s2:" << s2 << std::endl;
    // 长度判断
    if (s1.length() > s2.length())
    {
        return false;
    }
    vector<int> countArr(26, 0);
    for (auto element : countArr)
    {
        std::cout << element << ",";
    }
    std::cout << "111" << std::endl;

    for (int i = 0; i < s1.length(); i++)
    {
        countArr[s1[i] - 'a']++; // 端字符串字母的个数增加
        countArr[s2[i] - 'a']--; // 长字符串字母的个数减少
    }

    for (auto element : countArr)
    {
        std::cout << element << ",";
    }
    std::cout << "222" << std::endl;
    // 判断26个字母的所有个数是否都等于0
    if (allZero(countArr))
    {
        return true; // 短字符串s1，和长字符串s2的第一次遍历，就命中了变位词
    }

    // 刚开始的几个字符没有命中，继续遍历后面的字符子数组
    for (int i = s1.length(); i < s2.length(); i++)
    {
        countArr[s2[i] - 'a']--;
        countArr[s2[i - s1.length()] - 'a']++;

        for (auto element : countArr)
        {
            std::cout << element << ",";
        }
        std::cout << "333" << " ,i=" << i << std::endl;

        if (allZero(countArr))
        {
            return true;
        }
    }

    return false;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    auto res = checkInclusion("ab", "eidbaooo");
    // auto res = checkInclusion("ab", "eidbaooo");
    std::cout << "res:" << res << std::endl;

    // 遍历数组1
    // for (int element : res)
    // {
    //     std::cout << element << ",";
    // }
    // std::cout << std::endl;

    // 遍历数组2
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