#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
// #include "src/bean.h"

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
LCR 031. LRU 缓存
https://leetcode.cn/problems/OrIXps/description/

运用所掌握的数据结构，设计和实现一个  LRU (Least Recently Used，最近最少使用) 缓存机制 。

实现 LRUCache 类：
LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

示例：
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4

提示：
1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 105
最多调用 2 * 105 次 get 和 put
进阶：是否可以在 O(1) 时间复杂度内完成这两种操作？
 */

class MapNode
{
public:
    int key;
    int value;
    MapNode *prev;
    MapNode *next;
    MapNode(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {};
    ~MapNode() {};
};

/**
 * 1、审题：实现最近最少使用的缓存结构，要求缓存表有自己的容量，当往缓存中新增加数据时，如果数据个数已达到最大值，则删除最近没有使用的数据
 * 2、解题：哈希表加双向链表结构
 * - 使用哈希表是为了实现获取数据get，与插入数据put方法在O(1)时间内
 * - 使用链表维护最近最少使用的结点，对缓存数据进行操作，不管是get还是put，该结点都移动到链表的尾部，
 * - 当超过缓存容量，需要对数据进行删除时，则删除链表的头部结点。
 * - 删除结点，需要先获取前一个结点，然后next指针指向下一个节点，使用单链表结构需要每次从头遍历，改为使用双向链表实现
 * - 为了实现简便，使用两个哨兵节点 head，和tail
 * 3、总结
 * - LRU缓存列表，采用哈希表map和双向链表实现
 * - 双向链表可以直接获取到前继节点，方便进行节点删除
 * - lru特性，可将操作后的结点插入到链表的尾节点位置
 * - 使用哨兵节点head和tail简便操作
 * - 节点删除后，对应的map也需要清除，使用erase方法
 * - 注意已经删除的结点，再使用同样的方式获取到的节点数据已经不是原来的对象了，已经变化了
 */
class LRUCache
{
public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        head = new MapNode(0, 0);
        tail = new MapNode(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    /**
     * 根据传入的key值获取value，
     * - 先判断map中是否存在该key值，不存在返回-1
     * - 存在的话，获取到对应key值的MapNode节点
     * - 将该结点插入到双向链表尾部,现在原先链表位置删除，而后插入到链表尾部
     * - 返回节点的value值
     */
    int get(int key)
    {
        std::cout << " get() key:" << key << std::endl;
        if (map.find(key) == map.end())
        {
            return -1;
        }

        MapNode *node = map[key];

        moveToTail(node, node->value);

        print();
        return node->value;
    }
    /**
     * 插入数据：
     * - 先判断该key值是否存在？
     * 如果存在，则获取key值对应的结点，更新结点的值，并将该节点node插入到链表尾部
     * - 如果该key值数据不存在，那需要新插入一个节点
     * 插入前，要先判断是否超过容量，超过容量了，要先将头结点进行删除，然后再插入
     */
    void put(int key, int value)
    {
        std::cout << " put() key:" << key << " ,value:" << value << std::endl;
        if (map.find(key) != map.end())
        { // 存在，则更新，并插入到链表尾部
            moveToTail(map[key], value);
        }
        else
        {
            // 不存在，需要新插入节点
            if (count >= capacity) // 节点个数是否超过容量
            {
                // 先删除头结点
                MapNode *delNode = head->next;
                deleteNode(delNode);
                map.erase(delNode->key);
                /**
                 * 这个地方要注意,不能写成，因为 head->next删除后，再获取head->next已经不是原来的结点值了
                 * deleteNode(head->next);
                 * map.erase(head->next->key);
                 */
                count--;
            }

            // 插入新节点到尾部
            MapNode *newNode = new MapNode(key, value);
            insertTail(newNode);
            map[key] = newNode;
            count++;
        }

        print();
    }

    void moveToTail(MapNode *node, int newVal)
    {
        deleteNode(node);
        node->value = newVal;
        insertTail(node);
    }

    /**
     * 双向链表节点的删除：
     * - 先找到链表的前继节点，前继节点直接指向后继节点
     * - 后继节点的前继节点，指向前一位的前继节点
     */
    void deleteNode(MapNode *node)
    {
        MapNode *prevNode = node->prev;
        MapNode *nextNode = node->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        node->next = nullptr;
        node->prev = nullptr;

        // 也可以这样写，就不好理解
        // node->prev->next = node->next;
        // node->next->prev = node->prev;
    }

    /**
     * 将该结点插入到尾节点
     * - 先获取尾节点的前继节点prevNode，
     * - 将node节点与tail节点连接
     * - 再将ndoe节点和前继节点prevNode连接
     */
    void insertTail(MapNode *node)
    {
        MapNode *prevNode = tail->prev;
        node->next = tail;
        tail->prev = node;

        prevNode->next = node;
        node->prev = prevNode;
    }

    void print()
    {
        MapNode *node = head->next;
        while (node->next != nullptr)
        {
            std::cout << node->value << " ,";
            node = node->next;
        }
        std::cout << std::endl;

        std::cout << "map:";
        for (const auto &pair : map)
        {
            std::cout << pair.first << ": " << pair.second->value << std::endl;
        }
        std::cout << std::endl;
    }

private:
    int capacity = 0;
    int count = 0;
    MapNode *head;
    MapNode *tail;
    std::map<int, MapNode *> map;
};

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    //  * LRUCache* obj = new LRUCache(capacity);
    //  * int param_1 = obj->get(key);
    //  * obj->put(key,value);

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