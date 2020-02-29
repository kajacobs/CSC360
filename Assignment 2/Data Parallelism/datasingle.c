#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXLINELEN 100

float* data_points;
int size = 0;

int main(int argc, char *argv[]){

    // Opening File and creating array of data points
    char* token;
    float* data_points = (float*)malloc(0);
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
    if (argv[2] != NULL){
        size = atoi(argv[2]);
    }

    fclose(fp);

    float slope;
    float intercept;
    float error;
    int lowest_i = 0;
    int lowest_j = 0;
    float lowest_value = 0;
    float lowest_slope = 0;

    clock_t t;
    t = clock();
    for(int i = 0; i < size; i++){
        for(int j= i+1; j < size; j++){
            // calculate slope and intercept
            slope = (data_points[j]-data_points[i])/((float)j-(float)i);
            intercept = data_points[i] - ((float)i/(float)(j-i))*(data_points[j]-data_points[i]);
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
    printf("The minimum sum using %d points.\n", size);
    printf("Lowest error is %f at points %d and %d, with slope %f.\n",lowest_value, lowest_i, lowest_j, lowest_slope);
   t = clock() - t;

    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  
    printf("Took %f seconds to complete calculation.\n", time_taken); 
    
}