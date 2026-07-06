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
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LCR 106. 判断二分图
https://leetcode.cn/problems/vEAB3K/description/

存在一个 无向图 ，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。
给定一个二维数组 graph ，表示图，其中 graph{u} 是一个节点数组，由节点 u 的邻接节点组成。形式上，对于 graph{u} 中的每个 v ，都存在一条位于节点 u 和节点 v 之间的无向边。该无向图同时具有以下属性：
不存在自环（graph{u} 不包含 u）。
不存在平行边（graph{u} 不包含重复值）。
如果 v 在 graph{u} 内，那么 u 也应该在 graph{v} 内（该图是无向图）
这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。
二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 二分图 。
如果图是二分图，返回 true ；否则，返回 false 。

示例 1：

输入：graph = {{1,2,3},{0,2},{0,1,3},{0,2}}
输出：false
解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。

示例 2：
输入：graph = {{1,3},{0,2},{1,3},{0,2}}
输出：true
解释：可以将节点分成两组: {0, 2} 和 {1, 3} 。

提示：
graph.length == n
1 <= n <= 100
0 <= graph{u}.length < n
0 <= graph{u}{i} <= n - 1
graph{u} 不会包含 u
graph{u} 的所有值 互不相同
如果 graph{u} 包含 v，那么 graph{v} 也会包含 u
 */

/**
 * 之前的实现逻辑有个漏洞，就是没加入集合中的元素默认添加到集合A中，其实也可以添加到集合B中去。
 * - 可以采用广度优先遍历算法 + 标记法处理
 * - 广度优先搜索算法，采用队列queue保存元素，采用二维数组visited保存遍历标记
 * - 采用color二维数组标记存放到集合A（-1）与存放到集合B（1）的选择，默认是（0）值还没有分配
 * - 在广度优先搜索算法的过程中，判断当前遍历的元素保存在那个集合中，如果当前元素在集合A中，那与之链接的节点要么还没有分配（-1值），要么已在集合B中，如果已分配在集合A中了，那就不匹配了，直接返回false，反面情况类似思路处理
 */

bool bfs(vector<vector<int>> &graph, vector<bool> &visited, vector<int> &colors, int m)
{
    queue<int> queue;
    queue.push(m);
    visited[m] = true;

    while (!queue.empty())
    {
        int i = queue.front();
        queue.pop();

        if (graph[i].size() == 0)
        {
            continue;
        }

        // 遍历当前节点，所有的关联节点，添加判断他存放的集合位置
        for (int j = 0; j < graph[i].size(); j++)
        {
            int k = graph[i][j];
            std::cout << "i:" << i << "  ,k:" << k << std::endl;

            if (colors[i] == colors[k]) // 当前节点i，与关联节点k，存在相同的集合中，不符合题目要求
            {
                return false;
            }

            if (colors[k] == 0) // 未分配节点，分配到与当前节点对应的集合中去
            {
                colors[k] = 0 - colors[i];
            }

            if (visited[k])
            {
                continue;
            }

            for (auto ele : colors)
            {
                std::cout << ele << ",";
            }
            std::cout << std::endl;

            visited[k] = true;
            queue.push(k);
        }
    }

    return true;
}

/**
 * graph是链接表
 * - 不适合使用二维矩阵
 */
bool isBipartite(vector<vector<int>> &graph)
{
    int m = graph.size();
    vector<bool> visited(m, false);
    vector<int> colors(m, 0);

    for (int i = 0; i < m; i++)
    {
        if (!visited[i] && graph[i].size() > 0)
        {
            colors[i] = 1;
            bool res = bfs(graph, visited, colors, i); // 一个区域命中还不够，还所有的都命中才行
            if (!res)
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * 1、审题：输入一个二维数组，表示图结构，使用的数据结构是邻接表，每个节点关联的所有节点放到一个集合中
 * - 现在要将所有的节点分开成两个集合阵营set，要求一条边的两个节点，一个节点在集合A中，另一个节点在集合B中，
 * - 如果所有的节点都能按照这个规则拆分成两个集合，则返回true，否则返回false
 * 2、解题：
 * - 新建两个vector集合 setA，setB，用于保存节点需要存储的阵营
 * - 遍历所有的节点
 * -- 如果当前结合，在两个集合中都不存在，在默认将该节点添加到集合A中去，然后其他与之关联的节点存放到集合B中去
 * -- 如果当前节点存在集合A中，其他节点就需要保存到集合B中去，如果发现关联节点已经保存到集合A中去了，则与题意不符合，返回false
 * -- 相反，如果当前遍历的节点已经在集合B中了，则与之关联的节点应该保存到集合A中去，如果关联的节点已经保存到集合B中了，与题意不符合，返回false
 * - 最后返回true
 */
// bool isBipartite1(vector<vector<int>> &graph)
// {
//   vector<int> setA{};
//   vector<int> setB{};

//   /**
//    * 新家一个方法，用于判断元素ele是否在集合vector中
//    * - 存在的话，则返回true，否则返回false
//    * - 内部使用find 函数
//    */
//   auto contains = {}(const vector<int> &vec, const int &target)
//   {
//     auto it = std::find(vec.begin(), vec.end(), target);
//     if (it != vec.end()) // target值在集合vec中存在
//     {
//       return true;
//     }
//     return false;
//   };

//   int m = graph.size();
//   for (int i = 0; i < m; i++)
//   {
//     int type = 0;
//     if (!contains(setA, i) && !contains(setB, i)) // 两个集合中都不存在
//     {
//       type = 0;
//       setA.push_back(i);
//     }
//     else if (contains(setA, i)) // 当前节点存在于集合A中
//     {
//       type = 1;
//     }
//     else if (contains(setB, i)) // 当前节点存在于集合B中
//     {
//       type = 2;
//     }

//     int n = graph{i}.size();
//     for (int j = 0; j < n; j++)
//     {
//       if (type == 0) // 这里有问题，可以放到集合A中，也可以放到集合B中去，还是要用广度优先搜索算法来实现
//       {
//         setB.push_back(graph{i} {j});
//         continue;
//       }

//       if (type == 1)
//       {
//         if (contains(setA, graph{i} {j})) // 遍历节点在集合A中，关联节点也在集合A中，不符合要求
//         {
//           return false;
//         }
//         if (!contains(setB, graph{i} {j}))
//         {
//           setB.push_back(graph{i} {j});
//         }
//         continue;
//       }

//       if (type == 2)
//       {
//         if (contains(setB, graph{i} {j})) // 遍历节点在集合B中，关联节点也在集合B中，不符合要求
//         {
//           return false;
//         }
//         if (!contains(setA, graph{i} {j}))
//         {
//           setA.push_back(graph{i} {j});
//         }
//         continue;
//       }
//     }
//   }

//   return true;
// }

int main()
{
    std::cout << "《剑指》" << std::endl;

    /**
     * 输入：graph = {{1,2,3},{0,2},{0,1,3},{0,2}}
  输出：false
  解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。

  示例 2：
  输入：graph = {{1,3},{0,2},{1,3},{0,2}}
     */

    // vector<vector<int>> grid = {
    //     {1, 2, 3},
    //     {0, 2},
    //     {0, 1, 3},
    //     {0, 2}};
    // vector<vector<int>> grid = {
    //     {1, 3},
    //     {0, 2},
    //     {1, 3},
    //     {0, 2}};

    vector<vector<int>> grid = {
        {2, 4},
        {2, 3, 4},
        {0, 1},
        {1},
        {0, 1},
        {7},
        {9},
        {5},
        {},
        {6},
        {12, 14},
        {},
        {10},
        {},
        {10},
        {19},
        {18},
        {},
        {16},
        {15},
        {23},
        {23},
        {},
        {20, 21},
        {},
        {},
        {27},
        {26},
        {},
        {},
        {34},
        {33, 34},
        {},
        {31},
        {30, 31},
        {38, 39},
        {37, 38, 39},
        {36},
        {35, 36},
        {35, 36},
        {43},
        {},
        {},
        {40},
        {},
        {49},
        {47, 48, 49},
        {46, 48, 49},
        {46, 47, 49},
        {45, 46, 47, 48},
    };

    auto res = isBipartite(grid);
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
    //     for (auto element : ele)
    //     {
    //         std::cout << element << ",";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}