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
LCR 025. 两数相加 II
https://leetcode.cn/problems/lMSNwu/description/

给定两个 非空链表 l1和 l2 来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
可以假设除了数字 0 之外，这两个数字都不会以零开头。

示例 1：
输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]

示例 2：
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[8,0,7]

示例 3：
输入：l1 = [0], l2 = [0]
输出：[0]

提示：
链表的长度范围为 [1, 100]
0 <= node.val <= 9
输入数据保证链表代表的数字无前导 0

进阶：如果输入链表不能修改该如何处理？换句话说，不能对列表中的节点进行翻转。
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

/**
 * 1、审题：输入两个链表，链表整体表示一个非负整数，链表的每个结点为单独的一个数字，现在要将表示数字的链表进行相加处理，并返回操作后的链表头结点
 * 2、解题：翻转链表解法
 * - 将两个链表都进行翻转，同时遍历两个链表，获取到同样位置的链表节点
 * - 对链表节点中的数字，进行加法操作，并将加法操作后的结果插入到新链表中，
 * -- 遍历过程中会遇到其中一个链表的结点为null则返回数组0进行加法操作
 */
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{
    ListNode *dummy = new ListNode(); // 哨兵节点

    // 对l1，l2链表进行翻转操作
    ListNode *newL1 = reverseList(l1);
    ListNode *newL2 = reverseList(l2);
    int spac = 0; // 进位
    newL1->print();
    newL2->print();

    // 遍历链表的结点
    while (newL1 != nullptr || newL2 != nullptr)
    {
        // 获取当前链表结点的数字
        int num1 = (newL1 != nullptr ? newL1->val : 0);
        int num2 = (newL2 != nullptr ? newL2->val : 0);
        std::cout << "num1:" << num1 << " ,num2:" << num2 << " ,spac:" << spac << std::endl;

        int sum = num1 + num2 + spac;
        std::cout << "sum:" << sum << std::endl;
        spac = sum / 10; // 进位获取
        sum = (sum >= 10 ? sum % 10 : sum);
        std::cout << "sum:" << sum << " ,spac:" << spac << std::endl;

        ListNode *newNode = new ListNode(sum);
        // 链表插入到哨兵节点后面
        newNode->next = dummy->next;
        dummy->next = newNode;

        newL1 = newL1 != nullptr ? newL1->next : nullptr;
        newL2 = newL2 != nullptr ? newL2->next : nullptr;
    }

    if (spac != 0) // 最后的进位处理
    {
        ListNode *newNode = new ListNode(spac);
        // 链表插入到哨兵节点后面
        newNode->next = dummy->next;
        dummy->next = newNode;
    }

    return dummy->next;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // [7,2,4,3], l2 = [5,6,4]
    ListNode node1(7);
    ListNode node2(2);
    ListNode node3(4);
    ListNode node4(3);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node1.print();

    ListNode node21(5);
    ListNode node22(6);
    ListNode node23(4);
    node21.next = &node22;
    node22.next = &node23;
    node21.print();

    auto res = addTwoNumbers(&node1, &node21);

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