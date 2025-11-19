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
LCR 052. 递增顺序搜索树
https://leetcode.cn/problems/NYBBNL/description/

给你一棵二叉搜索树，请 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，
并且每个节点没有左子节点，只有一个右子节点。

示例 1：
输入：root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]

示例 2：
输入：root = [5,1,7]
输出：[1,null,5,null,7]

提示：
树中节点数的取值范围是 [1, 100]
0 <= Node.val <= 1000
 */

/**
 * 1、审题：
 * - 输入一棵二叉搜索树，要求将该二叉搜索树转变成只有右子节点的递增顺序搜索树
 * 2、解题：
 * - 二叉搜索树的定义是左子树节点值全部小于根节点值，而右子树结点值全部大于根节点值，左右子树也是一样的情况
 * - 要将原先的二叉树搜索树，转变成单条链的递增搜索树，意思是新的二叉树只有右子节点且还是二叉搜索树，则新的二叉树的根节点值最小，右子节点不断递增
 * - 采用中序遍历二叉搜索树，迭代代码方式，在遍历的过程中组装成新的递增搜索树
 */
TreeNode *increasingBST(TreeNode *root)
{
  TreeNode *first = nullptr;
  TreeNode *curr = root;
  TreeNode *prev = nullptr;
  std::stack<TreeNode *> stack;

  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->left;
    }

    // 从栈中取出栈顶元素
    curr = stack.top();
    stack.pop();

    if (prev != nullptr)
    {
      prev->right = curr;
    }
    else
    {
      first = curr;
    }
    prev = curr;
    prev->left = nullptr;
    curr = curr->right;
  }
  return first;
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