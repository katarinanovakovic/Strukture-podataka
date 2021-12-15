#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

typedef struct stablo S;
struct stablo {
	char* ime;
	S* child;
	S* sibling;
};
typedef struct stog Stog;
struct stog {
	S* directory;
	Stog* next;
	Stog* prev;
};

int MakeDir(S*);
int Menu(S*, Stog*);
int Dir(S*);
S* cd(S*, Stog*);
S* Back(S*, Stog*);
S* FindByName(char*, S*);
int PushStog(Stog*, S*);
S* PopStog(Stog*);
int Linija(Stog*, S*, S*);
Stog* FindLast(Stog*);

int main()
{
	S* root;
	root = (S*)malloc(sizeof(S));
	root->child = NULL;
	root->sibling = NULL;
	Stog* head;
	head = (Stog*)malloc(sizeof(Stog));
	head->next = NULL;
	head->prev = NULL;
	int status = 0;
	root->ime = (char*)malloc(MAX * sizeof(char));
	root->ime = "C:";

	do 
    {
		status = Menu(root, head);
	} 
    while (!status);

	return 0;
}

int MakeDir(S* current) {
	S* directory;
	directory = (S*)malloc(sizeof(S));
	directory->ime = (char*)malloc(MAX * sizeof(char));

	if (!directory)
		printf("Memorija nije uspjesno alocirana");

	if (current->child != NULL) {
		current = current->child;
		while (current->sibling != NULL) {
			current = current->sibling;
		}
		current->sibling=directory;
	}

	else
		current->child=directory;

	printf("Unesite ime direktorija: ");
	scanf(" %s", directory->ime);

	directory->sibling = NULL;
	directory->child = NULL;

	return 0;
    }

    int Dir(S* current) {

	if (current->child == NULL) {
		printf("Prazan direktorij!\n");
		return 0;
	}
		
	current = current->child;

	printf("Directories: \n");
	printf("\t- %s\n", current->ime);
	
	while (current->sibling != NULL) {
		printf("\t- %s\n", current->sibling->ime);
		current = current->sibling;
	}	

	return 0;
}

int PushStog(Stog* head, S* directory) {
	Stog* q = (Stog*)malloc(sizeof(Stog));
	
	q->next = head->next;
	q->prev = head;
	if (head->next != NULL) {
		head->next->prev = q;
	}
	head->next = q;
	q->directory = directory;

	 return 0;
}

S* PopStog(Stog* head) {
	Stog* q = (Stog*)malloc(sizeof(Stog));
	S* p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->directory;
	head->next = head->next->next;
	if(head->next!=NULL)
		head->next->prev = head;
	free(q);

	return p;
}

S* FindByName(char* name, S* current) {
	if (current->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	current = current->child;
	
	while (strcmp(name, current->ime) != 0 && current->sibling !=NULL) {
		current= current->sibling;
	}

	if (current->sibling == NULL) {
		if (strcmp(name, current->ime) != 0)
			return 0;
		else
			return current;
	}

	else
		return current;
}

S* cd(S* current, Stog* head)
{
	S* SearchedFile;
	char* ime;
	ime = (char*)malloc(MAX * sizeof(char));
	
	//printf("Koji direktorij zelite otvoriti: ");
	scanf("%s", ime);

	if (current->child == NULL) {
		printf("Nema direktorija koji mozete otvoriti!\n");
		return current;
	}
	
	SearchedFile=FindByName(ime, current);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return current;
	}

	PushStog(head, current);

	return SearchedFile;
}
    
S* Back(S* current, Stog* head)
{
	S* SearchedFile;
	
	SearchedFile = PopStog(head);

	if (SearchedFile == NULL) {
		printf("Ne moze se izaci iz root direktorija!\n");
		SearchedFile = current;
	}
	
	return SearchedFile;
}

Stog* FindLast(Stog* head)
{
	Stog* s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int Linija(Stog* head, S* root, S* current)
{
	Stog* s;

	s = FindLast(head);

	printf("\n");
	if (head->next == NULL) {
		printf("%s>", root->ime);
		return 0;
	}

	while (s->prev!=NULL) {
		printf("%s>", s->directory->ime);
		s = s->prev;
	}
	
	printf("%s>", current->ime);

	return 0;
}

int Menu(S* root, Stog* head) {
	S* Current = root;
	char command[MAX] = { 0 };

	printf("****************************************\n");
	printf("md <filename> - Dodaj novi direktorij\n");
	printf("cd <filename> - Otvori direktorij\n");
	printf("cd.. - Zatvoriti direktorij\n");
	printf("dir - Ispisi listu direktorija u trenutnome direktoriju\n");
	printf("refresh - Ponovo ispisi izbornik\n");
	printf("exit - Izlaz\n");
	printf("****************************************\n");

	while (1) {
		
		Linija(head, root, Current);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			MakeDir(Current);
		}

		else if (!strcmp(command, "cd")) {
			Current=cd(Current, head);
		}

		else if (!strcmp(command, "cd..")) {
			Current = Back(Current, head);
		}

		else if (!strcmp(command, "dir")) {
			Dir(Current);
		}

		else if (!strcmp(command, "exit")) {
			return 1;
		}

		else if (!strcmp(command, "refresh")) {
			return 0;
		}

		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}