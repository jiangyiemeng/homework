#ifndef _STACK
#define _STACK

#include<stdio.h> 

/****宏定义区****/
#define MAX_Length 21

#define Add '1'  /*加*/
#define Minus '1'  /*减*/
#define Multiply '2' /*乘*/
#define Divide '2' /*除*/
#define Surplus '3'	/*取余*/
#define Power '3'  /*次方*/
#define Squrt '3'  /*开方*/
#define Factorial  '3'  /*阶乘*/
#define Logarithm '3'  /*对数*/ 
/***************/

/***结构体定义区***/
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

/*函数声明区*/
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
