#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int* ArrayCreator(int*,int);
int ArrayFilling(int*,int);
void ArraySort(int*,int);
int Search(int*,int,int);
int Result(int*,int,int,int);
int Modifier(int*,int,int,int);

int main()
{
	int *m,x,n=SIZE,pos;
	m=ArrayCreator(m,n);
	n=ArrayFilling(m,n);
	ArraySort(m,n);
	printf("Please, type X: ");
	scanf("%d", &x);
	pos=Search(m,x,n);
	Result(m,pos,x,n);
	return 0;
}

int* ArrayCreator(int *m, int n)
{
	if(!(m=(int*)malloc(n*sizeof(int)))) printf("Error! Some problems with array creation!\nNot enough memory!\n");
	return m;
}

int ArrayFilling(int *m, int n)
{
	FILE *fin=fopen(".\\..\\arrsortext.txt", "r");
	int *p,x,i=0;
	p=m;
	if(fin)
	{
		while (fscanf(fin,"%d",&x)==1) 
		{
			*p++=x;
			i++;
		}
	}
	fclose(fin);
	return i;
}

void ArraySort(int *m, int n)
{
	int i, min=m[0],j,pos,tmp;
	for (i=0;i<n;i++)
	{
		j=i;
		while (j<n)
		{
			if(j==i) min=m[j];
			if(m[j]<min) 
			{
				min=m[j];
				pos=j;
			}
			j++;
		}
		if(m[i]>min)
		{
			tmp=m[pos];
			m[pos]=m[i];
			m[i]=tmp;
		}
	}
}

int Search(int *m, int x, int n)
{
	
	int left=0,right=(n-1),mid=1;
	if (x<m[left] || x>m[right]) return -1;
	if(x==m[left]) return 0;
	if(x==m[right]) return right;
	while (x>m[left] && x<m[right] && abs(left-right)>1)
		{
			mid=(left+right)/2;
			if(x==m[mid]) return mid;
			if (x>m[mid]) left = mid;
			else right = mid;
		}
	if(x>m[mid]) mid++;
	return ((-1)*mid);
}

int Result(int *m,int res, int x, int n)
{
	char yn;
	if (res==-1) 
	{
		printf("Number X(%d) doesn't belong to our array!\n",x);
		return 1;
	}
	if (res==0) 
	{
		printf("Number %d belongs to our array!\n It is the first item in array! (0)\n",x);
		return 1;	
	}
	if (res==n-1)
	{
	 	printf("Number %d belongs to our array!\n It is the last item in array! (%d)\n",x,n-1);
	 	return 1;
	}
	if(res>0)
	{
	 	printf("Number %d belongs to our array!\n Position is %d\n",x,res);
	 	return 1;
	}
	if(res<0)
	{
		printf("Number %d belongs to our array, but it hasn't any matches and can be placed at position number %d\n\nDo you want to add this number to array?\nType [y\\n]: ",x,abs(res));
		yn=getch();
		if (yn=='y') 
		{
			if(Modifier(m,n,abs(res),x)) printf("\nNumber was added to array!\nFilename: arrsortext.txt\nArray Size: %d\nOur number: %d\nPosition of new number: %d\nAvailable number of items for array: %d\n",n,x,abs(res),SIZE);
			else printf("\nWarning! Error while writing a file!");
		}
		else if (yn=='n') printf("\nOk! Let's keep an array unmodified!\nFilename: arrsortext.txt\nArray Size: %d\nOur number: %d\nEstimated position of new number: %d\nAvailable number of items for array: %d\n",n,x,abs(res),SIZE);
		else printf("\nYou typed other symbol. Array will not be modified!\nFilename: arrsortext.txt\nArray Size: %d\nOur number: %d\nEstaimated position of new number: %d\nAvailable number of items for array: %d\n",n,x,abs(res),SIZE);
		return 1;
	}
}

int Modifier(int *m,int n, int pos, int x)
{
	n++;
	if (n>SIZE) 
	{
		printf("\nSorry, but our array is full!");
		return 0;
	}
	FILE *fout=fopen(".\\..\\arrsortext.txt","w");
	if(!fout) printf("Can't create a file! Check permissions!'");
	int i;
	for(i=n;i>pos;i--) m[i]=m[i-1];
	m[pos]=x;
	for(i=0;i<n;i++) fprintf(fout,"%d ",m[i]);
	fclose(fout);
	return 1;
}
