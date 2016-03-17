#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define ARRSZ 100000
int N;
int buffer[ARRSZ];
sem_t mutex,empty[ARRSZ],fill[ARRSZ];
int wr_ptr=0,count=0,rd_ptr[ARRSZ]; 
int semval;

void put(int val){
	printf("producer puts %d\n",val);
	buffer[wr_ptr]=val;
	wr_ptr=(wr_ptr+1)%N;
	return;
}

void get(int thd_id){
	printf("\t\t\tconsumer %d reads %d\n",thd_id,buffer[rd_ptr[thd_id]]);
	rd_ptr[thd_id]=(rd_ptr[thd_id]+1)%N;
	return;
}

void * producer(void * arg){
	int i,j;i=0;
	//for(i=0;i< 2*N;i++){
	while(1){
		for(j=0;j<N;j++){
			sem_wait(&empty[j]);
		}
		sem_wait(&mutex);
		put(rand());
		sem_post(&mutex);
		
		for(j=0;j<N;j++){
			sem_post(&fill[j]);
		}
		i++;
	}
	return NULL;
}

void * consumer(void * arg){
	int i,j;
	int thd_id;
	thd_id=(int *)arg;
	//for (i = 0; i < 2*N; ++i){
	i=0;
	while(1){
		sem_wait(&fill[thd_id]);
		sem_wait(&mutex);
		get(thd_id);
		sem_post(&mutex);
		sem_post(&empty[thd_id]);
		i++;	
	}
}

int main()
{
	printf("enter size of buffer:");
	scanf("%d",&N);
	int i,j,rc;
	pthread_t p1,c[N],c1,c2,t;
	sem_init(&mutex,0,1);
	printf("PRODUCER\t\tCONSUMER\n");
	for(i=0;i<N;i++){
		sem_init(&empty[i],0,N);
		sem_init(&fill[i],0,0);
	}
	int rp=pthread_create(&p1,NULL,producer,NULL);
	for(i=0;i<N;i++){
		rc=pthread_create(&c[i],NULL,consumer,i);
	}
	rp=pthread_join(p1,NULL);
	for(i=0;i<N;i++){
		rc=pthread_join(c[i],NULL);
	}
	return 0;
}

