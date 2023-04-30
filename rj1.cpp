#include<iostream>
#include<stdio.h>

using namespace std;

int maxSonArray(int nums[], int len);/*������Ӷκͺ���*/
int standardIn();/*������������Ƿ�淶�ĺ���*/

int main() {
    int len;/*���鳤��*/
    cout << "���������� n �ĸ���:" << endl;

    while (1) {
        len = standardIn();
        if (len <= 0) {
            cout << "�������ݲ�����Ҫ��,����������" << endl;
            fflush(stdin);
        }
        else {
            break;
        }
    }

    int* nums = new int[len];/*�����������������*/

    cout << "\n���������� n ������:" << endl;
    for (int i = 0; i < len; i++) {
        nums[i] = standardIn();
    }

    cout << "\n����Ӷκ�Ϊ:" << endl;
    cout << maxSonArray(nums, len) << endl;

    return 0;
}

int maxSonArray(int nums[], int len) {
    int max = 0; /*���鳤��, �Ӷκ����ֵ*/
    int* sum = new int[len]; /*nums[n]֮ǰ������Ӷκ�*/
    sum[0] = nums[0]; 

    if (sum[0] > max) {
        max = sum[0];
    }

    for (int i = 1; i < len; i++) {
        if (sum[i - 1] > 0) {
        /*��nums[i]֮ǰ���Ӷκʹ���0�������nums[i]���Ӷκ�*/
            sum[i] = sum[i - 1] + nums[i];
        }
        else {
        /*��nums[i]֮ǰ���Ӷκ�С��0����nums[i]���Ӷκ�Ϊ������*/
            sum[i] = nums[i];
        }
        /*�����ε�����Ӷκʹ���֮ǰ������Ӷκͣ�����*/
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
        getchar();/*�̻س�*/
        /*�ж����������Ƿ�Ϊ����*/
        if (i == 0) {
            cout << "�������ݲ�����Ҫ��,����������" << endl;
        }
        else {
            break;
        }
    }
    return number;
}
