#include <Joystick.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define MAX_BUTTONS     24
#define BTN_RELEASED    0
#define BTN_PRESSED     1
#define TRI_BUTTON      0
#define CIR_BUTTON      1
#define X_BUTTON        2 //D14
#define SQR_BUTTON      3 //D15
#define X_BUTTON_PIN   14 //D2 used with gyro
#define SQR_BUTTON_PIN 15 //D3 used with gyro
#define L2_BUTTON       4
#define R2_BUTTON       5
#define L1_BUTTON       6
#define R1_BUTTON       7
#define SEL_BUTTON      8
#define STR_BUTTON      9
#define UP_BUTTON      10
#define RIGHT_BUTTON   11
#define DOWN_BUTTON    12
#define LEFT_BUTTON    13

#define L3_BUTTON      14 //A5
#define R3_BUTTON      15 //A2
#define TRI_BUTTON_A   16
#define CIR_BUTTON_A   17
#define X_BUTTON_A     18
#define SQR_BUTTON_A   19
#define UP_BUTTON_A    20
#define RIGHT_BUTTON_A 21
#define DOWN_BUTTON_A  22
#define LEFT_BUTTON_A  23

#define TOGGLE_SW      16

//Joysticks
const int SW_pin_L = A5; // digital pin connected to switch output
const int Y_pin_L = A4; // analog pin connected to Y output
const int X_pin_L = A3; // analog pin connected to X output

const int SW_pin_R = A2; // digital pin connected to switch output
const int Y_pin_R = A1; // analog pin connected to Y output
const int X_pin_R = A0; // analog pin connected to X output


//Gyro variables
Adafruit_MPU6050 mpu;

// Last state of the button
int lastButtonState[MAX_BUTTONS] = {0};

void setup() {
 // Initialize the joysticks
  pinMode(SW_pin_L, INPUT_PULLUP);
  pinMode(Y_pin_L, INPUT);
  pinMode(X_pin_L, INPUT);
  pinMode(SW_pin_R, INPUT_PULLUP);
  pinMode(Y_pin_R, INPUT);
  pinMode(X_pin_R, INPUT);
  
  // Initialize Button Pins
  pinMode(TRI_BUTTON, INPUT_PULLUP);
  pinMode(CIR_BUTTON, INPUT_PULLUP);
  for (int currentButton = L2_BUTTON; currentButton < L3_BUTTON; currentButton++)
  {pinMode(currentButton, INPUT_PULLUP);}
  pinMode(X_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SQR_BUTTON_PIN, INPUT_PULLUP);
  
  //Initialize the Gyro/Joystick switch
  pinMode(TOGGLE_SW, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();

  // Initialize the Gyro
  while (!mpu.begin()) 
  {delay(10);}
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100); 
  //Serial.begin(9600);            
}

void loop() {

  // Read the 14 buttons values
  //Buttons 0-1
  {
    int currentButtonState = !digitalRead(TRI_BUTTON);
    if (currentButtonState != lastButtonState[TRI_BUTTON])
    {
      Joystick.setButton(TRI_BUTTON, currentButtonState);
      lastButtonState[TRI_BUTTON] = currentButtonState;
    }  
  }
  
  {
    int currentButtonState = !digitalRead(CIR_BUTTON);
    if (currentButtonState != lastButtonState[CIR_BUTTON])
    {
      Joystick.setButton(CIR_BUTTON, currentButtonState);
      lastButtonState[CIR_BUTTON] = currentButtonState;
    }  
  }
  //Buttons 4-13
  for (int currentButton = L2_BUTTON; currentButton < L3_BUTTON; currentButton++)
  {
    int currentButtonState = !digitalRead(currentButton);
    if (currentButtonState != lastButtonState[currentButton])
    {
      Joystick.setButton(currentButton, currentButtonState);
      lastButtonState[currentButton] = currentButtonState;
    }
  }
  //Buttons 14-15
  {
    int currentButtonState = !digitalRead(X_BUTTON_PIN);
    if (currentButtonState != lastButtonState[X_BUTTON])
    {
      Joystick.setButton(X_BUTTON, currentButtonState);
      lastButtonState[X_BUTTON] = currentButtonState;
    }  
  }
  
  {
    int currentButtonState = !digitalRead(SQR_BUTTON_PIN);
    if (currentButtonState != lastButtonState[SQR_BUTTON])
    {
      Joystick.setButton(SQR_BUTTON, currentButtonState);
      lastButtonState[SQR_BUTTON] = currentButtonState;
    }  
  }

  //Read joysticks
  RightStickRead();
  LeftStickRead();
 
  //Read gyro
  if(!digitalRead(TOGGLE_SW))
  {ReadGyro();}

  /*Serial.print("Buttons = ");
  for(int j = 0 ;j <24;j++)
  {
   Serial.print(lastButtonState[j]);
  }
  Serial.println("");*/
  delay(50);
}

void RightStickRead(void)
{
  if(!digitalRead(SW_pin_R))    //R3
  {
    lastButtonState[R3_BUTTON] = BTN_PRESSED;
    Joystick.setButton(R3_BUTTON, BTN_PRESSED);
  } 
  else
  {
    lastButtonState[R3_BUTTON] = BTN_RELEASED;
    Joystick.setButton(R3_BUTTON, BTN_RELEASED);
  }
    
  if(analogRead(X_pin_R)>800)             //X
  {
    lastButtonState[X_BUTTON_A] = BTN_PRESSED;
    Joystick.setButton(X_BUTTON_A, lastButtonState[X_BUTTON_A]);
  }
  else if (analogRead(X_pin_R)<20)      //Triangle
  {
    lastButtonState[TRI_BUTTON_A] = BTN_PRESSED;
    Joystick.setButton(TRI_BUTTON_A, lastButtonState[TRI_BUTTON_A]);
  }
  else
  {
   lastButtonState[X_BUTTON_A] = BTN_RELEASED;
   lastButtonState[TRI_BUTTON_A] = BTN_RELEASED;
   Joystick.setButton(X_BUTTON_A, lastButtonState[X_BUTTON_A]);
   Joystick.setButton(TRI_BUTTON_A, lastButtonState[TRI_BUTTON_A]);
  }
    
  if(analogRead(Y_pin_R)>800)           //Square
  {
    lastButtonState[SQR_BUTTON_A] = BTN_PRESSED;
    Joystick.setButton(SQR_BUTTON_A, lastButtonState[SQR_BUTTON_A]);
  }
  else if(analogRead(Y_pin_R)<20)       //Circle
  {
    lastButtonState[CIR_BUTTON_A] = BTN_PRESSED;
    Joystick.setButton(CIR_BUTTON_A, lastButtonState[CIR_BUTTON_A]);
  }
  else
  {
   lastButtonState[SQR_BUTTON_A] = BTN_RELEASED;
   lastButtonState[CIR_BUTTON_A] = BTN_RELEASED;
   Joystick.setButton(SQR_BUTTON_A, lastButtonState[SQR_BUTTON_A]);
   Joystick.setButton(CIR_BUTTON_A, lastButtonState[CIR_BUTTON_A]);
  }
}

void LeftStickRead(void)
{
  if(!digitalRead(SW_pin_L))    //L3
    {
      lastButtonState[L3_BUTTON] = BTN_PRESSED;
      Joystick.setButton(L3_BUTTON, BTN_PRESSED);
    } 
    else
    {
      lastButtonState[L3_BUTTON] = BTN_RELEASED;
      Joystick.setButton(L3_BUTTON, BTN_RELEASED);
    }
    
    if(analogRead(X_pin_L)>800)       //Down
    {
      lastButtonState[DOWN_BUTTON_A] = BTN_PRESSED;
      Joystick.setButton(DOWN_BUTTON_A, lastButtonState[DOWN_BUTTON_A]);
    }
    else if (analogRead(X_pin_L)<20)  //UP
    {
      lastButtonState[UP_BUTTON_A] = BTN_PRESSED;
      Joystick.setButton(UP_BUTTON_A, lastButtonState[UP_BUTTON_A]);
    }
    else
    {
      lastButtonState[DOWN_BUTTON_A] = BTN_RELEASED;
      lastButtonState[UP_BUTTON_A] = BTN_RELEASED;
      Joystick.setButton(DOWN_BUTTON_A, lastButtonState[DOWN_BUTTON_A]);
      Joystick.setButton(UP_BUTTON_A, lastButtonState[UP_BUTTON_A]);
    }
    
    if(analogRead(Y_pin_L)>800)     //Left
    {
      lastButtonState[LEFT_BUTTON_A] = BTN_PRESSED;
      Joystick.setButton(LEFT_BUTTON_A, lastButtonState[LEFT_BUTTON_A]);
    }
    else if(analogRead(Y_pin_L)<20) //Right
    {
      lastButtonState[RIGHT_BUTTON_A] = BTN_PRESSED;
      Joystick.setButton(RIGHT_BUTTON_A, lastButtonState[RIGHT_BUTTON_A]);
    }
    else
    {
      lastButtonState[LEFT_BUTTON_A] = BTN_RELEASED;
      lastButtonState[RIGHT_BUTTON_A] = BTN_RELEASED;
      Joystick.setButton(LEFT_BUTTON_A, lastButtonState[LEFT_BUTTON_A]);
      Joystick.setButton(RIGHT_BUTTON_A, lastButtonState[RIGHT_BUTTON_A]);
    }
    
}

void ReadGyro(void)
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  if(a.acceleration.y>4)          //Right
  {
    if (BTN_PRESSED != lastButtonState[RIGHT_BUTTON])
    {
      lastButtonState[RIGHT_BUTTON] |= BTN_PRESSED;
      Joystick.setButton(RIGHT_BUTTON, lastButtonState[RIGHT_BUTTON]);
    }
  }
  else if(a.acceleration.y<-6)    //Left
  {
    if (BTN_PRESSED != lastButtonState[LEFT_BUTTON])
    {
      lastButtonState[LEFT_BUTTON] |= BTN_PRESSED;
      Joystick.setButton(LEFT_BUTTON, lastButtonState[LEFT_BUTTON]);
    }
  }
  else                          //None
  {
    if (BTN_RELEASED != lastButtonState[LEFT_BUTTON])
    {
      lastButtonState[LEFT_BUTTON] |= BTN_RELEASED;
      Joystick.setButton(LEFT_BUTTON, lastButtonState[LEFT_BUTTON]);
    }
    if (BTN_RELEASED != lastButtonState[RIGHT_BUTTON])
    {
      lastButtonState[RIGHT_BUTTON] |= BTN_RELEASED;
      Joystick.setButton(RIGHT_BUTTON, lastButtonState[RIGHT_BUTTON]);
    }
  }
 /*   
  if(a.acceleration.x>7)          //Down
  {
    if (BTN_PRESSED != lastButtonState[DOWN_BUTTON])
    {
      lastButtonState[DOWN_BUTTON] |= BTN_PRESSED;
      Joystick.setButton(DOWN_BUTTON, lastButtonState[DOWN_BUTTON]);
    }
  }
  else if(a.acceleration.x<-2)      //UP
  {
    if (BTN_PRESSED != lastButtonState[UP_BUTTON])
    {
      lastButtonState[UP_BUTTON] |= BTN_PRESSED;
      Joystick.setButton(UP_BUTTON, lastButtonState[UP_BUTTON]);
    }
  }
  else                          //None
  {
    if (BTN_RELEASED != lastButtonState[UP_BUTTON])
    {
      lastButtonState[UP_BUTTON] |= BTN_RELEASED;
      Joystick.setButton(UP_BUTTON, lastButtonState[UP_BUTTON]);
    }
    if (BTN_RELEASED != lastButtonState[DOWN_BUTTON])
    {
      lastButtonState[DOWN_BUTTON] |= BTN_RELEASED;
      Joystick.setButton(DOWN_BUTTON,  lastButtonState[DOWN_BUTTON]);
    }
  }*/
}
