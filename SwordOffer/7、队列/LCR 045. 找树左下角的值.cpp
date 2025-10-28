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
LCR 045. 找树左下角的值
https://leetcode.cn/problems/LwUNpT/description/

给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
假设二叉树中至少有一个节点。

示例 1：
输入: root = [2,1,3]
输出: 1

示例 2：
输入: [1,2,3,4,null,5,6,null,null,7]
输出: 7

提示：
二叉树的节点个数的范围是 [1,104]
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
 * 1、审题：
 * - 输入一棵二叉树，要求该二叉最低一层最左边节点的数值
 * 2、解题：双队列解法
 * - 对二叉树进行层序遍历，使用两个队列保存遍历到的每一层的结点值
 * - 在遍历完一层结点后，取出队列的队头元素，该值就是这一层最左边的结点值
 */
int findBottomLeftValue(TreeNode *root)
{
  std::queue<TreeNode *> queue1;
  std::queue<TreeNode *> queue2;
  queue1.push(root);
  int bottomLeft = queue1.front()->val;

  while (!queue1.empty())
  {
    // 取出1队列的头结点,并出队列
    TreeNode *node = queue1.front();
    queue1.pop();
    if (node->left != nullptr)
    {
      queue2.push(node->left);
    }
    if (node->right != nullptr)
    {
      queue2.push(node->right);
    }
    if (queue1.empty() && !queue2.empty())
    { // 队列1全部遍历完成，赋值队列2的数据给到队列1
      queue1 = queue2;
      queue2 = std::queue<TreeNode *>();
      bottomLeft = queue1.front()->val;
    }
  }
  return bottomLeft;
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