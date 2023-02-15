#include <algorithm>
#include <stdlib.h>
#include <pthread.h>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstdlib>

using namespace std;  
using namespace std::chrono;

int minumum;
int maximum;
int range;
int mode;
double median;
int sum;
double arithmetic_mean;
double harmonic_mean;
double standard_deviation;
double interquartile_range;

int number_amount;
int thread_amount=0;
int *numbers;


struct data
{
    double id; 
};



void find_min(int number_amount, int numbers[]){
    minumum = numbers[0];
    for (int i=1; i<number_amount; i++){
        if (numbers[i]<minumum){
            minumum=numbers[i];
        }
    }
}

void find_max(int number_amount, int numbers[]){
    maximum = numbers[0];
    for (int i=1; i<number_amount; i++){
        if (numbers[i]>maximum){
            maximum=numbers[i];
        }
    }
}

void find_range(int number_amount, int numbers[]){
    int max_range = numbers[0];
    int min_range = numbers[0];
    for (int i=1; i<number_amount; i++){
        if (numbers[i]>max_range){
            max_range=numbers[i];

        }
        else if(numbers[i]<min_range){
            min_range=numbers[i];
        }
    }
    range = max_range-min_range;
}

void find_mode(int number_amount, int numbers[]){
    //sort(numbers,numbers+number_amount);
    int times=1;
    int maxtimes=0;
    mode = numbers[0];
    for (int i=0; i<number_amount-1; i++){
        if(numbers[i]==numbers[i+1]){
            times+=1;
            if (times>maxtimes){
                maxtimes=times;
                mode=numbers[i];
            }
        }
        else{
            times=1;
        }
    }
}

void find_median(int number_amount, int numbers[]){
    //sort(numbers,numbers+number_amount);
    if(number_amount%2==0){
        median=(numbers[number_amount/2]+numbers[(number_amount/2)-1])/2.0;
    }
    else{
        median=(numbers[(number_amount-1)/2]);
    }
}
void find_sum(int number_amount, int numbers[]){
    sum=0; 
    for (int i=0;i<number_amount;i++){
        sum+=numbers[i];
    }
}
void find_arithmetic_mean(int number_amount, int numbers[]){
    //sort(numbers,numbers+number_amount);
    double sum_arit=0; 
    for (int i=0;i<number_amount;i++){
        sum_arit+=numbers[i];
    }
    arithmetic_mean=(sum_arit/double(number_amount));

}
void find_harmonic_mean(int number_amount, int numbers[]){
    //sort(numbers,numbers+number_amount);
    double harmonic_sum=0; 
    for (int i=0;i<number_amount;i++){
        harmonic_sum = harmonic_sum + (double)1 / numbers[i];
    }
    harmonic_mean=(number_amount/harmonic_sum);

}
void find_standart_deviation(int number_amount, int numbers[]){
    //sort(numbers,numbers+number_amount);
    find_arithmetic_mean(number_amount,numbers);
    double standard_deviation_sum = 0.0;
    for (int i=0;i<number_amount;i++){
        standard_deviation_sum += pow(numbers[i]-arithmetic_mean,2);
    }
    standard_deviation = sqrt(standard_deviation_sum/((double)number_amount-1.0));

}
void find_interquartile_range(int number_amount, int numbers[]){
    //sort(numbers,numbers+number_amount);
    double num1,num2;
    if(number_amount%2==0){
        if(number_amount%4==0){
            num1=(numbers[number_amount/4]+numbers[number_amount/4-1])/2;
            num2=(numbers[number_amount*3/4]+numbers[number_amount*3/4-1])/2;

        }
        else{
            num1=(numbers[(number_amount+2)/4-1]);
            num2=(numbers[number_amount-((number_amount+2)/4)]);
        }
    }
    else{
        if((number_amount+1)%4==0){
            num1=(numbers[(number_amount+1)/4-1]);
            num2=(numbers[number_amount-((number_amount+1)/4)]);
        }
        else{
            num1=(numbers[(number_amount-1)/4]+numbers[(number_amount-1)/4-1])/2;
            num2=(numbers[(number_amount-1)*3/4]+numbers[(number_amount-1)*3/4+1])/2;
        }
    }
    interquartile_range=num2-num1;

}
void generate_random(int number_amount, int numbers[]){

    for (int i=0; i<number_amount; i++){
        numbers[i] = 1000+rand()%9001;
    }
}


void *thread1_func(void *param){

    find_max(number_amount, numbers);
    pthread_exit(0);
}
void *thread2_func(void *param){

    find_range(number_amount,numbers);
    pthread_exit(0);
}
void *thread3_func(void *param){

    find_median(number_amount,numbers);
    pthread_exit(0);
}
void *thread4_func(void *param){

    find_arithmetic_mean(number_amount,numbers);
    pthread_exit(0);
}
void *thread5_func(void *param){

    find_standart_deviation(number_amount,numbers);
    pthread_exit(0);
}
void *thread6_func(void *param){

    find_min(number_amount, numbers);
    pthread_exit(0);
}
void *thread7_func(void *param){

    find_mode(number_amount,numbers);
    pthread_exit(0);
}
void *thread8_func(void *param){

    find_sum(number_amount,numbers);
    pthread_exit(0);
}
void *thread9_func(void *param){

    find_harmonic_mean(number_amount,numbers);
    pthread_exit(0);
}
void *thread10_func(void *param){

    find_interquartile_range(number_amount,numbers);
    pthread_exit(0);
}



int main (int argc,char* argv[]){
    number_amount = atoi(argv[1]);
    
    thread_amount=10;

    numbers = new int[number_amount];
    generate_random(number_amount, numbers);

    sort(numbers,numbers+number_amount);
    
    
    struct data *data;
   
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;
    pthread_t thread6;
    pthread_t thread7;
    pthread_t thread8;
    pthread_t thread9;
    pthread_t thread10;

    auto start = high_resolution_clock::now();
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);
    pthread_create(&thread3, NULL, thread3_func, NULL);
    pthread_create(&thread4, NULL, thread4_func, NULL);
    pthread_create(&thread5, NULL, thread5_func, NULL);
    pthread_create(&thread6, NULL, thread6_func, NULL);
    pthread_create(&thread7,NULL, thread7_func, NULL);
    pthread_create(&thread8, NULL, thread8_func, NULL);
    pthread_create(&thread9, NULL, thread9_func, NULL);
    pthread_create(&thread10, NULL, thread10_func, NULL);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    pthread_join(thread8, NULL);
    pthread_join(thread9, NULL);
    pthread_join(thread10, NULL);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end-start).count();


    ofstream file1("output3.txt");
    file1<<minumum<<endl;
    file1<<maximum<<endl;
    file1<<range<<endl;
    file1<<mode<<endl;
    file1<<median<<endl;
    file1<<sum<<endl;
    file1<<arithmetic_mean<<endl;
    file1<<harmonic_mean<<endl;
    file1<<standard_deviation<<endl;
    file1<<interquartile_range<<endl;
    file1<<duration;
    file1.close();
    

    
    return 0;
}