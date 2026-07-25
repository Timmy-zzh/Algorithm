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
LCR 111. 除法求值
https://leetcode.cn/problems/vlzXQL/description/

给定一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。
另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。
注意：输入总是有效的。可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

示例 1：
输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]

示例 2：
输入： equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]

示例 3：
输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]

提示：
1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj 由小写英文字母与数字组成
 */

/**
 * 1、审题：输入两个数组，数组equations中单个元素中的两个字符串相除得到的结果是数组values中元素值，
 * - 现在有新的数组queries，它里面的元素也是两两对应的，现在要根据之前已经存在的数组值，求queries数组中元素两元素的除法的结果值组成的数组并返回
 * 2、解题：dfs深度优先算法，
 * - 求queries数组中每个元素中的两个字符串，从开头与结尾元素的除法结果，需要遍历queries中的数组，拿到数组中元素的两个字符串，从第一个字符串开始
 * -- 进行深度优先遍历，从原始数组equations中找出开始字符串可以接下来的可执行的路径节点，直到遇到第二个字符串，并在这个过程中记录他们的比值结果
 * - 再使用一个vector集合保存有的的字符串
 */

/**
 * 根据提供的两个数组 equations和 values，查找一start为基准，他能达到的所有下一个节点和对应除法值的对应结果值pair结果，并返回
 */
vector<pair<string, double>> getLinkNodes(vector<vector<string>> &equations, vector<double> &values, const string &start)
{

    vector<pair<string, double>> linkNodes;

    for (int i = 0; i < equations.size(); i++)
    {

        vector<string> equation = equations[i];

        if (equation[0] == start) // 第一位元素等于start
        {
            linkNodes.push_back({equation[1], values[i]});
        }
        else if (equation[1] == start)
        {
            // 第二位元素等于start，valus值为倒数了
            linkNodes.push_back({equation[0], 1 / values[i]});
        }
    }

    return linkNodes;
}

double dfs(vector<vector<string>> &equations, vector<double> &values, vector<string> &visited,
           const string &start, const string &end, double itemValue)
{

    std::cout << "dfs --- start:" << start << " ,end:" << end << std::endl;
    if (end == start)
    {
        return itemValue;
    }

    // 根据start查找与之关联的下一个节点
    vector<pair<string, double>> linkNodes = getLinkNodes(equations, values, start);
    std::cout << "dfs --- start:" << start << " ,getLinkNodes === :" << std::endl;
    for (auto ele : linkNodes)
    {
        std::cout << "first:" << ele.first << " ,secode:" << ele.second;
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // 遍历，计算itemVlaue值
    for (const auto &node : linkNodes)
    {
        if (std::find(visited.begin(), visited.end(), node.first) != visited.end()) // 遍历过，不处理
        {
            continue;
        }
        visited.push_back(node.first);

        itemValue = itemValue * node.second;
        double res = dfs(equations, values, visited, node.first, end, itemValue);
        if (res != -1.0)
        {
            return res; // 找到了，直接返回
        }
        itemValue = itemValue / node.second;
    }

    return -1.0;
}

vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
{
    std::cout << "calcEquation:" << std::endl;

    vector<string> onlyWords;
    for (auto &equation : equations)
    {
        for (auto &word : equation)
        {
            if (std::find(onlyWords.begin(), onlyWords.end(), word) == onlyWords.end()) // 集合中没有，则添加到集合中去
            {
                onlyWords.push_back(word);
            }
        }
    }

    vector<double> resArr;
    vector<string> visited; // 记录已经遍历过的单词

    for (auto &querie : queries)
    {
        // 判断数组元素中，两个单词字符串是否在集合中
        if (std::find(onlyWords.begin(), onlyWords.end(), querie[0]) == onlyWords.end() ||
            std::find(onlyWords.begin(), onlyWords.end(), querie[1]) == onlyWords.end()) // 集合中没有
        {
            resArr.push_back(-1.0);
            continue;
        }
        visited.push_back(querie[0]);
        double itemValue = dfs(equations, values, visited, querie[0], querie[1], 1.0);
        resArr.push_back(itemValue);
        visited.clear();
    }

    return resArr;
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
     * 示例 1：
  输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
  输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
  解释：
  条件：a / b = 2.0, b / c = 3.0
  问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
  结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
     */

    // vector<string> wordList = {"0201", "0101", "0102", "1212", "2002"};
    // vector<string> wordList = {"8888"};

    // vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)

    vector<vector<string>> equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<vector<string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
    auto res = calcEquation(equations, values, queries);
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