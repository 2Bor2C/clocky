clocky
======

Alarm that runs away from you when you try to snooze it off ( "mbed" Microcontroller  - C programming )


"Clocky" The alarm clock that runs away from you !


Overview:

Ever late for your exams because of the alarm was too easy to snooze off. Why not have an alarm clock which runs away when you try to reach for the snooze button!

ECE 4180 : Embedded System Design
mbed: Arm based micro-controller https://mbed.org/
Use the online compiler available on mbed.org for ease in reproducing
Sonar Sensor used to detect an incoming user

List of Hardware Components

Mbed LPC 1768 http://mbed.org/handbook/mbed-NXP-LPC1768
Nokia LCD Display https://www.sparkfun.com/products/11062
Sonar Sensor https://www.sparkfun.com/products/8501
Speaker https://www.sparkfun.com/products/9151
Red Bot kit ( Wheels + Motors + Base) https://www.sparkfun.com/products/12032
H Bridge ICs
Push Buttons - 4 https://www.sparkfun.com/products/97
Connection for Individual Components

Push Buttons Push Buttons http://mbed.org/users/4180_1/notebook/pushbuttons/ The debounce was used to our advantage, all connected to digital in of the mbed. The project required 4 push buttons(PB). One for indicating the clock to reset the timer, One each for incrementing and decrementing the Digit counts while setting or resetting the values for hour and minute.

PB0	PB1	PB2	PB3
p19	p20	p21	p22
Nokia LCD http://mbed.org/cookbook/Nokia-LCD The LCD is required to display the real time; ask the alarm-hour and alarm-minute to be set from the user. LCD uses a SPI interface, but a library is already available and this was used by us.

mosi	sclk	cs	rst
p5	p7	p8	p9
Sonar Sensor The Sonar provides a simple analog output.

VDD	GND	DATA
Vout	gnd	p18
Speaker Speaker plays police siren as the alarm tone. A BJT 2N3904 is used to drive the Speaker.

VDD	GND	DATA
Vout	gnd	p18
H Bridge

fw1	fw2	rev1	rev2	pwm
p10	p13	p11	p14	p24
Both motors driven by a single external 9 volt battery connected to the supply terminals of h-bridge

/media/uploads/sdesai49/20131013_180305.jpg

Import programClocky

The Alarm Clock that runs away from you when you try to switch it off !

Last commit 17 Oct 2013 by  S D

Problems Faced

The Battery and USB current and regulated voltage problem. Once all the peripherals are connected. The LCD display draws a 100+ mA of current. The mbed draws a current of 130 + mAmps in normal mode. The Vout of the mbed is a regulated output providing much less voltage than 3. The H bridges start showing erratic behaviour. Maintaing separated batteries for motor supply and peripherals and mbed power helps and solves the above problem.
The push buttons can be used to call interrupt sub routines provided they are properly debounced. Our main loop was kept running without delays hoping to sample at least once.
Possible Improvements

The real time clock can be kept on running by using the input Vb of the mbed.
Attach IR sensors to detect walls and turn accordingly
Speed Control if the person is too near
Provide a way to set the alarm and the clock using an APP
The Bot can be even made to rotate after a certain period of time, ( just reverse the direction of the motors w.r.t to each other) if the sensor is not being activated and the volume can be increased. The rotating can also serve as taunting the person trying to catch. The added advantage would be if the sonar sensor is kept tilted to and angle with the vertical, it cover a greater scope searching for the incoming person.
Mbed can be used in a power save mode to shut of the unused peripherals. http://mbed.org/handbook/mbed-NXP-LPC1768
