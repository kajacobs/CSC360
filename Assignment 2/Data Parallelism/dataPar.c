#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXLINELEN 100
#define MAX_SIZE

void* mathtime(void* data_points);

float data_points[5000];
int numbers[5000];
pthread_mutex_t mutex;
int size = 0;
int lowest_i = 0;
int lowest_j = 0;
float lowest_value = 0;
float lowest_slope = 0;

int main(int argc, char *argv[]){

    // Opening File and creating array of data points
    char* token;
    char* line;
    size_t len;
    ssize_t read;
    double parsed_number;
    int x = 0;

    FILE* fp = fopen(argv[1], "r");
    if (fp != NULL){
        read = getline(&line, &len, fp);
        while ((read = getline(&line, &len, fp)) != -1){
            token = strtok(line, ",");
            token = strtok(NULL, ",");
            parsed_number = atof(token);
            size++;
            data_points[x] = (float)parsed_number;
            x++;
        }
    } else {
        printf("read failure\n");
        return 1;
    }
    if (argv[2] != NULL){
        size = atoi(argv[2]);
    }
    fclose(fp);


    clock_t t;
    t = clock();
    
    pthread_t pthread_id[6000];
    pthread_mutex_init(&mutex, NULL);
    for (int m = 0; m < size; m++){
        numbers[m] = m;
        pthread_create(&pthread_id[m], NULL, mathtime, &numbers[m]);
    }
    
    for(int n = 0; n < size; n++){
        pthread_join(pthread_id[n], NULL);
    }
    
    printf("The minimum sum using %d points.\n", size);
    printf("Lowest error is %f at points %d and %d, with slope %f.\n",lowest_value, lowest_i, lowest_j, lowest_slope);

    // calculating total time taken.
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("Took %f seconds to complete calculation.\n", time_taken);   
}

void* mathtime(void* number){
    int* i = number;
    float slope;
    float intercept;
    float error;

    for(int j = (*i)+1; j < size; j++){
        error = 0;
        // calculate slope and intercept       
        slope = (data_points[j]-data_points[*i])/((float)j-(float)(*i));
        intercept = data_points[*i] - ((float)(*i)/(float)(j-(*i)))*(data_points[j]-data_points[*i]);
        for (int k=0; k<size; k++) {
            error += fabs(data_points[k] - slope*(double)k-intercept);
        }
        pthread_mutex_lock(&mutex);
        if  (lowest_value == 0 || error < lowest_value) {
                lowest_value = error;
                lowest_i = *i;
                lowest_j = j;
                lowest_slope = slope;
            }
        pthread_mutex_unlock(&mutex);
    }   
    return NULL;
}