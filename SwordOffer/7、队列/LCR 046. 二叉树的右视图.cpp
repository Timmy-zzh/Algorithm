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
LCR 046. 二叉树的右视图
https://leetcode.cn/problems/WNC0Lk/description/

给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例 1：
输入: [1,2,3,null,5,null,4]
输出: [1,3,4]

示例 2：
输入: [1,null,3]
输出: [1,3]

示例 3：
输入: []
输出: []

提示：
二叉树的节点个数的范围是 [0,100]
-100 <= Node.val <= 100
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
 * - 输入一棵二叉树，想象自己站在树的右侧看这棵二叉树，则看到的是二叉树每一层最右边结点的值，将每一层的值从根节点往下放入队列中返回
 * 2、解题：
 * - 还是二叉树的层序遍历，使用双队列解法，每一层遍历结束都将下一层队列中的最后一个元素取出来， 该元素就是每层最右边结点
 */
vector<int> rightSideView(TreeNode *root)
{
    std::queue<TreeNode *> queue1;
    std::queue<TreeNode *> queue2;
    std::vector<int> res;
    if (root == nullptr)
    {
        return res;
    }
    queue1.push(root);
    res.push_back(queue1.back()->val);

    while (!queue1.empty())
    {
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
        {
            queue1 = queue2;
            queue2 = std::queue<TreeNode *>();
            res.push_back(queue1.back()->val);
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