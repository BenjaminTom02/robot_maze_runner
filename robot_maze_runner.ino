#define ENB 9
#define IN4 7
#define IN3 6
#define IN2 5
#define IN1 4
#define ENA 3 

int trigfront = 10;     
int echofront = 11;     
int trigleft = 13;     
int echoleft = 12;   

long durationfront, durationleft; 
int Ahead = 0, left = 0, distance; 
void setup(){
  delay(1000);
  Serial.begin(9600);
  pinMode(trigfront, OUTPUT);
  pinMode(echofront, INPUT);
  pinMode(trigleft, OUTPUT);
  pinMode(echoleft, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void Forward(){
  analogWrite(ENA, 125);  
  analogWrite(ENB, 120);
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);    
}

void BackUp(){
  analogWrite(ENA, 90);  
  analogWrite(ENB, 105);
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);    
}

void LeftTurn(){
  analogWrite(ENA, 200); 
  analogWrite(ENB, 100);  
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);  
}

void RightTurn(){
  analogWrite(ENA, 130); 
  analogWrite(ENB, 190);  
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);  
}

int readDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void loop(){
  Ahead = readDistance(trigfront, echofront);
  left = readDistance(trigleft, echoleft);
  Serial.print(" front: ");  Serial.print(Ahead) ;  Serial.print(" cm");
  Serial.print(" left: ") ;  Serial.println(left);  Serial.print(" cm");
  if (Ahead < 12 and left  < 12)
  {  
    RightTurn();  delay(90);   
    Serial.print("  TURN RIGHT");
    } 
    else if(Ahead<10 and left >20 ) 
  {  
    LeftTurn();      delay(90);
    Serial.print("  TURN LEFT");
    }
    else if (Ahead>17 and left >15) 
  {  
    LeftTurn();      delay(80);
    Serial.print("  TURN LEFT");
    Forward();
    } 
    else if (Ahead>13 and left<=10)  
  {
    Forward();
    Serial.print("  GO STRAIGHT");
    } 
     else if (Ahead<5)
  {
    BackUp();       delay(100);
    Serial.print("  MOVE BACK");
    RightTurn(); delay(100);
    }
     else 
  { 
    Forward();
    Serial.print("  GO STRAIGHT");
    }
  delay(100);  
}