#include "ps3_controller.h"

ps3_cont::ps3_cont(PinName TX, PinName RX) : Serial(TX, RX)
{


/*      情報が正しければくる情報
    ps3data[0] = 50;            //十進数で80 shift_jisで’P’ 
    ps3data[1] = 55;            //十進数で85 shift_jisで’S’
    ps3data[2] = 33;            //十進数で51 shift_jisで’3’
    
    ps3data[3] = 0;             // ボタン各種
    ps3data[4] = 0;             // ボタン各種

    ps3data[5] = 80;            //左ｘ軸 ジョイスティック(0~128基準~256) 
    ps3data[6] = 80;            //左ｙ軸 ジョイスティック(0~128基準~256)
    ps3data[7] = 80;            //右ｘ軸 ジョイスティック(0~128基準~256)
    ps3data[8] = 80;            //右ｙ軸 ジョイスティック(0~128基準~256)
*/
    data_buff = 6;              //ボタンからながれてくる最大の情報  現在は6 （ボタン各種2byte ジョイスティック4byte）
    data_check= 0;              //現在のデータの格納状態を見る
    temp_data = 0;              //データの格納

    for(int i=0; i<data_buff; i++){
        ps3data[i] = 0;
    }
    
    baud(115200);                      //sbdbt(RCB4HV フォーマット用)
    format(8,Serial::None,1);          //8bit 偶数パリティ ストップビット
    Serial::attach(this, &ps3_cont::getdata,Serial::RxIrq);

}


void ps3_cont::getdata()
{    
    if(Serial::readable()){                     //readable() 受信をした:1、していない:0

        temp_data = Serial::getc();
        if( (temp_data == 'P') && (data_check == 0)){
            data_check++;
        }
        else if((temp_data == 'S') && (data_check == 1)){
            data_check++;   
        }
        else if((temp_data == '3') && (data_check == 2)){     
            data_check++;   
        }
        else if((data_check >= 3) && (data_check <= 8 )){
            ps3data[data_check-3]=temp_data;
            data_check++;
        }
        else{
            data_check = 0;
        }   
    }
}


char ps3_cont::getbutton(unsigned char ps3_button )
{
    unsigned char i,ret = 0xff;
    
    if( (ps3_button == START) || (ps3_button == SELECT) ){
        ps3_button &= 0x0f;
        i = ps3data[1] & ps3_button;
        if(i == ps3_button){
            ret = 1;
        }
        else{
            ret = 0;
        }
    }
    else{
        i = (ps3_button >> 4) & 0x01;
                if(i == 1){
                    ret = ps3data[i] &  0x0f;
                    switch(ret){
                        case 0x0c:
                        case 0x03:
                            ret = 0;
                            break;
                        
                        default:
                            ret = ((ps3data[i] >> (ps3_button & 0x0f)) & 0x01);
                            break;
                    }
                }
                else{
                    ret = ((ps3data[i] >> (ps3_button & 0x0f)) & 0x01);
                }
            
    }
    return ret;

}


void ps3_cont::getjoystic_left(unsigned int *left_x, unsigned int *left_y){
    
    *left_x = ps3data[2];
    *left_y = ps3data[3]; 
    
}

void ps3_cont::getjoystic_right(unsigned int *right_x, unsigned int *right_y){
    
    *right_x = ps3data[4];
    *right_y = ps3data[5]; 
    
}


void ps3_cont::printdata(){

    Serial pc(USBTX,USBRX);
    
    for(int i=0 ; i<data_buff; i++){
        pc.printf("%x\t %x\t %x\t %x\t %x\t %x\t \r\n",ps3data[0],ps3data[1],ps3data[2],ps3data[3],ps3data[4],ps3data[5]);
    }

}
