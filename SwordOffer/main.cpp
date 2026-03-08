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
 * - 脑子得练才行,光看书,不动手写,那不行！效果打/home/yingzi/zzh_work/github/Algorithm/SwordOffer/12.排序/LCR 075. 数组的相对排序.cpp骨折。
 * - 多写,写思路,写想法,描述出来,自然就会思考的更清楚,更快速。
 * - 一定不要留下疑问而继续,一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt,cpp技术为当下所需要,接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时,1小时用于算法实现,1小时用于cpp和Qt,一个长久的积累,一个短期的提升。
 * - 不可复制粘贴,每一行代码都要自己实现,每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
LCR 077. 排序链表
https://leetcode.cn/problems/7WHec2/description/

给定链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

示例 1：
输入：head = [4,2,1,3]
输出：[1,2,3,4]

示例 2：
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]

示例 3：
输入：head = []
输出：[]

提示：
链表中节点的数目在范围 [0, 5 * 104] 内
-105 <= Node.val <= 105
进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 */

/**
 * 快慢指针，将输入的链表分割成前后两部分，并返回后半部分
 */
ListNode *spliteList(ListNode *head)
{
  ListNode *fast = head;
  ListNode *slow = head;
  ListNode *prev = nullptr;

  while (fast != nullptr && fast->next != nullptr)
  {
    fast = fast->next->next;
    prev = slow;
    slow = slow->next;
  }
  slow->next = nullptr;
  return slow;
}

ListNode *realSortList(ListNode *head)
{
  if (head->next == nullptr)
  {
    return head;
  }

  // 拆分链表
  ListNode *head2 = spliteList(head);

  // 对两段链表不断进行排序
  ListNode *newHead1 = realSortList(head);
  ListNode *newHead2 = realSortList(head2);

  // 将两个链表合并到一起 newHead1,newHead2
  // mergeList(head,head2);
  ListNode *dummy = new ListNode(0); // 虚拟临时指针
  ListNode *tempNode = dummy;
  while (newHead1 != nullptr && newHead2 != nullptr)
  {
    if (newHead1->next->val < newHead2->next->val)
    {
      tempNode->next = newHead1;
      newHead1 = newHead1->next;
    }
    else
    {
      dummy->next = newHead2;
      newHead2 = newHead2->next;
    }
    tempNode = tempNode->next;
  }
  if (newHead1 != nullptr)
  {
    tempNode = newHead1;
  }
  if (newHead2 != nullptr)
  {
    tempNode = newHead2;
  }

  return dummy->next;
}

/**
 * 使用归并排序算法进行遍历排序,归并排序采用的分支思想
 * - 将原先的链表不断拆分成两段，直到两段链表的长度为1为止
 * - 接着将两段链表重新拼接在一起，并且按照升序排列，并返回新排序好的链表
 */
ListNode *sortList(ListNode *head)
{
  return realSortList(head);
}

/**
 * 1、审题： 输入一个链表，要求将该链表进行升序排序处理，并最终返回排序后的链表
 * 2、解题：暴力解法
 * - 遍历原始的链表节点，并新建一个链表用于保存之前遍历的结点
 * - 将遍历到的结点插入到新链表中，并且是按照升序排序的，要求找到第一个大于当前结点大小的元素
 * 3、时间复杂度为n平方
 * - 内层for循环，每次都要重头开始遍历寻找到合适的前继节点用来插入新节点
 */
ListNode *sortList(ListNode *head)
{
  ListNode *dummy = new ListNode(-1);
  ListNode *headNode = dummy;

  // 遍历head链表，取出链表的结点
  ListNode *node = head;
  while (node != nullptr)
  {
    // 判断当前遍历到的结点大小于新链表的值大小
    while (headNode->next != nullptr && headNode->next->val < node->val)
    {
      headNode = headNode->next;
    }
    // 否则就是遍历到newNode链表的末尾节点，或者找到了第一个大于node节点的值->插入一个新节点
    ListNode *newNode = new ListNode(node->val);
    if (headNode->next == nullptr) // 链表尾部插入
    {
      headNode->next = newNode;
    }
    else
    {
      newNode->next = headNode->next; // 中间插入节点
      headNode->next = newNode;
    }
    // 重新将新链表设置为头结点，用于下次遍历判断大小
    headNode = dummy;
    // headNode->print();

    {
      ListNode *printNode = headNode;
      while (printNode != nullptr)
      {
        std::cout << printNode->val << " ,";
        printNode = printNode->next;
      }
      std::cout << std::endl;
    }

    node = node->next;
  }

  return dummy->next;
}

int main()
{
  std::cout << "剑指offer" << std::endl;
  ListNode node1(4);
  ListNode node2(2);
  ListNode node3(1);
  ListNode node4(3);

  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node1.print();

  ListNode *sortNode = sortList(&node1);

  sortNode->print();

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