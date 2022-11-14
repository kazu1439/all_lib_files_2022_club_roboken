#include "mbed.h"
#include "servo_motor_270.h"

ServoMotor_270::ServoMotor_270(PinName servo_pwmport_,float init_deg):servo_pwmport(servo_pwmport_){
    servo_pwmport.period(0.02);         //pwm周期を20msにする
    output_deg = init_deg;           //outputの初期化
    servo_pwmport.pulsewidth(0.0007);
    servo_pwmport.pulsewidth((init_deg/168750.0)+0.0007);
}

void ServoMotor_270::rot(float input_deg){
    
    float temp = 0.0;
    
    if(input_deg<0.0){                  //0度以下の値は0にする
        output_deg=0.0;
    }
    else if(input_deg>270.0){
        output_deg=270.0;
    }
    
    output_deg=input_deg; 
    servo_pwmport.pulsewidth((output_deg/168750.0)+0.0007);//pwmのパルスの出力幅を計算。この計算は23msが270度、7msが0度の計算式。
}


float ServoMotor_270::read(){
    return output_deg;
}


void ServoMotor_270::weak_condition(){
       servo_pwmport.pulsewidth(0.00005);   //脱力状態(50usで発生する)
}

