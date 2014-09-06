//Header/Library Inclusions : Mbed, Speaker, NokiaLCD.   Links Below 
//http://mbed.org/users/4180_1/notebook/using-a-speaker-for-audio-output///
 
#include "mbed.h"
#include "NokiaLCD.h"
#include "Speaker.h"
 
NokiaLCD lcd(p5, p7, p8, p9, NokiaLCD::LCD6610); // mosi, sclk, cs, rst, type
DigitalIn set(p19);         // push button for setting the timer
DigitalIn reset(p20);       // push button for reseting the timer
DigitalIn incr(p21);        // push button for incrementing hour/min set
DigitalIn decr(p22);        // push button for decrementing hour/min set
DigitalIn alarm_stop(p30);      
DigitalOut myled1(LED3);    // LEDs for testing sensor data reception
DigitalOut myled2(LED4);    
AnalogIn dis(p18);      // Analog input for sonar sensor
DigitalOut fw1(p10);    //Forward Motor 1
DigitalOut rev1(p11);   //Reverse Motor 1
DigitalOut fw2(p13);    //Forward Motor 2
DigitalOut rev2(p14);   //Reverse Motor 2
DigitalOut pwm(p24);    //Can be kept as PwmOut if speed control desired
DigitalOut led1(LED1);  
DigitalOut led2(LED2);

int main() {
    set_time(1379615410);          // real time clock set
    Speaker mySpeaker(p26);
    lcd.cls();
    lcd.background(0x0000FF);   // Background of blue color
    int alarm_minute=0;         // integer for storing alarm minutes set   
    int alarm_hour=0;           // integer for storing alarm hour set

    while(1){

            time_t seconds = time(NULL);
            lcd.background(0x0000FF);
            lcd.locate(0,0);
            lcd.printf("Time : ");
            lcd.locate(3,2);
            char buffer[32];                                        // Buffer for storing Time
            strftime(buffer, 32, "%I:%M:%S", localtime(&seconds));  // http://www.cplusplus.com/reference/ctime/strftime/
            lcd.printf("%s", buffer);
            wait(0.10);
            int i = (((buffer[0] - 48)*10) + (buffer[1]-48));       // Converting from Asci to Int
            int j = (((buffer[3] - 48)*10) + (buffer[4]-48));
         
            lcd.locate(0,5);
            lcd.printf("Alarm Set for : ");
            lcd.locate(3,7);
            lcd.printf("%d : %d",alarm_hour,alarm_minute);
             if((i == alarm_hour) && (j == alarm_minute))       // When the real time hour/ min match the alarm set
             {
                while(1)
                {
             
                     mySpeaker.PlayNote(969.0,0.5,0.3);                 // Speaker with police siren playnote( frequency, duration,volume)
                     mySpeaker.PlayNote(800.0,0.5,0.3);                 // http://mbed.org/users/4180_1/notebook/using-a-speaker-for-audio-output/
                    //Motor
                    int per;
                    per=dis*512/3.3;                                    // Sensor Calibrate
                    if(per<8)
                    {
                        led1=1;                                         // for distance up to 8 units
                        led2=0;
                        pwm=1;
                        fw1=0;
                        rev1=1;
                        fw2=0;
                        rev2=1;
                     }
                    
                    else 
                    {
                        led1=1;
                        led2=1;
                        pwm=0;
                    }
                    
                    //motor  code end
                             
                             if(alarm_stop == 1)
                             {
                                 alarm_minute--;
                                 break;
                             }
                }
            }
       if(reset)                                            // When Reset Clicked
       {                
        int count=0;                                        // This counts the number of states for reset and set push button clicks.
       while(count!=3)                                  
       {
            time_t seconds = time(NULL);
            lcd.locate(0,0);
            lcd.printf("Time : ");                                              
            lcd.locate(3,2);
            char buffer[32];
            strftime(buffer, 32, "%I:%M:%S", localtime(&seconds));
            lcd.printf("%s", buffer);
        
        if(count == 0) 
        {                                                   // Alarm hour to be set  state count 0
            lcd.locate(0,8);            
            lcd.printf("Select Hour:" );        
            lcd.locate(3,10);
            lcd.printf("%02d",alarm_hour );        
        }         
       
        if(count == 1)                                                                                  
        {                                                    // Alarm Minute to be Set state count 1               
            lcd.locate(0,8);            
            lcd.printf("Selected Hour:" );                          
            lcd.locate(3,10);
            lcd.printf("%02d",alarm_hour );        
            lcd.locate(0,13);            
            lcd.printf("Select Minute ",alarm_minute );
            lcd.locate(3,15);
            lcd.printf("%02d",alarm_minute );
                    
     } 
  // The if conditions below are for incrementing and decrementing the digits while setting hour and minute and also for 
  // relooping to be start value after  max or min reached
        if(incr && count == 1)                                      
         { 
            alarm_minute++;
            wait(0.25);
         }
        if(incr && count == 0)
        { 
            alarm_hour++;
            wait(0.25);
        }
        if(alarm_hour==25)
         {
            alarm_hour=0;
         }
        if(alarm_minute==60)
        {
            alarm_minute=0;
        }   
        if(decr && count == 1)
         { 
            alarm_minute--;
            wait(0.25);
         }
        if(alarm_minute==(-1))
        {
            alarm_minute=59;
        }
        if(decr && count == 0)
        { 
            alarm_hour--;
            wait(0.25);
        }
        if(alarm_hour==(-1))
        {
            alarm_hour=24;
           }
       // The user clicks set if he is done setting. The below condition checks for that
        if(set)
        {
            count = count + 1;
            wait(0.25);
            lcd.cls();
        }
        // Final alarm confirmation screen. Prompts the user for a final set.
        if(count == 2)
        {
            lcd.locate(0,8);
            lcd.printf("Alarm Set to -> ");
            lcd.locate(3,10);
            lcd.printf("%02d : %02d ",alarm_hour,alarm_minute);
            lcd.locate(0,13);
            lcd.printf("Press Set !");
            }
       }  
     }
        
  }
}
