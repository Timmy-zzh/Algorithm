#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

/**
 * 感想：
 * - 脑子得练才行，光看书，不动手写，那不行！效果打骨折。
 * - 多写，写思路，写想法，描述出来，自然就会思考的更清楚，更快速。
 */
using namespace std;
using namespace std;

/**
给定一个二维矩阵 matrix，以下类型的多个请求：
计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2) 。
实现 NumMatrix 类：
NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
int sumRegion(int row1, int col1, int row2, int col2) 返回左上角 (row1, col1) 、右下角 (row2, col2) 的子矩阵的元素总和。

示例 1：
输入:
["NumMatrix","sumRegion","sumRegion","sumRegion"]
[{{{3,0,1,4,2}
  ,{5,6,3,2,1}
  ,{1,2,0,1,5}
  ,{4,1,0,1,7}
  ,{1,0,3,0,5}}},

  [2,1,4,3]
 ,[1,1,2,2]
 ,[1,2,2,4]]
输出:
[null, 8, 11, 12]

解释:
NumMatrix numMatrix = new NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]]);
numMatrix.sumRegion(2, 1, 4, 3); // return 8 (红色矩形框的元素总和)
numMatrix.sumRegion(1, 1, 2, 2); // return 11 (绿色矩形框的元素总和)
numMatrix.sumRegion(1, 2, 2, 4); // return 12 (蓝色矩形框的元素总和)
 */

/**
 * 1、审题：
 * - 输入一个二维矩阵，给到一个子区域，要求该子区域二维矩阵的元素累加和
 * 2、解题
 * - 根据二维矩阵，求出二维矩阵在某个坐标位置上的累加和数据
 *
 */
class NumMatrix
{
public:
    vector<vector<int>> sumMatrix;
    NumMatrix(vector<vector<int>> &matrix)
    {
        int column = matrix.size();
        int row = matrix[0].size();
        int rowSum;
        std::cout << "matrix column:" << column << " ,row:" << row << std::endl;

        std::cout << "sumMatrix init:" << std::endl;
        sumMatrix = vector<vector<int>>(column + 1, vector<int>(row + 1, 0));
        for (vector<int> ele : sumMatrix)
        {
            for (int element : ele)
            {
                std::cout << element << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (int i = 0; i < column; i++)
        {
            rowSum = 0;
            for (int j = 0; j < row; j++)
            {
                rowSum += matrix[i][j];
                sumMatrix[i + 1][j + 1] = sumMatrix[i][j + 1] + rowSum;
            }
        }

        std::cout << "sumMatrix after:" << std::endl;
        for (vector<int> ele : sumMatrix)
        {
            for (int element : ele)
            {
                std::cout << element << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return sumMatrix[row2 + 1][col2 + 1] -
               sumMatrix[row1][col2 + 1] -
               sumMatrix[row2 + 1][col1] +
               sumMatrix[row1][col1];
    }
};

int main()
{
    std::cout << "Hello, Algorithm!" << std::endl;
    // vector<int> nums = {1, 7, 3, 6, 5, 6};
    // vector<int> nums = {0, 1, 0};
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}};

    for (vector<int> ele : matrix)
    {
        for (int element : ele)
        {
            std::cout << element << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    NumMatrix numMatrix{matrix};
    int res = numMatrix.sumRegion(2, 1, 4, 3);
    std::cout << "sumRegion(2,1,4,3) res:" << res << std::endl;
    res = numMatrix.sumRegion(1, 1, 2, 2);
    std::cout << "sumRegion(1,1,2,2) res:" << res << std::endl;
    res = numMatrix.sumRegion(1, 2, 2, 4);
    std::cout << "sumRegion(1,2,2,4) res:" << res << std::endl;

    // 遍历数组1
    // for (int element : res)
    // {
    //     std::cout << element << ",";
    // }
    // std::cout << std::endl;

    // 遍历数组2
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