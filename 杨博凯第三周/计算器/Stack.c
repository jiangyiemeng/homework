#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE
#include"Stack.h"
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*初始化栈*/
void InitStack(Stack* stack){
	stack->top  =-1;
}

/*判断栈是否为空*/
int is_empty(Stack* stack){
	return stack->top == -1; 
}

/*中缀->后缀转换器*/
void infixToPostfix(char** tokens,Stack* Calculation,const int capacity){
	
	/*建立临时存放符号的栈*/
	Stack Pending;
	InitStack(&Pending); 
	if (!(Pending.data = (char**)malloc( (capacity) * sizeof(char*)))){
		printf("出现错误");
		exit (1);
	}

	
	int cnt;  //临时计数器，确保讲算式全部压栈 
	for(cnt=0;cnt <= capacity-1;cnt++){

		/*数字压入后缀表达式栈*/
		if(isdigit(tokens[cnt][0]) || isdigit(tokens[cnt][1])) {
			Calculation->data[++Calculation->top] = tokens[cnt];
		}

		/*处理运算符*/
		else{
			/*若待处理栈是空栈，将符号压栈*/
			if(is_empty(&Pending)){
				Pending.data[++Pending.top] = tokens[cnt];
			}
			
			/*遇到 ） 弹出待处理栈中 （ 之前所有符号*/
			else{
				if(tokens[cnt][1] == ')') {
					while((Pending.data[Pending.top])[1] != '('){
						Calculation->data[++Calculation->top] = Pending.data[Pending.top--];
					}
					Pending.top--;
				}
				
				/*弹出优先级更高的符号，直至无更高的符号，再压栈*/
				else{
					while ((Pending.data[Pending.top])[2] >= tokens[cnt][2]) {
						if (Pending.data[Pending.top][1] != '(') {
							Calculation->data[++Calculation->top] = Pending.data[Pending.top--];
							if (is_empty(&Pending)) {
								break;
							}
						}
						else {
							break;
						}
					}
					Pending.data[++Pending.top] = tokens[cnt];
				} 

			}
		}

	}

	/*将预处理栈中剩下的符号全部压入后缀表达式栈*/
	while(Pending.top != -1){
		Calculation->data[++Calculation->top] = Pending.data[Pending.top--];
	} 
	
	/*标记后缀表达式的终点*/
	char END[] = "QQQ";
	Calculation->data[Calculation->top + 1] = END;

	free(Pending.data);

}
 

/*多位数，小数，负数处理器*/
void parseExpression(char** tokens, List* list) {
	int count = 0;
	Node* p = list->head;
	if (!p) {
		printf("出现错误");
		exit(1);
	}

	/*临时储存数字*/
	char* token = NULL;	
	token = (char*)malloc(MAX_Length * sizeof(char));
	if (!token) {
		printf("出现错误");
		exit(1);
	}

	/*处理正数*/
	while (p) {
		int cnt = 0;
		if (isdigit(p->value)) {
			while (p && (isdigit(p->value) || (p->value) == '.')) {
				token[cnt] = p->value;
				p = p->next;
				cnt++;
			}
			token[cnt] = '\0';
			strcpy(tokens[count], token);
			(count)++;
		}
		/*处理负数*/
		else if ((p->value) == '(' && (p->next->value) == '-') {
			p = p->next;
			p = p->next;
			token[cnt] = '-';
			cnt++;
			while (p && ((isdigit(p->value) || (p->value) == '.'))) {
				token[cnt] = p->value;				
				p = p->next;
				cnt++;
			}
			/*跳过右括号*/
			p = p->next;
			token[cnt] = '\0';
			strcpy(tokens[count], token);
			count++;
		}

		/*处理运算符*/
		else {
			token[cnt] = p->value;
			/*符号连续，防止 减号 与 负号 弄混*/
			token[cnt + 1] = token[cnt];
			token[cnt + 2] = p->priority;
			token[cnt + 3] = '\0';
			strcpy(tokens[count], token);
			count++;
			p = p->next;
		}

	}


	free(token);
	Destory(list);
}

/*计算tokens容量*/
void Capacity(List* list,int* capacity) {
	Node* p = list->head;
	*capacity = 0;
	while(p){
		if (isdigit(p->value)) {
			(*capacity)++;
			/*跳过数字*/
			do {
				p = p->next;
				if (p == NULL) {
					break;
				}
			} while (isdigit(p->value) || p->value == '.');
		}
		else if (p->value == '(') {
			(*capacity)++;
			p = p->next;
			if (p->value == '-') {
				/*处理负数*/
				do {
					p = p->next;
				} while ( p->value != ')');
				p = p->next;
			}
		}
		else {
			(*capacity)++;
			p = p->next;
		}
	}
}


/*创建算式链表*/
void CREATE(char item,List* pList){
	Node* node;
	if (!(node = (Node*)malloc(sizeof(Node)))) {
		printf("出现错误");
		exit(1);
	}

	node->value = item;
	node->next = NULL;
	
	switch(node->value){
		case '+':node->priority = Add;
		         break;
		case '-':node->priority = Minus;
				 break;
		case '*':node->priority = Multiply;
				 break;		 
		case '/':node->priority = Divide;
				 break;	
		case '%':node->priority = Surplus;
				 break;		
		case '^':node->priority = Power;
				 break;		
		case '!':node->priority = Factorial;
				 break;
		case 'S':node->priority = Squrt;
				 break;	
		case 'L':node->priority = Logarithm;
				 break;
		case '(':node->priority = '9';
				 break;
		case ')':node->priority = '9';
				 break;
	}
	
	if(pList->head != NULL){
		pList->tail->next = node;
		pList->tail = node;
	}else{
		pList->head = pList->tail = node;
	}

}


/*删除链表*/
void Destory(List* pList){
	Node* p = NULL;
	Node* q = NULL;
	for(p = pList->head,q=p->next; q != NULL ;p=q,q=q->next){
		free(p);
	}
} 

/*打印链表（测试用）*/
void Print(List* pList){
	Node* p;
	for(p=pList->head;p;p=p->next){
		printf("%c ",p->value);
	}
}

void tokens_init(char*** tokens,int capacity) {
	*tokens = (char**)malloc(capacity * sizeof(char*));
	if (*tokens == NULL) {
		printf("出现错误");
		exit(1);
	}
	int cnt;
	for (cnt = 0; cnt < capacity; cnt++) {
		(*tokens)[cnt] = (char*)malloc(MAX_Length * sizeof(char));
	}
}

void Calculation_init(Stack* Calculation,int capacity) {
	InitStack(Calculation);
	Calculation->data = NULL;
	Calculation->data = (char**)malloc((capacity + 1) * sizeof(char*));
	if (Calculation->data == NULL) {
		exit(1);
	}

}
