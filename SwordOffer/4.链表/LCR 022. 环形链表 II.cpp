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
给定一个链表，返回链表开始入环的第一个节点。 从链表的头节点开始沿着 next 指针进入环的第一个节点为环的入口节点。
如果链表无环，则返回 null。
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，
则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。
说明：不允许修改给定的链表。

示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。

示例 2：
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。

示例 3：
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。

提示：
链表中节点的数目范围在范围 [0, 104] 内
-105 <= Node.val <= 105
pos 的值为 -1 或者链表中的一个有效索引
 */

// 返回链表环中相遇的结点，没有环则返回null
ListNode *getLoopNode(ListNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    ListNode *fast = head->next;
    ListNode *slow = head;

    while (fast != nullptr && slow != nullptr)
    {
        std::cout << "fast:" << fast->val << std::endl;
        std::cout << "slow:" << slow->val << std::endl;
        if (fast == slow)
        {
            return slow;
        }
        slow = slow->next;
        fast = fast->next;
        if (fast != nullptr)
        {
            fast = fast->next;
        }
    }
    return nullptr;
}

/**
 * 1、审题：
 * - 输入一个链表头结点，判断该链表是否存在环，如果存在环则返回进入环的第一个节点，没有环则返回null；
 * 2、解题：
 * - 先判断链表是否存在环,通过快慢指针解决，只要链表存在环，则快慢指针一定会相遇。
 * - 那如何找到进入环的结点位置呢？
 * -- 先求出环的个数，通过遍历环中相遇的结点来计算环的总结点个数n
 * -- 则链表的总个数-减去环的结点个数，就是前面结点的个数，前面结点移动的个数位置就是环的入口结点
 * - 继续使用双指针，前一个指针先移动环个数n个位置，然后让后指针从头结点开始移动，两个指针相遇的结点位置就是环的入口结点
 */
ListNode *detectCycle(ListNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    ListNode *loopNode = getLoopNode(head);
    std::cout << "loopNode:" << loopNode->val << std::endl;
    if (loopNode == nullptr)
    {
        return nullptr;
    }

    // 计算环的结点个数
    int count = 1;
    ListNode *tempNode = loopNode->next;
    while (tempNode != loopNode)
    {
        tempNode = tempNode->next;
        count++;
    }
    std::cout << "loopNode count:" << count << std::endl;

    // 定义双指针，让pre指针先移动count位置
    ListNode *fast = head;
    ListNode *slow = head;
    for (int i = 0; i < count; i++)
    {
        fast = fast->next;
    }

    while (fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    ListNode node1(3);
    ListNode node2(2);
    ListNode node3(0);
    ListNode node4(-4);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node2; // 环

    // node1.print();

    auto res = detectCycle(&node1);

    std::cout << "res:" << res->val << std::endl;
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