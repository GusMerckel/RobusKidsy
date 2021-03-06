#ifndef ROBUSKIDSY_H
#define _ROBUSKIDSY_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "TCS34725.h"

// -------------------------------------------------------------------------------------------------------------
// Robus Classes
class Robus {
private:
  // Global private constants
  #define PWM_MOTOR_FREQ        30000   // this variable is used to define the time period 
  #define PWM_RESOUTION         8       // this will define the resolution of the signal which is 8 in this case
  #define ARROW_BUFFER_LENGHT   25      // large of buffer for smooth arrow's touch
public:
  // Global public constants
  #define UP    1     
  #define DOWN  2
  #define LEFT  3
  #define RIGHT 4
  #define FRONT 1
  #define BACK  0
  #define ON    1
  #define OFF   0
  
  class buttons {
  private:
    bool new_state = HIGH;
    bool old_state = HIGH;
  public:
    #define PRESSED           2
    #define RELEASED          3
    #define HOLD_RELEASED     0
    #define HOLD_PRESSED      1
    #define BUTTON_A          25
    #define BUTTON_B          26
    uint8_t pin;      
    uint8_t status;
    uint8_t read();
    
  } ButtonA, ButtonB;

  class Led {
  public:
    #define LED1    27
    #define LED2    21
    #define LED3    98
    #define LED4    99
    #define LEDW    16
    uint8_t status;
    uint8_t pin;
    bool Led1 = LOW, :1;
    bool Led2 = LOW, :1;
    bool Led3 = LOW, :1;
    bool Led4 = LOW, :1;
    bool LedW = LOW, :1;
    void set(bool);
    void on();
    void off();
    bool toggle();
      
  } Led1, Led2, Led3, Led4;

  class Arrows {    
  private:
    #define AN_UP             T5     
    #define AN_DOWN           T4
    #define AN_LEFT           T6
    #define AN_RIGHT          T3
    #define ARROW_BUFFER_SIZE 25
    uint8_t buffer[ARROW_BUFFER_SIZE];
    uint8_t thresshold = 30;
    uint8_t readIndex = 0;  // the index of the current reading
    uint16_t total = 0;     // the running total
    uint8_t average = 0;    // the average
    uint8_t untouchCalibrate = 70;
    uint8_t touchCalibrate = 3;
    bool new_state = LOW, :1;
    bool old_state = LOW, :1;
        
  public:
    #define UNTOUCHED         0
    #define TOUCHED           1
    #define HOLD_TOUCHED      2
    #define HOLD_UNTOUCHED    3
    uint8_t pin;
    // variables and function for analog reading
    uint8_t analog;
    uint8_t readAnalog();
    void calibrate(bool state);
    // variables and function for digital reading
    uint8_t digital;
    uint8_t readDigital();
        
  } ArrowUp, ArrowDown, ArrowLeft, ArrowRight;

  class classMove {
  private:
    
  public:
    #define DCM_LEFT_IN1            2
    #define DCM_LEFT_IN2            18
    #define DCM_RIGHT_IN1           4
    #define DCM_RIGHT_IN2           17
    #define PWM_CHANNEL_LEFT_IN1    0
    #define PWM_CHANNEL_LEFT_IN2    1
    #define PWM_CHANNEL_RIGHT_IN1   2
    #define PWM_CHANNEL_RIGHT_IN2   3
    
    uint8_t speed = 0;
    bool direction = FRONT;
    bool status = OFF;
    uint8_t pwm_channel;
    uint8_t dcm_in;
    void MotorLeft(int16_t);
    void MotorRight(int16_t);
    void straightForward(uint8_t);
    void straightBackward(uint8_t);
    void pivotLeft(uint8_t);
    void pivotRight(uint8_t);
    void closedLeft(uint8_t);
    void closedRight(uint8_t);
    void wideLeftFront(uint8_t, float);
    void wideLeftBack(uint8_t, float);
    void wideRightFront(uint8_t, float);
    void wideRightBack(uint8_t, float);
    void stop();

  } Move;

  class Buzzer {
  private:
    uint16_t old_frequency = 0;
  public:
    #define BUZZER  5
    #define PWM_CHANNEL_BUZZER  4
    char names[];
    uint16_t tones[];

    void playTone(int16_t, uint16_t);
    void playTone(int16_t);
    void playTone(int16_t, uint16_t, uint8_t);
    void noTone();
    void playNote(char, uint16_t);
    void r2d2(uint16_t);
  } Buzzer;

  class Neopixel {
  private:
  public:
    #define BLACK       0 
    #define RED         1
    #define GREEN       2
    #define BLUE        3
    #define YELLOW      4
    #define CYAN        6
    #define MAGENTA     5
    #define WHITE       7

    #define RAINBOW     0

    #define NONE        0
    #define ANY_BUTTON  5
    #define ANY_ARROW   6

    void begin();
    void color(uint8_t, uint8_t, uint8_t);
    void color(uint8_t, uint8_t);
    void color(uint8_t);
    void off();
    void fadeIn(uint8_t, uint16_t);
    void fadeOut(uint8_t, uint16_t);
    void fadeInOut(uint8_t, uint16_t, uint16_t, uint16_t);
    void heartBeat(uint8_t);
    void rainbow(uint16_t);
              
  } Neopixel;

  class ColorSensor {
  private:
    double hue, saturation, value;
    uint32_t sum;
    float r, g, b;
    uint16_t hue360;
  public:
    uint8_t color_value;
    String color_string;
    byte gammatable[256];
    uint16_t white, red, green, blue;
    uint8_t read();
    void enable();
    void disable();
    
  } ColorSensor;

  void begin();
};
// End of Robus classes
// ---------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------
// Independent helping Classes
class ColorConverter {
  public:
    static void RgbToHsv(uint8_t r, uint8_t g, uint8_t b, double &hue, double &saturation, double &value);
  
  private:
    static double threeway_max(double a, double b, double c);
    static double threeway_min(double a, double b, double c);
    static double hue2rgb(double p, double q, double t);
};


// End of independent helping classes
// ---------------------------------------------------------------------------------------------------------------

#endif
