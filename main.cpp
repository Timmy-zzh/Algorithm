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
LCR 044. 在每个树行中找最大值
https://leetcode.cn/problems/hPov7L/description/

给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。

示例 1：
输入: root = [1,3,2,5,3,null,9]
输出: [1,3,9]
解释:
          1
         / \
        3   2
       / \   \
      5   3   9

示例 2：
输入: root = [1,2,3]
输出: [1,3]
解释:
          1
         / \
        2   3

示例 3：
输入: root = [1]
输出: [1]

示例 4：
输入: root = [1,null,2]
输出: [1,2]
解释:
           1
            \
             2

示例 5：
输入: root = []
输出: []

提示：
二叉树的节点个数的范围是 [0,104]
-231 <= Node.val <= 231 - 1
 */

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
 * 解法3：双队列法
 *
 */

/**
 * 解法2：计数法
 *
 */
vector<int> largestValues(TreeNode *root)
{
}

/**
 * 二叉树与队列的使用
 * 1、审题：
 * - 输入一棵二叉树，要求找到二叉树每一层节点中的最大值，组成一个集合并返回
 * 2、审题：
 * - 核心在于遍历树的每一层节点，并从中找到最大值
 * - 可以通过树的层序遍历，问题在于如何知道刚好遍历完树的一层结点？
 * 方式1：在遍历的过程中，每层遍历完插入一个空的结点，当遍历到空节点时，就取出最大值
 */
vector<int> largestValues1(TreeNode *root)
{
  std::vector<int> res;
  std::queue<TreeNode *> queue;
  if (root == nullptr)
  {
    return res;
  }

  queue.push(root);
  queue.push(nullptr);
  int max = INT32_MIN;

  while (!queue.empty())
  {
    TreeNode *node = queue.front();
    queue.pop();

    if (node == nullptr)
    {
      if (!queue.empty())
      {
        queue.push(nullptr);
      }

      res.push_back(max);
      max = INT32_MIN;
    }
    else
    {
      // 不为空，取出该结点
      max = std::max(node->val, max);
      if (node->left != nullptr)
      {
        queue.push(node->left);
      }

      if (node->right != nullptr)
      {
        queue.push(node->right);
      }
    }
  }

  return res;
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

  // CBTInserter *obj = new CBTInserter(root);
  // int param_1 = obj->insert(v);
  // TreeNode *param_2 = obj->get_root();

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