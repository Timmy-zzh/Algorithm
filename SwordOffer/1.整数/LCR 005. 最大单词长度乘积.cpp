#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

/**
    给定一个字符串数组 words，请计算当两个字符串 words[i] 和 words[j] 不包含相同字符时，它们长度的乘积的最大值。假设字符串中只包含英语的小写字母。如果没有不包含相同字符的一对字符串，返回 0。

    示例 1：
    输入：words = ["abcw","baz","foo","bar","fxyz","abcdef"]
    输出：16
    解释：这两个单词为 "abcw", "fxyz"。它们不包含相同字符，且长度的乘积最大。

    示例 2：
    输入：words = ["a","ab","abc","d","cd","bcd","abcd"]
    输出：4
    解释：这两个单词为 "ab", "cd"。

    示例 3：
    输入：words = ["a","aa","aaa","aaaa"]
    输出：0
    解释：不存在这样的两个单词。
 */

/**
 * 解法3：位运算
 * - 之前26个字母位置存在的是bool类型，表示字符串包含的字母在26个字母位置是否存在
 * - bool类型只有true和false，也可以替换为使用int类型，该字母存在值为1，否则为0
 * 那最后如何判断两个字符中是否存在相同的字母呢？
 * - 使用一维整数数组，一个int整数类型长度为32字节，可以满足26个的标识
 * - 遍历所有的字符串数组，再遍历单个字符串，获取到字符，往左移该字符在26个字母中的位置，并且标记为1
 * - 最后两个整数进行&与运算，其结果为1，说明存在相同字母
 */
int maxProduct(vector<string> &words)
{
    int res = 0;
    int size = words.size();
    vector<int> arr(size, 0);

    // 遍历单个字符串，判断单个字符出现的位置，在出现的位置上设置arr数组元素为bool值
    for (int i = 0; i < size; i++)
    {
        std::string str = words[i];
        for (int j = 0; j < str.length(); j++)
        {
            arr[i] |= (1 << (str[j] - 'a'));
        }
        std::cout << "i:" << i << " ,word:" << words[i] << " ,arr item:" << arr[i] << std::endl;
        for (int j = 0; j < 32; j++)
        {
            std::cout << ((arr[i] >> (31 - j)) & 1) << " ";
        }
        std::cout << std::endl;
    }

    // 字符串两两判断是否存在相同字符
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            // if (arr[i] & arr[j] == 0) // 这样是不对的，
            if ((arr[i] & arr[j]) == 0)
            {
                std::cout << "words[i]:" << words[i] << " ,words[j]:" << words[j] << std::endl;
                // 没有相同的字符
                int productLen = words[i].length() * words[j].length();
                res = std::max(res, productLen);
            }
        }
    }

    return res;
}

/**
 * 第三层for循环改为遍历26个字符，判断两个字符是否存在相同的字符
 * - 存在的话退出循环
 */
int maxProduct3(vector<string> &words)
{
    int res = 0;
    int size = words.size();
    vector<vector<bool>> arr(size, vector<bool>(26, false));

    // 打印二维数组
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 遍历单个字符串，判断单个字符出现的位置，在出现的位置上设置arr数组元素为bool值
    for (int i = 0; i < size; i++)
    {
        std::string str = words[i];
        for (int j = 0; j < str.length(); j++)
        {
            arr[i][str[j] - 'a'] = true;
        }
    }
    std::cout << " after: " << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 字符串两两判断是否存在相同字符
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            int h = 0;
            for (; h < 26; h++)
            {
                if (arr[i][h] && arr[j][h])
                {
                    break;
                }
            }
            if (h == 26)
            {
                // 没有相同的字符
                int productLen = words[i].length() * words[j].length();
                res = std::max(res, productLen);
            }
        }
    }

    return res;
}

/**
 * 解法2：
 * - 暴力解法中有四层for循环，其中外层两个for循环是寻找两个需要比较的字符串，内层两个for循环是判断两个字符串是否有相同的字符
 * - 内层for循环可简化，通过哈希表的方式记录每个字符串中，单个字符是否出现过
 * -- 哈希表使用二维数组结构，一维数组元素存储的是数组中的单个字符串，一维数组长度是字符串数组长度，
 * -- 二维数组内层存储的是单个字符串是否出现-使用bool表示，因为字符串由小写字母组成，所以二维数组的长度是26
 */
int maxProduct2(vector<string> &words)
{
    int res = 0;
    int size = words.size();
    vector<vector<bool>> arr(size, vector<bool>(26, false));

    // 打印二维数组
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 遍历单个字符串，判断单个字符出现的位置，在出现的位置上设置arr数组元素为bool值
    for (int i = 0; i < size; i++)
    {
        std::string str = words[i];
        for (int j = 0; j < str.length(); j++)
        {
            arr[i][str[j] - 'a'] = true;
        }
    }
    std::cout << " after: " << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 字符串两两判断是否存在相同字符
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            std::string str1 = words[i];
            std::string str2 = words[j];
            int len1 = str1.length();
            int len2 = str2.length();
            int h = 0;
            for (; h < len1; h++)
            {
                int chIndex = str1[h] - 'a'; // 是第几个字符
                if (arr[i][chIndex] && arr[j][chIndex])
                {
                    break;
                }
            }
            if (h == len1)
            {
                // 没有相同的字符
                int productLen = len1 * len2;
                res = std::max(res, productLen);
            }
        }
    }

    return res;
}

/**
 * 1、审题：
 * - 输入一个字符串数组，数组两个元素中的字符串，可能存在相同的字符，要求寻找没有相同字符的两个字符串，要求他们的长度乘积最大并返回
 * 如果任意两个字符串都存在相同的字符，结果返回0
 * 2、解题：
 * - 解题关键在于：寻找出两个字符串，他们之间不存在相同的字符
 * 3、解法1：暴力解法
 * - 双层for循环，判断两个字符串两两是否存在相同的字符，内部还要有第三层for循环判断两个字符串是否存在相同字符
 * - 暴力解法会超出时间限制
 */
int maxProduct1(vector<string> &words)
{
    int res = 0;
    int size = words.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            std::string str1 = words[i];
            std::string str2 = words[j];
            int len1 = str1.length();
            int len2 = str2.length();
            int h = 0;
            for (; h < len1; h++)
            {
                // 遍历str1字符串中的字符，判断该字符在str1中是否存在，存在则退出当前for循环
                bool find = false;
                for (int g = 0; g < len2; g++)
                {
                    if (str1[h] == str2[g])
                    {
                        find = true;
                        break;
                    }
                }
                if (find)
                {
                    break;
                }
            }
            if (h == len1) // h遍历到str1字符串末尾，说明不存在相同字符
            {
                int productLen = len1 * len2;
                res = std::max(res, productLen);
            }
        }
    }

    return res;
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    vector<string> words = {"abcw", "baz", "foo", "bar", "fxyz", "abcdef"};
    auto res = maxProduct(words);

    std::cout << "res:" << res << std::endl;

    // 遍历res
    // for (int element : res)
    // {
    //     std::cout << element << ",";
    // }
    // std::cout << std::endl;

    return 0;
}