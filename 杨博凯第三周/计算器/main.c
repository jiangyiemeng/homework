#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Stack.h"
#include"Calculation.h"

int main(int argc, char *argv[]){
	
	/*������ʽ*/
	List list;
	char item;
	int capacity=0;
	
	printf("֧��С��(����2λС��)������ (�����������ţ�eg.(-1))����λ����ָ����^�����׳ˣ������������ţ��� S ���棩,ȡ������\n\
�������� L ���� eg. 5L125��5Ϊ������125Ϊ��������\n\
(ע��1.�벻Ҫʹ�ÿո�  2.֧�����20λ��������С���� 3.����=����  4.������Ӣ�����ţ���ĸΪ��д)\n\n");
again:
	list.head = list.tail = NULL;
	printf("��������ʽ��\n");
	do{
		scanf("%c",&item);
		if(item != '='){
			CREATE(item,&list);
		}
	}while(item != '=');
	/*����tokens������*/
	Capacity(&list, &capacity);


	/*�����ʽ,���ͷ�list*/
	char** tokens = NULL;
	tokens_init(&tokens,capacity);
	parseExpression(tokens, &list);

	/*����ֻ����һ�����ֻ���ŵ����*/
	isException(tokens, capacity);


	/*������ź�׺���ʽ��ջ*/ 
	Stack Calculation;
	Calculation_init(&Calculation, capacity);
	/*��׺->��׺ */
	infixToPostfix(tokens,&Calculation, capacity); 
	

	/*����*/
	_Calculation(&Calculation);


	/*�ͷ�����Ŀռ�*/
	Free(&Calculation, tokens, capacity);


	/*�Ƿ��ٴμ���*/
	if (isAgain()) {
		goto again;
	}
	
	return 0;
}
