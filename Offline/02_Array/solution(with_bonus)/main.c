#include<stdio.h>
#include<math.h>
#include<string.h>
#include "utils.c"

#define MAX_SIZE 1000000
#define MAX_BINS 1000
#define MAX_STARS 50

double data[MAX_SIZE];
int bin_counts[MAX_BINS];
double sorted[MAX_SIZE];

double min_value(int l){
    double data_min = data[0];
    for(int i = 1; i<l; i++){
        if(data[i]<data_min){
            data_min = data[i];
        }
    }
    return data_min;
}

double max_value(int l){
    double data_max = data[0];
    for(int i = 1; i<l; i++){
        if(data[i]>data_max){
            data_max = data[i];
        }
    }
    return data_max;
}

double mean_value(int l){
    double data_sum = 0;
    for(int i = 0;i<l;i++){
        data_sum = data_sum + data[i];
    }
    double data_mean = data_sum/l;
    return data_mean;
}

double stddev_value(int l){
    double mean = mean_value(l);
    double sum_of_diff = 0;
    for(int i = 0;i<l;i++){
        sum_of_diff = sum_of_diff + (mean-data[i])*(mean-data[i]);
    }
    double stddev = sqrt(sum_of_diff/(l-1));
    return stddev;
}

int compare(const void *x_void, const void *y_void){
    double x = *(double*)x_void;
    double y = *(double*)y_void;
    if(x<y) return -1;
    if(x>y) return 1;
    return 0;
}

double median(double x[], int l){
    
    qsort(x, l, sizeof(double), compare);
                
    double median;
    if(l%2 == 1){
        median = x[l/2];
    }else{
        median = (x[l/2] + x[(l/2 - 1)])/2;
    }
    return median;
}

int main(){

    printf("Commands:\n");
    printf("  set     - Set array size, seed, and distribution (uniform or gaussian)\n");
    printf("  min     - Print minimum value\n");
    printf("  max     - Print maximum value\n");
    printf("  mean    - Print mean value\n");
    printf("  stddev  - Print standard deviation\n");
    printf("  median  - Print median value\n");
    printf("  hist    - Plot histogram\n");
    printf("  summary - Print min, max, mean, stddev\n");
    printf("  help    - Show this help message\n");
    printf("  exit    - Exit the program\n");

    int n=-1, i;
    int seed = -1;
    char dist_type[10];
    double uni_min, uni_max;
    double gau_mean, gau_stddev; 
    char command[10];

    int bin;

    while(1){
        printf("\nEnter command: ");
        scanf("%s", command);
        if(strcmp(command, "set") == 0){

            printf("Enter number of elements (<= 1000000): ");
            scanf("%d", &n);
            while((n<1) || (n>MAX_SIZE)){
                printf("Invalid Input. Number must be between 1 to 1000000\n");
                printf("Enter number of elements (<= 1000000): ");
                scanf("%d", &n);
            }
            

            printf("Enter seed: ");
            scanf("%d", &seed);
            while(seed<0){
                printf("Invalid seed. Seed must be positive\n");
                printf("Enter seed: ");
                scanf("%d", &seed);
            }

            printf("Distribution? (uniform/gaussian): ");
            scanf("%s", dist_type);
            while((strcmp(dist_type, "gaussian") != 0) && (strcmp(dist_type, "uniform") != 0)){
                printf("Invalid Distribution type. It should be either gaussian or uniform\n");
                printf("Distribution? (uniform/gaussian): ");
                scanf("%s", dist_type);
            }

            if(strcmp(dist_type, "gaussian") == 0){
                printf("Enter mean and stddev: ");
                scanf("%lf %lf", &gau_mean, &gau_stddev);
            
                while(gau_stddev<0){
                    printf("You entered correct mean but invalid stddev. Stddev can be only positive number!\n");
                    printf("Enter only stddev: ");
                    scanf("%lf", &gau_stddev);
                }
                populate_array_gaussian(data, n, gau_mean, gau_stddev, seed);
                printf("Array initialized with gaussian distribution.\n");
            }else{
                printf("Enter min and max: ");
                scanf("%lf %lf", &uni_min, &uni_max);
                while(uni_min>=uni_max){
                    printf("Invalid input. Min can not be greater than or equal to Max");
                    printf("\nEnter min and max: ");
                    scanf("%lf %lf", &uni_min, &uni_max);
                }
                populate_array_uniform(data, n, uni_min, uni_max, seed);
                printf("Array initialized with uniform distribution.\n");
            }

        }else if(strcmp(command, "min") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                printf("Min       :   %.4lf\n", min_value(n));
            }

        }else if(strcmp(command, "max") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                printf("Max       :   %.4lf\n", max_value(n));
            }

        }else if(strcmp(command, "mean") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                printf("Mean      :   %.4lf\n", mean_value(n));
            }

        }else if(strcmp(command, "stddev") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                printf("Std Dev   :   %.4lf\n", stddev_value(n));
            }

        }else if(strcmp(command, "hist") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                printf("Enter number of bins: ");
                scanf("%d", &bin);
                while(bin>1000 || bin<1){
                    printf("Invalid number of bins. Must be between 1 and 1000\n");
                    printf("Enter number of bins: ");
                    scanf("%d", &bin);
                }
                double min = min_value(n);
                double max = max_value(n);

                double bin_width = (max-min)/bin;
                double a = min;
                double b = min + bin_width;
                int how_many_num_in_a_interval;
                int max_num_in_a_interval = -1;
                for(i=0;i<bin;i++){
                    how_many_num_in_a_interval = 0;
                    for(int j=0;j<n;j++){
                        if(i!=(bin-1)){
                            if(data[j]>=a && data[j]<b){
                                how_many_num_in_a_interval++;
                            }
                        }else{
                            if(data[j]>=a && data[j]<=b){
                                how_many_num_in_a_interval++;
                            }
                        }

                    }
                    bin_counts[i] = how_many_num_in_a_interval;

                    if(how_many_num_in_a_interval>max_num_in_a_interval){
                        max_num_in_a_interval = how_many_num_in_a_interval;
                    }
                    a = b;
                    b = b+bin_width;
                }


                a = min;
                b = min+bin_width;

                for(i=0;i<bin;i++){
                    int num_of_star = bin_counts[i]*MAX_STARS/max_num_in_a_interval;
                    printf("[%6.2lf - %6.2lf]: ", a, b);
                    for(int k=1;k<=num_of_star;k++){
                        printf("*");
                    }
                    printf("\n");
                    a = b;
                    b = b+bin_width;
                }

            }
        }else if(strcmp(command, "summary") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                printf("Min       :  %10.4lf\n", min_value(n));
                printf("Max       :  %10.4lf\n", max_value(n));
                printf("Mean      :  %10.4lf\n", mean_value(n));
                printf("Std Dev   :  %10.4lf\n", stddev_value(n));
                for(i=0;i<n; i++){
                    sorted[i] = data[i];
                }
                printf("Median    :  %10.4lf\n", median(sorted,n));
            }

        }else if(strcmp(command, "help") == 0){
            printf("Commands:\n");
            printf("  set     - Set array size, seed, and distribution (uniform or gaussian)\n");
            printf("  min     - Print minimum value\n");
            printf("  max     - Print maximum value\n");
            printf("  mean    - Print mean value\n");
            printf("  stddev  - Print standard deviation\n");
            printf("  median  - Print median value\n");
            printf("  hist    - Plot histogram\n");
            printf("  summary - Print min, max, mean, stddev\n");
            printf("  help    - Show this help message\n");
            printf("  exit    - Exit the program\n");

        }else if(strcmp(command, "exit") == 0){
            break;
        }else if(strcmp(command, "median") == 0){
            if(n==-1){
                printf("Array not initialized. Use 'set' command first.\n");
            }else{
                for(i=0;i<n; i++){
                    sorted[i] = data[i];
                }
                
                printf("Median    :   %.4lf\n", median(sorted, n));
            }

        }else{
            printf("Invalid Input. You can Check the command list using 'help' command!\n");
        }
    }
    return 0;
}