#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <queue>
// #include "src/bean.h"

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
LCR 067. 数组中两个数的最大异或值
https://leetcode.cn/problems/ms70jA/description/

给定一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。

示例 1：
输入：nums = [3,10,5,25,2,8]
输出：28
解释：最大运算结果是 5 XOR 25 = 28.

示例 2：
输入：nums = [0]
输出：0

示例 3：
输入：nums = [2,4]
输出：6

示例 4：
输入：nums = [8,10,2]
输出：10

示例 5：
输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
输出：127

提示：
1 <= nums.length <= 2 * 105
0 <= nums[i] <= 231 - 1
进阶：你可以在 O(n) 的时间解决这个问题吗？
 */

/**
 * 解法2：前缀树解法
 * - 将整数num转换成数位保存到前缀树中，数位是二进制，保存的数字不是0就是1，所以前缀树的子节点只有两个，
 * -- 每个整数int类型为32位，如果是正整数，则最左边数位为0。
 * - 先将数组中每个int整数插入到前缀树中，根据他的数位值来创建节点，从最高位到最低位
 * - 查找两个数字的最大异或值，先遍历数字，然后查找与之对应的数位是否存在，如果存在则选中这个节点并且异或值增加1
 * -- 如果没有说明这个数位位置存在相同的数字节点，异或值结果不能增加1，
 * - 问题的关键在于，查找异或值的过程中，下一个节点为异或值的目标节点，而异或值在最高位其值越高，
 * -- 所以异或值的结点从最高位开始就要选择值不同的结点，然后往下一直选择不同值的结点，如果没有不同值结点则选中相同值结点，异或值结果位数值不增加只往右移动
 */

/**
 * 位数前缀树
 * - 只有两个节点，使用长度为2的数组保存节点
 */
class TrieNode
{
public:
  TrieNode *childred[2];

  TrieNode()
  {
    for (int i = 0; i < 2; i++)
    {
      this->childred[i] = nullptr;
    }
  }

  ~TrieNode()
  {
    for (int i = 0; i < 2; i++)
    {
      this->childred[i] = nullptr;
    }
  }
};

TrieNode *buildTrie(vector<int> &nums)
{
  TrieNode *root = new TrieNode();
  // 遍历数组，取出int数字，从最高位取出数位，然后插入到前缀树中
  for (auto num : nums)
  {
    TrieNode *node = root;
    for (int i = 31; i >= 0; --i)
    {
      int bit = (num >> i) & 1; // 数位的数字
      if (node->childred[bit] == nullptr)
      {
        node->childred[bit] = new TrieNode();
      }
      node = node->childred[bit];
    }
  }
  return root;
}

int getMaxXOR(vector<int> &nums, TrieNode *root)
{
  int res = 0;
  // 遍历数组中的整数，根据该整数的数位，从高位到低位，查找与之对应数位的数字节点是否存在，存在或不存在都从该结点的对应结点位置开始往下遍历
  for (const auto num : nums)
  {
    TrieNode *node = root;
    int xorRes = 0;
    for (int i = 31; i >= 0; --i)
    {
      int bit = (num >> i) & 1;
      // 查找与之相对的结点是否存在
      if (node->childred[1 - bit] != nullptr)
      {
        xorRes = (xorRes << 1) + 1;
        node = node->childred[1 - bit];
      }
      else
      {
        xorRes = (xorRes << 1);
        node = node->childred[bit];
      }
    }
    res = std::max(res, xorRes);
  }

  return res;
}

int findMaximumXOR(vector<int> &nums)
{
  TrieNode *root = buildTrie(nums);
  return getMaxXOR(nums, root);
}

/**
 * 1、审题：
 * - 输入一个整数数组，要求对数组中的两个数字进行异或操作xor，并求出最终得到的异或值最大的数值并返回，
 * - 注意两个数字可以相同，所以异或值最小也比当前的遍历值要大
 * 2、解题：暴力解法
 * - 遍历数组中的元素，两两进行异或xor操作，并最出最大值
 */
int findMaximumXOR(vector<int> &nums)
{
  int res = 0;
  int size = nums.size();
  for (int i = 0; i < size; i++)
  { // 两层for循环
    int num1 = nums[i];
    for (int j = i + 1; j < size; j++)
    {
      int num2 = nums[j];
      int xorRes = num1 ^ num2;
      res = max(res, xorRes);
    }
  }
  return res;
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

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