//To run use g++ -std=c++11 -lpthread -o merge merge.cpp
//Author : Shreyash Shrikant Jadhav
// Program to sort numbers parallelly
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include <ratio>
#include <chrono>

#define MAX 10000
#define THREAD_MAX 8

using namespace std;
using namespace std::chrono;

int a[MAX];
int part = 0;

void merge(int low, int mid, int high)
{
	int* left = new int[mid - low + 1];
	int* right = new int[high - mid];

	int n1 = mid - low + 1;
    int n2 = high - mid;
    int i, j;

	for (i = 0; i < n1; i++)
		left[i] = a[i + low];

	for (i = 0; i < n2; i++)
		right[i] = a[i + mid + 1];

	int k = low;
	i = j = 0;

	while (i < n1 && j < n2) {
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];
	}
	while (i < n1) {
		a[k++] = left[i++];
	}

	while (j < n2) {
		a[k++] = right[j++];
	}
}

void merge_sort(int low, int high)
{
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

//Multi-threading to split the array to multiple threads
void* merge_sort(void* arg)
{
	int thread_part = part++;
	int low = thread_part * (MAX / THREAD_MAX);
	int high = (thread_part + 1) * (MAX / THREAD_MAX) - 1;
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}
//Function to check the lsit is properly sorted
void sort_check(int a[])
{
        int count1=0;
        for(int i =0; i < MAX; i++)
        {
                if(a[i] > a[i+1])
                        count1++;
        }
        if (count1 > 1)
                cout << "Error\n";
}

int main()
{
    srand(time(0));
    for (int i = 0; i < MAX; i++)
        a[i] = (rand() % 99900)+100;    
    // High resolution clock to time the sorting 
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    pthread_t threads[THREAD_MAX];
    //Creating multiple threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, merge_sort,(void*)NULL);
    //Joining the threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);
    //Merging the threads again
    merge(0,(MAX/8)-1,(MAX/4)-1);
    merge((MAX/4),((3*MAX)/8)-1,(MAX/2)-1);
    merge((MAX/2),((5*MAX)/8)-1,((3*MAX)/4)-1);
    merge(((3*MAX)/4),((7*MAX)/8)-1,MAX-1);
    merge(0,(MAX/4)-1,(MAX/2)-1);
    merge((MAX/2),((3*MAX)/4)-1,MAX-1);
    merge(0, (MAX/2)-1, MAX - 1);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	for(int i = 0; i< MAX; i++)
		cout << a[i] << " ";
    std::cout << time_span.count()*10000<< "\n";
    sort_check(a);
    return 0;
}
