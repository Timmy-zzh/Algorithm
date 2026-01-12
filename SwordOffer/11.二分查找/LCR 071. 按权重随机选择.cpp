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
LCR 071. 按权重随机选择
https://leetcode.cn/problems/cuyjEf/description/

给定一个正整数数组 w ，其中 w[i] 代表下标 i 的权重（下标从 0 开始），请写一个函数 pickIndex ，它可以随机地获取下标 i，选取下标 i 的概率与 w[i] 成正比。
例如，对于 w = [1, 3]，挑选下标 0 的概率为 1 / (1 + 3) = 0.25 （即，25%），而选取下标 1 的概率为 3 / (1 + 3) = 0.75（即，75%）。
也就是说，选取下标 i 的概率为 w[i] / sum(w) 。

示例 1：
输入：
inputs = ["Solution","pickIndex"]
inputs = [[[1]],[]]
输出：
[null,0]
解释：
Solution solution = new Solution([1]);
solution.pickIndex(); // 返回 0，因为数组中只有一个元素，所以唯一的选择是返回下标 0。

示例 2：
输入：
inputs = ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
inputs = [[[1,3]],[],[],[],[],[]]
输出：
[null,1,1,1,1,0]
解释：
Solution solution = new Solution([1, 3]);
solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4 。
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 1
solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4 。

由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
[null,1,1,1,1,0]
[null,1,1,1,1,1]
[null,1,1,1,0,0]
[null,1,1,1,0,1]
[null,1,0,1,0,0]
......
诸若此类。

提示：
1 <= w.length <= 10000
1 <= w[i] <= 10^5
pickIndex 将被调用不超过 10000 次
 */

/**
 * 1、审题： 输入一个整数数组，他有一个pickIndex方法，要求该方法返回数组中的一个下标，返回数组下标的概率和该下标对应元素的值在整个数组中的占比成正比
 * - 也就是说，该数组元素值越大，那么返回该元素下标的比例也越高
 * 2、解题：
 * - 将上面的问题转换成累加和数组，新数组的元素值表示能够承接的元素范围
 * - 使用变量total表示所有数组元素的累加和，根据该total值计算他的随机数，以随机数作为基准值取新的累加数组中获取对应的下标值
 * - 要求在新数组中寻找第一个比基准值大的元素，并返回该下标，使用二分法查询方式来解题
 */
class Solution
{
public:
    Solution(vector<int> &w)
    {
        for (auto num : w)
        {
            total += num;
            nums.push_back(total);
        }
    }
    static int genRandomNum(int total)
    {
        // 随机数引擎（生成器）
        std::random_device rd;
        std::mt19937 gen(rd());

        // 定义分布范围
        std::uniform_int_distribution<> dis(0, total - 1);

        // 生成随机数
        int random_num = dis(gen);
        return random_num;
    }

    int pickIndex()
    {
        // 生成随机数
        int p = genRandomNum(total);
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > p)
            {
                if (mid == 0 || nums[mid - 1] <= p)
                {
                    return mid;
                }
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return nums.size() - 1;
    }

private:
    int total = 0;
    std::vector<int> nums;
};

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