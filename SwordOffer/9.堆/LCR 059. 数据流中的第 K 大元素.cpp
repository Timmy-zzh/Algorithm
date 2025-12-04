#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stack>
#include <queue>
#include "src/bean.h"

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
 * 最大堆：
 * 最小堆：
 */

/**
LCR 059. 数据流中的第 K 大元素
https://leetcode.cn/problems/jBjn9C/description/

设计一个找到数据流中第 k 大元素的类（class）。注意是排序后的第 k 大元素，不是第 k 个不同的元素。

请实现 KthLargest 类：
KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。

示例：
输入：
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
输出：
[null, 4, 5, 5, 8, 8]

解释：
KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3);   // return 4
kthLargest.add(5);   // return 5
kthLargest.add(10);  // return 5
kthLargest.add(9);   // return 8
kthLargest.add(4);   // return 8

提示：
1 <= k <= 104
0 <= nums.length <= 104
-104 <= nums[i] <= 104
-104 <= val <= 104
最多调用 add 方法 104 次
题目数据保证，在查找第 k 大元素时，数组中至少有 k 个元素
 */

/**
 * 1、审题：
 * - 实现一个获取集合中第k大的值的一个类，在构造函数中输入数组nums和数值k
 * - 然后调用add方法，往集合中插入一个元素val，并且该方法返回集合中的第k大的值
 * 2、解题：
 * - 使用最小堆来求解集合中的最大值，priportyQueue,在构造函数中就开始组装数据，并保证最小堆只有k个元素
 * - 调用add方法插入元素时，先判断最小堆的元素个数是否大于k，如果大于k，则先删除堆中最小元素，然后添加新元素，
 * -- 如果最小堆的元素个数小于k，则直接添加元素，最后返回最小堆的根节点元素值
 */
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;
        // 往最小堆中添加元素，直接调用add方法
        for (auto num : nums)
        {
            add(num);
        }
    }

    /**
     * 往最小堆中添加元素：
     * - 如果当前堆的元素个数小于k，则直接添加元素
     * - 如果当前堆的元素个数大于等于k了，则需要先判断新插入的元素如果大于最小堆顶元素，则堆顶元素出队再插入，否则不插入
     */
    int add(int val)
    {
        if (min_heap.size() < k)
        {
            min_heap.push(val);
        }
        else if (min_heap.top() < val)
        {
            min_heap.pop();
            min_heap.push(val);
        }
        return min_heap.top();
    }

private:
    priority_queue<int, std::vector<int>, std::greater<int>> min_heap; // 最小堆
    priority_queue<int, std::vector<int>, std::less<int>> max_heap;    // 最大堆
    // 最大堆
    priority_queue<int, std::vector<int>> maxHeap;
    int k;
};

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(4);
    TreeNode node5(5);
    TreeNode node6(6);
    TreeNode node7(7);

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = &node5;

    node3.left = &node6;
    node3.right = &node7;

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