#include "mbed.h"
#include "dc_motor_1.h"

dc_motor_1::dc_motor_1( PinName pwm_port , PinName output_Port , bool dire):pwm(pwm_port),output(output_Port){
    hertz=16000.0; //MDD10Aの最大周波数は20kHs(50us).
    period_second=1.0/(hertz);
    pwm.period(period_second);
    magnification = period_second/100;
    output.write(1);
    pwm.pulsewidth(0.0);
    direction = dire;
}

void dc_motor_1::drive(float mtr_pwm){
    input_pwm = mtr_pwm;
    if( (mtr_pwm < 0) && (mtr_pwm >= -99.0)){
        output.write(direction);
        mtr_pwm = -1*mtr_pwm;
    }
    else if( (mtr_pwm > 0) && (mtr_pwm <= 99.0)){
        output.write(!direction);
    }
    else if( mtr_pwm < -99.0){
        output.write(direction);
        mtr_pwm = 99.0;
    }
    else if( mtr_pwm > 99.0){
        output.write(!direction);
        mtr_pwm = 99.0;    
    }
    
    mtr_pwm = mtr_pwm * magnification; //pwm周期の最少と最大をあわせるために倍率をかける．
    pwm.pulsewidth(mtr_pwm);
}

float dc_motor_1::read(){
    return input_pwm;
}