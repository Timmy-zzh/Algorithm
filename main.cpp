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

/************************************ 层序遍历 *************************************/
/**
 * 层序遍历，使用队列保存遍历到的结点，并不断放入队列中
 * - 且队列头数据不断出队列，队列尾不断入队列
 */
void levelorderTraversal(TreeNode *node)
{
  std::queue<TreeNode *> queue;
  // 使用vector使用
  if (node == nullptr)
  {
    return;
  }
  queue.push(node);
  while (!queue.empty())
  {
    TreeNode *frontNode = queue.front();
    std::cout << frontNode->val << " ," << std::endl;
    queue.pop();
    if (frontNode->left != nullptr)
    {
      queue.push(frontNode->left);
    }
    if (frontNode->right != nullptr)
    {
      queue.push(frontNode->right);
    }
  }
}

/************************************ 中序遍历 *************************************/

/**
 * 二叉树中序遍历
 * 递归实现：
 * - 先遍历左子树，根节点，再遍历右子树
 */
void inorderTraversal1(TreeNode *node)
{
  if (node == nullptr)
  {
    return;
  }
  inorderTraversal1(node->left);
  std::cout << node->val << " ," << std::endl;
  inorderTraversal1(node->right);
}

/**
 * 中序遍历：迭代法
 * - 使用栈保存遍历的结点，从根节点开始遍历
 * - 遍历顺序为先遍历左子树，接着遍历根节点，最后遍历右子树
 * - 所以如果有有左子树节点，则需要不断遍历其左子节点，并放到栈中保存
 * -- 当遍历到最左侧的叶子结点时，已经没有左子结点，则需要遍历当前根节点，对栈顶元素出栈
 * - 此时，对于这棵子树来说，已经遍历完了左子树和根节点，接下来需要遍历右子树了，所以当前遍历根节点转换到右子节点上来
 * - 如果右子节点为空，则继续从栈中取出栈顶元素来处理，
 * = 所以要实现不断遍历到最左侧的左子结点，需要使用while循环不断遍历到做左子结点并保存到栈中
 * - 如何左子结点遍历到叶子结点，则遍历当前的根节点，接着遍历他的右子节点，
 * - 如果右子节点为空，则从栈中取出之前遍历的左子节点，他是更上一层的父节点
 * - 如果右子节点和栈都为空了，则说明整棵树都遍历完了。
 */
void inorderTraversal2(TreeNode *node)
{
  std::stack<TreeNode *> stack;
  TreeNode *curr = node;
  while (curr != nullptr || !stack.empty())
  {
    while (curr != nullptr) // 不断深入遍历左子节点，知道最左侧的叶子结点
    {
      stack.push(curr);
      curr = curr->left;
    }

    // 当前curr为叶子结点的左子节点，为空，需要从栈中取出栈顶元素来遍历
    curr = stack.top();
    stack.pop();
    // 打印
    std::cout << curr->val << " ," << std::endl;
    /**
     * 遍历他的右子节点
     * - 如果右子节点不为空，则以右子节点为根节点，继续遍历他的左子结点
     * - 如果右子节点为空，则当前这棵子树遍历完了，需要从栈中取出他对应的父节点进行遍历
     */
    curr = curr->right;
  }
}

/************************************ 前序遍历 *************************************/

/**
 * 前序遍历：
 * - 先遍历根节点，再遍历左子树，最后是右子树
 */
void preorderTraversal1(TreeNode *node)
{
  if (node == nullptr)
  {
    return;
  }
  std::cout << node->val << " ," << std::endl;
  preorderTraversal1(node->left);
  preorderTraversal1(node->right);
}

/**
 * 前序遍历：迭代实现
 * - 使用栈保存遍历到的结点数据，先遍历根节点，再遍历左子树，最后遍历右子树
 */
void preorderTraversal2(TreeNode *node)
{
  std::stack<TreeNode *> stack;
  while (node != nullptr || !stack.empty())
  {
    // 节点不为空，则不断获取他的左子节点，并放入到栈中
    while (node != nullptr)
    {
      std::cout << node->val << " ," << std::endl;
      stack.push(node);
      node = node->left;
    }

    /**
     * 当左子树都遍历完了（node为空），则取出栈中的元素（一定有数据），
     * 栈顶元素为当前node节点的父节点，取出来遍历他的右子树
     */
    TreeNode *topNode = stack.top();
    stack.pop();
    node = topNode->right;
  }
}

/************************************ 后序遍历 *************************************/

/**
 * 后序遍历：
 * - 先遍历左子树，再遍历右子树，最后是根节点
 */
void postorderTraversal1(TreeNode *node)
{
  if (node == nullptr)
  {
    return;
  }
  postorderTraversal1(node->left);
  postorderTraversal1(node->right);
  std::cout << node->val << " ," << std::endl;
}

/**
 * 后续遍历：迭代实现
 * - 后续遍历的顺序是，先遍历左子树，接着遍历右子树，最后才是根节点
 * - 同样先使用while循环不断遍历左子节点，并将遍历到的结点放到栈中
 * - 当遍历到左侧的叶子结点时，取出栈顶节点，但是该结点现在还不做出栈操作，而是先判断他的右子节点之前是否遍历过
 * - 如果之前没有遍历过，则继续以他的右子节点为根节点进行遍历，如果之前遍历过，则遍历遍历当前结点，并且栈顶元素出栈
 * - 此时说明这棵左子树全部遍历完成，需要将curr的遍历结点设置为空，以便从栈中取出他的父节点，继续遍历他的右子树
 * -- 现在的问题是如何判断他的右子节点之前是否遍历过，通过设置一个prev属性，继续当前遍历的结点
 */
void postorderTraversal2(TreeNode *node)
{
  std::stack<TreeNode *> stack;
  TreeNode *curr = node;
  TreeNode *prev = nullptr;
  while (curr != nullptr || !stack.empty())
  {
    // 不断遍历查找他的左子节点
    while (curr != nullptr)
    {
      stack.push(curr);
      curr = curr->left;
    }

    // 左子树遍历完了，需要从获取出栈顶元素
    TreeNode *topNode = stack.top();
    // 判断之前是否遍历过他的右子节点,有左子节点，且之前没有遍历过-》继续遍历他的左子节点
    if (topNode->right != nullptr && prev != topNode->right)
    {
      curr = topNode->right;
    }
    else
    {
      // 出栈，
      stack.pop();
      std::cout << topNode->val << " ," << std::endl;
      prev = topNode;
      curr = nullptr; // 设置为空，让下一步从栈中取出父节点进行遍历
    }
  }
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

  std::cout << "层序遍历 levelorderTraversal" << std::endl;
  levelorderTraversal(&node1);

  std::cout << "中序遍历 inorderTraversal1" << std::endl;
  inorderTraversal1(&node1);
  std::cout << "inorderTraversal2" << std::endl;
  inorderTraversal2(&node1);

  std::cout << "前序遍历 preorderTraversal1" << std::endl;
  preorderTraversal1(&node1);
  std::cout << " preorderTraversal2" << std::endl;
  preorderTraversal2(&node1);

  std::cout << "后续遍历 postorderTraversal1" << std::endl;
  postorderTraversal1(&node1);
  std::cout << " postorderTraversal2" << std::endl;
  postorderTraversal2(&node1);

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