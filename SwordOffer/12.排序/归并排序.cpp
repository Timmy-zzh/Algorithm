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

void mergeSort(std::vector<int> &dst, std::vector<int> &nums, int start, int end)
{
  std::cout << "mergeSort start:" << start << " ,end:" << end << std::endl;
  // 判断合并范围
  if (start + 1 >= end)
  {
    return;
  }

  // 区间范围不断拆分
  int mid = start + (end - start) / 2;
  mergeSort(dst, nums, start, mid);
  mergeSort(dst, nums, mid, end);

  // 将两个区间进行合并[start,mid) , [mid,end)
  int k = start;
  int i = start;
  int j = mid;

  std::cout << "mergeSort  start:" << start << " ,mid:" << mid << " ,end:" << end << std::endl;
  while (i < mid || j < end)
  {
    // 找到左侧最小值,
    if (j == end || (i < mid && nums[i] < nums[j]))
    {
      dst[k++] = nums[i++];
    }
    else
    {
      dst[k++] = nums[j++];
    }
  }
  // 将排序好的区间范围数组元素，复制到nums中
  for (int i = start; i < end; i++)
  {
    nums[i] = dst[i];
  }
}

/**
 * 归并排序：
 * 归并排序同样使用分治思想,将数组不断拆分成更小的范围,直到范围为1
 * 然后将两个范围的数组合并,根据大小判断,不断遍历获取到更小值的元素,添加到新的数组中
 */
std::vector<int> sortArray(std::vector<int> &nums)
{
  // 新的数组,保存归并排序后的元素
  std::vector<int> dst(nums.size());
  std::cout << "nums address:" << &nums << " ,dst address:" << &dst << std::endl;
  mergeSort(dst, nums, 0, nums.size());
  return dst;
}

int main()
{
  std::cout << "《C++ Primer Plus》" << std::endl;

  vector<int> nums = {4, 1, 5, 6, 2, 7, 8, 3};

  for (auto ele : nums)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

  auto res = sortArray(nums);
  std::cout << "归并排序后" << std::endl;

  // std::cout << "res:" << res << std::endl;

  // 遍历1维数组
  for (auto ele : res)
  {
    std::cout << ele << ",";
  }
  std::cout << std::endl;

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