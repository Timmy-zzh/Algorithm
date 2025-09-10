#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
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
LCR 030. O(1) 时间插入、删除和获取随机元素
https://leetcode.cn/problems/FortPu/description/

设计一个支持在平均 时间复杂度 O(1) 下，执行以下操作的数据结构：

insert(val)：当元素 val 不存在时返回 true ，并向集合中插入该项，否则返回 false 。
remove(val)：当元素 val 存在时返回 true ，并从集合中移除该项，否则返回 false 。
getRandom：随机返回现有集合中的一项。每个元素应该有 相同的概率 被返回。

示例 1：
输入: inputs = ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
输出: [null, true, false, true, 2, true, false, 2]
解释:
RandomizedSet randomSet = new RandomizedSet();  // 初始化一个空的集合
randomSet.insert(1); // 向集合中插入 1 ， 返回 true 表示 1 被成功地插入
randomSet.remove(2); // 返回 false，表示集合中不存在 2
randomSet.insert(2); // 向集合中插入 2 返回 true ，集合现在包含 [1,2]
randomSet.getRandom(); // getRandom 应随机返回 1 或 2
randomSet.remove(1); // 从集合中移除 1 返回 true 。集合现在包含 [2]
randomSet.insert(2); // 2 已在集合中，所以返回 false
randomSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2

提示：
-231 <= val <= 231 - 1
最多进行 2 * 105 次 insert ， remove 和 getRandom 方法调用
当调用 getRandom 方法时，集合中至少有一个元素
 */

/**
 * 1、审题：实现时间复杂度O(1)的哈希表，包含操作插入，删除，和随机获取内部数据
 * 2、解题：
 * - 该题要实现哈希表的功能，主要要求是时间复杂度为O(1)
 * 插入操作：
 * - 使用动态数组vector保存插入后的数据，这样可以随机访问数组内的元素
 * 删除操作：
 * - 要实现数据的删除，需要先知道该数值在数组内的下标位置，可以使用map数据结构保存，key为数值，value为该数值在数组中的下标位置
 * - 这样就可以通过数值获取到对应保存的下标位置，
 * - 还有一个问题是数组中元素删除，需要将后面部分元素进行整体移动，时间复杂度为O(n)
 * - 要实现数组元素删除时间复杂度为O(1),可将当前需要删除的元素与数组尾部元素进行交换，然后直接删除数组尾部的元素
 * 随机获取操作：
 * - 使用random随机获取数组内的某一个元素
 */
class RandomizedSet
{
public:
    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        if (arrLocationMap.find(val) != arrLocationMap.end()) // 已经包含了
        {
            return false;
        }

        // 加入到数组和哈希表中
        arrLocationMap[val] = array.size();
        array.push_back(val);
        return true;
    }

    bool remove(int val)
    {
        // std::cout << "---------- remove val: ----------"<<val << std::endl;
        // 先判断数组中是否包含该数值
        if (arrLocationMap.find(val) == arrLocationMap.end()) // 不包含
        {
            return false;
        }

        // print();
        // 找到要删除原始的下标位置
        int removeIndex = arrLocationMap[val];
        // 与数组最后元素交换
        int size = array.size();
        int removeVal = array[removeIndex];
        int tailVal = array[size - 1];
        arrLocationMap[tailVal] = removeIndex;

        array[removeIndex] = tailVal;
        array[size - 1] = removeVal;
        // print();

        // 删除数组最后一个元素
        array.pop_back();
        arrLocationMap.erase(val);

        // print();
        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        // 使用mt引擎
        std::mt19937 generate(rd());
        // 创建分布
        std::uniform_int_distribution<int> dist(0, array.size() - 1);
        int index = dist(generate);
        std::cout << "index:" << index << std::endl;
        return array[index];
    }

    void print()
    {
        std::cout << "---------- print ----------" << std::endl;
        // 遍历数组
        std::cout << "array:";
        for (int i = 0; i < array.size(); i++)
        {
            std::cout << array[i] << " ,";
        }
        std::cout << std::endl;

        std::cout << "arrLocationMap:";
        for (const auto &pair : arrLocationMap)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> array;
    std::map<int, int> arrLocationMap; // 保存数组元素，和对应的数组下标
    std::random_device rd;             // 初始化随机数生成数
};

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    RandomizedSet randomSet;        // 初始化一个空的集合
    auto res = randomSet.insert(1); // 向集合中插入 1 ， 返回 true 表示 1 被成功地插入
    std::cout << "randomSet.insert(1) res:" << res << std::endl;
    res = randomSet.remove(2); // 返回 false，表示集合中不存在 2
    std::cout << "randomSet.remove(2) res:" << res << std::endl;
    res = randomSet.insert(2); // 向集合中插入 2 返回 true ，集合现在包含 [1,2]
    std::cout << "randomSet.insert(2) res:" << res << std::endl;
    randomSet.print();

    res = randomSet.getRandom(); // getRandom 应随机返回 1 或 2
    std::cout << "randomSet.getRandom() res:" << res << std::endl;

    res = randomSet.remove(1); // 从集合中移除 1 返回 true 。集合现在包含 [2]
    std::cout << "randomSet.remove(1) res:" << res << std::endl;
    res = randomSet.insert(2); // 2 已在集合中，所以返回 false
    std::cout << "randomSet.insert(2) res:" << res << std::endl;
    randomSet.print();

    res = randomSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2
    std::cout << "randomSet.getRandom() res:" << res << std::endl;
    randomSet.print();

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