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
 */
using namespace std;

/**
给定一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

示例 1：
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]

示例 2：
输入：head = [1], n = 1
输出：[]

示例 3：
输入：head = [1,2], n = 1
输出：[1]

提示：
链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 */

/**
 * 1、审题：
 * - 输入一个链表的头结点，和数字n，要求删除当前链表的倒数第n个结点，并返回处理后的链表头结点
 * 2、解题：双指针解法
 * - 使用快指针先从链表头结点开始遍历n个结点位置，
 * - 然后慢指针才开始从头结点开始遍历，等到快指针遍历到链表末尾了，也就是next指针为null
 * - 则对慢指针的后面位置的结点进行删除，当前慢指针的位置是要删除的倒数第n个结点的前一个结点位置
 * - 使用锚点指针
 * 例子：链表 1,2,3,4,5
 * - 要求删除的链表倒数第2个位置的结点4，则慢指针停止的位置是节点3位置
 */
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    ListNode *dummy = new ListNode(); // 锚点节点指针
    dummy->next = head;

    ListNode *fast = dummy;
    ListNode *slow = dummy;
    for (int i = 0; i < n; i++)
    {
        fast = fast->next;
    }
    while (fast->next != nullptr)
    {
        fast = fast->next;
        slow = slow->next;
    }

    // 慢指针节点删除
    slow->next = slow->next->next;

    return dummy->next;
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

    auto res = removeNthFromEnd(&node1, 2);

    res->print();

    // std::cout << "res:" << res << std::endl;
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