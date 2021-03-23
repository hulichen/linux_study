#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NUM 128
#define INIT 1
#define INC_SIZE 1
#define ALL -1

#pragma warning(disable:4996)

typedef struct person{
	char name[NUM/4];
	char sex;
	int age;
	char telphone[NUM/4];
	char address[NUM];
}person_t;

typedef struct contact{
	int cap;
	int size;
	person_t persons[0];
}contact_t;

extern void InitContact(contact_t **ct);
extern void AddPersonToContact(contact_t **ct);
extern void ShowContact(contact_t *ct,int pos);
extern void DelPersonFromContact(contact_t *ct);
extern void SearchContact(contact_t *ct);
//extern void ModfiyContact(contact_t *ct);
extern void ClearContact(contact_t *ct);
extern void SortContact(contact_t *ct);





#endif
