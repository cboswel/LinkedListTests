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
char check = 'x';
struct apprentice* temp = NULL;
struct apprentice newApprentice;

FILE* file;
int result;

void createHead()
{
head = malloc(sizeof(struct Node)+sizeof(struct apprentice));
head->data = malloc(sizeof(struct apprentice));
head->next = NULL;

fseek(file, 0, SEEK_SET);
fread(head->data, sizeof(struct apprentice), 1, file);
};

void createNode(int x)
{
int result;

file = fopen("data.bin", "rb+");

if (!file) {
	printf("Can't create file");
}

oldAddress = newNode;
newNode = malloc(sizeof(struct Node));
newNode->data = malloc(sizeof(struct apprentice));

fseek(file, (sizeof(struct apprentice)*(x)), SEEK_SET);
fread(newNode->data, sizeof(struct apprentice), 1, file);

fclose(file);
newNode->next = NULL;
newNode->prev = oldAddress;
oldAddress->next = newNode;
}

void linkedList()
{
createHead();

int loopCount;

printf("Current unsorted list of apprentices\n");
for (loopCount = 0; loopCount < row; loopCount++) {
	fseek(file, sizeof(struct apprentice)*(loopCount), SEEK_SET);
	fread(&newApprentice, sizeof(struct apprentice), 1, file);
	printf("%15s, %15s, %15d\n", newApprentice.firstName, newApprentice.secondName, newApprentice.age);
}

newNode = head;
									/* Problem: Minimum of two table entries, or can't set up head and second */
for (loopCount = 1; loopCount < row; loopCount++)
	{
	if (newNode->next == NULL)
		{
		createNode(loopCount);
	} else {
		while (newNode->next != NULL) {
			newNode = newNode->next;
		}
		createNode(loopCount);
		}
	}
}

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
	}
}
int loopCount;

printf("Sorted by Age\n");
newNode = head;
while (newNode->next != NULL) {
	nodePrint();
	newNode = newNode->next;
}
nodePrint();
}


int dataCheck()
{
file = fopen("data.bin", "rb+");
char check = 'x';

if (!file) {
	printf("Can't create file");
	return(1);
	}

fseek(file, 0L, SEEK_END);
if (ftell(file) == 0) {
	printf("No apprentices on record!\n");
	while (check!='y'||check!='Y'||check!='n'||check!='N') {
		check = 'x';
		printf("Input one now? (y/n)");
		scanf(" %c", &check);
		printf("%c\n", check);
		if (check =='y'||check!='Y') {
			return(1);
		} else if (check =='n'||check!='N') {
			return(0);
			}
		}
	}
}

int dataWrite() {
	char check = 'x';
	file = fopen("data.bin", "ab");
	if (!file) {
		printf("Can't create file");
		return(1);
	}
	printf("Enter new apprentice information\n");
	printf("First name?\n");
	scanf(" %s", &newApprentice.firstName);
	printf("First name is %s\n", newApprentice.firstName);
	printf("Second name?\n");
	scanf(" %s", &newApprentice.secondName);
	printf("Surname is %s\n", newApprentice.secondName);
	printf("Age?\n");
	scanf(" %d", &newApprentice.age);
	printf("They are %d years old\n", newApprentice.age);
	printf("Apprentice added!\n");
	printf("\n%15s, %15s, %15d\n\n", newApprentice.firstName, newApprentice.secondName, newApprentice.age);
	fwrite(&newApprentice, sizeof(struct apprentice), 1, file);
	fclose(file);
	
	check = 'x';
	while (check != 'y'||check != 'Y'||check != 'n'||check != 'N')
		{
		printf("add more apprentices? (y/n)");
		scanf(" %c", &check);
		printf("%c\n", check);

		if (check =='y') {
			return(3);
		} else if (check =='n') {
			return(0);
				}
			}
		}
	


int dataInput()
{
int complete = 0;
char check = 'x';

while (complete != 1) {
	row = (ftell(file) / sizeof(struct apprentice));
	printf ("there are currently %d apprentices on file\n", row);
	while (check!='y'||check!='Y'||check!='n'||check!='N') {
		check = 'x';
		printf("add more to file? (y/n)");
		scanf(" %c", &check);
		printf("%c\n", check);
		if (check =='y'||check =='Y') {	
			result = dataWrite();
		} else if (check =='n'||check!='N') {
			complete = 1;
			break;
			}
		}
	}
return 0;
}

int main()
{
char check = 'x';
int loopCount;

result = dataCheck();

while (result != 0) {
	result = dataInput();
}

while (check !='r'||check !='w')
	{
	printf("read apprentice list or write new entries? (r/w)");
	scanf(" %c", &check);
	printf("%c\n", check);

	if (check =='w') {
		result = 3;
		break;
	} else if (check =='r') {
		result = 2;
		break;
	}
	}
while (result == 2 || result == 3) {
	if (result == 2) {
		break;
	} else if (result == 3) {
		result = dataInput();
	}
}


linkedList();

printf("Unsorted\n");
newNode = head;
while (newNode->next != NULL) {
	nodePrint();
	newNode = newNode->next;
}
nodePrint();


sortAge();

return 0;
}
