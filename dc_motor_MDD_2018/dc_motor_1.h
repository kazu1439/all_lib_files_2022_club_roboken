#ifndef _DC_MOTOR_1_
#define _DC_MOTOR_1_

#include "FastPWM.h"

class dc_motor_1{
    
    public:
        dc_motor_1(PinName pwm_port ,PinName Output_Port,bool);   //コンストラクタ
        void drive(float);
        float read();
        
    private:
        float input_pwm;
        float hertz;
        float period_second;
        float magnification;
        FastPWM pwm;
        DigitalOut output;
        bool direction;
        
};
#endif