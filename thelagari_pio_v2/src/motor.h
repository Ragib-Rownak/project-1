#ifndef MOTOR_H
#define MOTOR_H

#include<Arduino.h>

class MOTOR
{
  private:
    int A1, A2, _PWMA, STB, B1, B2, _PWMB,_limit;
    
    int constrainSpeed(int val){
      return constrain(val, 0, _limit == 0 ? 255 : _limit);  // Fallback to 255
    }

  public:
    //constructor/default function/method declaration
    MOTOR(int AIN1, int AIN2, int PWMA, int BIN1, int BIN2, int PWMB, int STBY)
    : A1(AIN1),A2(AIN2),_PWMA(PWMA),B1(BIN1),B2(BIN2),_PWMB(PWMB),STB(STBY)
    
    {

      pinMode(A1,OUTPUT);
      pinMode(A2,OUTPUT);
      pinMode(_PWMA,OUTPUT);
      pinMode(B1,OUTPUT);
      pinMode(B2,OUTPUT);
      pinMode(_PWMB,OUTPUT);
      pinMode(STB,OUTPUT);
      digitalWrite(STB,LOW);
     }
    
    void begin()
    { digitalWrite(STB,HIGH); }
    
    void idle()
    { digitalWrite(STB,LOW); }


    void setConstrain(int limit)
    { _limit = limit; }
    
    void forwardA(int speed)
    {
      digitalWrite(A1,HIGH);
      digitalWrite(A2,LOW);
      analogWrite(_PWMA, constrainSpeed(speed)); // Set constrain on speed. The logic in private class
    }
    
    void reverseA(int speed)
    {
      digitalWrite(A1,LOW);
      digitalWrite(A2,HIGH);
      analogWrite(_PWMA, constrainSpeed(speed)); // Set constrain on speed. The logic in private class
    }
    
    void softBrakeA()
    { analogWrite(_PWMA, 0); }

    void hardBrakeA()
    {
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      analogWrite(_PWMA, 0);
    }

    void forwardB(int speed)
    {
      digitalWrite(B1,LOW);
      digitalWrite(B2,HIGH);
      analogWrite(_PWMB, constrainSpeed(speed)); // Set constrain on speed. The logic in orivate class
    }
    
    void reverseB(int speed)
    {
      digitalWrite(B1,HIGH);
      digitalWrite(B2,LOW);
      analogWrite(_PWMB, constrainSpeed(speed)); // Set constrain on speed. The logic in private class
    }
    
    void softBrakeB()
    { analogWrite(_PWMB, 0); }

    void hardBrakeB()
    {
      digitalWrite(B1,LOW);
      digitalWrite(B2,LOW);
      analogWrite(_PWMB, 0);
    }

};

#endif
