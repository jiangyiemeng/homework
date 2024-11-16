#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    double num;
    struct node* next;
}node;

typedef struct list{
    node* head;
    node* top;
}list;

void nodeadd(list* plist, double m){
    node* p=(node*)malloc(sizeof(node));
    p->num=m;
    p->next=NULL;
    if(plist->top==NULL){
    	plist->top=p;
	}
	else{
		p->next=plist->top;
		plist->top=p;
	}
}

double nodeout(list* plist){
	node* e;
	e=plist->top;
	double ifm = e->num;
	plist->top=e->next;
	free(e);
    return ifm;
}

double gettop(list* plist){
	//printf("top=%lf\n", plist->top->num);
    return plist->top->num;
}

double calculate(double a, double b, char op){
	double ret;
	switch(op){
		case '+': ret=a+b;break;
		case '-': ret=a-b;break;
		case '*': ret=a*b;break;
		case '/': {
			if(b==0){
			printf("被除数不能为0，错误");
			}else{
			ret=a/b;	
			}
			break;
		}
	}
	return ret;
	
}

double allcal(char* arr){
    //printf("arrin=%s\n", arr);
	list list;
	list.top=NULL;
	node* e;
	int i=0;
	double result;
	char* token = strtok(arr, " ");
//	printf("token=%c\n", token[2]);
	while(token!=NULL){
  //  printf("calculate\n");
  // printf("token=%c\n", token[0]);
		if(isdigit(token[0])){
			nodeadd(&list, atof(&token[0]));
            gettop(&list);}
            else if(list.top->num==0&&token[0]=='/'){
            	printf("被除数不能为0，错误");
            	
			} 
        else{
			double a =nodeout(&list);
           // printf("a=%lf\n",a);
			double b =nodeout(&list);
           //printf("b=%lf\n",b);
			nodeadd(&list,calculate(b,a,token[0]));
            
		}
		//i++;
		token =strtok(NULL, " ");
	}
    gettop(&list);
	result = gettop(&list);
   // printf("result=%lf\n", result);
	return result;
	
}



int main(void){
	char arr[1000];
	gets(arr);
//	printf("arr=%s\n", arr);
	double ret = allcal(arr);
	printf("ret=%lf", ret);
	return 0;
	}
	
	

