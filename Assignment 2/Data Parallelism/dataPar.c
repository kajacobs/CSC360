#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXLINELEN 100

void* mathtime(void* data_points);

int** error_values;
float* data_points;

int main(int argc, char *argv[]){
    
    char* token;
    float* data_points = (float*)malloc(0);
    int size = 0;
    char* line;
    size_t len;
    ssize_t read;
    float parsed_number;

    FILE* fp = fopen(argv[1], "r");
    if (fp != NULL){
        read = getline(&line, &len, fp);
        while ((read = getline(&line, &len, fp)) != -1){
            token = strtok(line, ",");
            token = strtok(NULL, ",");
            parsed_number = atof(token);
            size++;
            data_points = (float*)realloc((void*)data_points, size*sizeof(float));
            data_points[size-1] = (float)parsed_number;
        }
    } else {
        printf("read failure\n");
        return 1;
    }
    fclose(fp);

    /*
    pthread_t pthread_id[size];

    for (int i = 0; i < size; i++){
        pthread_create(&pthread_id[i], NULL, mathtime, &data_points);
    }

    for(int i = 0; i < size; i++){
        pthread_join(pthread_id[i], NULL);
    }
    */
    double slope;
    double intercept;
    double error;
    int lowest_i = 0;
    int lowest_j = 0;
    float lowest_value = 0;
    float lowest_slope = 0;

    clock_t t;
    t = clock();
    for(int i = 0; i < size; i++){
        for(int j= i+1; j < size; j++){
            // calculate slope and intercept
            slope = (data_points[j]-data_points[i])/(j-i);
            intercept = data_points[i] - (i/(j-i))*(data_points[j]-data_points[i]);
            error = 0;
            for (int k=0; k<size; k++) {
                error += fabs(data_points[k] - slope*(double)k-intercept);
            }
            if  (lowest_value == 0 || error < lowest_value) {
                lowest_value = error;
                lowest_i = i;
                lowest_j = j;
                lowest_slope = slope;
            }
        }
    }

    /*
    int myerror = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0, j < size; j++){
            if (error_values[i][j] < myerror) {
                myerror = error_values[i][j];
            }
        }
    }
    */
    printf("The minimum sum using %d points.\n", size);
    printf("Lowest error is %f at points %d and %d, with slope %f.\n",lowest_value, lowest_i, lowest_j, lowest_slope);
   t = clock() - t;

    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  
    printf("Took %f seconds to complete calculation.\n", time_taken); 
    
}

void* mathtime(void* data_points){

    return NULL;
}