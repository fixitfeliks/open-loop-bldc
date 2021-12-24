//GND 11 10 9  
//PWM 8 7 6
int PWM_A = 8;
int GND_A = 11;
int PWM_B = 7;
int GND_B = 10;
int PWM_C = 6;
int GND_C = 9;

//-- PWM_C, GND_C ,PWM_B, GND_B, PWM_A, GND_A
int comMatrix[][6] = {
  {0, 0, 0, 1, 1, 0},
  {1, 0, 0, 1, 0, 0},
  {1, 0, 0, 0, 0, 1},
  {0, 0, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 0},
  {0, 1, 0, 0, 1, 0},
};

void setup(){ 
  //3.9KHz PWM
  TCCR1B = TCCR1B & B11111000 | B00000010;
  TCCR2B = TCCR2B & B11111000 | B00000010; 
  
  pinMode(PWM_A, OUTPUT);
  pinMode(GND_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(GND_B, OUTPUT);
  pinMode(PWM_C, OUTPUT);
  pinMode(GND_C, OUTPUT);
}

void setDriveRegister(int matrix[][6], int seq, int pwm){
  // PWM_C, GND_C ,PWM_B, GND_B, PWM_A, GND_A
  analogWrite(PWM_C, matrix[seq][0] * 255);
  analogWrite(GND_C, matrix[seq][1] * pwm);
  analogWrite(PWM_B, matrix[seq][2] * 255);
  analogWrite(GND_B, matrix[seq][3] * pwm);
  analogWrite(PWM_A, matrix[seq][4] * 255);
  analogWrite(GND_A, matrix[seq][5] * pwm);
}

void loop(){
  // PWM_C, GND_C ,PWM_B, GND_B, PWM_A, GND_A
  int i = 0;
  int delayTMR = 20;
  int counter = 0;
  while(true){
        setDriveRegister(comMatrix, i, 200);
    i++;
    if(i==6) i =0;
    
    // Start up delay 20 to 15
    counter++;
    delay(delayTMR);
    if((counter == 100 && delayTMR > 15 && delayTMR != 20) || (counter == 1000 && delayTMR == 20)){
      counter = 0;
      delayTMR--;
    }
  }
}
