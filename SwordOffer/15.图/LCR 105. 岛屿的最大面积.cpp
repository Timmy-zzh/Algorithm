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
LCR 105. 岛屿的最大面积
https://leetcode.cn/problems/ZL6zAn/description/

给定一个由 0 和 1 组成的非空二维数组 grid ，用来表示海洋岛屿地图。
一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
找到给定的二维数组中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。

示例 1：
输入: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
输出: 6
解释: 对于上面这个给定矩阵应返回 6。注意答案不应该是 11 ，因为岛屿只能包含水平或垂直的四个方向的 1 。

示例 2：
输入: grid = [[0,0,0,0,0,0,0,0]]
输出: 0

提示：
m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] is either 0 or 1
注意：本题与主站 695 题相同： https://leetcode.cn/problems/max-area-of-island/
 */

/**
 * 1、审题：输入一个二维矩阵，矩阵中的元素是数字0和1；1表示陆地，0表示海洋，多个1链接在一起组成岛屿
 * - 现在要求最大岛屿的面积
 * 2、解题：图的广度优先遍历解法
 * - 遍历矩阵中的每个元素，只要这个元素是陆地，且之前没有访问过，则以这个元素为起点，去求和这个陆地所有相连的陆地的总面积
 * - 使用二位矩阵来保存元素是否访问过，如果之前访问过则过滤掉
 * - 使用广度优先遍历来求岛屿的面积，需要使用先进先出的队列来保存遍历的元素，然后在遍历的过程中记录元素的个数，累加起来就是岛屿的面积了
 */

/**
 * 还可以使用深度优先遍历方法来实现：
 * - 通过递归来实现，根据当前遍历的节点，遍历上下左右四个方向位置的节点，是否也是陆地，是的话，继续按照当前的查询方式，不断扩张陆地面积
 */
void getArea(int m, int n, vector<vector<int>> &grid, vector<vector<bool>> &visited, int i, int j, int &itemArea)
{
    if (visited[i][j])
    {
        return;
    }

    visited[i][j] = true;
    itemArea++;

    // 然后查找上下左右四个方向的位置元素，
    // 判断是否遍历过，是否是陆地，是否有越界，满足条件插入到队列的末尾

    // 上
    if (i - 1 >= 0 && visited[i - 1][j] == false && grid[i - 1][j] == 1)
    {
        getArea(m, n, grid, visited, i - 1, j, itemArea);
    }

    // 下
    if (i + 1 < m && visited[i + 1][j] == false && grid[i + 1][j] == 1)
    {
        getArea(m, n, grid, visited, i + 1, j, itemArea);
    }

    // 左
    if (j - 1 >= 0 && visited[i][j - 1] == false && grid[i][j - 1] == 1)
    {
        getArea(m, n, grid, visited, i, j - 1, itemArea);
    }

    // 右
    if (j + 1 < n && visited[i][j + 1] == false && grid[i][j + 1] == 1)
    {
        getArea(m, n, grid, visited, i, j + 1, itemArea);
    }
}

/**
 * 广度优先遍历
 * - 使用队列，vected
 */
void getArea1(int m, int n, vector<vector<int>> &grid, vector<vector<bool>> &visited, int i, int j, int &itemArea)
{
    queue<vector<int>> queue;
    queue.push({i, j});

    while (!queue.empty())
    {
        // 取出队列中的位置
        auto node = queue.front();
        queue.pop();
        int i = node[0];
        int j = node[1];
        if (visited[i][j])
        {
            continue;
        }

        visited[i][j] = true;
        itemArea++;

        // 然后查找上下左右四个方向的位置元素，
        // 判断是否遍历过，是否是陆地，是否有越界，满足条件插入到队列的末尾

        // 上
        if (i - 1 >= 0 && visited[i - 1][j] == false && grid[i - 1][j] == 1)
        {
            queue.push({i - 1, j});
        }

        // 下
        if (i + 1 < m && visited[i + 1][j] == false && grid[i + 1][j] == 1)
        {
            queue.push({i + 1, j});
        }

        // 左
        if (j - 1 >= 0 && visited[i][j - 1] == false && grid[i][j - 1] == 1)
        {
            queue.push({i, j - 1});
        }

        // 右
        if (j + 1 < n && visited[i][j + 1] == false && grid[i][j + 1] == 1)
        {
            queue.push({i, j + 1});
        }
    }
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int resArea = 0;
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                int itemArea = 0;
                getArea(m, n, grid, visited, i, j, itemArea);
                std::cout << "i:" << i << " ,j:" << j << " ,itemArea:" << itemArea << "," << std::endl;
                resArea = max(resArea, itemArea);
            }
            visited[i][j] = true;
        }
    }
    return resArea;
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    // vector<vector<int>> grid = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    //                             {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    //                             {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    //                             {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
    //                             {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
    //                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    //                             {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    //                             {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};

    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}};

    auto res = maxAreaOfIsland(grid);
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