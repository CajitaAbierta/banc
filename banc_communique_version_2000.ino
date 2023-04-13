/* code pour banc marchant de Marie-Pier Vanchestein novembre 2022
  cours AVM2204 - Systèmes Actifs - prof Alexandre Castonguay - technicien Pierre Gaudet

  1x moteur bidirectionel par patte
  1x switch par patte pour détecter la retractation

  mouvement avant/arrière: moteur 1 et 3
  mouvement de coté: moteur 2 et 4

  "La danse aléatoire"
  Le banc se déplace par en avant (mot1&3 cw)
  Le banc se déplace de coté (gauche?) (mot2&4 cw)
  Le banc se déplace par en arrière (mot1&3 ccw)
  Le banc se déplace de l'autre coté (droite?) (mot2&4 ccw)
*/
#include <ESP32Servo.h>
int SW01 = 33;  // patte 1
int SW02 = 32;  // patte 2
int SW03 = 22;  // patte 3 // was 0 causing issues on downloading code
int SW04 = 4;   // patte 4

int SW01V = 1;  // variable qui contient le status de la swicth, initialisée a 1
int SW02V = 0;
int SW03V = 0;
int SW04V = 0;

int MOT01Cw = 13;   // HIGH active moteur en rotation cw (horraire) doit être LOW sinon
int MOT01Ccw = 25;  // HIGH active moteur en rotation ccw (anti-horraire) doit être LOW sinon
int MOT02Cw = 26;
int MOT02Ccw = 27;
int MOT03Cw = 16;
int MOT03Ccw = 17;
int MOT04Cw = 18;
int MOT04Ccw = 19;
int Aleatoire;

bool directionsonar = true;



Servo myservo;

#define trigPin 15
#define echoPin 5
long duration;
long distance;
int pos = 0;
int servoPin = 14;

bool var = true;

void setup() {

  Serial.begin(115200);  // pour debugging

  pinMode(MOT01Cw, OUTPUT);
  pinMode(MOT01Ccw, OUTPUT);
  pinMode(MOT02Cw, OUTPUT);
  pinMode(MOT02Ccw, OUTPUT);
  pinMode(MOT03Cw, OUTPUT);
  pinMode(MOT03Ccw, OUTPUT);
  pinMode(MOT04Cw, OUTPUT);
  pinMode(MOT04Ccw, OUTPUT);
  pinMode(SW01, INPUT_PULLUP);
  pinMode(SW02, INPUT);
  pinMode(SW03, INPUT);
  pinMode(SW04, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 620, 2420);

  delay (500);
  myservo.write(-90);
}
void sonar() {
  // Envoie de l'onde
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Réception de l'écho
  duration = pulseIn(echoPin, HIGH);

  // Calcul de la distance
  distance = (duration / 2) / 29.1;
  if (distance >= 450 || distance <= 0) {
    Serial.println("Hors plage");
  }
  else {
    Serial.print("distance = ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay (15);
}
void loop() {

  Aleatoire = random(5, 15);

  for (int i = Aleatoire; i > 0; i--) {
    digitalWrite (MOT01Cw, HIGH);
    digitalWrite (MOT03Cw, HIGH);
    delay (500);
    while (SW01V || SW03V)
    { SW01V = digitalRead (SW01);
      delay (10);
      digitalWrite (MOT01Cw, SW01V);
      SW03V = digitalRead (SW03);
      delay (10);
      digitalWrite (MOT03Cw, SW03V);
    }
    digitalWrite (MOT01Cw, LOW);
    digitalWrite (MOT03Cw, LOW);

    delay (2500);
    SW01V = 1;
    SW03V = 1;


    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (165);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(250);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

  }



  Aleatoire = random(5, 15);
  for (int i = Aleatoire; i > 0; i--) {
    digitalWrite (MOT02Cw, HIGH);
    digitalWrite (MOT04Cw, HIGH);
    delay (500);
    while (SW02V || SW04V)
    { SW02V = digitalRead (SW02);
      delay (10);
      digitalWrite (MOT02Cw, SW02V);
      SW04V = digitalRead (SW04);
      delay (10);
      digitalWrite (MOT04Cw, SW04V);
    }
    digitalWrite (MOT02Cw, LOW);
    digitalWrite (MOT04Cw, LOW);

    delay (2500);
    SW02V = 1;
    SW04V = 1;


    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (165);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(250);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

  }

  Aleatoire = random(5, 15);

  for (int i = Aleatoire; i > 0; i--) {
    digitalWrite (MOT01Ccw, HIGH);
    digitalWrite (MOT03Ccw, HIGH);
    delay (500);
    while (SW01V || SW03V)
    { SW01V = digitalRead (SW01);
      delay (10);
      digitalWrite (MOT01Ccw, SW01V);
      SW03V = digitalRead (SW03);
      delay (10);
      digitalWrite (MOT03Ccw, SW03V);
    }
    digitalWrite (MOT01Ccw, LOW);
    digitalWrite (MOT03Ccw, LOW);

    delay (2500);
    SW01V = 1;
    SW03V = 1;


     myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (165);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(250);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

  }

  Aleatoire = random(5, 15);
  for (int i = Aleatoire; i > 0; i--) {
    digitalWrite (MOT02Ccw, HIGH);
    digitalWrite (MOT04Ccw, HIGH);
    delay (500);
    while (SW02V || SW04V)
    { SW02V = digitalRead (SW02);
      delay (10);
      digitalWrite (MOT02Ccw, SW02V);
      SW04V = digitalRead (SW04);
      delay (10);
      digitalWrite (MOT04Ccw, SW04V);
    }
    digitalWrite (MOT02Ccw, LOW);
    digitalWrite (MOT04Ccw, LOW);

    delay (2500);
    SW02V = 1;
    SW04V = 1;

    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }
    myservo.write (165);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (125);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (83);
    delay(250);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

    myservo.write (37);
    delay(350);
    sonar();

    while (distance < 80 && distance > 25) {
      delay (250);
      sonar();
    }

  }
}
