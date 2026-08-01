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

/**
 * 感想：
 * - 脑子得练才行,光看书,不动手写,那不行！效果打骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 * - 学以致用，才会发生改变，更何况不学
 */
using namespace std;

/**
LCR 113. 课程表 II
https://leetcode.cn/problems/QA2IGt/description/

现在总共有 numCourses 门课需要选，记为 0 到 numCourses-1。
给定一个数组 prerequisites ，它的每一个元素 prerequisites[i] 表示两门课程之间的先修顺序。
例如 prerequisites[i] = [ai, bi] 表示想要学习课程 ai ，需要先完成课程 bi 。
请根据给出的总课程数  numCourses 和表示先修顺序的 prerequisites 得出一个可行的修课序列。
可能会有多个正确的顺序，只要任意返回一种就可以了。如果不可能完成所有课程，返回一个空数组。

示例 1：
输入: numCourses = 2, prerequisites = [[1,0]]
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1]。

示例 2：
输入: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。因此，一个正确的课程顺序是 [0,1,2,3]。另一个正确的排序是 [0,2,1,3]。

示例 3：
输入: numCourses = 1, prerequisites = []
输出: [0]
解释: 总共 1 门课，直接修第一门课就可。

提示：
1 <= numCourses <= 2000
0 <= prerequisites.length <= numCourses * (numCourses - 1)
prerequisites[i].length == 2
0 <= ai, bi < numCourses
ai != bi
prerequisites 中不存在重复元素
 */

/**
 * 1、审题：现在一共有n门需要学习的课程，和两门课程之前学习的顺序组合关系数组 prerequieites,内部的单个元素是一个数组：数组内有两门课程标记先要修后面课程，才能修前面课程
 * - 问根据学习课程的顺序关系，得出一个可以课程学习的序列
 * 2、解题：拓扑排序算法
 * - 先将每门课程的入度和出度找出来，先找出所有入度为0的课程，放到队列中，去除这个课程，然后找出他指向的课程
 * - 对应指向课程的入度减少1，然后判断入度减少的课程的入度是否等于0，等于0的话需要放到队列中去
 * - 使用一个大小为n的vector数组保存每门课程对应的入度，再从中选出入度为0的课程，放到队列queue中去
 * - 然后while遍历，从队列中不断取出入度为0的课程，再通过prerequisites课程关系数组，找出存在依赖的课程，存在依赖关系的课程的入度对应减少1，并判断入度是否为0
 * - 将入度为0的新的课程添加到队列中去，直到队列为空
 * - 将所有出队列的课程添加到一个集合中并返回
 * 3、之前有个问题没想明白，就是如果刚开始如果有两个以上的节点的入度都是0，那如果都一开始就全部放入到队列中去，
 * - 后面从队列中获取的话，就是先从队列中获取这两个入度为0的节点，第一个节点遍历后的节点都得往后靠
 * - 其实这样也没问题啊？ 之前这快一直转不过弯来。
 */
vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{

    vector<int> resArr;
    // 课程对应入度的数组
    vector<int> inputArr(numCourses, 0);

    // 遍历 prerequisites 找出课程对应的入度
    for (auto item : prerequisites)
    {
        inputArr[item[0]]++;
    }

    // 遍历inputArr，找到入度为0的课程，放到队列中去
    queue<int> queue;
    for (int course = 0; course < numCourses; course++)
    {
        if (inputArr[course] == 0)
        {
            queue.push(course);
        }
    }

    while (!queue.empty())
    {
        auto node = queue.front();
        queue.pop();
        resArr.push_back(node);

        // 遍历 prerequisites ，找到与之存在关系的课程
        for (auto item : prerequisites)
        {
            if (node == item[1])
            {
                // 他的入度要减少
                inputArr[item[0]]--;

                // 减少一个入度后，判断入度是否为0
                if (inputArr[item[0]] == 0)
                {
                    queue.push(item[0]);
                }
            }
        }
    }

    return resArr.size() == numCourses ? resArr : vector<int>();
}

int main()
{
    std::cout << "《剑指》" << std::endl;

    vector<vector<int>> graph = {
        {1, 2},
        {3},
        {3},
        {},
    };

    /**
  输入: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
  输出: [0,1,2,3] or [0,2,1,3]
     */

    // vector<string> wordList = {"0201", "0101", "0102", "1212", "2002"};
    // vector<string> wordList = {"8888"};

    // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)

    vector<vector<int>> prerequisites = {
        {1, 0},
        {2, 0},
        {3, 1},
        {3, 2},
    };
    auto res = findOrder(4, prerequisites);
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
    //   for (auto element : ele)
    //   {
    //     std::cout << element << ",";
    //   }
    //   std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}