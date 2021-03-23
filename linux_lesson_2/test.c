#include <stdio.h>
#include <windows.h>

#pragma warning(disable:4996)

int main()
{
	FILE *fp = fopen("log.txt", "rb");
	if (NULL == fp){
		printf("fopen error\n");
		return 1;
	}
	char buf[16];
	size_t num = 0;
	int index = num;
	while ((num = fread(buf+index, 1, 4, fp)) > 0)
	{
		index += num;
	}

	if (feof(fp)){
		printf("success, end if file...\n");
	}

	//const char *s = "abcdefg";
	//fwrite(s, strlen(s), 1, fp);
	fclose(fp);

	//int x = 0;
	//fread();

	//int a = 10000; 
	//二进制： 10 27 00 00 (内存)-》10 27 00 00（硬盘）
	// 文本：10 27 00 00 (内存)-》31 30 30 30 30（硬盘）
	//fprintf(fp, "%d", a);
	//fwrite(&a, sizeof(int), 1, fp);

	//fseek(fp, 0, SEEK_END);
	//int x = ftell(fp);
	//rewind(fp);
	//printf("size: %d\n", x);


	//rewind(fp);
	//f_seek(fp, 0, SEEK_SET);
	//FILE * pFile;
	//pFile = fopen("example.txt", "wb");
	//fputs("This is an apple.", pFile);
	//fseek(pFile, 9, SEEK_SET);
	//fputs(" sam", pFile);
	//fclose(pFile);
	//FILE *fp = fopen("log.txt", "r");
	//if (NULL == fp){
	//	printf("fopen error!\n");
	//	return 1;
	//}
	//fseek(fp, -3, SEEK_END);
	//int count = 0;
	//while (count < 3){
	//	char c = fgetc(fp);
	//	printf("%c", c);
	//	count++;
	//}
	//int pos = ftell(fp);
	//printf("pos: %d\n", pos);
	//char c = 'A';
	//while ((c = fgetc(fp)) != EOF){
	//	printf("pos: %d [%c]\n", ftell(fp), c);
	//}

	//fclose(fp);
	system("pause");
	return 0;
}
