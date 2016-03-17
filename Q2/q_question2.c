/* works fyn but no queues...*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//#define N 3 // inn size
#define ARRSZ 100000
int TEAMS1=0,TEAMS2=0,N;
pthread_cond_t y[ARRSZ],l[ARRSZ];
pthread_mutex_t mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
int counter1=0,counter2=0;
int lan_que[ARRSZ],york_que[ARRSZ];
int lan_tail=-1,lan_head=0,york_head=0,york_tail=-1;
void * func1(void * arg){
	int i=((int *)arg),flag=0;
	pthread_mutex_lock(&mutex);
			york_tail=(york_tail+1);
			york_que[york_tail]=i;
			printf("\t\t\tyork %d entered queue\n",i);
		while(counter1==N||counter2!=0){
			pthread_cond_wait(&y[i],&mutex);
		}
		york_head=(york_head+1);
		printf("\t\t\tyork %d left queue\n",i);
		counter1++;
		printf("york %d entered\n",i );
	pthread_mutex_unlock(&mutex);
	sleep(1);
	pthread_mutex_lock(&mutex);
	printf("york %d leaving \n",i );
	counter1--;
	int temp=N-counter1;int yh=york_head;
	while(temp>0 && yh<=york_tail){
		pthread_cond_signal(&y[york_que[yh]]);
		yh++;
		temp--;
	}
	temp=N-counter2;int lh=lan_head;
	while(counter1==0 && temp>0 && lh<=lan_tail){
		pthread_cond_signal(&l[lan_que[lh]]);
		temp--;
		lh++;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void * func2(void * arg){
	int i=((int *)arg);
	pthread_mutex_lock(&mutex);
		lan_tail=(lan_tail+1);
		lan_que[lan_tail]=i;
		printf("  \t\t\t\t\t\tlan %d entered queue \n",i);
		while(counter2==N||counter1!=0)
			pthread_cond_wait(&l[i],&mutex);
		lan_head=(lan_head+1);
		printf("  \t\t\t\t\t\tlan %d left queue\n",i);
		counter2++;
		printf("lanchester %d entered\n",i );
	pthread_mutex_unlock(&mutex);
	sleep(1);
	pthread_mutex_lock(&mutex);
	printf("lanchester %d leaving \n",i );
	counter2--;
	int temp=N-counter1;int yh=york_head;
	while(counter2==0 && temp>0 && yh<=york_tail){
		pthread_cond_signal(&y[york_que[yh]]);
		temp--;
		yh++;
	}
	temp=N-counter2;int lh=lan_head;
	while(temp>0 && lh<=lan_tail){
		pthread_cond_signal(&l[lan_que[lh]]);
		lh++;
		temp--;
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int main(){
	int i,t,tot;
	pthread_t york[ARRSZ],lan[ARRSZ];
	printf("enter inn size:");
	scanf("%d",&N);
	printf("enter number of soldiers:");
	scanf("%d",&tot);
	i=0;int j=0;
	printf("ENTRY  \t\t\t YORKS QUEUE\t\t  LANCHESTER'S QUEUE\n");
	while(tot--){
		if(rand()%2==0){
			y[TEAMS1++]=(pthread_cond_t)PTHREAD_COND_INITIALIZER;
			t=pthread_create(&york[i],NULL,func1,i);
			i++;
		}
		else{
			l[TEAMS2++]=(pthread_cond_t)PTHREAD_COND_INITIALIZER;
			t=pthread_create(&lan[j],NULL,func2,j);
			j++;
		}

	}
	/*printf("number of yorks=%d\n",TEAMS1);	
	printf("number of lanchesters=%d\n",TEAMS2);*/		
	for(i=0;i<TEAMS1;i++){
		t=pthread_join(york[i],NULL);
	}
	for(i=0;i<TEAMS2;i++){
		t=pthread_join(lan[i],NULL);
	}
}
