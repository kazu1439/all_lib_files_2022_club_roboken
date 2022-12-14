/**********************************************************************
	File	lpf.h
	Ver		1.0.1
	Date	1.0.0	2017/9/28
			1.0.1	2017/10/15	setTimeConstとsetInputPrevを追加
	Auther	Maegaki Noriyoshi
	note	ローパスフィルタを双一次変換して離散化した．
**********************************************************************/

/**********************************************************************
 Includes guard
**********************************************************************/
#ifndef __LPF_H__
#define __LPF_H__

/**********************************************************************
 Includes
**********************************************************************/
#include "mbed.h"

/**********************************************************************
 Low-pass filter class
**********************************************************************/
class LPF{
	public:
		LPF(){}
		LPF(float t_const_sec, float ctrl_period_sec);
		
		void set(float t_const_sec, float ctrl_period_sec);	// 時定数とサンプル周期を設定する関数
		void setTimeConst(float t_const_sec);				// 時定数のみを再設定する関数．変数の初期化はしない
		void setInputPrev(float input_prev);				// ローパスフィルタの初期値と前回の出力値を（0以外にするの場合）設定する関数．
		void reset();
		float filter(float input);
		
	private:
		float t_const_sec_;
		float ctrl_period_sec_;	
		float output_;
		float input_prev_;
		
		float coeff_a_;			// フィルタをかけるときに使用する係数a
		float coeff_b_;			// フィルタをかけるときに使用する係数b
	
};

#endif

/**********************************************************************
 Usage example
**********************************************************************/



