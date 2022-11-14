#include "mbed.h"
#include "moving_ave.h"

moving_ave::moving_ave(){
    
    temp = 0.0;
        
}

void moving_ave::init_read(float init_value){
    
    start_val = init_value;
     
    for(int i=0; i<pastval_num; i++){
        real_val[i] = start_val;
    }

} 


/**** 移動平均をかけた結果を返す *************/
float moving_ave::MVresult_read(float before_moving_value){
    temp = 0.0;
    real_val[0] = before_moving_value;
  
    for(int j=0; j<pastval_num; j++){
        temp = temp + real_val[j];
    }
    moving_ave_result = (temp/pastval_num);
     
    for(int k=1; k<pastval_num; k++){
        real_val[pastval_num-k] = real_val[pastval_num-(k+1)];   
    }

    return moving_ave_result;
}