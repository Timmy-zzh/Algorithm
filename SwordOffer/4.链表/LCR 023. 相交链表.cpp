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
 */
using namespace std;

/**
给定两个单链表的头节点 headA 和 headB ，请找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。
图示两个链表在节点 c1 开始相交：
题目数据 保证 整个链式结构中不存在环。
注意，函数返回结果后，链表必须 保持其原始结构 。

示例 1：
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。

示例 2：
输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
输出：Intersected at '2'
解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。
在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。

示例 3：
输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
这两个链表不相交，因此返回 null 。

提示：
listA 中节点数目为 m
listB 中节点数目为 n
0 <= m, n <= 3 * 104
1 <= Node.val <= 105
0 <= skipA <= m
0 <= skipB <= n
如果 listA 和 listB 没有交点，intersectVal 为 0
如果 listA 和 listB 有交点，intersectVal == listA[skipA + 1] == listB[skipB + 1]
进阶：能否设计一个时间复杂度 O(n) 、仅用 O(1) 内存的解决方案？
 */

/**
 * 使用快慢指针找到链表中环的相遇结点
 * - 犯错点：注意刚开始fast结点就要指向next指针，否则会进入while的if判断条件中
 */
ListNode *findLoopNode(ListNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }
    ListNode *fast = head->next;
    ListNode *slow = head;

    while (fast != nullptr && slow != nullptr)
    {
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
 * 1、审题：输入两个链表，判断两个链表是否相连，如果相连则返回相交的结点，否则返回null
 * 2、解题：
 * - 将问题转化为环形链表的入口点，和LCR22题一样了
 * - 将链表a的首尾结点相连
 * - 操作链表b，从链表b的头结点开始遍历，如果链表a和b相交的话，则链表b一定存在环情况，
 * - 使用快慢指针找到环中相遇的结点，遍历环中结点，找到环的个数count
 * - 根据环的个数，继续使用双指针，让快指针先移动count，然后让慢指针开始移动，直到快慢指针相遇，此时的结点即为相交节点
 * - 返回该相交节点，返回前需要将之前的链表b断开，恢复原样
 */
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    std::cout << "headA.val:" << headA->val << std::endl;
    std::cout << "headB.val:" << headB->val << std::endl;

    if (headA == nullptr || headB == nullptr) // 过滤空链表
    {
        return nullptr;
    }

    // 1、找到链表a的尾节点
    ListNode *tailNode = headA;
    while (tailNode->next != nullptr)
    {
        tailNode = tailNode->next;
    }

    std::cout << "tailNode.val:" << tailNode->val << std::endl;
    // 2、将链表a，的头尾节点相连
    tailNode->next = headA;

    // 3、判断链表b是否存在环
    ListNode *loopNode = findLoopNode(headB);

    std::cout << "loopNode.val:" << loopNode->val << std::endl;
    if (loopNode == nullptr)
    { // 不存在环，说明链表a，b不相交
        tailNode->next = nullptr;
        return nullptr;
    }

    // 4、找到链表中环的结点个数
    int nodeCount = 1;
    ListNode *tempNode = loopNode->next;
    std::cout << "tempNode.val:" << tempNode->val << std::endl;
    while (tempNode != loopNode)
    {
        tempNode = tempNode->next;
        nodeCount++;
    }
    std::cout << "nodeCount:" << nodeCount << std::endl;
    std::cout << "headB.val:" << headB->val << std::endl;

    // 5、使用快慢指针，查找链表b环的入口结点
    ListNode *fast = headB;
    ListNode *slow = headB;
    for (int i = 0; i < nodeCount; i++)
    {
        fast = fast->next;
    }
    std::cout << "fast.val:" << fast->val << std::endl;
    std::cout << "slow.val:" << slow->val << std::endl;

    // 快慢指针同时移动，直到相遇
    while (fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }

    tailNode->next = nullptr;
    return slow;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    // intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3

    ListNode node1(4);
    ListNode node2(1);
    ListNode node3(8);
    ListNode node4(4);
    ListNode node5(5);

    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node1.print();

    ListNode node21(5);
    ListNode node22(0);
    ListNode node23(1);
    node21.next = &node22;
    node22.next = &node23;
    node23.next = &node3;
    node21.print();

    auto res = getIntersectionNode(&node1, &node21);

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