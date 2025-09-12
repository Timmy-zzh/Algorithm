#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
// #include "src/bean.h"

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
LCR 032. 有效的字母异位词
https://leetcode.cn/problems/dKk3P7/description/

给定两个字符串 s 和 t ，编写一个函数来判断它们是不是一组变位词（字母异位词）。
注意：若 s 和 t 中每个字符出现的次数都相同且字符顺序不完全相同，则称 s 和 t 互为变位词（字母异位词）。

示例 1：
输入：s = "anagram", t = "nagaram"
输出：true

示例 2：
输入：s = "rat", t = "car"
输出：false

示例 3：
输入：s = "a", t = "a"
输出：false

提示：
1 <= s.length, t.length <= 5 * 104
s 和 t 仅包含小写字母

进阶: 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？
 */

/**
 * 1、审题：输入两个字符串，判断这两个字符串是否是异位词，异位词是两个字符串中的各个字母个数都相同
 * 2、解题：使用数组保存对应字母出现的次数
 * - 因为字符串限制了只包含小写字母，可以使用26个长度的int数组，来保存单个字母出现的次数
 * - 先判断两个字符串的长度，不一样直接返回false
 * - 字符串长度相同，则先遍历字符串1，保存每个字母出现的个数
 * - 接着遍历字符串2，遍历到的字母个数需要减1，如果出现了字母个数为0，则不满足异位词条件
 * - 判断如果两个字符串都一样，与不符合异位词情况，需要过滤
 * - 如果字符串内容没有限制，则使用map哈希表结构来保存字符出现的次数
 */
bool isAnagram(string s, string t)
{
    if (s.length() != t.length())
    {
        return false;
    }
    if (s == t)
    {
        return false;
    }

    std::vector<int> nums(26, 0);

    for (int i = 0; i < s.length(); i++)
    {
        nums[s[i] - 'a']++;
    }

    for (int i = 0; i < t.length(); i++)
    {
        if (nums[t[i] - 'a'] == 0)
        {
            return false;
        }
        nums[t[i] - 'a']--;
    }

    return true;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // std::cout << "res:" << res << std::endl;

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