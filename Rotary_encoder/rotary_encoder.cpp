#include "rotary_encoder.h"
rotary_encoder::rotary_encoder(
    PinName channelA,
    PinName channelB,
    PinName index,
    int pulsesPerRev,
    Encoding encoding ) : channelA_( channelA ), channelB_( channelB ),
    index_( index ) {
    pulses_       = 0;
    revolutions_  = 0;
    pulsesPerRev_ = ( float )pulsesPerRev;
    encoding_     = encoding;
    velocity      = 0.0;
    deg           = 0.0;
    deg_prev      = 0.0;
    rad           = 0.0;
    rad_prev      = 0.0;
    not_reset_pulses_ = 0;
    not_reset_deg     = 0;
    not_reset_rad     = 0;
    int chanA = channelA_.read();
    int chanB = channelB_.read();
    currState_ = ( chanA << 1 ) | ( chanB );
    prevState_ = currState_;
    channelA_.rise( this, &rotary_encoder::encode );
    channelA_.fall( this, &rotary_encoder::encode );
    if (encoding == X4_ENCODING){
        channelB_.rise( this, &rotary_encoder::encode );
        channelB_.fall( this, &rotary_encoder::encode );
        magnification = 4.0;
    }
    else {
        magnification = 2.0;
    }
    float sesolved_value = 1 / ( pulsesPerRev_ * magnification );       //360または2*paiを割るための値
    resolution_rad_ = ( 2 * 3.14159 * sesolved_value ); // 分解能
    resolution_deg_ = ( 360.0 * sesolved_value );
    if (index !=  NC){
        index_.rise( this, &rotary_encoder::index );
    }
}
void rotary_encoder::reset( void ) {
    pulses_      = 0;
    revolutions_ = 0;
    deg          = 0.0;
    rad          = 0.0;
}
/*
* @fn set_current_rad( float current_rad )
* @brief 今の値がcurrent_radになるようにpulses_を変更
*/
void rotary_encoder::set_current_rad( float current_rad ){
    pulses_ = ( int )( current_rad / resolution_rad_ );
    return;
}
int rotary_encoder::getCurrentState( void ) {
    return currState_;
}
int rotary_encoder::getPulses( void ) {
    return pulses_;
}
float rotary_encoder::getVel( float CTRL_PERIOD ){
    velocity = ( rad - rad_prev ) / CTRL_PERIOD;
    return velocity;
}
float rotary_encoder::getDeg( void ) {
    deg_prev = deg;
    deg = pulses_ * resolution_deg_;
    return deg;
}
float rotary_encoder::not_reset_getDeg( void ) {
    not_reset_deg = not_reset_pulses_ * resolution_deg_;
    return not_reset_deg;
}
float rotary_encoder::getRad( void ){
    rad_prev = rad;
    rad = pulses_ * resolution_rad_;
    return rad;
}
float rotary_encoder::not_reset_getRad( void ){
    not_reset_rad = not_reset_pulses_ * resolution_rad_;
    return not_reset_rad;
}
void rotary_encoder::encode( void ) {
    int chanA  = channelA_.read();
    int chanB  = channelB_.read();
    currState_ = ( chanA << 1 ) | ( chanB );
    if (encoding_ == X2_ENCODING){
        if (( prevState_ == 0x3 && currState_ == 0x0 ) || ( prevState_ == 0x0 && currState_ == 0x3 )){
            pulses_++;
            not_reset_pulses_++;
        }
        else if (( prevState_ == 0x2 && currState_ == 0x1 ) || ( prevState_ == 0x1 && currState_ == 0x2 )){
            pulses_--;
            not_reset_pulses_--;
        }
    }
    else if (encoding_ == X4_ENCODING){
        if ((( currState_ ^ prevState_ ) != INVALID ) && ( currState_ != prevState_ )){
            int change = ( prevState_ & PREV_MASK ) ^ (( currState_ & CURR_MASK ) >> 1 );
            if (change == 0){
                change = -1;
            }
            pulses_ -= change;
            not_reset_pulses_ -= change;
        }
    }
    prevState_ = currState_;
}
void rotary_encoder::index( void ) {
    revolutions_++;
}
