#ifndef _rotary_encoder_H_
#define _rotary_encoder_H_

#include "mbed.h"


#define PREV_MASK 0x1
#define CURR_MASK 0x2
#define INVALID   0x3
class rotary_encoder {
public:
    enum Encoding {
        X2_ENCODING,
        X4_ENCODING
    };

    rotary_encoder( PinName channelA, PinName channelB, PinName index, int pulsesPerRev, Encoding encoding = X2_ENCODING );

    void reset( void );
    void set_current_rad( float );
    int getCurrentState( void );
    int getPulses( void );
    float getDeg( void );
    float getRad( void );
    float getVel( float );
    float not_reset_getRad( void );
    float not_reset_getDeg( void );

private:
    void encode( void );
    void index( void );
    Encoding encoding_;
    InterruptIn channelA_;
    InterruptIn channelB_;
    InterruptIn index_;

    float pulsesPerRev_;
    uint8_t prevState_;
    uint8_t currState_;
    volatile int pulses_;
    volatile int revolutions_;
    float resolution_rad_;
    float resolution_deg_;
    float magnification;        //角度の分解能を決めるために必要な変数
    float deg;
    float velocity;
    float deg_prev;
    float rad;
    float rad_prev;
    /* 2月24日追加　(リセットできる角度と，リセットをかけてもリセットされない角度を取るために追加した) */
    volatile int not_reset_pulses_;
    float not_reset_deg;
    float not_reset_rad;

};

#endif
