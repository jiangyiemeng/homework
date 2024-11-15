#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include"Stack.h"
#include"Calculation.h"

int _Calculation(Stack* Calculation) {
	/*符号*/
	int i = 0;
	/*数字*/
	double num;
	int j = -1,k = -1;
	int cnt = 0;

	while (Calculation->data[i] != NULL) {
		cnt = 0;		

		/*找到下一个运算符*/
		while (isdigit(Calculation->data[i][0]) || isdigit(Calculation->data[i][1])) {
			i++;
		}

		if (Calculation->data[i][0] == 'Q') {
			/*返回存放结果的位置*/
			_Print(Calculation, j);
			return;
		}


		j = i-1;
		while (cnt != 2) {
			/*找到第一个数字*/
			if (isdigit(Calculation->data[j][0]) ||  isdigit(Calculation->data[j][1])) {
				k = j-1;
				cnt++;

				/*只需1个数字时直接退出循环*/
				if (Calculation->data[i][0] == 'S' || Calculation->data[i][0] == '!') {
					break;
				}

				while (cnt != 2) {
					
					/*防止越界,只剩一个数字时退出*/
					if (k == -1) {
						/*返回存放结果的位置*/
						_Print(Calculation, j);
						return;
					}
					/*找到第二个数字*/
					if (isdigit(Calculation->data[k][0]) || isdigit(Calculation->data[k][1])) {
						cnt++;
					}

					/*找到两个数字退出*/
					if (cnt == 2) {
						break;
					}
										
					k--;
				}
			}

			/*找到两个数字退出*/
			if (cnt == 2) {
				break;
			}
			
			/*防止越界,只剩一个数字时退出*/
			if (j == 0) {
				break;
			}
			j--;
		}


		/*还有运算符未执行*/
		if (Calculation->data[i] != NULL ) {
			switch (Calculation->data[i][1]) {
			case '+':
				/*将使用过的数字处理掉*/
				_Add(Calculation->data[k],Calculation->data[j]);
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			case '-':
				_Minus(Calculation->data[k], Calculation->data[j]);			
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			case '*':
				_Multiply(Calculation->data[k], Calculation->data[j]);
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			case '/':
				_Devide(Calculation->data[k], Calculation->data[j]);
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			case '%':
				 _Surplus(Calculation->data[k], Calculation->data[j]);
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			case '^':
				 _Power(Calculation->data[k], Calculation->data[j]);
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			case 'S':
				 _Squrt(Calculation->data[j]);
				i++;
				break;
			case '!':
				 _Factorial(Calculation->data[j]);
				i++;
				break;
			case 'L':
				 _Logarithm(Calculation->data[k], Calculation->data[j]);
				strcpy(Calculation->data[k], "E");
				i++;
				break;
			}
		}
	}


}

/*加*/
void _Add(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);

	double num_3 = num_1 + num_2;
	sprintf(b,"%.2f", num_3);

}

/*减*/
void _Minus(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);

	double num_3 = num_1 - num_2;

	sprintf(b, "%.2f", num_3);
}

/*乘*/
void _Multiply(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);

	double num_3 = num_1 * num_2;
	sprintf(b, "%.2f", num_3);

}

/*除*/
void _Devide(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	if (num_2 == 0.0) {
		printf("出现错误");
		exit(1);
	}

	double num_3 = num_1 / num_2;
	sprintf(b, "%.2f", num_3);

}

/*取余*/
void _Surplus (char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	if (num_2 == 0.0) {
		printf("出现错误");
		exit(1);
	}

	double num_3 = fmod(num_1,num_2);
	sprintf(b, "%.2f", num_3);

}

/*次方*/
void _Power(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	if (num_1 == 0.0) {
		printf("出现错误");
		exit(1);
	}

	double num_3 = pow(num_1, num_2);
	sprintf(b, "%.2f", num_3);

}

/*开方*/
void _Squrt(char* b) {
	double num_1 = atof(b);
	if (num_1 < 0) {
		printf("出现错误");
		exit(1);
	}
	double num_3 = sqrt(num_1);
	sprintf(b, "%.2f", num_3);

}

/*阶乘*/
void _Factorial(char* b) {
	double num_1 = atof(b);
	double num_3 = 1;

	int i;
	for (i = 1; i <= num_1; i++) {
		num_3 *= i;
	}

	sprintf(b, "%.2f", num_3);
}

/*对数*/
void _Logarithm(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	double num_3;

	if (num_1 <= 0 || num_1 == 1 || num_2 <= 0) {
		printf("出现错误");
		exit(1);
	}
	
	num_3 = log(num_2) / log(num_1);
	sprintf(b, "%.2f", num_3);

}

void _Print(Stack* Calculation,int result) {
	printf("%.2lf\n", atof(Calculation->data[result]));
}

void Free(Stack* Calculation, char** tokens,int capacity) {
	int cnt;
	free(Calculation->data);
	for (cnt = 0; cnt < capacity; cnt++) {
		free(tokens[cnt]);
	}
	free(tokens);
}

int isAgain(void) {
	printf("\n------------------\n");
	printf("---是否再次计算---\n");
	printf("---是     请按1---\n");
	printf("---否     请按0---\n");
	printf("------------------\n");
	int again;
	scanf("%d", &again);
	return again;
}

void isException(char** tokens,int capacity) {
	if (capacity == 1) {
		if (isdigit(tokens[0][0]) || isdigit(tokens[0][1])) {
			printf("%.2lf\n", atof(tokens[0]));
			free(tokens[0]);
			free(tokens);
			exit(0);
		}
		else {
			printf("出现错误\n");
			exit (0);
		}
	}
}