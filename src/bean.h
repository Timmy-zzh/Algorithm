
#include <iostream>
#include <random>
#include <algorithm>

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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}

    /**
     * 打印
     */
    void print()
    {
        // 前序遍历，根左右
        travelBefore(this);
    }

    void travelBefore(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        std::cout << "node:" << node->val << std::endl;
        travelBefore(node->left);
        travelBefore(node->right);
    }
};

/**
 * 前缀树节点
 */
class TrieNode
{
public:
    bool isWord = false;
    TrieNode *children[26]; // 数组

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }

    ~TrieNode()
    {
        for (int i = 0; i < 26; i++)
        {
            delete children[i];
            children[i] = nullptr;
        }
    }

    void dfs(TrieNode *node, string word)
    {
        if (node->isWord)
        {
            std::cout << "word:" << word << std::endl;
        }

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                string newWord = word + char('a' + i);
                dfs(node->children[i], newWord);
            }
        }
    }

    /**
     * 打印，深度优先遍历
     */
    void print()
    {
        dfs(this, "*");
    }
};

static int genRandomNum(int total)
{
    // 随机数引擎（生成器）
    std::random_device rd;
    std::mt19937 gen(rd());

    // 定义分布范围
    std::uniform_int_distribution<> dis(0, total - 1);

    // 生成随机数
    int random_num = dis(gen);
    return random_num;
}