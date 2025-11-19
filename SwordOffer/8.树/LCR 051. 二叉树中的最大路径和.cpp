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
LCR 051. 二叉树中的最大路径和
https://leetcode.cn/problems/jC7MId/description/

路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。
该路径 至少包含一个 节点，且不一定经过根节点。路径和 是路径中各节点值的总和。

给定一个二叉树的根节点 root ，返回其 最大路径和，即所有路径上节点值之和的最大值。

示例 1：
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6

示例 2：
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42

提示：
树中节点数目范围是 [1, 3 * 104]
 */

/**
 * 1、审题：
 * - 输入一棵非空的二叉树，要求在这棵二叉树中，查找一条路径上的结点，要求该路径上的所有节点值和最大，并返回这个最大值
 * 2、解题：
 * - 题目要求的该路径没有说要从根节点开始，也没有说要到某个节点结束，可以是树中任意个结点组合成的路径
 * - 问题的核心为如何找到这个路径，使用后续遍历方式，遍历这棵二叉树，
 * - 将问题进行细化，可以看做左子树，根节点和右子树三个部分，那这条路径可以有好几种情况：
 * -- 左子树的最大值路径； 右子树的最大值路径； 左子树+根节点+右子树组合成的路径；
 * -- 而在遍历时返回的值，是当前左子树或者左子树经过当前结点组成的路径和的最大值
 * - 所以每次遍历左右子树的时候，都是传入一个对象引用，
 */
int dfs(TreeNode *node, int &maxSum)
{
  if (node == nullptr)
  {
    return 0; // 叶子结点
  }

  // 非叶子结点，获取当前结点下的左子树的最大值
  int leftMaxSum = INT32_MIN;
  // 如果左子树路径上的结点全是负数，则不取这个路径上的任何一个节点
  int left = max(0, dfs(node->left, leftMaxSum));

  // 右子树也一样
  int rightMaxSum = INT32_MIN;
  int right = max(0, dfs(node->right, rightMaxSum));

  // 左右子树的最大值,不包含根节点
  maxSum = max(leftMaxSum, rightMaxSum);

  // 求最大路径和,全路径
  maxSum = max(maxSum, left + right + node->val);

  // 返回左或右子树的最大值路径
  return node->val + max(left, right);
}

int maxPathSum(TreeNode *root)
{
  int maxSum = INT32_MIN;
  dfs(root, maxSum);
  return maxSum;
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