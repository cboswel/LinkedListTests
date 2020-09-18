#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct apprentice
{
char firstName[15];
char secondName[15];
int age;
};

struct Node
{
struct apprentice* data;
struct Node* next;
struct Node* prev;
};


char firstNames[6][15] = {"Charlie", "Tom", "Joe", "Alan", "Queen", "Amy"};
char secondNames[6][15] = {"Boswell", "Hanks", "Blogs", "Turing", "Elizabeth", "Winehouse"};
int ages[6] = {14, 61, 39, 25, 99, 17};
int nodeCount = (sizeof(ages) / 4);

struct Node head;
struct Node newNode;
struct Node oldAddress;	

struct Node* phead = &head;
struct Node* pnewNode = &newNode;
struct Node* poldAddress = &oldAddress;
	


void createHead()
{
phead = malloc(sizeof(struct Node));
printf("test");
strncpy(phead->data->firstName, firstNames[0], 15);
strncpy(phead->data->secondName, secondNames[0], 15);
phead->data->age = ages[0];
phead->next = NULL;
phead->prev = NULL;
printf("headCreated");

};

void createNode(int x)
{
poldAddress = pnewNode;
printf("test");
pnewNode = malloc(sizeof(struct Node));
strncpy(pnewNode->data->firstName, firstNames[x], 15);
strncpy(pnewNode->data->secondName, secondNames[x], 15);
pnewNode->data->age = ages[x];
pnewNode->next = NULL;
pnewNode->prev = poldAddress;
poldAddress->next = pnewNode;
printf("nodeCreated");
};

void linkedList()
{
createHead();

pnewNode = phead;

int loopCount;										/* Problem: Minimum of two table entries, or can't set up head and second */
for (loopCount = 1; loopCount < (nodeCount - 1); loopCount++)
	{while (pnewNode->next != NULL)
		{pnewNode = pnewNode->next;
		};
	createNode(loopCount);
	};
};

void nodePrint()
{
printf("%15s, %15s, %3d/n", pnewNode->data->firstName, pnewNode->data->secondName, pnewNode->data->age);
};

int main()
{
linkedList();
pnewNode = phead;
int loopCount;	 
for (loopCount = 1; loopCount <= (nodeCount - 1); loopCount++)
	{while (pnewNode->next != NULL)
		{pnewNode = pnewNode->next;
		};
	nodePrint();
	};
return 0;
}