//Nghia Vo - Homework 9 - Using quick sort to sort 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100
struct state {
	char stateName[MAX+1];
	long int population2020;
	long int population2010;
	double percentUnder;
	double percentEqual;
	double percentGreater;
};

void swap(struct state ele1, struct state ele2);
int find_largest(struct state list[], int n);
void sort_states(struct state list[], int n);
int compare(const void *p, const void* q);
int main()
{
	char fileName[MAX+1];
	char head[MAX+1] = "sorted_";
	printf("Enter the file name: ");
	scanf("%s", fileName);
	struct state listOfState[MAX];
	strcpy(fileName, strcat(head,fileName));
	FILE *fp = fopen("state_demographics.csv","r");
	FILE *fw = fopen(fileName,"w");
	int i = 0;
	if(fp == NULL)
	{ 
		printf("error on reading");
		return 1;
	}
	//read file
	while(!feof(fp) && !ferror(fp))
	{
		fscanf(fp,"%[^,],%ld,%ld,%lf,%lf,%lf\n", listOfState[i].stateName, &listOfState[i].population2020, &listOfState[i].population2010, &listOfState[i].percentUnder, &listOfState[i].percentEqual, &listOfState[i].percentGreater);	
			 i++;
	}
	//temp = malloc(i*sizeof(struct state));
	//temp = listOfState;
	qsort(listOfState, i, sizeof(struct state), compare);
	//sort_states(listOfState, i);
	if(fw == NULL) 
	{
		printf("error on writng");
		return 1;
	}
	//write file
	for(int j = 0; j < i; j++)
		fprintf(fw, "%s, %ld, %ld, %0.1lf, %0.1lf, %0.1lf\n", listOfState[j].stateName, listOfState[j].population2020, listOfState[j].population2010, listOfState[j].percentUnder, listOfState[j].percentEqual, listOfState[j].percentGreater);	return 0;
}
//find largest element
int find_largest(struct state list[], int n)
{
	double min = list[0].percentGreater;
	int min_index = 0;
	for(int i = 1; i < n; i++)
	{	
		if(list[i].percentGreater < min)
		{
			min = list[i].percentGreater;
			min_index = i;
		}
	} 
	return min_index;
}
//sort function 
void sort_states(struct state list[], int n)
{
	if(n == 1) return;
	int min = find_largest(list, n);
	struct state temp = list[min];
        list[min] = list[n-1];
        list[n-1] = temp;
	sort_states(list, n - 1);
}
//compare function
int compare(const void *p, const void* q){
	struct state *a = (struct state *)p, *b = (struct state *)q;
	if(a->percentGreater < b->percentGreater)
		return 1;
	else if(a->percentGreater ==  b->percentGreater)
		return 0;
	else return -1;
}
