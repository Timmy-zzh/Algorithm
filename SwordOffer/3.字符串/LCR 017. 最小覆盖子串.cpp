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
    给定两个字符串 s 和 t 。返回 s 中包含 t 的所有字符的最短子字符串。如果 s 中不存在符合条件的子字符串，则返回空字符串 "" 。
    如果 s 中存在多个符合条件的子字符串，返回任意一个。
    注意： 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。

    示例 1：
    输入：s = "ADOBECODEBANC", t = "ABC"
    输出："BANC"
    解释：最短子字符串 "BANC" 包含了字符串 t 的所有字符 'A'、'B'、'C'

    示例 2：
    输入：s = "a", t = "a"
    输出："a"

    示例 3：
    输入：s = "a", t = "aa"
    输出：""
    解释：t 中两个字符 'a' 均应包含在 s 的子串中，因此没有符合条件的子字符串，返回空字符串。
 */

bool hasCover(std::vector<int> countMap)
{
    for (int count : countMap)
    {
        if (count > 0)
        {
            return false;
        }
    }
    return true;
}

/**
 * 1、审题：
 * - 输入两个字符串，长字符串s和短字符串t，在长字符串中寻找一个最短的子字符串，该子字符串要求包含短字符串t中所有的字符
 * 2、解题：
 * - 还是使用双指针和哈希表解法，和之前题目一样的解题思路
 * - 使用哈希表保存短字符串t中字符出现的个数，
 * - 并且使用双指针定位子字符串，判断字符出现的个数，判断当前子字符串场景下，是否全部包含短字符串
 */
string minWindow(string s, string t)
{
    if (s.length() < t.length())
    {
        return "";
    }

    std::vector<int> countMap(256, 0);

    for (int i = 0; i < t.length(); i++)
    {
        countMap[t[i]]++;
        countMap[s[i]]--;
    }

    // 判断是否命中p变位词在字符串s中
    if (hasCover(countMap))
    {
        return s.substr(0, t.length());
    }

    std::string res = "";
    int left = 0;
    int right = t.length();
    int minLen = INT32_MAX;

    for (; right < s.length(); right++)
    {
        countMap[s[right]]--;
        // 判断是否有包含短字符串
        while (hasCover(countMap))
        {
            std::cout << "left:" << left << " ,right:" << right << ",minLen:" << minLen << std::endl;
            if ((right - left + 1) < minLen)
            {
                /**
                 * substr方法，
                 * 第一个参数是开始截取的索引
                 * 第二个参数是截取的个数
                 */
                minLen = right - left + 1;
                res = s.substr(left, minLen);
                std::cout << "left:" << left << " ,right:" << right << ",minLen:" << minLen << ",res:" << res << std::endl;
            }
            countMap[s[left]]++;
            left++;
        }
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // auto res = minWindow("ADOBECODEBANC", "ABC");
    // auto res = minWindow("a","a");
    auto res = minWindow("abc", "b");

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