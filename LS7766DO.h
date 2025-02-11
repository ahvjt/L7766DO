/*
   LS7366.h - Library for using the LSI/CSI LS7366 quadrature encoder counter with serial interface
   Created by David Jabon
   License: GPL 3.0
  The count values that are returned are always unsigned longs (32 bit integers) .
*/

#ifndef LS7766DO_h
#define LS7766DO_h

#include "Arduino.h"
#include <SPI.h>

/* MDR0 configuration data
   The configutation byte is formed by choosing one element from each group.
*/

//Count modes 
#define NQUAD 0x00                //non-quadrature mode 
#define QUADRX1 0x01              //X1 quadrature mode 
#define QUADRX2 0x02             //X2 quadrature mode 
#define QUADRX4 0x03              //X4 quadrature mode 

//Running modes
#define FREE_RUN 0x00 
#define SINGE_CYCLE 0x04 
#define RANGE_LIMIT 0x08 
#define MODULO_N 0x0C

//Index modes 
#define DISABLE_INDX 0x00       //index_disabled 
#define INDX_LOADC 0x10         //index_load_CNTR
#define INDX_RESETC 0x20        //index_rest_CNTR 
#define INDX_LOADO 0x30         //index_load_OL 
//
#define ASYNCH_INDX 0x00        //asynchronous index 
#define SYNCH_INDX 0x40         //synchronous index 

//Clock filter modes 
#define FILTER_1 0x00           //filter clock frequncy division factor 1 
#define FILTER_2 0x80           //filter clock frequncy division factor 2 


/* MDR1 configuration data
   The configutation byte is formed by choosing one element from each group.
*/

//Flag modes 
#define FLGa_Carry 0x01      //Enable Carry on FLGa
#define FLGa_Borrow 0x02     //Enable Borrow on FLGa
#define FLGa_Compare 0x04    //Enable Compare on FLGa
#define FLGa_Index 0x08      //Enable Index on FLGa
#define FLGb_UpDown 0x10     //Set Up/Down count direction
#define FLGa_Inst 0x80       //FLGa non-latched and instantaneous

//Enable or disable counter  
#define EN_CNTR 0x00        //counting enabled 
#define DIS_CNTR 0x04       //counting disabled 
 
//1 to 4 bytes data-width 
#define BYTE_4 0x00         //four byte mode           
#define BYTE_3 0x01         //three byte mode           
#define BYTE_2 0x02         //two byte mode           
#define BYTE_1 0x03         //one byte mode


/* LS7366R op-code list */ 
#define CLR_CNTR 0x01       //Reset counter    
#define LOAD_CNTR 0x02      //Load counter
#define LOAD_ODR 0x04       //Load ODR register
#define CLR_STR 0x08        //Clear STR
#define MASTER_RESET 0x10   //Master reset ALL registers
#define CLR_MDR0 0x10
#define CLR_MDR1 0x10
#define SET_SIGN_BIT 0x20   //Set sign bit (STR bit0)
#define SET_RESET_BIT 0x40  //Reset sign bit (STR bit0) 
#define READ_MDR0 0x48 
#define READ_MDR1 0x50 
#define READ_CNTR   0x60 
#define READ_OTR    0x68 
#define READ_STR    0x70 
#define WRITE_MDR1 0x90 
#define WRITE_MDR0 0x88 
#define WRITE_DTR   0x98 
#define LOAD_CNTR   0xE0   
#define LOAD_OTR    0xE8    


class LS7766DO
{
  public:
	LS7766DO(byte CS_pin);
	void clear_mode_register_0();
	void clear_mode_register_1();
	void clear_counter();
	void clear_status_register();
	byte read_mode_register_0();
	byte read_mode_register_1();
	unsigned long read_counter();
	unsigned long read_OTR();
	byte read_status_register();
	void write_mode_register_0(byte val);
	void write_mode_register_1(byte val);
	void write_data_register(unsigned long val);
	void load_counter();
	void load_OTR();
  private:
	byte CS_pin;
	byte datawidth;
	long left_extend_MSB(long val);
};

#endif
