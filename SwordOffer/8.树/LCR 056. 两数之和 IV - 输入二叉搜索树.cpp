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
LCR 056. 两数之和 IV - 输入二叉搜索树
https://leetcode.cn/problems/opLdQZ/description/

给定一个二叉搜索树的 根节点 root 和一个整数 k , 请判断该二叉搜索树中是否存在两个节点它们的值之和等于 k 。假设二叉搜索树中节点的值均唯一。

示例 1：
输入: root = [8,6,10,5,7,9,11], k = 12
输出: true
解释: 节点 5 和节点 7 之和等于 12

示例 2：
输入: root = [8,6,10,5,7,9,11], k = 22
输出: false
解释: 不存在两个节点值之和为 22 的节点

提示：
二叉树的节点个数的范围是  [1, 104].
-104 <= Node.val <= 104
root 为二叉搜索树
-105 <= k <= 105
 */

/**
 * 1、审题：
 * - 输入一棵二叉搜索树和目标值k，要求查找二叉树中是否存在两个节点的值之和等于目标值k，并返回结果
 * 2、解题：
 * - 哈希表+中序遍历解法：中序遍历过程中使用哈希表map保存遍历到的节点值，并判断是否存在k-val的值，在之前是否存在
 * - 双指针+二分法查找：因为输入的二叉搜索树中序遍历是升序的，可采用二分查找方法，分别从二叉树的前后最大最小值节点开始遍历
 * -- 如果两个节点值和等于目标值则返回，如果和大于目标值，则右侧最大节点值左移，否则左侧最小值右移
 */
bool findTarget(TreeNode *root, int k)
{
  std::vector<int> vector;
  std::stack<TreeNode *> stack;
  TreeNode *curr = root;

  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->left;
    }

    curr = stack.top();
    stack.pop();
    if (find(vector.begin(), vector.end(), k - curr->val) != vector.end())
    {
      return true;
    }
    vector.push_back(curr->val);
    curr = curr->right;
  }
  return false;
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