#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
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
LCR 035. 最小时间差
https://leetcode.cn/problems/569nqc/description/

给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。

示例 1：
输入：timePoints = ["23:59","00:00"]
输出：1

示例 2：
输入：timePoints = ["00:00","23:59","00:00"]
输出：0

提示：
2 <= timePoints <= 2 * 104
timePoints[i] 格式为 "HH:MM"
 */

/**
 * 1、审题：
 * - 输入一个表示时间字符串的数组，时间表示格式为"HH:MM"，就这个给出的时间数组中，相邻两个时间之间差值最小，并以分钟数返回
 * 2、解题：
 * 解法1：暴力解法
 * - 让每个时间和其他的时间进行比较并求差值，获取最小值，时间复杂度高为O(n的平方)
 *
 * 解法2：先排序后求差值
 * - 对输入的vector时间进行排序，先判断小时，再判断分钟时间，按照升序进行排序
 * - 对遍历后的时间数组，进行两两求差值，得到差值最小的数据，
 * - 还要注意头尾两个时间的处理，也要求他们之间的差值
 * - 如果遇到两个时间相同，则直接返回0
 *
 * 解法3：哈希表解法
 * - 将一天的时间全部按照分钟来表示，全部数值为 60*24 = 1440
 * - 使用一个布尔数组bool[24]，表示该时间是否有值，这样就转换成求1440个数组内，有bool=true值的差值
 * - 还是要注意头尾两个时间的差值计算
 * 
 * 3、总结：
 * - pair的使用
 * - find和substr方法，对字符串进行截取，如果有多个截取使用getline进行循环截取
 * - 将时间字符串转成数字，因为一天的时间是固定的，使用数组代替哈希表进行数据的保存
 */

static int getMin(const std::string &time)
{
    int pos = time.find(":");
    if (pos == std::string::npos)
    {
        return 0;
    }

    // 获取到小时
    std::string hourStr = time.substr(0, pos);
    std::string minStr = time.substr(pos + 1);
    return std::stoi(hourStr) * 60 + std::stoi(minStr);
}

/**
 * 哈希表解法：将时间数组中的时间，转成bool数组
 */
int findMinDifference(vector<string> &timePoints)
{
    std::vector<bool> timeBools(1440, false);
    if (timePoints.size() > 1440)
    {
        return 0;
    }
    // 遍历，组合bool数组
    for (int i = 0; i < timePoints.size(); i++)
    {
        int min = getMin(timePoints[i]);
        std::cout << "min:" << min << std::endl;
        if (timeBools[min])
        {
            return 0;
        }
        timeBools[min] = true;
    }

    // 继续遍历timeBools 求时间差
    int res = INT32_MAX;
    // 临时变量，标记前一个值为true的数据，和最前，最后的位置
    int prev = -1;
    int first = timeBools.size();
    int last = 0;

    for (int i = 0; i < timeBools.size(); i++)
    {
        if (timeBools[i]) // 为true
        {
            if (prev != -1)
            {
                // 求差值
                int diff = i - prev;
                if (diff < res)
                {
                    res = diff;
                }
            }
            prev = i;
            first = std::min(first, i);
            last = std::max(last, i);
        }
    }

    std::cout << "res1:" << res << std::endl;
    // 求头尾两个时间的差值
    int diff = first + timeBools.size() - last;
    if (diff < res)
    {
        res = diff;
    }
    std::cout << "res2:" << res << std::endl;

    return res;
}

// 使用find找到冒号：的位置pos，再使用substr方法进行时间的切割
static std::pair<int, int> parseTime(const std::string &time)
{
    int pos = time.find(":");
    if (pos == std::string::npos)
    {
        return {0, 0};
    }

    // 获取到小时
    std::string hourStr = time.substr(0, pos);
    std::string minStr = time.substr(pos + 1);
    return {std::stoi(hourStr), std::stoi(minStr)};
}

int findMinDifference1(vector<string> &timePoints)
{
    // 升序排序处理
    std::sort(timePoints.begin(), timePoints.end(),
              [](const std::string &a, const std::string &b)
              {
                  // 将a，b处理，获取到小时和分钟,根据：进行分割
                  auto aTime = parseTime(a);
                  std::cout << "a:" << aTime.first << ":" << aTime.second << std::endl;
                  auto bTime = parseTime(b);
                  std::cout << "b:" << bTime.first << ":" << bTime.second << std::endl;
                  if (aTime.first == bTime.first) // 小时相等，比较分钟
                  {
                      return aTime.second < bTime.second;
                  }
                  else
                  {
                      return aTime.first < bTime.first;
                  }
              });

    std::cout << "for ----- :" << std::endl;
    for (auto element : timePoints)
    {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    int res = INT32_MAX;

    // 遍历排序后的数据，求取他们之间的差值
    for (int i = 1; i < timePoints.size(); i++)
    {
        auto preTime = parseTime(timePoints[i - 1]);
        auto currTime = parseTime(timePoints[i]);
        int diff = (currTime.first - preTime.first) * 60 + (currTime.second - preTime.second);

        if (diff == 0)
        { // 存在相同的两个时间
            return 0;
        }
        if (diff < res)
        {
            res = diff;
        }
        std::cout << "res1 :" << res << std::endl;
    }
    // 前后两个时间点的差值
    auto firstTime = parseTime(timePoints[0]);
    firstTime.first = firstTime.first + 24;
    auto lastTime = parseTime(timePoints[timePoints.size() - 1]);
    int diff = (firstTime.first - lastTime.first) * 60 + (firstTime.second - lastTime.second);
    if (diff < res)
    {
        res = diff;
    }
    std::cout << "res2 :" << res << std::endl;

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // vector<string> timePoints = {"00:00", "23:59", "00:00"};
    vector<string> timePoints = {"01:01", "02:01"};

    auto res = findMinDifference(timePoints);
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