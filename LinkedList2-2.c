#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

char firstNames[100][15] = {};
char secondNames[100][15] = {};
int ages[70] = {};
int row = 0;

struct Node* head = NULL;
struct Node* newNode = NULL;
struct Node* oldAddress = NULL;
struct Node* next = NULL;
struct Node* prev = NULL;
struct apprentice* temp = NULL;


void listData()
{
FILE* file = fopen("data.csv", "r");
char line[35];
int column = 0;
char* value = malloc(sizeof(line));
char* c = malloc(sizeof(line));

for (fgets(line, sizeof(line), file); c = fgets(line, sizeof(line), file); row++)
	{
	value = (strtok(c, "," "\n"));
	while (value != NULL)
		{
		if (column == 0)
			{
			strcpy(firstNames[row], value);
			}
		else if (column == 1)
			{
			strcpy(secondNames[row], value);
			}
		else if (column == 2)
			{
			ages[row] = value;
			}
		column++;
		if (column > 2)
			{
			column = 0;
			}
	value = strtok(NULL, ",");
		}
	}
}


void createHead()
{
head = malloc(sizeof(struct Node)+sizeof(struct apprentice));
head->data = malloc(sizeof(struct apprentice));
head->next = NULL;
strncpy(head->data->firstName, firstNames[0], 15);
strncpy(head->data->secondName, secondNames[0], 15);
head->data->age = ages[0];
};

void createNode(int x)
{
oldAddress = newNode;
newNode = malloc(sizeof(struct Node));
newNode->data = malloc(sizeof(struct apprentice));
strncpy(newNode->data->firstName, firstNames[x], 15);
strncpy(newNode->data->secondName, secondNames[x], 15);
newNode->data->age = ages[x];
newNode->next = NULL;
newNode->prev = oldAddress;
oldAddress->next = newNode;
};

void linkedList()
{
createHead();

newNode = head;

int loopCount;										/* Problem: Minimum of two table entries, or can't set up head and second */
for (loopCount = 1; loopCount < row; loopCount++)
	{
	if (newNode->next == NULL)
		{
		createNode(loopCount);
		} 
	else {
		newNode = newNode->next;
		};
	};
};

void nodePrint()
{
printf("%15s, %15s, %15d\n", newNode->data->firstName, newNode->data->secondName, newNode->data->age);
};

void sortAge()
{
int complete = 0;
newNode = head;

while (complete < 2)
	{
	if (newNode->next != NULL)
		{
		newNode = newNode->next;
		oldAddress = newNode->prev;
		if (oldAddress->data->age > newNode->data->age)
			{
			temp = newNode->data;
			newNode->data = oldAddress->data;
			oldAddress->data = temp;
			newNode = head;
			}
		}
	else {
		complete++;
	};
};
};

int main()
{

listData();

linkedList();

sortAge();

newNode = head;
int loopCount;	 
for (loopCount = 1; loopCount <= (row); loopCount++)
	{if (newNode->next != NULL)
		{nodePrint();
		newNode = newNode->next;
		}
	else {nodePrint();
	};
};
return 0;
}