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
LCR 119. 最长连续序列
https://leetcode.cn/problems/WhsWhI/description/

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

示例 1：
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

示例 2：
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9

提示：
0 <= nums.length <= 104
-109 <= nums[i] <= 109

进阶：可以设计并实现时间复杂度为 O(n) 的解决方案吗？
 */

/**
 * leetcode题解思路：
 * - 找到增长序列的最小元素，然后不断从set集合中获取序列中的下一个元素，并随即更新序列的长度
 */
int longestConsecutive(vector<int> &nums)
{
    unordered_set<int> allSet;
    for (auto ele : nums)
    {
        allSet.insert(ele);
    }

    int res = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int currNum = nums[i];
        int currNumCount = 1;

        if (!allSet.count(currNum - 1)) // 找到序列中的最小的那个数
        {
            while (allSet.count(currNum + 1))
            {
                std::cout << "currNum:" << currNum << std::endl;
                currNum++;
                currNumCount++;
            }
            res = max(res, currNumCount);
        }
    }

    return res;
}

/**
 * 并查集解法：
 * - 先过滤重复元素，使用map保存每个元素的跟节点，然后再用map保存每个根节点元素对应的个数
 * - 对新数组中的元素进行并查集操作，元素之间相差1的节点合并到同一个子集中，对应的根节点元素和根节点对应的个数也随着合并操作而更新
 * - 两层for循环还是会超过时间限制，改为一层for循环，使用集合保存过滤后的数据，使用set保存数据
 */

int findFather2(std::map<int, int> &fathers, int i)
{
    if (fathers[i] == i)
    {
        return i; // 根节点是自己，返回去
    }
    int f = findFather2(fathers, fathers[i]);
    fathers[i] = f;
    return fathers[i];
}

bool merge3(std::map<int, int> &fathers, std::map<int, int> &fatherCountMap, int i, int j)
{
    int fI = findFather2(fathers, i);
    int fJ = findFather2(fathers, j);
    if (fI == fJ)
    {
        return false;
    }
    fatherCountMap[fI] += fatherCountMap[fJ];
    fathers[fJ] = fI;
    return true;
}

int longestConsecutive4(vector<int> &nums)
{
    std::map<int, int> fatherMap;
    std::map<int, int> fatherCountMap;
    std::set<int> all;
    for (auto ele : nums)
    {

        fatherMap[ele] = ele;
        fatherCountMap[ele] = 1;
        all.insert(ele);
    }

    int res = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int num = nums[i];
        // 判断当前遍历的元素， 在all集合中是否存在相差为1的元素，存在的话，则合并到一个子集中，并更新元素的个数
        if (all.count(num + 1)) // 存在
        {
            merge3(fatherMap, fatherCountMap, num, num + 1);
        }

        if (all.count(num - 1)) // 存在
        {
            merge3(fatherMap, fatherCountMap, num, num - 1);
        }
    }

    for (auto it : fatherCountMap)
    {
        std::cout << "fatherCountMap num:" << it.first << " ,count:" << it.second << std::endl;
        res = max(res, it.second);
    }

    return res;
}

bool merge2(std::map<int, int> &fathers, int i, int j)
{
    int fI = findFather2(fathers, i);
    int fJ = findFather2(fathers, j);
    if (fI == fJ)
    {
        return false;
    }

    fathers[fJ] = fI;
    return true;
}

int longestConsecutive3(vector<int> &nums)
{
    vector<int> newNums;
    for (auto num : nums)
    {
        if (std::find(newNums.begin(), newNums.end(), num) == newNums.end()) // 新数组中没有该元素，则添加
        {
            newNums.push_back(num);
        }
    }

    std::map<int, int> fatherMap;
    std::map<int, int> fatherCountMap;
    // 遍历1维数组
    for (auto ele : newNums)
    {
        std::cout << ele << ",";
        fatherMap[ele] = ele;
        fatherCountMap[ele] = 1;
    }
    std::cout << std::endl;

    int res = 0;
    for (int i = 0; i < newNums.size(); i++)
    {
        for (int j = i + 1; j < newNums.size(); j++)
        {
            int fatherI = findFather2(fatherMap, newNums[i]);
            int fatherJ = findFather2(fatherMap, newNums[j]);
            std::cout << "merge --------- i:" << i << " ,nums[i]:" << nums[i] << "  ,j:" << j << " , nums[j]:" << nums[j] << " , fatherJ:" << fatherJ << std::endl;
            // 判断他们是否相差一
            if ((newNums[i] - newNums[j] == 1 || newNums[i] - newNums[j] == -1) && merge2(fatherMap, newNums[i], newNums[j]))
            {
                fatherCountMap[fatherI] += fatherCountMap[fatherJ];
            }

            for (auto it : fatherCountMap)
            {
                std::cout << " num:" << it.first << " ,count:" << it.second << std::endl;
            }
        }
    }

    for (auto it : fatherCountMap)
    {
        std::cout << "fatherCountMap num:" << it.first << " ,count:" << it.second << std::endl;
        res = max(res, it.second);
    }

    return res;
}

/**
 * 使用广度优先算法实现
 * - 遍历数组中所有整数，过滤一遍，将相同的元素过滤只保留一个整数，保证过滤后的整数都不相同，不存在重复的数据
 * - 然后采用广度优先算法，每次从当前遍历的元素开始广度优先搜，寻找与当前元素差值为1的元素，并放到队列中去，寻找到了则序列长度增加1
 * == 结果会超出时间限制，还是要用并查集方法来处理，但必须先过滤一遍，保证处理的数组中不能有重复的元素
 */
int bfs(vector<int> newNums, int num)
{
    int count = 1;
    std::queue<int> queue;
    queue.push(num);
    // 先要把自己去掉
    auto it = std::find(newNums.begin(), newNums.end(), num);
    if (it != newNums.end()) // 存在，则添加到队列中，并且在数组中该元素也需要删除
    {
        newNums.erase(it);
    }

    while (!queue.empty())
    {
        int node = queue.front();
        queue.pop();

        int preNum = node - 1;
        it = std::find(newNums.begin(), newNums.end(), preNum);
        if (it != newNums.end()) // 存在，则添加到队列中，并且在数组中该元素也需要删除
        {
            queue.push(preNum);
            newNums.erase(it);
            count++;
        }

        int nextNum = node + 1;
        it = std::find(newNums.begin(), newNums.end(), nextNum);
        if (it != newNums.end()) // 存在，则添加到队列中，并且在数组中该元素也需要删除
        {
            queue.push(nextNum);
            newNums.erase(it);
            count++;
        }
    }
    return count;
}

int longestConsecutive2(vector<int> &nums)
{
    vector<int> newNums;
    for (auto num : nums)
    {
        if (std::find(newNums.begin(), newNums.end(), num) == newNums.end()) // 新数组中没有该元素，则添加
        {
            newNums.push_back(num);
        }
    }

    // 遍历1维数组
    for (auto ele : newNums)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    // 遍历 newNums 中的元素，以当前遍历元素为起点开始bfs，
    int res = 0;
    for (int i = 0; i < newNums.size(); i++)
    {
        int count = bfs(newNums, newNums[i]);
        std::cout << "bfs newNums[i]:" << newNums[i] << " ,count:" << count << std::endl;
        res = max(res, count);
    }

    return res;
}

/**
 * 1、审题：输入一个整数数组，要求找出所有整数组成的连续序列的最长序列，并返回最长序列的长度
 * 2、解题：并查集解法
 * - 先使用双层for循环，使的每个元素，都能与后面的元素进行判断比对，找到与外层循环元素，绝对值相差为1的元素，将他们放到同一个子集中
 * - 并最后求最长子集的个数并返回
 * - 需要新增一个map<int,vector<int>> map,集合用于判断同一个根节点下是否有相同的元素，如果已经有相同的元素了，则不添加到集合中来了
 */
int findFather(vector<int> &fathers, int i)
{
    if (fathers[i] == i)
    {
        return i; // 根节点是自己，返回去
    }
    int f = findFather(fathers, fathers[i]);
    fathers[i] = f;
    return fathers[i];
}

bool merge(vector<int> &fathers, int i, int j)
{
    int fI = findFather(fathers, i);
    int fJ = findFather(fathers, j);
    if (fI == fJ)
    {
        return false;
    }

    fathers[fJ] = fI;
    return true;
}

int longestConsecutive1(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
    {
        return 0;
    }

    vector<int> fathers(n, 0);
    std::map<int, int> rootNumMap;            // 根节点，对应的子集个数
    std::map<int, vector<int>> rootValuesMap; // 根节点，对应的子集集合
    for (int i = 0; i < n; i++)
    {
        fathers[i] = i;
        rootNumMap[i] = 1;
        vector<int> values;
        values.push_back(nums[i]);
        rootValuesMap[i] = values;
    }

    int res = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            std::cout << "for for i:" << i << " ,nums[i]:" << nums[i] << "  ,j:" << j << " , nums[j]:" << nums[j] << std::endl;

            if (nums[i] == nums[j])
            {
                merge(fathers, i, j);
                continue;
            }

            int fI = findFather(fathers, i);
            int fJ = findFather(fathers, j);
            if ((nums[i] - nums[j] == 1 || nums[i] - nums[j] == -1) && fI != fJ)
            {
                std::cout << "merge --------- :" << i << " ,nums[i]:" << nums[i] << "  ,j:" << j << " , nums[j]:" << nums[j] << std::endl;
                std::vector<int> valuesFI = rootValuesMap[fI];
                std::vector<int> valuesFJ = rootValuesMap[fJ];

                fathers[fJ] = fI;
                rootNumMap[fI] += rootNumMap[fJ];
                if (std::find(valuesFI.begin(), valuesFI.end(), nums[j]) != valuesFI.end()) // 之前子集中有这个元素存在，则需要将根节点的个数减少1，并且更新rootMap集合的数据
                {
                    rootNumMap[fI]--;
                }

                // 更新 rootValuesMap 的集合,将fJ中的添加到fI的集合中去
                for (auto value : valuesFJ)
                {
                    valuesFI.push_back(value);
                }
                rootValuesMap[fI] = valuesFI;

                for (auto it : rootNumMap)
                {
                    std::cout << " i:" << it.first << " ,num:" << it.second << std::endl;
                }
            }
        }
    }

    for (auto it : rootNumMap)
    {
        std::cout << " i:" << it.first << " ,num:" << it.second << std::endl;
        res = max(res, it.second);
    }

    return res;
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    vector<string> words = {"tars", "rats", "arts", "star"};

    // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    // vector<vector<int>> prerequisites = {
    //     {1, 0},
    //     {2, 0},
    //     {3, 1},
    //     {3, 2},
    // };

    // vector<int> nums = {1, 2, 3};
    // vector<vector<int>> isConnected = {
    //     {1, 0, 0, 1},
    //     {0, 1, 1, 0},
    //     {0, 1, 1, 1},
    //     {1, 0, 1, 1},
    // };
    // vector<vector<int>> isConnected = {
    //     {1, 1, 0},
    //     {1, 1, 0},
    //     {0, 0, 1},
    // };

    vector<int> nums = {100, 4, 200, 1, 3, 2};
    // vector<int> nums = {4, 0, -4, -2, 2, 5, 2, 0, -8, -8, -8, -8, -1, 7, 4, 5, 5, -4, 6, 6, -3};
    auto res = longestConsecutive(nums);
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