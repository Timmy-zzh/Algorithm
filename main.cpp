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
#include "src/bean.h"
#include <random>
#include <algorithm>
#include <unordered_set>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。写就是思考
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LeetCode 67. 二进制求和
https://leetcode.cn/problems/add-binary/description/

给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。

示例 1：
输入:a = "11", b = "1"
输出："100"

示例 2：
输入：a = "1010", b = "1011"
输出："10101"

提示：
1 <= a.length, b.length <= 104
a 和 b 仅由字符 '0' 或 '1' 组成
字符串如果不是 "0" ，就不含前导零
 */

/**
 * 1、审题：输入两个字符串，字符串是由二进制的0和1组成，现在要将两个字符串中的二进制进行加法运算，并以二进制的形式返回他们的和
 * 2、解题：
 * - 通过while循环，不断两个字符串中二进制的最低位，两个字符串都需要获取，如果没有则使用0代替，
 * - 将获取到的字符串转成int类型，然后进行加法运算，如何和超过1，则需要进位处理
 * - 将所有字符串位数的和结果添加到结果字符串中
 */
string addBinary(string a, string b)
{
  int index1 = a.length() - 1;
  int index2 = b.length() - 1;
  string res = "";
  int carry = 0; // 进位
  int item = 0;
  while (index1 >= 0 || index2 >= 0)
  {
    int int1 = index1 >= 0 ? (a[index1] - '0') : 0;
    int int2 = index2 >= 0 ? (b[index2] - '0') : 0;

    int sum = int1 + int2 + carry;
    carry = sum / 2; // 进位
    item = sum % 2;  // 取余，就是当前位的值

    res = std::to_string(item) + res;

    index1--;
    index2--;
  }

  if (carry > 0)
  {
    res = std::to_string(carry) + res;
  }

  return res;
}

int main()
{
  std::cout << "《剑指》" << std::endl;
  auto res = addBinary("11", "1");
  std::cout << "res:" << res << std::endl;

  // vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};
  // vector<string> words = {"tars", "rats", "arts", "star"};

  // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
  // vector<vector<int>> prerequisites = {
  //     {1, 0},
  //     {2, 0},
  //     {3, 1},
  //     {3, 2},
  // };

  // vector<int> nums = {1, 2, 3};
  // vector<vector<int>> isConnected = {
  //     {1, 0, 0, 1},
  //     {0, 1, 1, 0},
  //     {0, 1, 1, 1},
  //     {1, 0, 1, 1},
  // };
  // vector<vector<int>> isConnected = {
  //     {1, 1, 0},
  //     {1, 1, 0},
  //     {0, 0, 1},
  // };

  // vector<int> nums = {100, 4, 200, 1, 3, 2};
  // vector<int> nums = {4, 0, -4, -2, 2, 5, 2, 0, -8, -8, -8, -8, -1, 7, 4, 5, 5, -4, 6, 6, -3};
  // auto res = longestConsecutive(nums);
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
  //   for (auto element : ele)
  //   {
  //     std::cout << element << ",";
  //   }
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "map +++++++++++++++ " << std::endl;
  // for (auto ele : map)
  // {
  //   std::cout << ele.first << " ---- nextNodes: " << std::endl;
  //   for (auto ele : ele.second)
  //   {
  //     std::cout << ele;
  //     std::cout << std::endl;
  //   }

  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  // std::cout << "inDegreeMap ============ " << std::endl;
  // for (auto ele : inDegreeMap)
  // {
  //   std::cout << ele.first << " ---- " << ele.second;
  //   std::cout << std::endl;
  // }
  // std::cout << std::endl;

  return 0;
}