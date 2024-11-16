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
	/*����*/
	int i = 0;
	/*����*/
	double num;
	int j = -1,k = -1;
	int cnt = 0;

	while (Calculation->data[i] != NULL) {
		cnt = 0;		

		/*�ҵ���һ�������*/
		while (isdigit(Calculation->data[i][0]) || isdigit(Calculation->data[i][1])) {
			i++;
		}

		if (Calculation->data[i][0] == 'Q') {
			/*���ش�Ž����λ��*/
			_Print(Calculation, j);
			return;
		}


		j = i-1;
		while (cnt != 2) {
			/*�ҵ���һ������*/
			if (isdigit(Calculation->data[j][0]) ||  isdigit(Calculation->data[j][1])) {
				k = j-1;
				cnt++;

				/*ֻ��1������ʱֱ���˳�ѭ��*/
				if (Calculation->data[i][0] == 'S' || Calculation->data[i][0] == '!') {
					break;
				}

				while (cnt != 2) {
					
					/*��ֹԽ��,ֻʣһ������ʱ�˳�*/
					if (k == -1) {
						/*���ش�Ž����λ��*/
						_Print(Calculation, j);
						return;
					}
					/*�ҵ��ڶ�������*/
					if (isdigit(Calculation->data[k][0]) || isdigit(Calculation->data[k][1])) {
						cnt++;
					}

					/*�ҵ����������˳�*/
					if (cnt == 2) {
						break;
					}
										
					k--;
				}
			}

			/*�ҵ����������˳�*/
			if (cnt == 2) {
				break;
			}
			
			/*��ֹԽ��,ֻʣһ������ʱ�˳�*/
			if (j == 0) {
				break;
			}
			j--;
		}


		/*���������δִ��*/
		if (Calculation->data[i] != NULL ) {
			switch (Calculation->data[i][1]) {
			case '+':
				/*��ʹ�ù������ִ����*/
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

/*��*/
void _Add(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);

	double num_3 = num_1 + num_2;
	sprintf(b,"%.2f", num_3);

}

/*��*/
void _Minus(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);

	double num_3 = num_1 - num_2;

	sprintf(b, "%.2f", num_3);
}

/*��*/
void _Multiply(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);

	double num_3 = num_1 * num_2;
	sprintf(b, "%.2f", num_3);

}

/*��*/
void _Devide(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	if (num_2 == 0.0) {
		printf("���ִ���");
		exit(1);
	}

	double num_3 = num_1 / num_2;
	sprintf(b, "%.2f", num_3);

}

/*ȡ��*/
void _Surplus (char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	if (num_2 == 0.0) {
		printf("���ִ���");
		exit(1);
	}

	double num_3 = fmod(num_1,num_2);
	sprintf(b, "%.2f", num_3);

}

/*�η�*/
void _Power(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	if (num_1 == 0.0) {
		printf("���ִ���");
		exit(1);
	}

	double num_3 = pow(num_1, num_2);
	sprintf(b, "%.2f", num_3);

}

/*����*/
void _Squrt(char* b) {
	double num_1 = atof(b);
	if (num_1 < 0) {
		printf("���ִ���");
		exit(1);
	}
	double num_3 = sqrt(num_1);
	sprintf(b, "%.2f", num_3);

}

/*�׳�*/
void _Factorial(char* b) {
	double num_1 = atof(b);
	double num_3 = 1;

	int i;
	for (i = 1; i <= num_1; i++) {
		num_3 *= i;
	}

	sprintf(b, "%.2f", num_3);
}

/*����*/
void _Logarithm(char* a, char* b) {
	double num_1 = atof(a);
	double num_2 = atof(b);
	double num_3;

	if (num_1 <= 0 || num_1 == 1 || num_2 <= 0) {
		printf("���ִ���");
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
	printf("---�Ƿ��ٴμ���---\n");
	printf("---��     �밴1---\n");
	printf("---��     �밴0---\n");
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
			printf("���ִ���\n");
			exit (0);
		}
	}
}