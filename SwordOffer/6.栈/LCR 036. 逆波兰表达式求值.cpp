#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <stack>
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
LCR 036. 逆波兰表达式求值
https://leetcode.cn/problems/8Zf90G/description/

根据 逆波兰表示法，求该后缀表达式的计算结果。
有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。

说明：
整数除法只保留整数部分。
给定逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

示例 1：
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

示例 2：
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

示例 3：
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：
该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

提示：
1 <= tokens.length <= 104
tokens[i] 要么是一个算符（"+"、"-"、"*" 或 "/"），要么是一个在范围 [-200, 200] 内的整数

逆波兰表达式：
逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。
平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：
去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中。
 */

/**
 * 1、审题：输入一个字符串数组，字符串数组中的内容为数字和运算符，采用逆波兰表达式，求字符串数组组成的逆波兰表达式的结果
 * 2、解题：使用栈保存运算符计算后的结果
 * - 遍历字符串数组，遇到数字则入栈，遇到运算符（加减乘除）则取出栈顶的两个数字进行运算，并将结果入栈
 * - 继续遍历字符串数组，直到全部遍历完，最后栈中只有一个元素，也就是逆波兰表达式的最终结果
 * 3、总结：
 * - cpp中栈的操作，插入push_back，取出top，删除pop
 * - 表达式运算操作注意，从栈顶出去的元素是后操作数
 * - 将字符串数字转成整数使用stoi
 */
int evalRPN(vector<string> &tokens)
{
  std::stack<int> stack;
  for (int i = 0; i < tokens.size(); i++)
  {
    std::string token = tokens[i];
    if (token == "+" || token == "-" || token == "*" || token == "/")
    {
      // 是云算法,取出栈顶元素，两个
      int next = stack.top();
      stack.pop();
      int prev = stack.top();
      stack.pop();

      int num = 0;
      // 计算
      if (token == "+")
      {
        num = prev + next;
      }
      else if (token == "-")
      {
        num = prev - next;
      }
      else if (token == "*")
      {
        num = prev * next;
      }
      else if (token == "/")
      {
        num = prev / next;
      }

      // 运算符操作结果入栈
      stack.push(num);
    }
    else
    {
      // 是数字
      stack.push(std::stoi(token));
    }
  }

  return stack.top();
}

int main()
{
  std::cout << "Hello, Algorithm!" << std::endl;

  // vector<string> timePoints = {"00:00", "23:59", "00:00"};
  vector<string> timePoints = {"01:01", "02:01"};

  auto res = evalRPN(timePoints);
  std::cout << "res:" << res << std::endl;

  // 遍历1维数组
  // for (auto element : res)
  // {
  //     std::cout << element << ",";
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