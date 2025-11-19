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
LCR 048. 二叉树的序列化与反序列化
https://leetcode.cn/problems/h54YBf/description/

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

示例 1：
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]

示例 2：
输入：root = []
输出：[]

示例 3：
输入：root = [1]
输出：[1]

示例 4：
输入：root = [1,2]
输出：[1,2]

提示：
输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，也可以采用其他的方法解决这个问题。
树中结点数在范围 [0, 104] 内
-1000 <= Node.val <= 1000
 */

/**
 * 1、审题：
 * - 对一个二叉树进行序列化与反序列化
 * 2、解题：
 * - 二叉树的序列化操作，是输入一棵二叉树，处理后返回一串字符串，反序列化操作则是输入一串字符串，返回一棵二叉树
 * - 二叉树的序列化采用前序遍历二叉树的方式，当遇到空节点时，返回特殊字符#，非空节点则返回节点数值
 * - 反序列化则不断遍历字符串中的字符，使用一个int值标记当前遍历到的字符位置，通过不断获取字符串中的字符，来构造二叉树的结点，遇到字符为#，则说明需要构造空节点
 */
class Codec
{
public:
  string serialize(TreeNode *root)
  {
    if (root == nullptr)
    {
      return "#";
    }
    std::string leftStr = serialize(root->left);
    std::string rightStr = serialize(root->right);
    return std::to_string(root->val) + "," + leftStr + "," + rightStr;
  }

  TreeNode *deserializeReal(const vector<string> &strs, int &i)
  {
    // 获取当前遍历到的字符
    string str = strs[i];
    i++;
    std::cout << "i=" << i << " ,str=" << str << std::endl;
    if (str == "#")
    {
      return nullptr;
    }
    TreeNode *node = new TreeNode(std::stoi(str));
    node->left = deserializeReal(strs, i);
    node->right = deserializeReal(strs, i);
    return node;
  }

  vector<string> splitString(const string &input)
  {
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(',');

    while (end != string::npos)
    {
      result.push_back(input.substr(start, end - start));
      start = end + 1;
      end = input.find(',', start);
    }

    // 添加最后一个元素
    result.push_back(input.substr(start));

    return result;
  }

  TreeNode *deserialize(string data)
  {
    int index = 0;
    // 将string以，为间隔符，进行分割，转成字符串数组
    vector<string> strs = splitString(data);

    return deserializeReal(strs, index);
  }
};

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