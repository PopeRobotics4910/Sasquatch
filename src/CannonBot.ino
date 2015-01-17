#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Servo.h>
#include <EEPROM.h>
#include <RobotOpen.h>



/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1
ROEncoder TalonLeft1(0);   // Motor Controller PWM 0
ROEncoder TalonLeft2(1);   // Motor Controller PWM 1
ROEncoder TalonRight1(2);  // Motor Controller PWM 2
ROEncoder TalonRight2(3);  // Motor Controller PWM 3
RODigitalIO sprinklerValve1(0, OUTPUT);  // DIO channel 0, output mode
RODigitalIO sprinklerValve2(1, OUTPUT);  // DIO channel 1, output mode
RODigitalIO sprinklerValve3(2, OUTPUT);  // DIO channel 2, output mode
RODigitalIO sprinklerValve4(3, OUTPUT);  // DIO channel 3, output mode
IPAddress ip (10,49,10,2);


ROPWM leftDrive1(0);
ROPWM leftDrive2(1);
ROPWM rightDrive1(2);
ROPWM rigDrive2(3);


void setup()
{
 /* Set IPAddress */
  RobotOpen.setIP(ip);
  
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // Constantly update PWM values with joystick values
  // Analog sticks feed back values from 0-255
  // 255 - usb1.leftY() to invert a drive
  rightDrive1.write(255-usb1.rightY());
  rightDrive2.write(255-usb1.rightY());
  leftDrive1.write(usb1.leftY());
  leftDrive2.write(usb1.leftY());

  //Logitech Gamepad Button 2
  if (usb1.btnLShoulder())
    sprinklerValve1.on();
  else
    sprinklerValve1.off();

  //Logitech Gamepad Button 3    
  if (usb1.btnRShoulder())
    sprinklerValve2.on();
  else
    sprinklerValve2.off();
  
  //Logitech Gamepad Button 1    
  if (usb1.lTrigger())
    sprinklerValve3.on();
  else
    sprinklerValve3.off();
    
  //Logitech Gamepad Button 4
  if (usb1.rTrigger())
    sprinklerValve4.on();
  else
    sprinklerValve4.off();  
}


/* This is called while the robot is disabled
 * All outputs are automatically disabled (PWM, Solenoid, Digital Outs)
 */
void disabled() {
  // safety code
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RODashboard.publish("Left Talon 1", TalonLeft1.read());
  RODashboard.publish("Left Talon 2", TalonLeft2.read());
  RODashboard.publish("Right Talon 1", TalonRight1.read());
  RODashboard.publish("Right Talon 2", TalonRight2.read());
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
