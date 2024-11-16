#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"Stack.h"
#include"Calculation.h"

int main(int argc, char *argv[]){
	
	/*创建算式*/
	List list;
	char item;
	int capacity=0;
	
	printf("支持小数(保留2位小数)，负数 (负数请用括号，eg.(-1))，多位数，指数（^），阶乘（！），，根号（用 S 代替）,取余运算\n\
对数（用 L 代替 eg. 5L125（5为底数，125为真数））\n\
(注：1.请不要使用空格  2.支持最大20位数，包括小数点 3.输入=结束  4.括号用英文括号，字母为大写)\n\n");
again:
	list.head = list.tail = NULL;
	printf("请输入算式：\n");
	do{
		scanf("%c",&item);
		if(item != '='){
			CREATE(item,&list);
		}
	}while(item != '=');
	/*计算tokens的容量*/
	Capacity(&list, &capacity);


	/*存放算式,并释放list*/
	char** tokens = NULL;
	tokens_init(&tokens,capacity);
	parseExpression(tokens, &list);

	/*处理只输入一个数字或符号的情况*/
	isException(tokens, capacity);


	/*建立存放后缀表达式的栈*/ 
	Stack Calculation;
	Calculation_init(&Calculation, capacity);
	/*中缀->后缀 */
	infixToPostfix(tokens,&Calculation, capacity); 
	

	/*计算*/
	_Calculation(&Calculation);


	/*释放申请的空间*/
	Free(&Calculation, tokens, capacity);


	/*是否再次计算*/
	if (isAgain()) {
		goto again;
	}
	
	return 0;
}
