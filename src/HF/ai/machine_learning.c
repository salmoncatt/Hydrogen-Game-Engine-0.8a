#include "machine_learning.h"


void hf_test_machine_learning(){
    
    f64 deviation = 0;
    f64 b0 = 0;
    f64 b1 = 0;
    f64 learn_rate = 0.01;
    
    //to store best data values
    f64 best_b0 = 0;
    f64 best_b1 = 0;
    f64 best_deviation = 999999999999;
    
    u32 epochs = 500;
    f64 data_x[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    f64 data_y[11] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    f64* x = hf_array_create_from_data(data_x, f64, 11);
    f64* y = hf_array_create_from_data(data_y, f64, 11);
    
    for(u32 i = 0; i < epochs; i++){
        for(u32 j = 0; j < hf_array_size(x); j++){
            f64 prediction = b0 + b1 * x[j];
            deviation = prediction - y[j];
            b0 = b0 - learn_rate * deviation;
            b1 = b1 - learn_rate * deviation * x[j];
            printf("b0: [%lf], b1: [%lf], deviation: [%lf]\n", b0, b1, deviation);
            
            if(fabs(deviation) < best_deviation){
                best_deviation = fabs(deviation);
                best_b0 = b0;
                best_b1 = b1;
            }
            
        }
    }
    
    
    printf("[best values]    b0: [%lf], b1: [%lf], deviation: [%lf]\n\n\n", best_b0, best_b1, best_deviation);
    printf("[HF AI] testing...\n");
    
    
    for(u32 i = 0; i < 100; i++){
        f64 prediction = best_b0 + b1 * i;
        printf("in: [%u], prediction: [%lf]\n", i, prediction);
    }
    
}