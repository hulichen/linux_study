#include "test.h"

//void Print()
//{
//	printf("hello world\n");
//	Print();
//}

int Strlen(char *s)
{
	if (*s == '\0'){
		return 0;
	}
	return 1 + Strlen(s + 1);


	//int len = 0;
	//char*p = s;
	//while (*p != '\0'){
	//	len++;
	//	p++;
	//}
	//return len;
}

int main()
{
	char *s = "abcd1234";
	int len = Strlen(s);
	printf("%d\n", len);
	//Print();
	//printf("%d\n", g_val);
	//Show();
	return 0;
}
