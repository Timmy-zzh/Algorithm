
#include <iostream>

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