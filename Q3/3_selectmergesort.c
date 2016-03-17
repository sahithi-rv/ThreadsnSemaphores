#include <stdio.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#define N 100001
int shmid,temp_shmid;
int *sharedArray,n;
int c[N];
void divide(int a,int b){
	int pos[2];
	pos[0]=a;pos[1]=b;
	if(pos[0]>=pos[1]){
		return;
	}
	//selection sort
	else if(b-a+1<5){
		int t,j,k,mini;
		for(j=a;j<=b;j++){
			mini=j;
			for(k=j+1;k<=b;k++){
				if(sharedArray[mini]>sharedArray[k])
					mini=k;
			}
			t=sharedArray[j];
			sharedArray[j]=sharedArray[mini];
			sharedArray[mini]=t;
		}
	}
	int r1,r2;
	int mid=(pos[0]+pos[1])/2;
	//printf("mid %d beg %d end %d\n",mid,pos[0],pos[1]);
	pid_t p1,p2;
	p1 = fork();
	if(p1==0){
		divide(pos[0],mid);
		exit(0);
	}
	else if(p1<0) perror("terminated");
	else{
		p2 = fork();
		if(p2==0){
			divide(mid+1,pos[1]);
			exit(0);
		}
		else if(p1<0) perror("terminated");
		else{

			waitpid(p1,&r1,0);
			waitpid(p2,&r2,0);		
		}
	}
	int i=pos[0],j=mid+1;
	int end=pos[1],k=0,beg=pos[0];
	while(i<=mid&&j<=pos[1]){
		if(sharedArray[i]>sharedArray[j])
		{
			c[k++]=sharedArray[j];
			j++;
		}
		else
		{
			c[k++]=sharedArray[i];
			i++;
		}
	}
	while(i<=mid)
	{
		c[k++]=sharedArray[i];
		i++;
	}
	while(j<=end)
	{
		c[k++]=sharedArray[j];
		j++;
	}
	k=0;
	for(i=beg;i<=end;i++)
		sharedArray[i]=c[k++];
}
int main(){
	int i,j,r1;
	scanf("%d",&n);
	shmid=shmget(IPC_PRIVATE,sizeof(int)*n,IPC_CREAT|0666);
	sharedArray=(int *)shmat(shmid,NULL,0);
	for(i=0;i<n;i++){
		scanf("%d",&sharedArray[i]);
	}
	int p[]={0,n-1};
	divide(0,n-1);
	for(i=0;i<n;i++)printf("%d ",sharedArray[i] );
	printf("\n");
	return 0;
}



