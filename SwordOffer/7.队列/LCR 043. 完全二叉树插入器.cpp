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
LCR 043. 完全二叉树插入器
https://leetcode.cn/problems/NaqhDT/description/

完全二叉树是每一层（除最后一层外）都是完全填充（即，节点数达到最大，第 n 层有 2n-1 个节点）的，并且所有的节点都尽可能地集中在左侧。
设计一个用完全二叉树初始化的数据结构 CBTInserter，它支持以下几种操作：
CBTInserter(TreeNode root) 使用根节点为 root 的给定树初始化该数据结构；
CBTInserter.insert(int v)  向树中插入一个新节点，节点类型为 TreeNode，值为 v 。使树保持完全二叉树的状态，并返回插入的新节点的父节点的值；
CBTInserter.get_root() 将返回树的根节点。

示例 1：
输入：inputs = ["CBTInserter","insert","get_root"], inputs = [[[1]],[2],[]]
输出：[null,1,[1,2]]

示例 2：
输入：inputs = ["CBTInserter","insert","insert","get_root"], inputs = [[[1,2,3,4,5,6]],[7],[8],[]]
输出：[null,3,4,[1,2,3,4,5,6,7,8]]

提示：
最初给定的树是完全二叉树，且包含 1 到 1000 个节点。
每个测试用例最多调用 CBTInserter.insert  操作 10000 次。
给定节点或插入节点的每个值都在 0 到 5000 之间。
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
 * 解法2：
 * - 在构造函数的时候对树进行层序遍历，找到需要补充左右子节点的结点位置
 * - 在调用insert方法的时候，从队列中直接获取队列的头结点，然后插入左或右子节点，如果当前结点的左右子节点都满了，则进行入队和出队操作
 * - 采用这种实现方式不用每次调用insert方法的时候，都需要进行层序遍历
 */
class CBTInserter
{
public:
    CBTInserter(TreeNode *root)
    {
        m_root = root;
        // 层序遍历
        queue.push(root);
        while (!queue.empty())
        {
            TreeNode *node = queue.front();
            if (node->left != nullptr && node->right != nullptr)
            {
                // 左右子节点都不为空，则左右子节点入队列，队头元素出队列
                queue.pop();
                queue.push(node->left);
                queue.push(node->right);
            }
            else
            {
                // 找到了需要补左右子节点的结点，
                break;
            }
        }
    }

    /**
     * 获取队头元素，该元素就是需要新插入结点的目标节点
     * - 插入后，判断其左右子节点是否完满，完满的话，需要进行入队出队操作
     */
    int insert(int v)
    {
        TreeNode *newNode = new TreeNode(v);
        if (queue.empty())
        {
            queue.push(newNode);
            m_root = newNode;
            return v;
        }

        TreeNode *node = queue.front();
        if (node->left == nullptr)
        {
            node->left = newNode;
        }
        else
        {
            node->right = newNode;

            queue.pop();
            queue.push(node->left);
            queue.push(node->right);
        }

        return node->val;
    }

    TreeNode *get_root()
    {
        return m_root;
    }

private:
    std::queue<TreeNode *> queue;
    TreeNode *m_root;
};

/**
 * 队列的使用，广度优先算法
 * 1、审题：创建一个二叉树插入器的类，内部包含的二叉树是完全二叉树形式，并暴露两个方法插入insert，和获取树的根节点
 * - 要求在插入树节点内部的二叉树还是完全二叉树的形式
 * 2、解题：
 * - 根据完全二叉树的特性，树的每层结点都应该是满的，最后一层可以不填充满，但是树节点位置是从左到右排列的。
 * - 在调用插入insert方法时，层序遍历树的结点，找到左右子节点不满的结点，并新插入对应缺失的结点
 * - 层序遍历使用队列保存元素
 * - 优化，如果每次调用插入方法，都需要从根节点开始层序遍历的话时间复杂度就高了，可以使用队列保存待插入节点的父节点
 */
class CBTInserter1
{
public:
    CBTInserter1(TreeNode *root)
    {
        m_root = root;
    }

    /**
     * 层序遍历根节点，使用队列queue保存遍历结点元素
     * 并找到左右自己点缺失的结点，添加对应缺失的结点
     */
    int insert(int v)
    {
        TreeNode *newNode = new TreeNode(v);
        if (m_root == nullptr)
        {
            m_root = newNode;
            return v;
        }
        TreeNode *node = m_root;
        queue.push(node);
        while (!queue.empty())
        {
            TreeNode *tempNode = queue.front();
            if (tempNode->left == nullptr) // 左子节点为空，则插入左子节点
            {
                tempNode->left = newNode;
                return tempNode->val;
            }

            // 右子节点为空，插入
            if (tempNode->right == nullptr)
            {
                tempNode->right = newNode;
                return tempNode->val;
            }
            else
            {
                // 右子节点不为空，说明该结点左右节点都是满的，则左右子节点入队列，当前结点出队列
                queue.push(tempNode->left);
                queue.push(tempNode->right);
                queue.pop();
            }
        }
        return 0;
    }

    TreeNode *get_root()
    {
        return m_root;
    }

private:
    std::queue<TreeNode *> queue;
    TreeNode *m_root;
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
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