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
LCR 078. 合并 K 个升序链表
https://leetcode.cn/problems/vvXgSW/description/

给定一个链表数组，每个链表都已经按升序排列。
请将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6

示例 2：
输入：lists = []
输出：[]

示例 3：
输入：lists = [[]]
输出：[]

提示：
k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4
 */

/**
 * 合并两个链表：
 * - 创建临时链表节点，然后不断将值小的结点插入到链表中
 */
ListNode *mergeList(ListNode *head1, ListNode *head2)
{
  ListNode *dummy = new ListNode();
  ListNode *curr = dummy;

  while (head1 != nullptr && head2 != nullptr)
  {
    if (head1->val < head2->val)
    {
      curr->next = head1;
      head1 = head1->next;
    }
    else
    {
      curr->next = head2;
      head2 = head2->next;
    }
    curr = curr->next;
  }
  curr->next = head1 != nullptr ? head1 : head2;
  return dummy->next;
}

/**
 * 二分查找不断拆分，递归实现
 * 然后合并两个链表
 */
ListNode *mergeKListsReal(vector<ListNode *> &lists, int start, int end)
{
  if (start + 1 == end)
  {
    return lists[start];
  }

  int mid = start + (end - start) / 2;
  ListNode *head1 = mergeKListsReal(lists, start, mid);
  ListNode *head2 = mergeKListsReal(lists, mid, end);

  return mergeList(head1, head2);
}

/**
 * 解法2：采用归并排序拆分思想
 * - 先将归并算法思想，将链表数据中的所有链表进行不断拆分，分成两个部分，直到只剩下单独的一个链表，然后将前后两部分链表合并
 */
ListNode *mergeKLists(vector<ListNode *> &lists)
{
  if (lists.empty())
  {
    return nullptr;
  }
  return mergeKListsReal(lists, 0, lists.size());
}

/**
 * 1、审题：输入k个升序排序的链表，现在要将这k个链表合并成一个单独的链表
 * 2、解题：将所有链表的头结点放到一个小顶堆数组中，然后取最小值添加到链表中，不断重复这个步骤
 * - 节点添加到链表中，需要将后面节点继续插入到小顶堆中
 */
static bool camp(ListNode *m, ListNode *n)
{
  return m->val > n->val;
}

ListNode *mergeKLists1(vector<ListNode *> &lists)
{
  priority_queue<ListNode *, std::vector<ListNode *>, decltype(&camp)> min_heap(camp);

  // 1、遍历k个链表，将链表头结点插入到最小堆中
  for (auto item : lists)
  {
    if (item != nullptr)
    {
      min_heap.push(item);
    }
  }

  // 2、新建最终结果链表，获取最小堆的堆顶元素，取出来并插入到结果链表中
  ListNode *dummy = new ListNode(0);
  ListNode *curr = dummy;
  while (!min_heap.empty())
  {
    auto topNode = min_heap.top();
    min_heap.pop();
    curr->next = topNode;

    // 添加
    if (topNode->next != nullptr)
    {
      min_heap.push(topNode->next);
    }
    curr = curr->next;
  }

  return dummy->next;
}

int main()
{
  std::cout << "《剑指offer》" << std::endl;
  ListNode node1(4);
  ListNode node2(2);
  ListNode node3(1);
  ListNode node4(3);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node1.print();

  // auto res = sortArray(nums);
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