#ifndef _SERVO_MOTOR_270_
#define _SERVO_MOTOR_270_

class ServoMotor_270{
    public:
        ServoMotor_270(PinName,float);//コンストラクタ （引き数1:pwmのピン,引数2:初期角度)
        void rot(float);                //引数 目標角度
        float read();                   
        void weak_condition();          //脱力状態にする
                    
    private:
        float output_deg;
        PwmOut servo_pwmport;
    
};
#endif