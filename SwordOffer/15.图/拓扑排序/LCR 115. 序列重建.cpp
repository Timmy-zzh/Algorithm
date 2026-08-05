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
LCR 115. 序列重建
https://leetcode.cn/problems/ur2n8P/description/

给定一个长度为 n 的整数数组 nums ，其中 nums 是范围为 [1，n] 的整数的排列。还提供了一个 2D 整数数组 sequences ，其中 sequences[i] 是 nums 的子序列。
检查 nums 是否是唯一的最短 超序列 。最短 超序列 是 长度最短 的序列，并且所有序列 sequences[i] 都是它的子序列。对于给定的数组 sequences ，可能存在多个有效的 超序列 。

例如，对于 sequences = [[1,2],[1,3]] ，有两个最短的 超序列 ，[1,2,3] 和 [1,3,2] 。
而对于 sequences = [[1,2],[1,3],[1,2,3]] ，唯一可能的最短 超序列 是 [1,2,3] 。[1,2,3,4] 是可能的超序列，但不是最短的。
如果 nums 是序列的唯一最短 超序列 ，则返回 true ，否则返回 false 。
子序列 是一个可以通过从另一个序列中删除一些元素或不删除任何元素，而不改变其余元素的顺序的序列。

示例 1：
输入：nums = [1,2,3], sequences = [[1,2],[1,3]]
输出：false
解释：有两种可能的超序列：[1,2,3]和[1,3,2]。
序列 [1,2] 是[1,2,3]和[1,3,2]的子序列。
序列 [1,3] 是[1,2,3]和[1,3,2]的子序列。
因为 nums 不是唯一最短的超序列，所以返回false。

示例 2：
输入：nums = [1,2,3], sequences = [[1,2]]
输出：false
解释：最短可能的超序列为 [1,2]。
序列 [1,2] 是它的子序列：[1,2]。
因为 nums 不是最短的超序列，所以返回false。

示例 3：
输入：nums = [1,2,3], sequences = [[1,2],[1,3],[2,3]]
输出：true
解释：最短可能的超序列为[1,2,3]。
序列 [1,2] 是它的一个子序列：[1,2,3]。
序列 [1,3] 是它的一个子序列：[1,2,3]。
序列 [2,3] 是它的一个子序列：[1,2,3]。
因为 nums 是唯一最短的超序列，所以返回true。

提示：
n == nums.length
1 <= n <= 104
nums 是 [1, n] 范围内所有整数的排列
1 <= sequences.length <= 104
1 <= sequences[i].length <= 104
1 <= sum(sequences[i].length) <= 105
1 <= sequences[i][j] <= n
sequences 的所有数组都是 唯一 的
sequences[i] 是 nums 的一个子序列
 */

/**
 * 1、审题：输入一个整数数组nums，和一个二维数组 sequences,现在要判断sequences中的每个元素，也就是单个数组都是nums的子序列
 * - 也就是按照nums的部分有序的序列元素可以组成 sequences 中的数组元素，问nums满足二维数组中元素的序列的条件时，是否最短
 * 2、解题： 之前都是根据零散的元素，来找关系（路径），现在是知道了他们的关系，求提供的路径是否是最短的
 * - 还是用拓扑排序算法，根据 sequences 求所有数组满足条件的拓扑关系，而且是一个一个的单向关系节点连接起来的拓扑关系
 * - 把求到的拓扑关系和题目给出的nums长度做比较，
 * - 遍历 sequences， 内层for循环遍历其中的单个数组，根据数组中元素的前后顺序关系，去查找他们的关系，使用map<int,vecotr<int>> 保存节点之前的有向图的关系
 * - 然后根据有向图，求他们的入度，然后根据有向图和入度，求他们的拓扑序列结果，
 * - 求他的拓扑序列结果是否只有一个，且最短的那个和题目提供的nums是否相同，并将结果返回
 */
bool sequenceReconstruction(vector<int> &nums, vector<vector<int>> &sequences)
{
    // 遍历 sequences 拿出内部的单个数组进行遍历，并且根据数组中元素的前后关系，构建当前元素指向下一个节点元素的集合，
    std::map<int, vector<int>> map; // 当前节点key，指向下一节点的集合
    std::map<int, int> inDegreeMap; // 入度
    queue<int> queue;
    vector<int> resPath;

    for (int i = 0; i < sequences.size(); i++)
    {
        vector<int> items = sequences[i];
        if (items.size() == 1)
        {
            // 只有一个元素
            int prev = items[0];
            if (map.find(prev) == map.end()) // map集合中不包含key值，则添加value值为 数组
            {
                vector<int> nextNodes;
                map[prev] = nextNodes;
            }
            inDegreeMap[prev] = 0;
        }
        else
        {

            for (int j = 0; j < items.size() - 1; j++)
            {
                int prev = items[j];
                int next = items[j + 1];
                if (map.find(prev) == map.end()) // map集合中不包含key值，则添加value值为 数组
                {
                    vector<int> nextNodes;
                    nextNodes.push_back(next);
                    map[prev] = nextNodes;
                }
                else
                {
                    // 取出来再添加
                    map[prev].push_back(next);
                }

                inDegreeMap[prev] = 0;
                inDegreeMap[next] = 0;
            }
        }
    }

    // 再根据元素节点间关系，构建他们的入度关系，并将入度为0的节点添加到队列中
    for (auto it : map)
    {
        int key = it.first;
        vector<int> value = it.second;
        for (auto next : value)
        {
            inDegreeMap[next]++;
        }
    }

    // 遍历1维数组

    std::cout << "map +++++++++++++++ " << std::endl;
    for (auto ele : map)
    {
        std::cout << ele.first << " ---- nextNodes: " << std::endl;
        for (auto ele : ele.second)
        {
            std::cout << ele;
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "inDegreeMap ============ " << std::endl;
    for (auto ele : inDegreeMap)
    {
        std::cout << ele.first << " ---- " << ele.second;
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (auto it : inDegreeMap)
    {
        if (it.second == 0)
        {
            queue.push(it.first);
        }
    }

    if (queue.size() != 1)
    {
        return false;
    }

    // 遍历队列，不断从队列中取出入度为0的节点，得到节点的集合
    while (!queue.empty())
    {
        auto node = queue.front();
        queue.pop();
        resPath.push_back(node);

        std::cout << "while (!queue  ---- " << node << std::endl;

        // 找到node节点的下一个节点的集合，遍历他并减少他们的入度
        vector<int> nodes = map[node];
        for (auto neigNode : nodes)
        {
            inDegreeMap[neigNode]--;

            if (inDegreeMap[neigNode] == 0)
            {
                queue.push(neigNode);
            }
        }

        // 如何判断，当前遍历的节点是否是最后一个？
        if (queue.size() > 1)
        {
            std::cout << "queue.size() != 1 =========== " << node << std::endl;
            return false;
        }
    }
    // 遍历1维数组
    for (auto ele : resPath)
    {
        std::cout << ele << ",";
    }
    std::cout << std::endl;

    // 题目要求是nums是唯一的拓扑系列，要求他的下一个节点只能有一个节点
    return resPath.size() == nums.size();
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    // vector<vector<int>> graph = {
    //     {1, 2},
    //     {3},
    //     {3},
    //     {},
    // };

    /**
  输入: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
  输出: [0,1,2,3] or [0,2,1,3]
     */

    // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
    // vector<string> words = {"z", "x", "z"};
    // vector<string> words = {"z", "z"};
    // vector<string> words = {"zy", "zx"};
    // vector<string> words = {"wrt", "wrtkj"};
    vector<string> words = {"ac", "ab", "b"};

    // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)

    // vector<vector<int>> prerequisites = {
    //     {1, 0},
    //     {2, 0},
    //     {3, 1},
    //     {3, 2},
    // };

    //  nums = [1,2,3], sequences = [[1,2],[1,3],[2,3]]
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> sequences = {{1, 2}, {1, 3}, {2, 3}};
    auto res = sequenceReconstruction(nums, sequences);
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

    return 0;
}