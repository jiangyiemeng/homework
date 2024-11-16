#ifndef _STACK
#define _STACK

#include<stdio.h> 

/****�궨����****/
#define MAX_Length 21

#define Add '1'  /*��*/
#define Minus '1'  /*��*/
#define Multiply '2' /*��*/
#define Divide '2' /*��*/
#define Surplus '3'	/*ȡ��*/
#define Power '3'  /*�η�*/
#define Squrt '3'  /*����*/
#define Factorial  '3'  /*�׳�*/
#define Logarithm '3'  /*����*/ 
/***************/

/***�ṹ�嶨����***/
typedef struct stack{
	char** data;
	int top;
} Stack;

typedef struct node{
	char value;
	char priority;
	struct node* next; 
} Node;

typedef struct list{
	Node* head; 
	Node* tail;
} List;
/*****************/

/*����������*/
void InitStack(Stack* stack);
int is_empty(Stack* stack);
void infixToPostfix(char** tokens,Stack* Calculation, const int count);
char pop(Stack* stack);
void parseExpression(char** tokens, List* list);
void Capacity(List* list, int* capacity);

void CREATE(char item,List* pList);
void tokens_init(char*** tokens, int capacity);
void Calculation_init(Stack* Calculation, int capacity);
void Destory(List* pList);
void Print(List* pList);
/***********/

#endif
