#ifndef _MOVING_AVE_
#define _MOVING_AVE_
#include "mbed.h"

#define pastval_num 20

class moving_ave {
    public:
        moving_ave();    //移動平均クラス
        void  init_read(float);     //初期のアナログの値を格納するために行う関数
        float MVresult_read(float); //移動平均前の値を渡し，移動平均をかけ終わった値を返す．
        
        
    private:
        float real_val[pastval_num];
        float start_val;
        
        float temp;
        float moving_ave_result;
            
};
#endif