#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "src/bean.h"

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 * - 一定不要留下疑问而继续，一定要要把问题彻底搞清楚。
 * - 想不明白的就画图辅助理解
 * - 技术精进：算法为长远； Qt，cpp技术为当下所需要，接着是架构设计
 * -- 每天花在技术提升上的时间至少2小时，1小时用于算法实现，1小时用于cpp和Qt，一个长久的积累，一个短期的提升。
 */
using namespace std;

/**
LCR 026. 重排链表
https://leetcode.cn/problems/LGjMqU/description/

给定一个单链表 L 的头节点 head ，单链表 L 表示为：
 L0 → L1 → … → Ln-1 → Ln
请将其重新排列后变为：
L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

示例 1：
输入: head = [1,2,3,4]
输出: [1,4,2,3]

示例 2：
输入: head = [1,2,3,4,5]
输出: [1,5,2,4,3]

提示：
链表的长度范围为 [1, 5 * 104]
1 <= node.val <= 1000
 */

ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;
    ListNode *next = nullptr;

    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

void mergeList(ListNode *node1, ListNode *node2)
{
    ListNode *tempNode = new ListNode();

    while (node1 != nullptr || node2 != nullptr)
    {
        tempNode->next = node1;
        node1 = node1->next;
        tempNode = tempNode->next;

        if (node2 != nullptr)
        {
            tempNode->next = node2;
            node2 = node2->next;
            tempNode = tempNode->next;
        }
    }
}

/**
 * 1、审题：输入一个链表，例如链表节点数据内容为（1,2,3,4,5,6），对链表重新排列，排列后的链表内容为(1,6,2,5,3,4)
 * 2、解题：
 * - 先将链表分成两段，使用快慢指针实现，找到链表的中间节点
 * - 将后半部分的链表进行翻转，
 * - 最后将链表的前半部分数据段和翻转后的部分链表进行合并，没有返回说明是在原始链表中处理
 */
void reorderList(ListNode *head)
{
    // 1、快慢指针找链表中间节点,使用哨兵节点
    ListNode *dummy = new ListNode();
    dummy->next = head;
    ListNode *slow = dummy;
    ListNode *fast = dummy->next;

    while (slow != nullptr && fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast != nullptr)
        {
            fast = fast->next;
        }
    }

    // 2、 找到中间节点，将链表截断
    ListNode *mid = slow->next;
    slow->next = nullptr;
    std::cout << "截断后的两个链表：" << std::endl;
    head->print();
    mid->print();
    // 翻转链表
    ListNode *temp = reverseList(mid);
    std::cout << "翻转后的链表：" << std::endl;
    temp->print();

    // 3、将两个链表合并
    mergeList(head, temp);
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    ListNode node1(1);
    ListNode node2(2);
    ListNode node3(3);
    ListNode node4(4);
    ListNode node5(5);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node1.print();

    reorderList(&node1);
    node1.print();

    // auto res = reorderList(&node1);
    // std::cout << "res:" << res->val << std::endl;
    // res->print();

    // 遍历1维数组
    // for (int element : res)
    // {
    //     std::cout << element << ",";
    // }
    // std::cout << std::endl;

    // 遍历2维数组
    // for (vector<int> ele : res)
    // {
    //     for (int element : ele)
    //     {
    //         std::cout << element << ",";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}