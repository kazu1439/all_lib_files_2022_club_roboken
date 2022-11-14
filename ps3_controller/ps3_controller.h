#ifndef _PS3_CONTROLLER_H_
#define _PS3_CONTROLLER_H_
#include "mbed.h"

//#define 

//button_name   10進数     2進数
//                                   ps3_data[3]  ps3_data[4]

#define up          0x10    // 1      0000 0000  0000 0001
#define under       0x11    // 2      0000 0000  0000 0010
#define right       0x12    // 4      0000 0000  0000 0100
#define left        0x13    // 8      0000 0000  0000 1000

#define triangle    0x14    // 16     0000 0000  0001 0000
#define cross       0x15    // 32     0000 0000  0010 0000
#define circle      0x16    // 64     0000 0000  0100 0000
#define square      0x00    // 256    0000 0001  0000 0000

#define L1          0x01    // 512    0000 0010  0000 0000
#define L2          0x02    // 1024   0000 0100  0000 0000
#define R1          0x03    // 2048   0000 1000  0000 0000
#define R2          0x04    // 4096   0001 0000  0000 0000

#define START       0x23    // 3      0000 0000  0000 0011
#define SELECT      0x2c    // 12     0000 0000  0000 1100

#define PI 3.141592654  //円周率


class ps3_cont : public Serial
{
    public:
        ps3_cont(PinName TX, PinName RX);
        void getdata(void);
        void printdata(void);
        char getbutton(unsigned char);
        /*joysticを使用する場合はmain文の中でポインタを渡すようにすればいい*/
        void getjoystic_left(unsigned int *,unsigned int *);
        void getjoystic_right(unsigned int *,unsigned int *);
        
        unsigned char ps3data[6];
        
    private:
//        unsigned char ps3data[6];
        unsigned char temp_data;
        int data_buff;
        int data_check;
        
};
#endif