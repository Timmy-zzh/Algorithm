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
LCR 116. 省份数量
https://leetcode.cn/problems/bLyHh0/description/

有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。
省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。
返回矩阵中 省份 的数量。

示例 1：
输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
输出：2

示例 2：
输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
输出：3

提示：
1 <= n <= 200
n == isConnected.length
n == isConnected[i].length
isConnected[i][j] 为 1 或 0
isConnected[i][i] == 1
isConnected[i][j] == isConnected[j][i]
 */

/**
 * 1、审题：输入一个二维数组，数组中的元素为0或者1, arr[i][j] = 1,表示城市i和城市标记j之前相连，如果arr[i][j]=0;说明两个城市之间不相连
 * - 相连的城市属于同一个省份，不相连的说明不在同一个省份，现在要求提供的这些城市，一共有属于几个省份，并返回省份个数
 * 2、解题：使用图的广度搜索算法
 * - 使用n*n的 vector<bool>[n][n] visited 的数组表示哪些城市被访问过了，从城市0开始遍历，放到队列中去，并找到与城市0相连接的其他城市，也放到队列中去，他们都是属于同一个省份
 * - 遍历过的城市在数组visited中的值变为true，
 * - 从原始数组中获取一个城市，如果他之前没有遍历过，则返回1，表示他是一个新的省份，并需要将属于该省份的所有城市都进行标记
 * - 直到所有城市都标记完成
 */
void bfs(vector<vector<int>> &isConnected, vector<bool> &visited, int n, int k)
{
  // 找到与k相连的城市
  queue<int> queue;
  visited[k] = true;
  queue.push(k);

  while (!queue.empty())
  {
    int node = queue.front();
    queue.pop();
    std::cout << " bfs  node-------:" << node << std::endl;

    for (int i = 0; i < n; i++)
    {
      if (i == node || visited[i])
      {
        continue;
      }
      std::cout << " node:" << node << " ,i:" << i << " ,isConnected[k][i]:" << isConnected[node][i] << std::endl;
      if (isConnected[node][i] == 1)
      {
        std::cout << " bfs  i -------:" << i << std::endl;
        queue.push(i);
        visited[i] = true;
      }
    }
  }
}

int findCircleNum(vector<vector<int>> &isConnected)
{
  int n = isConnected.size();
  vector<bool> visited(n, false);

  int resNum = 0;
  for (int i = 0; i < n; i++)
  {
    if (!visited[i])
    {
      std::cout << " for i:" << i << std::endl;
      bfs(isConnected, visited, n, i);
      resNum++;
    }
  }
  return resNum;
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
  // vector<int> nums = {1, 2, 3};
  vector<vector<int>> isConnected = {{1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, {1, 0, 1, 1}};

  // int findCircleNum(vector<vector<int>> &isConnected)
  auto res = findCircleNum(isConnected);
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