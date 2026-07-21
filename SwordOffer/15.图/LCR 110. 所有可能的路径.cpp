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
LCR 110. 所有可能的路径
https://leetcode.cn/problems/bP4bmD/description/

给定一个有 n 个节点的有向无环图，用二维数组 graph 表示，请找到所有从 0 到 n-1 的路径并输出（不要求按顺序）。
graph 的第 i 个数组中的单元都表示有向图中 i 号节点所能到达的下一些结点（译者注：有向图是有方向的，即规定了 a→b 你就不能从 b→a ），若为空，就是没有下一个节点了。

示例 1：
输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3

示例 2：
输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

示例 3：
输入：graph = [[1],[]]
输出：[[0,1]]

示例 4：
输入：graph = [[1,2,3],[2],[3],[]]
输出：[[0,1,2,3],[0,2,3],[0,3]]

示例 5：
输入：graph = [[1,3],[2],[3],[]]
输出：[[0,1,2,3],[0,3]]

提示：
n == graph.length
2 <= n <= 15
0 <= graph[i][j] < n
graph[i][j] != i
保证输入为有向无环图 (GAD)
 */

/**
 * 1、审题：输入一个有向无环图，使用的结构是邻接表，每个节点都指向他连接的随后节点的数组
 * - 现在要求从第一个节点0开始到最后节点n-1的所有路径的集合并返回
 * 2、解题：广度优先算法 bfs
 * - 从开始节点开始不断往后续节点开始扩展，并保存在队列中，并不断填充到路径队列中去
 * - 不行，要使用dfs深度优先算法，加上回溯算法
 */

void helper(vector<vector<int>> &graph, vector<vector<int>> &resPaths, int n, vector<int> &path, int i)
{
    if (i == n - 1)
    {
        vector<int> newPath(path);
        resPaths.push_back(newPath);
        return;
    }

    vector<int> linkNodes = graph[i];

    // 遍历map
    // std::cout << i << " ---> " << std::endl;
    // for (auto ele : linkNodes)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    // std::cout << i << " path ---> " << std::endl;
    // for (auto ele : path)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    for (auto node : linkNodes)
    {
        path.push_back(node);
        helper(graph, resPaths, n, path, node);
        path.pop_back();
    }
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
{
    vector<vector<int>> resPaths;
    vector<int> path{0};
    int n = graph.size();

    helper(graph, resPaths, n, path, 0);

    return resPaths;
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    vector<vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {},
    };
    // vector<string> wordList = {"0201", "0101", "0102", "1212", "2002"};
    // vector<string> wordList = {"8888"};

    auto res = allPathsSourceTarget(graph);
    // std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    // for (auto ele : res)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    // 遍历2维数组
    for (vector<int> ele : res)
    {
        for (auto element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}