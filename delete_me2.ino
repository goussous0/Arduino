int  red_led_pin  =2;    
int green_led_pin  =4;   
int tempPin =A0 ; 
int gasAPin =A1;
int echo =6;    
int trigger =7;    
int ldrPin  =A5;   
int modePin  =3;    
int resetPin  =5;   
int mode =0;
float temp = 0.0;
float smoke = 0.0;
float distance =0.0;

void setup() {
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(modePin,INPUT);
  pinMode(tempPin, INPUT);
  
  
  Serial.begin(9600);
}

void loop() {

  
  while (mode_button() == 1 )
  {
    mode +=1;
    if (mode == 4)
    {
      mode = 0;
    }
  }

  Serial.print("mode: ");Serial.println(mode);

  
    if (mode == 1)
    {
      digitalWrite(green_led_pin,HIGH);
      if ((temperture() >= 50 && digitalRead(resetPin)!= 1) || (digitalRead(resetPin)!= 1 && gasLevel() > 500))
      {
        // turn the buzzer on 
        digitalWrite(red_led_pin,HIGH);
        delay(500);
        
      }
     
      Serial.print("temperture  ");
      Serial.print(temperture());
      Serial.println(" C");
      Serial.print("smoke  ");
      Serial.println(gasLevel()); 
      delay(1000);
   
    }
    else if (mode == 2)
    {
      distance = 0.01723 * howFar();
      Serial.print("distance  ");Serial.println(distance);
      if (distance <= 80 && distance > 50)  
      {
        digitalWrite(red_led_pin,HIGH);
        delay(500);
        digitalWrite(red_led_pin,LOW);
        delay(500);

      }
      else if   (distance  <= 50 && distance  > 20)
      {
        digitalWrite(red_led_pin,HIGH);
        delay(250);
        digitalWrite(red_led_pin,LOW);
        delay(250);

      }
      else if (distance <= 20 )
      {
        digitalWrite(red_led_pin,HIGH);
        delay(50);
        digitalWrite(red_led_pin,LOW);
        delay(50);

      }
     
    }
    else if (mode == 3 )
    {
      Serial.print("room light ");
      Serial.println(lightValue());
   
    }
    else
    {

      digitalWrite(green_led_pin,LOW);
      digitalWrite(red_led_pin,LOW);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
     
    }
  
  
  delay(1000);
  
}

float temperture()
{
  temp = analogRead(tempPin);
  temp = temp /1024.0;
  temp = temp*5000;
  temp = temp/10;
  return temp;
}

int mode_button()
{
  return digitalRead(modePin);
}

int reset_button()
{
  return digitalRead(resetPin);
}

float gasLevel()
{
  return analogRead(gasAPin);
}

float howFar()
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  return pulseIn(echo,HIGH);
}

float lightValue()
{
  return analogRead(ldrPin);
}
