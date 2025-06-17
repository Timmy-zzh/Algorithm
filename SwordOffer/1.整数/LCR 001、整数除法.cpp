#include <iostream>

/**
 * 题目：
给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用 乘法、除法和取余运算。
整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345 将被截断为 8 ，-2.7335 将被截断至 -2 。
返回被除数 dividend 除以除数 divisor 得到的 商 。
注意：假设我们的环境只能存储 32 位 有符号整数，其数值范围是 [−231,  231 − 1] 。
本题中，如果商 严格大于 231 − 1 ，则返回 231 − 1 ；如果商 严格小于 -231 ，则返回 -231 。

示例 1:
输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = 3.33333.. ，向零截断后得到 3 。

示例 2:
输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = -2.33333.. ，向零截断后得到 -2 。

提示：
-231 <= dividend, divisor <= 231 - 1
divisor != 0
 */

/**
 * 1、审题：
 * - 输入两个int整数，计算两个整数相除后商的值，要求不能使用运算符的乘、除和取模运算符，只能使用加、减法实现
 * 2、解题：
 * 通过减法不断遍历减少除数的大小，看一共遍历了多少次，当除数小于被除数时，遍历的次数就是最终的结果
 * - int类型的值范围，处理值溢出问题，int值范围[-2^31, 2^31-1]
 * -- -2^31 / -1 结果溢出问题，
 * - 判断除法的两个数据的正负号情况，使用异或运算符 ^
 * - 使用long long类型，将int类型扩大类型范围，使用static_cast类型转换处理
 * - while循环
 */
int divide1(int dividend, int divisor)
{
    // 溢出特殊情况处理
    if (dividend == INT32_MIN && divisor == -1)
    {
        return INT32_MAX;
    }

    // 判断最终商是否是负数？ 异或处理，两个相同的0，两个不同为1
    int isNegative = (dividend < 0) ^ (divisor < 0);
    std::cout << "isNegative:" << isNegative << std::endl;

    // 扩展类型范围，类型转换
    long long dividendAbs = abs(static_cast<long long>(dividend));
    long long divisorAbs = abs(static_cast<long long>(divisor));

    int res = 0;

    while (dividendAbs >= divisorAbs)
    {
        dividendAbs -= divisorAbs;
        res++;
    }
    std::cout << "res:" << res << std::endl;

    if (isNegative)
    {
        res = -res;
    }

    return res;
}

/**
 * 4、疑问
 * - 现在使用了long long类型，对int类型进行扩展类型范围，如果计算机只支持32位运算，怎么办？-》为避免范围值溢出，使用负数进行计算
 */
int divide2(int dividend, int divisor)
{
    std::cout << "dividend:" << dividend << " ,divisor:" << divisor << std::endl;
    // 将正整数转成负数进行计算
    int isNegative = 2;

    if (dividend > 0)
    {
        dividend = -dividend;
        isNegative--;
    }
    if (divisor > 0)
    {
        divisor = -divisor;
        isNegative--;
    }
    // isNegative=1,说明除法的两个数中，其中有一个为负数，则最终商的结果为负数
    std::cout << "isNegative:" << isNegative << std::endl;

    int result = 0;

    // 使用负数进行不断循环的递减 divisor
    while (dividend <= divisor)
    {
        int value = divisor;
        int quotient = 1;
        while (value >= 0xc0000000 && dividend <= value + value) // 0xc0000000 是最小负数值的一半
        {
            quotient += quotient; // quotient的2倍
            value += value;       // value的2倍
        }

        dividend -= value;
        result += quotient;
        // std::cout << "------------dividend:" << dividend << std::endl;
        // std::cout << "------------divisor:" << divisor << std::endl;
        // std::cout << "result:" << result << std::endl;
    }
    std::cout << "result:" << result << std::endl;

    return isNegative == 1 ? -result : result;
}

/**
 * 2、解题：使用二分查找法
 * - 使用减法的方式，当除数为最大值被除数为1时，每次遍历除数减少1，需要遍历INT_MAX次数，会导致程序运行超时（O(n))
 * - 改为每次减少的大小为被除数的2的倍数，这样遍历次数只有logn次，
 * -- 两层while循环，外层还是判断除数是否大于被除数，内层while循环，则对被除数进行2的阶乘数进行相乘，看是否大于除数
 * -- 大于的话，则不能一次减这么多，小于的话继续乘以2
 * 3、总结：
 * - abs将转换后的int类型的数据，使用abs方法取绝对值
 * - 使用位移运算代替乘法，value = value << 1，表示value往左移动一位，也就是value值乘以2的结果继续赋值给value
 * - 打印需要消耗时间，
 * - value值在做左偏移时，结果值会溢出，需要扩大类型范围为long long
 */
int divide(int dividend, int divisor)
{
    // 溢出特殊情况处理
    if (dividend == INT32_MIN && divisor == -1)
    {
        return INT32_MAX;
    }

    // 判断最终商是否是负数？ 异或处理，两个相同的0，两个不同为1
    int isNegative = (dividend < 0) ^ (divisor < 0);
    std::cout << "isNegative:" << isNegative << std::endl;

    // 扩展类型范围，类型转换
    long long dividendAbs = abs(static_cast<long long>(dividend));
    long long divisorAbs = abs(static_cast<long long>(divisor));

    long long result = 0;

    while (dividendAbs >= divisorAbs)
    {
        long long value = divisorAbs;
        // 使用位移代替乘法
        long long num = 1; // 阶乘的个数
        while (dividendAbs >= (value << 1))
        {
            std::cout << "------------ dividendAbs:" << dividendAbs << std::endl;
            std::cout << "value:" << value << std::endl;
            std::cout << "num:" << num << std::endl;

            value = value << 1;
            num = num << 1; // 2的倍数
        }
        std::cout << "============value:" << value << std::endl;
        std::cout << "num:" << num << std::endl;

        dividendAbs -= value;
        result += num;
    }

    if (isNegative)
    {
        result = -result;
    }

    return static_cast<int>(result);
}

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    // int res = divide2(15, -2);
    int res = divide2(2147483647, 1);
    std::cout << "Result: " << res << std::endl;

    return 0;
}