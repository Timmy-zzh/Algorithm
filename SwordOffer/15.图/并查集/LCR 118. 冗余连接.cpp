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
LCR 118. 冗余连接
https://leetcode.cn/problems/7LpjUW/description/

树可以看成是一个连通且 无环 的 无向 图。
给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。
图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。
请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的边。

示例 1：
输入: edges = [[1,2],[1,3],[2,3]]
输出: [2,3]

示例 2：
输入: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
输出: [1,4]

提示:
n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
edges 中无重复元素
给定的图是连通的
 */

/**
 * 1、审题：输入一个长度为n的边的数组，表示n个节点之间存在的连接关系，本来n个节点的结构是一颗树结构
 * - 但是中间的一条边导致树结构中存在了环，现在要找出这条边并返回
 * 2、解题：并查集方法
 * - 遍历edges边的结合，每条边相连，就把他们归拢到一个子集中去，就是设置他们的根节点相同，
 * - 如果遇到一个边上的两个节点，他们已经都属于同一个子集中了，那这条边就是多出来导致环的那条边。找到他并返回
 * - 如果有多条这样的边，返回最后一条
 */

int findFather(vector<int> &fathers, int i)
{
    if (fathers[i] == i)
    {
        return i;
    }
    int father = findFather(fathers, fathers[i]);
    fathers[i] = father;
    return fathers[i];
}

vector<int> findRedundantConnection(vector<vector<int>> &edges)
{
    vector<int> resArr;
    int n = edges.size();

    // 给n个节点设置他的根节点为自身
    vector<int> fathers(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        fathers[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        vector<int> edge = edges[i];

        // 找到边上两个节点的根节点
        int father1 = findFather(fathers, edge[0]);
        int father2 = findFather(fathers, edge[1]);

        if (father1 == father2)
        {
            resArr = edge;
        }
        else
        {
            // 合并
            fathers[father2] = father1;
        }
    }

    return resArr;
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

    // auto res = numSimilarGroups(words);
    // std::cout << "res:" << res << std::endl;

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