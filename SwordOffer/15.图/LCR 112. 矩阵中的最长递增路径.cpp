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
LCR 112. 矩阵中的最长递增路径
https://leetcode.cn/problems/fpTFWP/description/

给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径的长度。
对于每个单元格，你可以往上，下，左，右四个方向移动。 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。

示例 1：
输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
输出：4
解释：最长递增路径为 [1, 2, 6, 9]。

示例 2：
输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
输出：4
解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。

示例 3：
输入：matrix = [[1]]
输出：1

提示：
m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 231 - 1
 */
int dfs(vector<vector<int>> &matrix, vector<vector<int>> &cache, vector<vector<int>> &dirs, int i, int j)
{
  if (cache[i][j] != 1)
  {
    return cache[i][j];
  }

  int m = matrix.size();
  int n = matrix[0].size();

  for (auto dir : dirs)
  {
    int r = i + dir[0];
    int c = j + dir[1];

    if (0 <= r && r < m && 0 <= c && c < n && matrix[r][c] > matrix[i][j])
    {
      int path = dfs(matrix, cache, dirs, r, c);
      cache[r][c] = max(cache[r][c], path);
      cache[i][j] = max(cache[i][j], path + 1);
    }
  }
  return cache[i][j];
}

int longestIncreasingPath(vector<vector<int>> &matrix)
{
  int m = matrix.size();
  int n = matrix[0].size();

  // 四个方向的数组
  vector<vector<int>> dirs = {
      {-1, 0}, // 左
      {1, 0},  // 右
      {0, -1}, // 上
      {0, 1},  // 下
  };
  int resPath = 1;
  vector<vector<int>> cache(m, vector<int>(n, 1));

  int path = 1;
  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[0].size(); j++)
    {
      path = dfs(matrix, cache, dirs, i, j);
      resPath = max(path, resPath);
    }
  }
  return resPath;
}

/**
 * 1、审题：输入一个二维数组，数组中的元素都是正整数，现在要从中找到不断递增路径的最大长度，并返回
 * 2、解题：dfs深度优先算法
 * - 遍历矩阵中的每个元素，以该元素为起点，不断向四周寻找比当前元素更大的节点，并且路径不断增加，找到后最终返回最长的递增路径长度
 * 3、算法超时：因为两层遍历过程中，每次从矩阵中的元素出发去寻找最长路径，都需要全部计算
 * - 优化：添加一个缓存，保存每次从开始位置计算得到的的最长路径的长度值，用于下一次计算缓存使用，不用每次都计算，直接从缓存中获取
 */
void dfs1(vector<vector<int>> &matrix, int i, int j, int path, int &resPath)
{
  if (path > resPath)
  {
    resPath = path;
  }

  // 四个方向的数组
  vector<vector<int>> dirs = {
      {-1, 0}, // 左
      {1, 0},  // 右
      {0, -1}, // 上
      {0, 1},  // 下
  };

  int m = matrix.size();
  int n = matrix[0].size();

  for (auto dir : dirs)
  {
    int r = i + dir[0];
    int c = j + dir[1];

    if (0 <= r && r < m && 0 <= c && c < n)
    {
      // 目标值是否比当前值大
      if (matrix[r][c] > matrix[i][j])
      {
        dfs1(matrix, r, c, path + 1, resPath);
      }
    }
  }
}

int longestIncreasingPath1(vector<vector<int>> &matrix)
{
  int resPath = 1;

  for (int i = 0; i < matrix.size(); i++)
  {
    for (int j = 0; j < matrix[0].size(); j++)
    {
      dfs1(matrix, i, j, 1, resPath);
    }
  }
  return resPath;
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

  /**
   * 示例 1：
输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
   */

  // vector<string> wordList = {"0201", "0101", "0102", "1212", "2002"};
  // vector<string> wordList = {"8888"};

  // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)

  vector<vector<int>> matri = {
      {9, 9, 4},
      {6, 6, 8},
      {2, 1, 1},
  };
  auto res = longestIncreasingPath(matri);
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