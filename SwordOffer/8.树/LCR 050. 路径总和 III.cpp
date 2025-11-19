#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <stack>
#include <queue>
#include "src/bean.h"

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/**
LCR 050. 路径总和 III
https://leetcode.cn/problems/6eUYwP/description/

给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

示例 1：
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。

示例 2：
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3

提示:
二叉树的节点个数的范围是 [0,1000]
-109 <= Node.val <= 109
-1000 <= targetSum <= 1000
 */

/**
 * 1、审题：
 * - 输入一棵二叉树和一个目标值targetSum，要求找到在二叉树中连续节点的值累加和等于目标值的个数
 * 2、解题：
 * - 题目要求在二叉树中连续的结点路径，并没有要求一定要从根节点开始，到叶子结点结束，中间部分的结点路径之和也可以
 * - 使用前序遍历法，记录遍历到当前结点的路径之和path，
 * - 使用map保存遍历过程中路径之和和对应个数，这样做的目的可以通过当前路径之和path减去目标值targetSum,判断map中是否存在该差值的键，
 * -- 如果存在则说明到当前结点位置结束，存在一条路径（可能是中间某个节点开始），其路径之和等于目标值
 * -- 相当于在遍历过程中，遍历到每个节点都有一个路径之和path，且都有一个对应的map集合，键值对为路径之和与路径和对应个数的值
 * - 通过判断路径之和与目标值targetSum之差，来判断结果值是否在map集合中是否存在对应的键
 * - 因为前序遍历，从根节点开始遍历到左子树再到右子树，path的值是有副本，但是map的值是同一个指针，所以在遍历完当前结点后，需要将到该结点的路径和减去其个数表示退出当前结点
 * - 在前序遍历的过程中，将所求问题进行拆解，最终的问题是求输入的目标二叉树中路径和等于目标值的个数，可以拆解为三个部分，
 * -- 也就是到当前结点位置的个数，和到左右子树的个数，三者之和
 */
int dfs(TreeNode *node, int target, std::map<double, int> map, double path)
{
  if (node == nullptr)
  {
    return 0;
  }
  // 到当前结点时，他的路径之和
  path = path + node->val;
  // 求到当前结点他的路径和的个数
  int count = 0;
  if (map.find(path - target) != map.end()) // 存在这样的路径和
  {
    count = map[path - target];
  }
  // 添加path路径和的个数
  if (map.find(path) != map.end()) // 存在这样的路径和
  {
    int tempC = map[path];
    map[path] = tempC + 1;
  }
  else
  {
    map[path] = 1;
  }

  // 加上到左右子树位置时，他的路径之和
  count += dfs(node->left, target, map, path);
  count += dfs(node->right, target, map, path);

  // 这个节点遍历结束了，则到这个节点的路径和，需要在map中删除
  int tempC = map[path];
  map[path] = tempC - 1;
  return count;
}

int pathSum(TreeNode *root, int targetSum)
{
  std::map<double, int> map;
  map[0] = 1;
  return dfs(root, targetSum, map, 0);
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

  TreeNode node1(1);
  TreeNode node2(2);
  TreeNode node3(3);
  TreeNode node4(4);
  TreeNode node5(5);
  TreeNode node6(6);
  TreeNode node7(7);

  node1.left = &node2;
  node1.right = &node3;

  node2.left = &node4;
  node2.right = &node5;

  node3.left = &node6;
  node3.right = &node7;

  // vector<string> matrix = {"10100", "10111", "11111", "10010"};

  // for (auto ele : matrix)
  // {
  //   std::cout << ele << ",";
  // }
  // std::cout << std::endl;

  // auto res = maximalRectangle(matrix);

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
  //     for (auto element : ele)
  //     {
  //         std::cout << element << ",";
  //     }
  //     std::cout << std::endl;
  // }
  // std::cout << std::endl;

  return 0;
}