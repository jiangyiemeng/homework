#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE
#include"Stack.h"
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*��ʼ��ջ*/
void InitStack(Stack* stack){
	stack->top  =-1;
}

/*�ж�ջ�Ƿ�Ϊ��*/
int is_empty(Stack* stack){
	return stack->top == -1; 
}

/*��׺->��׺ת����*/
void infixToPostfix(char** tokens,Stack* Calculation,const int capacity){
	
	/*������ʱ��ŷ��ŵ�ջ*/
	Stack Pending;
	InitStack(&Pending); 
	if (!(Pending.data = (char**)malloc( (capacity) * sizeof(char*)))){
		printf("���ִ���");
		exit (1);
	}

	
	int cnt;  //��ʱ��������ȷ������ʽȫ��ѹջ 
	for(cnt=0;cnt <= capacity-1;cnt++){

		/*����ѹ���׺���ʽջ*/
		if(isdigit(tokens[cnt][0]) || isdigit(tokens[cnt][1])) {
			Calculation->data[++Calculation->top] = tokens[cnt];
		}

		/*���������*/
		else{
			/*��������ջ�ǿ�ջ��������ѹջ*/
			if(is_empty(&Pending)){
				Pending.data[++Pending.top] = tokens[cnt];
			}
			
			/*���� �� ����������ջ�� �� ֮ǰ���з���*/
			else{
				if(tokens[cnt][1] == ')') {
					while((Pending.data[Pending.top])[1] != '('){
						Calculation->data[++Calculation->top] = Pending.data[Pending.top--];
					}
					Pending.top--;
				}
				
				/*�������ȼ����ߵķ��ţ�ֱ���޸��ߵķ��ţ���ѹջ*/
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

	/*��Ԥ����ջ��ʣ�µķ���ȫ��ѹ���׺���ʽջ*/
	while(Pending.top != -1){
		Calculation->data[++Calculation->top] = Pending.data[Pending.top--];
	} 
	
	/*��Ǻ�׺���ʽ���յ�*/
	char END[] = "QQQ";
	Calculation->data[Calculation->top + 1] = END;

	free(Pending.data);

}
 

/*��λ����С��������������*/
void parseExpression(char** tokens, List* list) {
	int count = 0;
	Node* p = list->head;
	if (!p) {
		printf("���ִ���");
		exit(1);
	}

	/*��ʱ��������*/
	char* token = NULL;	
	token = (char*)malloc(MAX_Length * sizeof(char));
	if (!token) {
		printf("���ִ���");
		exit(1);
	}

	/*��������*/
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
		/*������*/
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
			/*����������*/
			p = p->next;
			token[cnt] = '\0';
			strcpy(tokens[count], token);
			count++;
		}

		/*���������*/
		else {
			token[cnt] = p->value;
			/*������������ֹ ���� �� ���� Ū��*/
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

/*����tokens����*/
void Capacity(List* list,int* capacity) {
	Node* p = list->head;
	*capacity = 0;
	while(p){
		if (isdigit(p->value)) {
			(*capacity)++;
			/*��������*/
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
				/*������*/
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


/*������ʽ����*/
void CREATE(char item,List* pList){
	Node* node;
	if (!(node = (Node*)malloc(sizeof(Node)))) {
		printf("���ִ���");
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


/*ɾ������*/
void Destory(List* pList){
	Node* p = NULL;
	Node* q = NULL;
	for(p = pList->head,q=p->next; q != NULL ;p=q,q=q->next){
		free(p);
	}
} 

/*��ӡ���������ã�*/
void Print(List* pList){
	Node* p;
	for(p=pList->head;p;p=p->next){
		printf("%c ",p->value);
	}
}

void tokens_init(char*** tokens,int capacity) {
	*tokens = (char**)malloc(capacity * sizeof(char*));
	if (*tokens == NULL) {
		printf("���ִ���");
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
