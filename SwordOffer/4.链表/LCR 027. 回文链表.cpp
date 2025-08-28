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
LCR 027. 回文链表
https://leetcode.cn/problems/aMhZSa/description/

给定一个链表的 头节点 head ，请判断其是否为回文链表。
如果一个链表是回文，那么链表节点序列从前往后看和从后往前看是相同的。

示例 1：
输入: head = [1,2,3,3,2,1]
输出: true

示例 2：
输入: head = [1,2]
输出: false

提示：
链表 L 的长度范围为 [1, 105]
0 <= node.val <= 9
进阶：能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

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
 * 1、审题：输入一个链表，判断该链表是否是回文链表
 * 2、解题：
 * = 暴力解法：遍历链表，将链表节点数据保存到数组中，然后判断数组中的数据是否是回文
 * = 链表翻转判断
 * - 回文链表与回文字符串一样的道理，要求链表从正向或者从反向遍历获取到的结点内容都一样
 * - 实现思路：使用快慢指针将链表截断成两个部分，将后面部分翻转，然后同时遍历两个链表节点，看是否相同
 */
bool isPalindrome(ListNode *head)
{
    std::cout << "isPalindrome:" << std::endl;
    if (head == nullptr || head->next == nullptr)
    {
        return true;
    }
    // 使用快慢指针查找中间节点
    ListNode *fast = head->next;
    ListNode *slow = head;

    // 获取中间节点，并截断,需要找到中间节点的前一个结点指针
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *midNode = slow->next;
    slow->next = nullptr;

    std::cout << " 获取中间节点，并截断:" << midNode->val << std::endl;
    head->print();
    midNode->print();
    // 翻转后半部分链表
    ListNode *reverse = reverseList(midNode);
    std::cout << " 翻转链表 reverseList:" << std::endl;
    reverse->print();
    ListNode *node = head;

    // 遍历
    while (node != nullptr && reverse != nullptr)
    {
        std::cout << "node->val:" << node->val << " ,reverse->val:" << reverse->val << std::endl;
        if (node->val != reverse->val)
        {
            return false;
        }
        node = node->next;
        reverse = reverse->next;
    }

    return true;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    ListNode node1(1);
    ListNode node2(1);
    ListNode node3(2);
    ListNode node4(1);
    ListNode node5(2);
    ListNode node6(1);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    // node4.next = &node5;
    // node5.next = &node6;
    node1.print();

    // reorderList(&node1);
    // node1.print();

    auto res = isPalindrome(&node1);
    std::cout << "res:" << res << std::endl;

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