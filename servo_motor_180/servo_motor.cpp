#include "mbed.h"
#include "servo_motor.h"
 
ServoMotor::ServoMotor(PinName servo_pwmport_,float init_deg):servo_pwmport(servo_pwmport_){
    servo_pwmport.period(0.02);         //pwm周期を20msにする
    output_deg = init_deg;              //outputの初期化
    servo_pwmport.pulsewidth(0.0006);
    servo_pwmport.pulsewidth((init_deg/100000)+0.0006);
}
 
void ServoMotor::rot(float input_deg){
    if(input_deg<0.0){                  //0度以下の値は0にする
        output_deg=0.0;
    }
    else if(input_deg>180.0){
        output_deg=180.0;
    }
    output_deg=input_deg; 
    servo_pwmport.pulsewidth((output_deg/100000)+0.0006);//pwmのパルスの出力幅を計算。この計算は24msが180度、0.6msが0度の計算式。
}
 
float ServoMotor::read(){
    return output_deg;
}