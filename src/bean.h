
#include <iostream>

// 链表节点
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    /**
     * 打印
     */
    void print()
    {
        ListNode *node = this;
        while (node != nullptr)
        {
            std::cout << node->val << " ,";
            node = node->next;
        }
        std::cout << std::endl;
    }
};

// 多级链表节点
// class Node
// {
// public:
//     int val;
//     Node(int x) : val(x) {}
//     Node *prev = nullptr;
//     Node *next = nullptr;
//     Node *child = nullptr;

//     void print()
//     {
//         Node *node = this;
//         while (node != nullptr)
//         {
//             std::cout << "node.val:" << node->val << " ," << std::endl;

//             if (node->prev != nullptr)
//             {
//                 std::cout << "---- prev node.val:" << node->prev->val << " ," << std::endl;
//             }
//             else
//             {
//                 std::cout << "prev node.val: null ," << std::endl;
//             }

//             node = node->next;
//         }
//         // std::cout << std::endl;
//     }
// };

class Node
{
public:
    int val;
    Node *next;

    Node() {}

    Node(int _val)
    {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node *_next)
    {
        val = _val;
        next = _next;
    }

    void print()
    {
        // 循环链表的打印，定义一个使用节点node，用于不断遍历，知道node的next指针指向head指针
        Node *node = this;
        std::cout << node->val << " ,";
        while (node->next != this)
        {
            node = node->next;
            std::cout << node->val << " ,";
        }
        std::cout << std::endl;
    }
};
