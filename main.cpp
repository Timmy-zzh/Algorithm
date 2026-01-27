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

#include <random>
#include <algorithm>

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打/home/yingzi/zzh_work/github/Algorithm/SwordOffer/12.排序/LCR 075. 数组的相对排序.cpp骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 */
using namespace std;

void mySwap(std::vector<int> &nums, int a, int b)
{
  int temp = nums[a];
  nums[a] = nums[b];
  nums[b] = temp;
}

static int genRandomNum(int start, int end)
{
  // 随机数引擎（生成器）
  std::random_device rd;
  std::mt19937 gen(rd());

  // 定义分布范围
  std::uniform_int_distribution<> dis(start, end - 1);

  // 生成随机数
  int random_num = dis(gen);
  return random_num;
}

int getPoivt(std::vector<int> &nums, int start, int end)
{
  int randIndex = genRandomNum(start, end);
  mySwap(nums, randIndex, end); // 精准值交换到数组末尾

  int small = start - 1;

  for (int i = start; i < end; i++)
  {
    if (nums[i] < nums[end]) // 遍历到的数组元素小于基准值
    {
      small++;
      mySwap(nums, small, i);
    }
  }

  small++;
  mySwap(nums, small, end);
  return small;
}

/**
 * - 先获取基准值,在 (start,end) 范围内获取一个随机数位置
 * - 然后以这个随机数位置为基准值,交换到最后位置
 * - 然后遍历数组范围,寻找到比基准值小的元素,与前面区域的位置进行交换
 */
void quickSortReal(std::vector<int> &nums, int start, int end)
{
  std::cout << "start:" << start << " ,end:" << end << std::endl;
  if (start >= end)
  {
    return;
  }

  int povit = getPoivt(nums, start, end);
  std::cout << " quickSortReal povit:" << povit << std::endl;
  for (auto ele : nums)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

  quickSortReal(nums, start, povit - 1);
  quickSortReal(nums, povit + 1, end);
}

/**
 * 快速排序
 * - 分治思想,通过递归函数,获取数组中一个随机元素作为基准值,将数组分为两个部分,前面部分小于基准值大小,后面部分小于基准值
 * - 然后继续对前后两个区域进行递归处理,直到区域范围为1
 */
vector<int> quickSort(vector<int> &nums)
{
  quickSortReal(nums, 0, nums.size() - 1);
  return nums;
}

int main()
{
  std::cout << "《C++ Primer Plus》" << std::endl;

  vector<int> nums = {4, 1, 5, 3, 6, 2, 7, 8};
  for (auto ele : nums)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

  quickSort(nums);
  std::cout << "quickSort(nums)----------" << std::endl;

  for (auto ele : nums)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

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