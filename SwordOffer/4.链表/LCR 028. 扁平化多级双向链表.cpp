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
LCR 028. 扁平化多级双向链表
https://leetcode.cn/problems/Qv1Da2/description/

多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，可能指向单独的双向链表。
这些子列表也可能会有一个或多个自己的子项，依此类推，生成多级数据结构，如下面的示例所示。

给定位于列表第一级的头节点，请扁平化列表，即将这样的多级双向链表展平成普通的双向链表，使所有结点出现在单级双链表中。

示例 1：
输入：head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
输出：[1,2,3,7,8,11,12,9,10,4,5,6]
解释：
输入的多级列表如下图所示：
扁平化后的链表如下图：

示例 2：
输入：head = [1,2,null,3]
输出：[1,3,2]
解释：
输入的多级列表如下图所示：
  1---2---NULL
  |
  3---NULL

示例 3：
输入：head = []
输出：[]

如何表示测试用例中的多级链表？
以 示例 1 为例：
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL
序列化其中的每一级之后：

[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]
为了将每一级都序列化到一起，我们需要每一级中添加值为 null 的元素，以表示没有节点连接到上一级的上级节点。

[1,2,3,4,5,6,null]
[null,null,7,8,9,10,null]
[null,11,12,null]
合并所有序列化结果，并去除末尾的 null 。
[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]

提示：
节点数目不超过 1000
1 <= Node.val <= 10^5
 */

/**
 * 遍历链表节点：
 * - 不断遍历链表结点，并返回链表的尾节点
 * - 情况一：如果整个链表中所有结点都没有子节点，则对链表正常遍历并返回最后的尾节点
 * - 情况二：如果中途有一个节点有子节点，则递归调用recursFlatten方法，获取子节点的子链表的头结点和尾节点，
 * -- 插入到预先的链表中，注意是双向链表，链表插入的时候需要对前后指针域next，prev都要处理
 */
Node *recursFlatten(Node *head)
{
    Node *node = head;
    // 尾节点
    Node *tail = node;

    // 遍历结点，并更新尾节点
    while (node != nullptr)
    {
        // 获取下一个节点
        Node *nextNode = node->next;
        // 判断子链表是否存在
        Node *childNode = node->child;
        if (childNode != nullptr)
        {
            // 继续递归遍历子节点，要将childNode的子链表插入到node，和next节点之间
            Node *childTail = recursFlatten(childNode);
            // 插入
            childTail->next = nextNode;
            if (nextNode != nullptr)
            {
                nextNode->prev = childTail;
            }
            node->next = childNode;
            childNode->prev = node;

            tail = childTail;
            node->child = nullptr; // 断开子链表
        }
        else
        {
            // 没有子节点情况
            tail = node;
        }

        node = nextNode; // 指向下一个节点
    }
    std::cout << "tail.val:" << tail->val << std::endl;

    return tail;
}

/**
 * 1、审题：输入一个链表，链表中有的结点除了有指向前后的前继节点prev和后继节点next，还有指向下一个层级的子节点child，
 * - 形状就像二叉树一样，只不过结点之间是双向链表节点，现在要将这种带层级的链表进行展开，使得先遍历下层子节点，而后继续遍历后继节点
 * 2、解题：递归遍历与迭代结合实现
 * - 题目要求是遇到子节点，就在子节点位置截断，并将子层级中的所有结点都插入到截断位置，并且结点末尾需要继续连接之前结点的后继节点next
 * - 所以先正常遍历结点，判断当前结点的child子节点是否为空，如果为空，再进行递归遍历，并在遍历的过程中获取连接的头尾节点，
 * - 头结点可以在递归前获取到，递归后需要返回尾节点tailNode，将该自子节点链表整体插入到原先的链表中，
 * - 链表操作都是在原始链表中进行，需要注意连接的指针域指向逻辑
 * 3、总结：
 * - 双向链表，节点包含前继节点prev与后继节点next，双向链表的结点插入操作步骤处理
 * - 包含多层链表的结点，需要将child指针域指向为空
 * - 要操作链表，通过赋值一个新的临时指针变量来处理，原始链表的头结点指针不动
 */
Node *flatten(Node *head)
{
    recursFlatten(head);
    return head;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);
    Node node5(5);
    Node node6(6);
    Node node7(7);
    Node node8(8);
    Node node9(9);
    Node node10(10);
    Node node11(11);
    Node node12(12);

    // 双向循环
    node1.next = &node2;
    node2.prev = &node1;

    node2.next = &node3;
    node3.prev = &node2;

    node3.next = &node4;
    node4.prev = &node3;

    node4.next = &node5;
    node5.prev = &node4;

    node5.next = &node6;
    node6.prev = &node5;

    node3.child = &node7;
    node7.next = &node8;
    node8.prev = &node7;

    node8.next = &node9;
    node9.prev = &node8;

    node9.next = &node10;
    node10.prev = &node9;

    node8.child = &node11;
    node11.next = &node12;
    node12.prev = &node11;

    // node1.print();
    flatten(&node1);
    node1.print();

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