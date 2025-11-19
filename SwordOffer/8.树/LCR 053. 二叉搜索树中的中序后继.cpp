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
LCR 053. 二叉搜索树中的中序后继
https://leetcode.cn/problems/P5rCT8/description/

给定一棵二叉搜索树和其中的一个节点 p ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。
节点 p 的后继是值比 p.val 大的节点中键值最小的节点，即按中序遍历的顺序节点 p 的下一个节点。

示例 1：
输入：root = [2,1,3], p = 1
输出：2
解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。

示例 2：
输入：root = [5,3,6,2,4,null,null,1], p = 6
输出：null
解释：因为给出的节点没有中序后继，所以答案就返回 null 了。

提示：
树中节点的数目在范围 [1, 104] 内。
-105 <= Node.val <= 105
树中各节点的值均保证唯一。
 */

/**
 * 解题2：二叉搜索树解法
 * - 根据二叉搜索树特性，左子树所有结点值比根节点值小，右子树所有节点值比根节点值大，
 * - 从根节点开始遍历，如果遍历到的当前节点值比目标节点p的值要小，则继续遍历大的右子树结点
 * - 如果遍历到的当前结点值比目标值大，则继续寻找他的左子节点，因为他的左子结点肯定也比当前结点值要大（如果有的话）
 */
TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p)
{
    TreeNode *result = nullptr;
    TreeNode *curr = root;
    while (curr != nullptr)
    {
        if (curr->val > p->val)
        {
            result = curr;
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    return result;
}

/**
 * 1、审题：
 * - 输入一棵二叉搜索树，和其中一个节点p，要求按照中序遍历的顺序找到节点p的下一个节点，并返回，没有则返回null
 * 2、解题：
 * - 迭代方式遍历二叉搜索树，使用一个变量记录是否找到了与节点p相同的结点，如果找到了，则下一个节点就是目标值了
 */
TreeNode *inorderSuccessor1(TreeNode *root, TreeNode *p)
{
    std::stack<TreeNode *> stack;
    TreeNode *curr = root;
    bool found = false;
    while (curr != nullptr || !stack.empty())
    {
        while (curr != nullptr)
        {
            stack.push(curr);
            curr = curr->left;
        }
        curr = stack.top();
        stack.pop();

        if (found)
        {
            return curr;
        }

        if (curr->val == p->val)
        {
            found = true;
        }
        curr = curr->right;
    }
    return nullptr;
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