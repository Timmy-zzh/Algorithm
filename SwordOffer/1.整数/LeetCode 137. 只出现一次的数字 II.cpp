#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <queue>
#include "src/bean.h"
#include <random>
#include <algorithm>
#include <unordered_set>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。写就是思考
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
137. 只出现一次的数字 II
https://leetcode.cn/problems/single-number-ii/description/

给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。

示例 1：
输入：nums = [2,2,3,2]
输出：3

示例 2：
输入：nums = [0,1,0,1,0,1,99]
输出：99

提示：
1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
 */

/**
 * 1、审题：
 * - 输入一个整数数组，数组中的整数每个数字都出现了三次，但其中有个数字只出现了一次，现在要求找出这个只出现一次的数字并返回
 * 2、解题：二进制记录法
 * - 每个整数int类型大小是4个字节也就是32位，使用一个32长度的整数数组用来保存数组中所有数字的二进制的累计和
 * - 如果一个数字在数组中出现了三次，那在某个二进制位中他的累计和要么等于3，要么等于0，可将该累加和求3的余数，他们肯定都是0
 * - 采用这种思路，将数组中所有数字的二进制的每个位置的值进行累加起来，再与3求余数，得到的余数组合起来，就是那个单独出现一次数组的二进制
 */
int singleNumber1(vector<int> &nums)
{
    // 创建一个32长度的int数组
    vector<int> arr(32, 0);
    int res = 0;

    // 对数组中每个数字，都去找到他们二进制对应32个位置的数值，并累加起来
    for (int i = 0; i < nums.size(); i++)
    {
        int num = nums[i];
        for (int j = 0; j < 32; j++)
        {
            arr[32 - j - 1] += (num >> j) & 1;
        }
    }

    // 取出32位数组中每个位置的二进制累加和，与3相除取余数，
    for (int j = 0; j < 32; j++)
    {
        res = (res << 1) + (arr[j] % 3);
    }

    return res;
}

/**
 * 使用map保存每个数字出现的次数，最后找出出现一次的数字并返回
 */
int singleNumber(vector<int> &nums)
{
    // 创建一个32长度的int数组
    std::map<int, int> map;
    int res = 0;

    // 对数组中每个数字，都去找到他们二进制对应32个位置的数值，并累加起来
    for (int i = 0; i < nums.size(); i++)
    {
        int num = nums[i];
        if (map.find(num) == map.end()) // 不存在
        {
            map[num] = 1;
        }
        else
        {
            map[num] = map[num] + 1;
        }
    }

    for (auto it : map)
    {
        if (it.second == 1)
        {
            return it.first;
        }
    }
    return res;
}

int main()
{
    std::cout << "《剑指》" << std::endl;
    vector<int> nums = {0, 1, 0, 1, 0, 1, 100};
    auto res = singleNumber(nums);
    std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    // for (auto ele : res)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    // 遍历2维数组
    // for (vector<int> ele : res)
    // {
    //   for (auto element : ele)
    //   {
    //     std::cout << element << ",";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "map +++++++++++++++ " << std::endl;
    // for (auto ele : map)
    // {
    //   std::cout << ele.first << " ---- nextNodes: " << std::endl;
    //   for (auto ele : ele.second)
    //   {
    //     std::cout << ele;
    //     std::cout << std::endl;
    //   }

    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "inDegreeMap ============ " << std::endl;
    // for (auto ele : inDegreeMap)
    // {
    //   std::cout << ele.first << " ---- " << ele.second;
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}