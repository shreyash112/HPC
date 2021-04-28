
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

pthread_mutex_t forks[10000];//Intialize the mutex for forks
int max_num;//maximum number of philosoophers to enter
int traverse[10000];//array to check whether all the philosophers have ate

//This function puts the mutex on the fork n and (n+1)%number of philosoophers
//At a time multiple philosophers can eat on whose side the
void *func(int n)
   {
	srand(10);
	//int i=0;
	while(1){
		//printf("Round %d\n", i);
		printf ("Philosopher %d is thinking\n",n+1);
		sleep(1);
		pthread_mutex_lock(&forks[n]);
		pthread_mutex_lock(&forks[(n+1)% max_num]);
		printf ("Philosopher %d is eating with forks %d and %d\n",n+1,n+1,(n+1)%max_num+1);
		traverse[n] = n;
		sleep(rand()%10);
		pthread_mutex_unlock(&forks[n]);
		pthread_mutex_unlock(&forks[(n+1)%max_num]);
		printf ("Philosopher %d finished eating with forks %d and %d\n",n+1,n+1,(n+1)%max_num+1);
		//i++;
	}
   return(NULL);
   }

int main(int argc, char **argv)
{
	
	if(argc < 2){
		printf("Input Error. Correct format is <philosopher number>\n");
		return 0;
	}
	
   int i;
   int num_phil = atoi(argv[1]);
   pthread_t philosopher[num_phil];
   max_num = num_phil;
   for(i=0;i<num_phil;i++)
      pthread_mutex_init(&forks[i],NULL);

   for(i=0;i<num_phil;i++)
      pthread_create(&philosopher[i],NULL,(void *)func,(void *)i);

   for(i=0;i<num_phil;i++)
      pthread_join(philosopher[i],NULL);

   for(i=0;i<num_phil;i++)
      pthread_mutex_destroy(&forks[i]);
  //This only to check whether each philosoopher is fed
   for(int i = 0; i < num_phil; i++)
        printf("%d 	",traverse[i]);
	printf("\n");
   return 0;
   }
