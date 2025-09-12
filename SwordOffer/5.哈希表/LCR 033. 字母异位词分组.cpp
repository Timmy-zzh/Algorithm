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
LCR 033. 字母异位词分组
https://leetcode.cn/problems/sfvd7V/description/

给定一个字符串数组 strs ，将 变位词 组合在一起。 可以按任意顺序返回结果列表。
注意：若两个字符串中每个字符出现的次数都相同，则称它们互为变位词。

示例 1：
输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

示例 2：
输入: strs = [""]
输出: [[""]]

示例 3：
输入: strs = ["a"]
输出: [["a"]]

提示：
1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] 仅包含小写字母
 */

/**
 * 1、审题：输入一个字符串数组，要求找出数组中互为变位词的字符串，相同变位词的字符串放到一个数组中，最后合并到一起然后返回一个大的数组
 * 2、解题：
 * - 遍历字符串数组，遍历到的字符串，要查找是否已经存在互为变位词的字符串，需要使用map集合存储，key值为变位词，value为对应变位词存储的集合
 * - 如何高效的寻找到变位词呢？将字符串进行排序，只要是变位词排序后最终结果都一样
 */
vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    std::vector<std::vector<std::string>> res;
    std::map<std::string, std::vector<std::string>> map;

    for (std::string str : strs)
    {
        std::string sortStr = str;
        // 先进行排序
        std::sort(sortStr.begin(), sortStr.end());

        if (map.find(sortStr) == map.end()) // 不包含，则添加
        {
            std::vector<std::string> items;
            items.push_back(str);
            map[sortStr] = items;
        }
        else
        {
            // 包含，则取出value进行添加
            map[sortStr].push_back(str);
        }
    }

    // 将map中所有value取出来放到res中
    for (const auto &pair : map)
    {
        res.push_back(pair.second);
    }

    return res;
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