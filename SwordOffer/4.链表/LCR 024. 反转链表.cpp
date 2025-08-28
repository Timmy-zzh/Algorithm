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
 LCR 024. 反转链表
 https://leetcode.cn/problems/UHnkqh/description/

给定单链表的头节点 head ，请反转链表，并返回反转后的链表的头节点。

示例 1：
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]

示例 2：
输入：head = [1,2]
输出：[2,1]

示例 3：
输入：head = []
输出：[]

提示：
链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000
进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
 */

/**
 * 1、审题：输入一个链表，要求将该链表的结点进行翻转，并最终返回翻转后的链表头结点
 * 2、解题：
 * - 使用三个指针变量来实现，prev，curr，next
 * - prev用于记录翻转后的链表的头结点，也就是原始链表操作的前一个结点位置
 * - curr用于记录当前操作的指针，next指针用于记录当前操作指针curr的下一个指针结点
 * - 在curr操作的时候，需要使用next指针记录curr的下一个指针位置，因为curr的处理逻辑是将指针域指向prev
 * - 如果没有next指针记录着，则链表就会断开了，而prev也需要重新赋值为curr指针，这样prev就一直是翻转后链表的头结点位置
 */
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;
    ListNode *next = nullptr;

    while (curr != nullptr)
    {
        // 记录下一个指针位置
        next = curr->next;
        // curr指针域处理指向prev翻转后的指针头结点
        curr->next = prev;
        // 翻转后链表的头结点prev更新
        prev = curr;
        // curr指针重新赋值为next，让原始链表继续往后遍历
        curr = next;
    }
    return prev;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3

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

    auto res = reverseList(&node1);

    std::cout << "res:" << res->val << std::endl;
    res->print();

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