#ifndef _SERVO_MOTOR_
#define _SERVO_MOTOR_
 
class ServoMotor{
    public:
        ServoMotor(PinName,float);//コンストラクタ （引き数1:pwmのピン,引数2:初期角度[deg])
        void rot(float);
        float read();
                    
    private:
        float output_deg;
        PwmOut servo_pwmport;
    
};
#endif