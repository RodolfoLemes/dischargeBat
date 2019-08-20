// Very simple Arduino Lithium-ion battery capacity tester
// from electronicsblog.net

#define buzzer 5
#define rele 2
#define rele2 7
#define LED 13
#define resistor 4.7
#define resistor2 4.7

float capacity = 0, value, voltage, current, time = 0;
float capacity2 = 0, value2, voltage2, current2, time2 = 0;

void measure (void) {

  value = analogRead(0);

  voltage = value / 1024 * 5.0;

  current = voltage / resistor;

  capacity = capacity + current / 3600;

  time++;

  value2= analogRead(5);

  voltage2 = value2 / 1024 * 5.0;

  current2 = voltage2 / resistor2;

  capacity2 = capacity2 + current2 / 3600;

  time2++;

  Serial.print("Tensao= ");
  Serial.print(voltage);

  Serial.print("V Corrente= ");
  Serial.print(current);

  Serial.print("A Capacidade= ");
  Serial.print(capacity);
  Serial.print("Ah ");

  Serial.print("Tempo de Descarga= ");
  Serial.print(time);
  Serial.print("s ");

  Serial.print("\n");

  
  Serial.print("Tensao2= ");
  Serial.print(voltage2);

  Serial.print("V Corrente2= ");
  Serial.print(current2);

  Serial.print("A Capacidade2= ");
  Serial.print(capacity2);
  Serial.print("Ah ");

  Serial.print("Tempo de Descarga2= ");
  Serial.print(time2);
  Serial.print("s ");

  Serial.print("\n");
}

boolean x = false;

ISR(TIMER1_OVF_vect) {
  TCNT1 = 0x0BDC;
  x = !x;

  measure();

}

void setup() {

  pinMode(LED, OUTPUT);

  TIMSK1 = 0x01; // enabled global and timer overflow interrupt;
  TCCR1A = 0x00; // normal operation page 148 (mode0);
  TCNT1 = 0x0BDC; // set initial value to remove time error (16bit counter register)
  TCCR1B = 0x04; // start timer/ set clock

  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  
  Serial.begin(9600);

};

void loop () {

  digitalWrite(LED, x);

  delay(2000);
  if(voltage < 2.7){
    digitalWrite(rele, HIGH);
  }else{
    digitalWrite(rele, LOW);
  }

  if(voltage2 < 2.7){
    //digitalWrite(rele2, HIGH);
    if(voltage2 == 0){
       return;
    }
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }//else{
    //digitalWrite(rele2, LOW);
  //}

 

};
