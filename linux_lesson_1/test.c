#include "test.h"

int g_val = 100;

void Show()
{
	for (int i = 0; i < 5; i++){
		printf("hello world: %d\n", i);
	}
}






















//#include <stdio.h>
//#include <math.h>
//#include <string.h>
//#include <windows.h>
//
//#pragma warning(disable:4996)
//
//void swap(int *xp, int *yp)
//{
//	int temp = *xp;
//	*xp = *yp;
//	*yp = temp;
//}
////yes:1, no:0
//int IsPrimeNumber(int n)
//{
//	//n = a * b; //10 = 2*5
//	//for (int i = 2; i < n; i++){
//	for (int i = 2; i <= (int)sqrt(n); i++){
//
//		if (n % i == 0){
//			return 0;
//		}
//	}
//	return 1;
//}
//
//int IsLeapYear(int year)
//{
//	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
//}
//
//int BinSearch(double arr[], int num, double n)
//{
//	int left = 0;
//	int right = num - 1;
//	while (left <= right){
//		int mid = left + ((right - left) >> 1);
//		if (n < arr[mid]){
//			right = mid-1;
//		}
//		else if (n > arr[mid]){
//			left = mid + 1;
//		}
//		else{
//			return mid;
//		}
//	}
//
//	return -1;
//}
//void Inc(int *cp)
//{
//	(*cp)++;
//}
//int main()
//{
//	char dst[64] = "hello,";
//	int len = strlen(strcat(dst, "bit"));
//	printf("%d\n", len);
//
//	//char * str = strcat(dst, "bit");
//	//printf("%s\n", str);
//    //printf("%d", printf("%d", printf("%d", 43)));
//	//int num = printf("abcdefg:%d\n", 12345);
//	//printf("\nnum = %d\n", num);
//
//	//дһ��������ÿ����һ������������ͻὫnum��ֵ����1��
//	//int count = 1;
//	//for (int i = 0; i < 10; i++){
//	//	Inc(&count);
//	//	printf("%d\n", count);
//	//}
//	//дһ��������ʵ��һ��������������Ķ��ֲ���
//	//double arr[] = { 3.14, 4.4, 5.6, 5.7, 5.8, 7.8, 9.0 };
//	//int num = sizeof(arr) / sizeof(arr[0]);
//
//	//int pos = BinSearch(arr, num, 5.9);
//	//printf("%d\n", pos);
//	//дһ�������ж�һ���ǲ������ꡣ
//	//for (int year = 1; year <= 2020; year++){
//	//	if (IsLeapYear(year)){
//	//		printf("%d ", year);
//	//	}
//	//}
//	//printf("\n");
//	//дһ�����������ж�һ�����ǲ�������
//	//for (int i = 2; i <= 1000; i++){
//	//	if (IsPrimeNumber(i)){
//	//		printf("%d ", i);
//	//	}
//	//}
//	//printf("\n");
//
//	//int a = 10;
//	//int b = 20;
//	//printf("before: a = %d, b = %d\n", a, b);
//	//swap(&a, &b);
//	//printf("after: a = %d, b = %d\n", a, b);
//
//	system("pause");
//	return 0;
//}