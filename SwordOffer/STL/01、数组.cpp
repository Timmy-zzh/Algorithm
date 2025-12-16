#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <random>
#include <stack>
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
 * 数组的使用：
 * - 数组的创建，与赋值
 * - 数组元素的获取
 * - 数组遍历
 * 数组使用注意项：
 * - 越界问题
 * - 数组赋值
 * - 数组与指针
 */
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ",";
    }
    std::cout << std::endl;
}

// 数组声明
void array_declare()
{
    std::cout << "数组的声明!" << std::endl;
    int size = 5;
    int arr[size] = {1, 2, 3};
    printArray(arr, 5);

    // 声明未初始化,未初始化的元素是随机数
    int arr1[5];
    printArray(arr1, 5);

    // 声明并初始化全部元素
    int arr2[5] = {1, 2, 3, 4, 5};
    printArray(arr2, 5);

    // 声明并部分初始化, 剩余的元素会自动初始化为0
    int arr3[5] = {1, 2, 3};
    int arr31[5] = {0}; // 数组元素5个全是0
    printArray(arr3, 5);

    // 不设置数组大小，自动推导
    int arr4[] = {1, 2, 3, 4, 5};
    std::cout << sizeof(arr4) / sizeof(arr4[0]) << std::endl;

    // 声明并初始化，一起来
    int arr5[3]{1, 2, 3};
    printArray(arr5, 3);

    printArray(arr5, 5); // 获取超过数组长度的元素，arr5[3],arr5[4]; 不会报错，但是获取的数据不对，正确做法是在获取前要先判断数组越界范围
}

void array_visit()
{
    std::cout << "数组访问与修改!" << std::endl;
    int nums[5] = {1, 2, 3, 4, 5};
    printArray(nums, 5);

    // 获取第1个元素
    std::cout << "第一个元素：" << nums[0] << std::endl;
    std::cout << "第三个元素：" << nums[2] << std::endl;
    std::cout << "第八个元素：" << nums[7] << std::endl; // 不报错，内存中胡乱取的一个数字

    // 修改元素
    nums[1] = 25;
    nums[4] = 100;
    printArray(nums, 5);
}

void array_traverse()
{
    std::cout << "数组的遍历!" << std::endl;
    int arr[] = {1, 2, 3, 4, 5};
    // 获取数组的大小
    int size = sizeof(arr) / sizeof(arr[0]);
    std::cout << "数组长度：" << size << std::endl;

    // 传统for循环遍历
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ",";
    }
    std::cout << std::endl;

    // 范围for循环遍历
    for (int num : arr)
    {
        std::cout << num << ",";
    }
    std::cout << std::endl;
}

/**
 * 错误，不能返回局部数组
 * 因为函数内声明的int arr[5]是局部变量，在函数执行完会销毁
 * - 改为使用 堆上创建呢？ 使用new初始化,记得要delete
 */
int *getArr()
{
    // int arr[5] = {1, 2, 3, 4, 5};
    int *arr = new int[5]{10, 20, 30};
    return arr;
}
void array_notice()
{
    std::cout << "数组注意事项!" << std::endl;
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5];
    // arr2 = arr1; // 不可以数组赋值

    // 需要手动赋值
    for (int i = 0; i < 5; i++)
    {
        arr2[i] = arr1[i];
    }
    printArray(arr1, 5);
    printArray(arr2, 5);

    int *arr = getArr();
    printArray(arr, 5);
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;

    array_declare();
    array_visit();
    array_traverse();
    array_notice();

    // vector<string> matrix = {"10100", "10111", "11111", "10010"};

    // for (auto ele : matrix)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    // auto res = maximalRectangle(matrix);

    // std::cout << "res:" << res << std::endl;

    // 遍历1维数组
    // for (auto ele : res)
    // {
    //   std::cout << ele << ",";
    // }
    // std::cout << std::endl;

    // 遍历2维数组
    // for (vector<int> ele : res)
    // {
    //     for (auto element : ele)
    //     {
    //         std::cout << element << ",";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    return 0;
}