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
LCR 107. 01 矩阵
https://leetcode.cn/problems/2bCMpM/description/

给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
两个相邻元素间的距离为 1。

示例 1：
输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]

示例 2：
输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]

提示：
m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] is either 0 or 1.
mat 中至少有一个 0
 */

/**
 * 1、审题：输入一个二维矩阵，矩阵中的元素由0和1组成，其中的一个元素到上下左右位置的距离是1，现在要输出一个与mat原始数组相同大小的数组，
 * - 要求新数组grid中的元素是原始数组mat中元素位置，到距离最新的元素0的位置的距离值。
 * 2、解题：广度优先算法
 * - 遍历原始数组mat，对于遍历到的每个位置的元素，去四周查找元素值为0的距离，使用广度优先搜索算法，不断将上下左右位置的找出来
 * - 如果遇到元素值为0的元素，则停止广度搜索，将距离该位置的距离直接返回即可
 * = 还可以使用递归算法
 * = 再尝试深度优先算法
 */

int getDistance(vector<vector<int>> &mat, int x, int y)
{

  int m = mat.size();
  int n = mat[0].size();
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  std::cout << "x:" << x << " ,y:" << y << std::endl;

  for (vector<int> ele : mat)
  {
    for (auto element : ele)
    {
      std::cout << element << ",";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  queue<vector<int>> queue;
  queue.push({x, y});
  visited[x][y] = true;

  queue.push({-1, -1});
  int distance = 1;

  vector<vector<int>> dirs = {
      {0, -1}, // 左
      {0, 1},  // 右
      {-1, 0}, // 上
      {1, 0},  // 下
  };

  while (!queue.empty())
  {
    vector<int> pos = queue.front();
    queue.pop();

    std::cout << "==== pos[0]:" << pos[0] << " ,pos[1]:" << pos[1] << std::endl;
    if (pos[0] == -1 && pos[1] == -1)
    {
      distance++;
      std::cout << "<<< queue.push({-1, -1});" << std::endl;
      queue.push({-1, -1});
      continue;
    }

    // 遍历上下左右的四个位置的元素
    for (int i = 0; i < dirs.size(); i++)
    {
      int r = pos[0] + dirs[i][0];
      int c = pos[1] + dirs[i][1];

      if (r >= 0 && r < m && c >= 0 && c < n)
      {
        std::cout << "x:" << x << " ,y:" << y << " ,r:" << r << " ,c:" << c << std::endl;
        if (visited[r][c])
        {
          continue;
        }
        visited[r][c] = true;

        if (mat[r][c] == 1)
        {
          std::cout << "x:" << x << " ,y:" << y << " ,r:" << r << " ,c:" << c << " ,queue.push({r, c}); " << " ,distance:" << distance << std::endl;
          queue.push({r, c});
        }
        else
        {
          std::cout << "---- x:" << x << " ,y:" << y << " ,r:" << r << " ,c:" << c << " ,distance:" << distance << std::endl;
          return distance;
        }
      }
    }
  }

  return distance;
}

vector<vector<int>> updateMatrix1(vector<vector<int>> &mat)
{
  int m = mat.size();
  int n = mat[0].size();

  vector<vector<int>> grid(m, vector<int>(n, 0));

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (mat[i][j] == 1)
      {
        grid[i][j] = getDistance(mat, i, j);

        for (vector<int> ele : grid)
        {
          for (auto element : ele)
          {
            std::cout << element << ",";
          }
          std::cout << std::endl;
        }
        std::cout << std::endl;
      }
    }
  }
  return grid;
}

/**
 * 1、上面的解题思路，是遍历所有的元素值为1的点，从该点开始进行广度优先搜索算法，不断将周围的元素值为1的节点添加到队列中来
 * - 每次向外围广度扩散查询时，距离开始遍历节点的锚点值距离就加1；直到遇到元素值为0的节点，才停止，并返回当前距离值
 * - 那如何直到当前周围一圈，也就是同一个距离的节点都遍历完成了呢？通过插入特殊节点值来判断，每当同距离的一圈节点值遍历完成后，就插入一个新的特殊节点值。
 * - 并且为了过滤重复节点的遍历，需要使用visited数组来记录遍历过的值 bool值保存
 * = 但是这样的计算方式，就需要每次都要从新的节点位置开始扩散遍历，存在很多重复计算
 * 2、为了解决这个问题，需要换个思路，还是使用广度优先遍历算法bfs，只不过是先将所有的元素值为0的节点添加到队列中
 * - 原始数组的距离，如果元素值为0的距离值为0，元素值为1的距离值为max最大值，
 * - 从队列中不断取出元素，去查找四周位置的节点，如果发现周围元素的距离值大于遍历节点位置的距离值加1，则需要更新为新的节点值，因为发现存在更短距离的节点值了
 * - 并且将当前更新的节点添加到队列中去。
 */
vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
{
  int m = mat.size();
  int n = mat[0].size();
  queue<vector<int>> queue;
  vector<vector<int>> disVec(m, vector<int>(n, 0)); // 新的矩阵，用于保存节点元素距离值的

  // 遍历找出所有的元素为0的节点，更新距离值，并将该节点添加到队列中去
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (mat[i][j] == 0)
      {
        queue.push({i, j});
        disVec[i][j] = 0;
      }
      else
      {
        disVec[i][j] = INT32_MAX;
      }
    }
  }

  // 四周位置的坐标增向量
  vector<vector<int>> dirs = {
      {0, -1}, // 左
      {0, 1},  // 右
      {-1, 0}, // 上
      {1, 0}   // 下
  };

  // 不断从队列中取出节点值坐标，查找他四周的节点，并判断距离
  while (!queue.empty())
  {
    vector<int> item = queue.front();
    queue.pop();
    int i = item[0];
    int j = item[1];

    for (int k = 0; k < dirs.size(); k++)
    {
      int r = i + dirs[k][0];
      int c = j + dirs[k][1];

      if (0 <= r && r < m && 0 <= c && c < n)
      {
        if (disVec[r][c] > disVec[i][j] + 1)
        {
          disVec[r][c] = disVec[i][j] + 1;
          queue.push({r, c});
        }
      }
    }
  }

  return disVec;
}

int main()
{
  std::cout << "《剑指》" << std::endl;

  vector<vector<int>> grid = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0},
  };

  // vector<vector<int>> grid = {
  //     {0, 0, 0},
  //     {0, 1, 0},
  //     {1, 1, 1},
  // };

  // vector<vector<int>> grid = {
  //     {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
  //     {0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
  //     {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
  //     {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
  //     {0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
  //     {0, 0, 1, 0, 1, 1, 1, 0, 1, 0},
  //     {0, 1, 0, 1, 0, 1, 0, 0, 1, 1},
  //     {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
  //     {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
  //     {1, 1, 1, 1, 0, 1, 0, 0, 1, 1},
  // };

  // vector<vector<int>> grid = {
  //     {1, 1, 0, 0, 1, 0, 0, 1, 1, 0},
  //     {1, 0, 0, 1, 0, 1, 1, 1, 1, 1},
  //     {1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
  //     {0, 1, 1, 1, 0, 1, 1, 1, 1, 1},
  //     {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
  //     {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
  //     {0, 1, 1, 1, 1, 1, 1, 0, 0, 1},
  //     {1, 1, 1, 1, 1, 0, 0, 1, 1, 1},
  //     {0, 1, 0, 1, 1, 0, 1, 1, 1, 1},
  //     {1, 1, 1, 0, 1, 0, 1, 1, 1, 1},
  // };

  auto res = updateMatrix(grid);
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