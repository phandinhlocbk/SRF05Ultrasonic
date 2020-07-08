#include <main.h>
#include <var.h>
#include "lcd.c"
#define SRF05_TRIGGER1   PIN_B1
#define SRF05_TRIGGER2   PIN_B2
#define SRF05_TRIGGER3   PIN_B3
#define SRF05_ECHO      PIN_B0
#define NO_OBJECT       100
#define dmax            90
#INT_EXT
void Ngat_Ngoai(void)
{  
   disable_interrupts(GLOBAL);
   num_pulse+=get_timer1();
   range_ok=1;
   enable_interrupts(GLOBAL);
}
#INT_TIMER1           
void  Ngat_Timer1(void) 
{
   disable_interrupts(GLOBAL);
   num_pulse+=0xffff; 
   enable_interrupts(GLOBAL);
}
///Cam bien trai
void  SRF05_1_StartRange()
{
   while(!range_ok)
   {
         output_high(SRF05_TRIGGER1);
         delay_ms(15);                          // Phai tao 1 xung len co do lon it nhat 10ms
         output_low(SRF05_TRIGGER1);             // Bat dau phep do.
         while(!(input(SRF05_ECHO)));           // Doi cho den khi chan ECHO duoc keo len cao
         set_timer1(0);
         enable_interrupts(GLOBAL);
         delay_ms(50);
   }
}
float32 SRF05_1_GetDistance()
{
   float32 time_us=0,distance=0;
   SRF05_1_StartRange();
   disable_interrupts(GLOBAL);
   if(num_pulse>180000)
   {
      num_pulse=0;
      range_ok=0;
   return NO_OBJECT;
   }
   else
   {
      time_us=num_pulse/6;
      distance=time_us/58;
      num_pulse=0;
      range_ok=0;
   return distance;
   }
}
////Cam bien giua
void  SRF05_2_StartRange()
{
   while(!range_ok)
   {
         output_high(SRF05_TRIGGER2);
         delay_ms(15);                          // Phai tao 1 xung len co do lon it nhat 10ms
         output_low(SRF05_TRIGGER2);             // Bat dau phep do.
         while(!(input(SRF05_ECHO)));           // Doi cho den khi chan ECHO duoc keo len cao
         set_timer1(0);
         enable_interrupts(GLOBAL);
         delay_ms(50);
   }
}
float32 SRF05_2_GetDistance()
{
   float32 time_us=0,distance=0;
   SRF05_2_StartRange();
   disable_interrupts(GLOBAL);
   if(num_pulse>180000)
   {
      num_pulse=0;
      range_ok=0;
   return NO_OBJECT;
   }
   else
   {
      time_us=num_pulse/6;
      distance=time_us/58;
      num_pulse=0;
      range_ok=0;
   return distance;
   }
}
////Cam bien phai
void  SRF05_3_StartRange()
{
   while(!range_ok)
   {
         output_high(SRF05_TRIGGER3);
         delay_ms(15);                          // Phai tao 1 xung len co do lon it nhat 10ms
         output_low(SRF05_TRIGGER3);             // Bat dau phep do.
         while(!(input(SRF05_ECHO)));           // Doi cho den khi chan ECHO duoc keo len cao
         set_timer1(0);
         enable_interrupts(GLOBAL);
         delay_ms(50);
   }
}
float32 SRF05_3_GetDistance()
{
   float32 time_us=0,distance=0;
   SRF05_3_StartRange();
   disable_interrupts(GLOBAL);
   if(num_pulse>180000)
   {
      num_pulse=0;
      range_ok=0;
   return NO_OBJECT;
   }
   else
   {
      time_us=num_pulse/6;
      distance=time_us/58;
      num_pulse=0;
      range_ok=0;
   return distance;
   }
}
///Dieu khien dong co
int x,y;
INT16 PWM;
void Stop()
{
   x=0;
   y=0;
   SET_PWM1_DUTY(x);
   SET_PWM2_DUTY(y);
}
void go_ahead()
{
   x=600;
   y=600;
   SET_PWM1_DUTY(x);
   SET_PWM2_DUTY(y);
}
void turn_right()
{
   
   x=300;
   y=600;
   SET_PWM1_DUTY(x);
   SET_PWM2_DUTY(y);
}
void turn_left()
{
   x=600;
   y=300;
   SET_PWM1_DUTY(x);
   SET_PWM2_DUTY(y);
}

///chuong trinh chinh
void main()
{  
   unsigned char str[20],i=0;
   float32 range_l;
   float32 range_c;
   float32 range_r;
   output_float(SRF05_ECHO);
   output_drive(SRF05_TRIGGER1);
   output_drive(SRF05_TRIGGER2);
   output_drive(SRF05_TRIGGER3);
   port_b_pullups (TRUE);
   ext_int_edge(H_TO_L);                  // ngat canh xuong
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);//F_TIMER1=F_OSC/4
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);            // kich hoat ngat ngoai
   disable_interrupts(GLOBAL);
   while(TRUE)
   {
            range_l=SRF05_1_GetDistance();
            range_c=SRF05_2_GetDistance();
            range_r=SRF05_3_GetDistance();
            if (range_c<dmax)
            {
               if (range_l<=dmax) && (range_l<=range_r)
               {
                  turn_right();
               }
               else
               {
                  if (range_r<=dmax) && (range_r<=range_l)
                  {
                  turn_left();
                  }
               }
            }
            else
            {
               if range_r<=dmax*0.4
               {
               turn_left();
               }
               if range_l<=dmax*0.4
               {
               turn_right();
               }
               if (range_c>dmax)&&(range_l<=dmax)&&range_r<=dmax
               {
               go_ahead();
               }
            }
            
     }
   
}
                
