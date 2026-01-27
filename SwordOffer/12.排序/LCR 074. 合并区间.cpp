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
 * - 想不明白的就画图辅助理解。
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
LCR 074. 合并区间
https://leetcode.cn/problems/SsGoHC/description/

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

示例 1：
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

提示：
1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104
 */

/**
 * 1、审题：
 * - 输入一个数组，数组中的每个元素是也是一个包含一个范围的数组，现在要对数组中每个范围进行处理，将相互重叠的范围进行合并，并返回最终合并的数组
 * 2、解题：
 * - 先排序，对数组根据范围值的开始位置进行升序排序，可以使用stl的排序算法
 * - 然后遍历排序后的数组，判断当前遍历的范围，和前一个范围是否有重叠，有重叠的情况则合并，没有重叠则将前一个范围放入到数组中
 * - 并最终返回结果，记得遍历完后，要将最后一个范围添加到数组中。
 */
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    // 先排序
    std::sort(intervals.begin(), intervals.end(),
              [](const vector<int> &a, const vector<int> &b)
              { return a[0] < b[0]; });

    // 遍历，从第2个范围值开始
    vector<int> prevArr = intervals[0];
    vector<vector<int>> res;

    for (int i = 1; i < intervals.size(); i++)
    {
        vector<int> currArr = intervals[i];
        /**
         * 判断当前遍历的范围，和prev范围是否有重叠
         * 重叠的条件是，prev[1] >= currArr[0]
         */
        if (currArr[1] <= prevArr[1]) // 判断是否有有包含
        {
            continue;
        }

        // 有重叠
        if (currArr[0] <= prevArr[1])
        {
            // 跟新prevArr[1]
            prevArr[1] = currArr[1];
        }
        else
        {
            // 没有重叠，将前一个范围入队列，重新赋值prevArr
            res.push_back({prevArr[0], prevArr[1]});
            prevArr = currArr;
        }
    }
    res.push_back({prevArr[0], prevArr[1]});

    return res;
}

int main()
{
    std::cout << "《C++ Primer Plus》" << std::endl;

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