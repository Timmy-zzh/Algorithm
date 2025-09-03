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
 * - 不可复制粘贴，每一行代码都要自己实现，每一次代码实现都是一次锻炼机会
 */
using namespace std;

/**
LCR 029. 循环有序列表的插入
https://leetcode.cn/problems/4ueAj6/description/

给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal ，使这个列表仍然是循环升序的。
给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。
如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。
如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。

示例 1：
输入：head = [3,4,1], insertVal = 2
输出：[3,4,1,2]
解释：在上图中，有一个包含三个元素的循环有序列表，你获得值为 3 的节点的指针，我们需要向表中插入元素 2 。新插入的节点应该在 1 和 3 之间，插入之后，整个列表如上图所示，最后返回节点 3 。

示例 2：
输入：head = [], insertVal = 1
输出：[1]
解释：列表为空（给定的节点是 null），创建一个循环有序列表并返回这个节点。

示例 3：
输入：head = [1], insertVal = 0
输出：[1,0]

提示：
0 <= Number of Nodes <= 5 * 10^4
-10^6 <= Node.val <= 10^6
-10^6 <= insertVal <= 10^6
 */

void insertNode(Node *head, Node *newNode)
{
    Node *currNode = head;
    Node *bigNode = head;

    // 寻找合适的节点插入位置
    while (currNode->next != head && !(currNode->val <= newNode->val && newNode->val <= currNode->next->val))
    {
        currNode = currNode->next;
        if (bigNode->val <= currNode->val)
        {
            bigNode = currNode;
        }
    }
    std::cout << "currNode->val:" << currNode->val << std::endl;
    std::cout << "bigNode->val:" << bigNode->val << std::endl;

    if (currNode->val <= newNode->val && newNode->val <= currNode->next->val)
    {
        // 新链表插入
        newNode->next = currNode->next;
        currNode->next = newNode;
    }
    else
    {
        newNode->next = bigNode->next;
        bigNode->next = newNode;
    }
}

/**
 * 1、审题：
 * - 输入一个有序的循环链表的头结点，和需要插入的数字，新插入一个节点后，链表还是有序的，并返回循环链表
 * 2、解题：循环链表插入
 * - 要往链表中插入节点，需要先找到插入点的前继节点的位置
 * - 遍历链表节点，分三种情况：
 * -- 当前链表为空，新插入结点
 * -- 当前链表只有一个节点，新插入节点，新节点插入到头结点后面，并重新设置循环节点
 * -- 当链表有超过2个结点，新插入节点，需要遍历寻找到合适的位置，
 * - 循环链表的遍历，使用节点node和next节点，判断是否等于头结点，
 * - 在遍历的时候，判断node与next节点间是否合适插入节点，并记录当前最大值节点指针，
 * - 如果最后没找到合适的插入位置，那就插入到最大值节点后面
 */
Node *insert(Node *head, int insertVal)
{
    Node *newNode = new Node(insertVal);
    if (head == nullptr)
    {
        newNode->next = newNode;
        head = newNode;
    }
    else if (head == head->next)
    {
        newNode->next = head;
        head->next = newNode;
    }
    else
    {
        insertNode(head, newNode);
    }

    return head;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    Node *node1 = new Node(3);
    Node *node2 = new Node(4);
    Node *node3 = new Node(1);

    node1->next = node2;
    node2->next = node3;
    node3->next = node1;

    node1->print();
    auto res = insert(node1, 2);
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