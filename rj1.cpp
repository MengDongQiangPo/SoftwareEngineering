#include<iostream>
#include<stdio.h>

using namespace std;

int maxSonArray(int nums[], int len);/*求最大子段和函数*/
int standardIn();/*检测输入数据是否规范的函数*/

int main() {
    int len;/*数组长度*/
    cout << "请输入整数 n 的个数:" << endl;

    while (1) {
        len = standardIn();
        if (len <= 0) {
            cout << "输入数据不符合要求,请重新输入" << endl;
            fflush(stdin);
        }
        else {
            break;
        }
    }

    int* nums = new int[len];/*创建存放整数的数组*/

    cout << "\n请依次输入 n 个整数:" << endl;
    for (int i = 0; i < len; i++) {
        nums[i] = standardIn();
    }

    cout << "\n最大子段和为:" << endl;
    cout << maxSonArray(nums, len) << endl;

    return 0;
}

int maxSonArray(int nums[], int len) {
    int max = 0; /*数组长度, 子段和最大值*/
    int* sum = new int[len]; /*nums[n]之前的最大子段和*/
    sum[0] = nums[0]; 

    if (sum[0] > max) {
        max = sum[0];
    }

    for (int i = 1; i < len; i++) {
        if (sum[i - 1] > 0) {
        /*若nums[i]之前的子段和大于0，则更新nums[i]的子段和*/
            sum[i] = sum[i - 1] + nums[i];
        }
        else {
        /*若nums[i]之前的子段和小于0，则nums[i]的子段和为其自身*/
            sum[i] = nums[i];
        }
        /*若本次的最大子段和大于之前的最大子段和，更新*/
        if (sum[i] > max) {
            max = sum[i];
        }
    }

    return max;
}

int standardIn() {
    int number, i;
    while (1) {
        i = scanf("%d", &number);
        getchar();/*吞回车*/
        /*判断输入数据是否为整数*/
        if (i == 0) {
            cout << "输入数据不符合要求,请重新输入" << endl;
        }
        else {
            break;
        }
    }
    return number;
}
