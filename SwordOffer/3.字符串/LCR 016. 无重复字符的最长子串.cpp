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
给定一个字符串 s ，请你找出其中不含有重复字符的 最长连续子字符串 的长度。

示例 1：
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子字符串是 "abc"，所以其长度为 3。

示例 2：
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子字符串是 "b"，所以其长度为 1。

示例 3：
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

示例 4：
输入: s = ""
输出: 0

提示：
0 <= s.length <= 5 * 104
s 由英文字母、数字、符号和空格组成
 */

bool hasDoubleCh(std::vector<int> countMap)
{
    for (int count : countMap)
    {
        if (count > 1)
        {
            return true;
        }
    }
    return false;
}
/**
 * 1、审题：
 * - 输入一个字符串s，求其中的一个子字符串的长度，要求字符串中的字母没有出现重复
 * 2、解题：
 * - 双指针加哈希表解法
 * - 使用一个256长度的int[]数组保存字符串中字符出现的次数，（256是ASCII码字符表个数）
 * - 使用双指针定位子字符串的区域，刚开始左右两个指针都指向第一个字符
 * - 通过判断哈希表中是否存在相同字符，如果不相同则右指针向右移动，否则左指针向右移动
 * - 并判断当前子字符串的长度
 * 3、总结：
 * - 使用int[]数组的长度为256，用于标识所有字符，不用检出字符a
 */
int lengthOfLongestSubstring(string s)
{
    int res = 0;
    std::vector<int> countMap(256, 0);

    int left = 0;
    int right = 0;

    for (; right < s.length(); right++)
    {
        countMap[s[right]]++;
        // 判断是否有相同的字符
        while (hasDoubleCh(countMap))
        {
            countMap[s[left]]--;
            left++;
        }
        res = std::max(res, (right - left + 1));
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // auto res = lengthOfLongestSubstring("abcabcbb");
    // auto res = lengthOfLongestSubstring("pwwkew");
    auto res = lengthOfLongestSubstring(" ");

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