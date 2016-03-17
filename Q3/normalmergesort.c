#include <stdio.h>
#define N 100009

int a[N],c[N];
void divide(int beg,int end)
{
	int mid,i,j,k;
	if(beg>=end)
		return;
	mid=(beg+end)/2;
	divide(beg,mid);
	divide(mid+1,end);

	i=beg;j=mid+1;
	k=0;
	while(i<=mid&&j<=end)
	{
		if(a[i]>a[j])
		{
			c[k++]=a[j];
			j++;
		}
		else
		{
			c[k++]=a[i];
			i++;
		}
	}
	while(i<=mid)
	{
		c[k++]=a[i];
		i++;
	}
	while(j<=end)
	{
		c[k++]=a[j];
		j++;
	}
	k=0;
	for(i=beg;i<=end;i++)
		a[i]=c[k++];
}

int main()
{
	int i,j,n;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	divide(0,n-1);
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}