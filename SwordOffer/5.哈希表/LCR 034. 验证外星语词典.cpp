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
LCR 034. 验证外星语词典
https://leetcode.cn/problems/lwyVBB/description/

某种外星语也使用英文小写字母，但可能顺序 order 不同。字母表的顺序（order）是一些小写字母的排列。
给定一组用外星语书写的单词 words，以及其字母表的顺序 order，只有当给定的单词在这种外星语中按字典序排列时，返回 true；否则，返回 false。

示例 1：
输入：words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
输出：true
解释：在该语言的字母表中，'h' 位于 'l' 之前，所以单词序列是按字典序排列的。

示例 2：
输入：words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
输出：false
解释：在该语言的字母表中，'d' 位于 'l' 之后，那么 words[0] > words[1]，因此单词序列不是按字典序排列的。

示例 3：
输入：words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
输出：false
解释：当前三个字符 "app" 匹配时，第二个字符串相对短一些，然后根据词典编纂规则 "apple" > "app"，因为 'l' > '∅'，其中 '∅' 是空白字符，定义为比任何其他字符都小（更多信息）。

提示：
1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
在 words[i] 和 order 中的所有字符都是英文小写字母。
 */

bool judgeSort(std::string str1, std::string str2, std::map<char, int> orderMap)
{
    for (int i = 0; i < str1.length(); i++)
    {
        char ch1 = str1[i];
        // 长度判断
        if (str2.length() <= i)
        {
            return false;
        }
        else
        {
            char ch2 = str2[i];
            // 判断字母位置
            if (orderMap[ch1] < orderMap[ch2])
            {
                return true;
            }
            else if (orderMap[ch1] == orderMap[ch2]) // 相等继续遍历
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    // str1的长度为空，不存在
    return true;
}

/**
 * 1、审题：输入一个字符串数组和对应的字母排序规则order，判断输入的字符串数组中的字符串是否是升序的，是的话返回true否则返回false
 * 2、解题：
 * - 遍历字符串数组，只要判断前后两个字符串是否是符合排序规则，如果是的话继续遍历下一组字符串，如果不符合规则则直接返回false
 * - 所以核心点在于判断两个字符串是否符合给出的order排序规则，使用哈希表map保存order规则中字母顺序所在的下标位置，
 */
bool isAlienSorted(vector<string> &words, string order)
{
    std::map<char, int> orderMap;
    for (int i = 0; i < order.length(); i++)
    {
        orderMap[order[i]] = i;
    }

    for (int i = 0; i < words.size() - 1; i++)
    {
        // 判断两个字符串，是否符合规则
        if (!judgeSort(words[i], words[i + 1], orderMap))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    // vector<string> words = {"hello", "leetcode"};
    // string order = "hlabcdefgijkmnopqrstuvwxyz";

    vector<string> words = {"word", "world", "row"};
    string order = "worldabcefghijkmnpqstuvxyz";

    auto res = isAlienSorted(words, order);
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