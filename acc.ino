#define trigPin 2
#define echoPin 4

// DC motor 1
#define IN1 7
#define IN2 8
#define EN12 6 

//DC motor 2
#define IN3 9
#define IN4 10
#define EN34 11

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN12, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN34, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duracion, distancia;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH); //microsegundos
  distancia = (duracion/2)/29.1;

  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia>=50 && distancia<=300){// 2cm - 400cm

    acelerar(255);
  }

  else if (distancia>=10 && distancia<50){  //mapeo

    int dist = map(distancia, 10, 50, 70, 255);

    acelerar(dist);
  } 

  else if (distancia<10 && distancia>1){
    frenar();
  }
  
  else {
    frenar();
  }

  delay(100);

}

void acelerar(int velocidad)
{
   analogWrite(EN12 ,velocidad);
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);

   analogWrite(EN34 ,velocidad);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
}

void frenar()
{
   digitalWrite(EN12, LOW);
   digitalWrite(EN34, LOW);
}
