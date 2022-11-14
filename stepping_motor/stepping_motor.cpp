#include "mbed.h"
#include "stepping_motor.h"

stepping_motor::stepping_motor( PinName pulse_pin , PinName dir_pin , float ppn, float f):pulse(pulse_pin),direction(dir_pin){
    pulse_per_num = ppn;
    frequency = f;
}

void stepping_motor::rot(float input_deg, bool dir){
    pulse = 1;
    direction = dir;
    number_of_pulse = pulse_per_num * (input_deg/360);
    for(int i = 0; i < number_of_pulse; i++){
        direction = dir;
        pulse = 1;
        wait_us(frequency/2.0);
        pulse = 0;
        wait_us(frequency/2.0);        
    }
}
