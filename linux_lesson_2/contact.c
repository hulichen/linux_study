#include "contact.h"

static int IsFull(contact_t *ct)
{
	assert(ct);

	return ct->size == ct->cap;
}

static int Inc(contact_t **ct)
{
	assert(*ct);
	int ret = 0;
	contact_t *p = (contact_t*)realloc(*ct, sizeof(contact_t)+sizeof(person_t)*((*ct)->cap + INC_SIZE));
	if (NULL != p){
		printf("realloc success!\n");
		p->cap = (*ct)->cap + INC_SIZE;
		*ct = p;
		ret = 1;
	}

	return ret;
}

static int IsExist(contact_t *ct, const char *telphone)
{
	assert(ct);
	person_t *p = ct->persons;
	person_t *end = ct->persons + ct->size;
	while (p < end){
		if (0 == strcmp(p->telphone, telphone)){
			return p - ct->persons;
		}
		p++;
	}
	return -1;
}

void InitContact(contact_t **ct)
{
	*ct = (contact_t*)malloc(sizeof(contact_t)+INIT*sizeof(person_t));
	if (NULL == *ct){
		printf("malloc error!\n");
		exit(1);
	}

	(*ct)->size = 0;
	(*ct)->cap = INIT;
}

void AddPersonToContact(contact_t **ct)
{
	assert(*ct);
	//IsFull():1, 0
	if (!IsFull(*ct) || Inc(ct)){
		//add person
		person_t *p = (*ct)->persons + (*ct)->size;
		printf("Please Enter Name# ");
		scanf(" %s", p->name);
		printf("Please Enter sex# ");
		scanf(" %c", &(p->sex));
		printf("Please Enter age# ");
		scanf(" %d", &(p->age));
		printf("Please Enter telphone# ");
		scanf(" %s", p->telphone);
		//已经存在(1, 0),满了,空间不够了
		if (IsExist(*ct, p->telphone) >= 0){
			printf("该用户已经存在!\n");
			return;
		}
		printf("Please Enter address# ");
		scanf(" %s", p->address);

		(*ct)->size += 1;
		printf("add %s success!\n", p->name);
	}
	else{
		printf("realloc error!\n");
	}
}

void ShowContact(contact_t *ct, int pos)
{
	assert(ct);
	printf("%d/%d\n", ct->size, ct->cap);
	if (pos == -1){
		if (ct->size == 0){
			printf("empty!\n");
		}
		for (int i = 0; i < ct->size; i++){
			printf("%10s | %10s\n", ct->persons[i].name, ct->persons[i].telphone);
		}
	}
	else{
		printf("%10s | %10s\n", ct->persons[pos].name, ct->persons[pos].telphone);
	}
}

void DelPersonFromContact(contact_t *ct)
{
	assert(ct);

	char telphone[NUM / 4];
	printf("Please Enter Delete Telphone# ");
	scanf("%s", telphone);

	int pos = IsExist(ct, telphone);
	if (pos >= 0){
		ct->persons[pos] = ct->persons[ct->size-1];
		ct->size -= 1;
		printf("delete %s success!\n", telphone);
	}
	else{
		printf("delete %s is not exist!\n", telphone);
	}
}

void SearchContact(contact_t *ct)
{
	assert(ct);
	char telphone[NUM / 4];
	printf("Please Enter Search Telphone# ");
	scanf("%s", telphone);
	int pos = IsExist(ct, telphone);
	if (-1 == pos){
		printf("user %s is not exist!\n", telphone);
	}
	else{
		ShowContact(ct, pos);
	}
}

void ClearContact(contact_t *ct)
{
	assert(ct);
	ct->size = 0;
}

void SortContact(contact_t *ct)
{
	assert(ct);
	//qsrot(ct->persons, ct->size, sizeof(person_t), compPerson);
}