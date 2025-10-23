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
 * - 解法2使用current值来标记当前层的个数，也可以采用两个队列来替换，当前队列保存当前层需要遍历的元素
 * - next队列保存下一层需要遍历的元素，当current的值减少为0时，进行队列的替换
 */
vector<int> largestValues(TreeNode *root)
{
    std::queue<TreeNode *> currQueue;
    std::queue<TreeNode *> nextQueue;
    int max = INT32_MIN;
    int current = 0;
    std::vector<int> res;
    if (root == nullptr)
    {
        return res;
    }
    currQueue.push(root);
    current = 1;

    while (!currQueue.empty())
    {
        TreeNode *node = currQueue.front();
        currQueue.pop();

        if (node->left != nullptr)
        {
            nextQueue.push(node->left);
        }
        if (node->right != nullptr)
        {
            nextQueue.push(node->right);
        }

        current--;
        max = std::max(max, node->val);
        if (current == 0)
        {
            res.push_back(max);
            currQueue = nextQueue;
            current = currQueue.size();

            nextQueue = std::queue<TreeNode *>();
            max = INT32_MIN;
        }
    }

    return res;
}

/**
 * 解法2：计数法
 * - 在层序遍历过程中，记录每层的数量，使用两个变量current和next
 * - current标记当前层的结点个数，next记录下一层结点的个数，遍历的时候当前层个数current不断减少，next的值不断增加
 * - 当current为0时，说明当前层所有结点都遍历完成后，此时获取出这一层的最大值保存到集合中，并将current的值设置为next的值，从而开始下一层级的遍历
 * -- 其实next的值就等于遍历过程中队列中元素的个数
 */
vector<int> largestValues3(TreeNode *root)
{
    std::vector<int> res;
    std::queue<TreeNode *> queue;
    int current = 0;
    int max = INT32_MIN;
    if (root == nullptr)
    {
        return res;
    }

    // 根节点入队列
    queue.push(root);
    current = 1;

    while (!queue.empty())
    {
        TreeNode *node = queue.front();
        queue.pop();

        if (node->left != nullptr)
        {
            queue.push(node->left);
        }

        if (node->right != nullptr)
        {
            queue.push(node->right);
        }

        // 计算处理
        current--;
        max = std::max(max, node->val);
        if (current == 0) // 当前一层遍历完了
        {
            res.push_back(max);
            current = queue.size();
            max = INT32_MIN;
        }
    }

    return res;
}

vector<int> largestValues2(TreeNode *root)
{
    std::vector<int> res;
    std::queue<TreeNode *> queue;
    int current = 0;
    int next = 0;
    int max = INT32_MIN;
    if (root == nullptr)
    {
        return res;
    }

    // 根节点入队列
    queue.push(root);
    current = 1;

    while (!queue.empty())
    {
        TreeNode *node = queue.front();
        queue.pop();

        if (node->left != nullptr)
        {
            queue.push(node->left);
            next++;
        }

        if (node->right != nullptr)
        {
            queue.push(node->right);
            next++;
        }

        // 计算处理
        current--;
        max = std::max(max, node->val);
        if (current == 0)
        {
            res.push_back(max);
            current = next;
            next = 0;
            max = INT32_MIN;
        }
    }

    return res;
}

/**
 * 二叉树与队列的使用
 * 1、审题：
 * - 输入一棵二叉树，要求找到二叉树每一层节点中的最大值，组成一个集合并返回
 * 2、审题：
 * - 核心在于遍历树的每一层节点，并从中找到最大值
 * - 可以通过树的层序遍历，问题在于如何知道刚好遍历完树的一层结点？
 * 解法1：在遍历的过程中，每层遍历完插入一个空的结点，当遍历到空节点时，就取出最大值
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