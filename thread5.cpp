#include <algorithm>
#include <stdlib.h>
#include <pthread.h>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstdlib>

using namespace std;  
using namespace std::chrono;

//variables
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
int *numbers;  //numbers list


struct data
{
    double id; 
};


//minumum value func
void find_min(int number_amount, int numbers[]){
    minumum = numbers[0];
    for (int i=1; i<number_amount; i++){
        if (numbers[i]<minumum){
            minumum=numbers[i];
        }
    }
}

//maximum value func
void find_max(int number_amount, int numbers[]){
    maximum = numbers[0];
    for (int i=1; i<number_amount; i++){
        if (numbers[i]>maximum){
            maximum=numbers[i];
        }
    }
}

//range function
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

//mode function
void find_mode(int number_amount, int numbers[]){
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

//median function
void find_median(int number_amount, int numbers[]){
    if(number_amount%2==0){
        median=(numbers[number_amount/2]+numbers[(number_amount/2)-1])/2.0;
    }
    else{
        median=(numbers[(number_amount-1)/2]);
    }
}

//sum of all element function
void find_sum(int number_amount, int numbers[]){
    sum=0; 
    for (int i=0;i<number_amount;i++){
        sum+=numbers[i];
    }
}

//arithmetic mean function
void find_arithmetic_mean(int number_amount, int numbers[]){
    double sum_arit=0; 
    for (int i=0;i<number_amount;i++){
        sum_arit+=numbers[i];
    }
    arithmetic_mean=(sum_arit/double(number_amount));

}

//harmonic mean function
void find_harmonic_mean(int number_amount, int numbers[]){
    double harmonic_sum=0; 
    for (int i=0;i<number_amount;i++){
        harmonic_sum = harmonic_sum + (double)1 / numbers[i];
    }
    harmonic_mean=(number_amount/harmonic_sum);

}

//standart deviation function
void find_standart_deviation(int number_amount, int numbers[]){
    find_arithmetic_mean(number_amount,numbers);
    double standard_deviation_sum = 0.0;
    for (int i=0;i<number_amount;i++){
        standard_deviation_sum += pow(numbers[i]-arithmetic_mean,2);
    }
    standard_deviation = sqrt(standard_deviation_sum/((double)number_amount-1.0));

}

//interquartile range function
void find_interquartile_range(int number_amount, int numbers[]){
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

//generate random number from 1000 to 10000
void generate_random(int number_amount, int numbers[]){

    for (int i=0; i<number_amount; i++){
        numbers[i] = 1000+rand()%9001;
    }
}

//pthread functions
void *thread1_func(void *param){

    find_max(number_amount, numbers);
    find_min(number_amount, numbers);
    pthread_exit(0);
}
void *thread2_func(void *param){

    find_range(number_amount,numbers);
    find_mode(number_amount,numbers);
    pthread_exit(0);
}
void *thread3_func(void *param){

    find_median(number_amount,numbers);
    find_sum(number_amount,numbers);
    pthread_exit(0);
}
void *thread4_func(void *param){

    find_arithmetic_mean(number_amount,numbers);
    find_harmonic_mean(number_amount,numbers);
    pthread_exit(0);
}
void *thread5_func(void *param){

    find_standart_deviation(number_amount,numbers);
    find_interquartile_range(number_amount,numbers);
    pthread_exit(0);
}



int main (int argc,char* argv[]){
    number_amount = atoi(argv[1]);
    
    thread_amount=5;

    numbers = new int[number_amount];
    generate_random(number_amount, numbers);
    
    sort(numbers,numbers+number_amount);

    struct data *data;
   
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;

    auto start = high_resolution_clock::now();              //time start
    pthread_create(&thread1, NULL, thread1_func, NULL);  //create pthreads
    pthread_create(&thread2, NULL, thread2_func, NULL);
    pthread_create(&thread3, NULL, thread3_func, NULL);
    pthread_create(&thread4, NULL, thread4_func, NULL);
    pthread_create(&thread5, NULL, thread5_func, NULL);


    pthread_join(thread1, NULL);    //joining main thread
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    auto end = high_resolution_clock::now();                //time end
    auto duration = duration_cast<microseconds>(end-start).count();


    ofstream file1("output2.txt");      //printing to file
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