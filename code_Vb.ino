#include <IRremote.h>
#include <Servo.h> //servomotoren besturen 

//Variabelen --------------------------------------------------------------------------------------------------------- 
int choixMode = 0;
int choixModeUltrason = 1;
int choixModeSuiveur = 2;

//Variabelen ivm motoren --------------------------------------------------------------------------------------------------------------- 
const int moteurGaucheA = 5;
const int moteurGaucheR = 6;
const int moteurDroitA = 11;
const int moteurDroitR = 10;

char valSerie;

//Variabele infrarood -------------------------------------------------------------------------------------------------------------- 
const int irPin = 2; //Pin du récepteur IR

//Constantes associées aux boutons de la manette
const long irAvancer = 0x00FF629D;
const long irReculer = 0x00FF02FD;
const long irDroite = 0x00FFC23D;
const long irGauche = 0x00FF22DD;
const long irArreter = 0x00FFa25D;
const long irModeSuiveur = 0x00FF9867;
const long irModeUltrason = 0x00FFE21D;

IRrecv irrecv(irPin); //Objet recevant les signaux à décoder
decode_results irResultat; //Contient le résultat du décodage

//DÉCLARATIONS EN LIEN AVEC LE CAPTEUR DE DISTANCE ET LE SERVOMOTEUR -------------------------------------------------------------------------------- 
const int echoPin = 13; // singaal ontvangen 
const int triggerPin = 12; // signaal sturen

int distanceAvant;
int distanceDroite;
int distanceGauche;
float intervalle;

Servo myservo; //Servo aanmaken 
const int delay_time = 250; //Tijd dat servo nodig heeeft om de aftsanden van elke kant te meten

//DÉCLARATIONS EN LIEN AVEC LES CAPTEURS DE LUMINOSITÉ -------------------------------------------------------------------------------------------- 
const int capteurGauche = 7;
const int capteurCentre = 4;
const int capteurDroit = 3;
bool etatCapteurGauche;
bool etatCapteurCentre;
bool etatCapteurDroit;

//SETUP ---------------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  
  Serial.begin(9600);
  
  //Wielen
  pinMode(moteurGaucheA, OUTPUT);
  pinMode(moteurGaucheR, OUTPUT);
  pinMode(moteurDroitA, OUTPUT);
  pinMode(moteurDroitR, OUTPUT);
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);
  
  //IR decoderen
  irrecv.enableIRIn();
  
  //sensoren voor afstand en servomotoren
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  myservo.attach(9);
  myservo.write(90);
  
  //kleursensoren
  pinMode(capteurGauche, INPUT);
  pinMode(capteurCentre, INPUT);
  pinMode(capteurDroit, INPUT);
}

//Functies motoren ------------------------------------------------------------------------------------------------------------------------
void avancer()
{
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}

void gauche()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}
void droite()
{
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);
}
void reculer()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, HIGH);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, HIGH);
}
void arreter()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);
}
void pivoterGauche()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, HIGH);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}
void pivoterDroite()
{
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, HIGH);
}

//FONCTIONS POUR LE MODE ULTRASON -------------------------------------------------------------------------------------------------------------- 
void mesurerDistanceAvant()
{
  myservo.write(90);
  delay(delay_time);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
  intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
  Serial.println("Distance avant:");
  Serial.println(intervalle);
  distanceAvant = intervalle; //Arrondissement de la distance
}

void mesurerDistanceGauche()
{
  myservo.write(180);
  delay(delay_time);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
  intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
  Serial.println("Distance gauche:");
  Serial.println(intervalle);
  distanceGauche = intervalle;
}

void mesurerDistanceDroite()
{
  myservo.write(0);
  delay(delay_time);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
  intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
  Serial.println("Distance droite:");
  Serial.println(intervalle);
  distanceDroite = intervalle;
}

void modeUltrason()
{
  mesurerDistanceAvant();
  
  if(distanceAvant < 25) //Si la distance avant est de moins de 25cm
  {
    arreter();
    mesurerDistanceGauche();
    delay(delay_time);
    mesurerDistanceDroite();
    delay(delay_time);
    
    if(distanceGauche < 15 && distanceDroite < 15) //Als de afstand links en de afstand
    {
      reculer();
      delay(500);
      pivoterGauche();
      delay(250);
    }
    else if(distanceGauche > distanceDroite) // Als de afstand links > is dan de afstand rechts 
    {
      pivoterGauche();
      delay(250);
    }
    else if(distanceGauche <= distanceDroite) //Als de afstand links kleiner of gelijk aan is dan de afstand rechts 
    {
      pivoterDroite();
      delay(250);
    }
  }
  else //Als de afstand vooraan > 25 cm is 
  {
    avancer();
  }
}

void commandeSerie()
{
  if(Serial.available())
  {
    valSerie = Serial.read();
    
    choixMode = 0;
    
    if(valSerie == 'w')
    avancer();
    else if(valSerie == 'a')
    gauche();
    else if(valSerie == 's')
    reculer();
    else if(valSerie == 'd')
    droite();
    else if(valSerie == 'q')
    arreter();
    else if(valSerie == 'z')
    pivoterGauche();
    else if(valSerie == 'x')
    pivoterDroite();
    else if(valSerie == '1')
    choixMode = choixModeUltrason;
    else if(valSerie == '2')
    choixMode = choixModeSuiveur;
  }
}

void modeSuiveur()
{
  etatCapteurGauche = digitalRead(capteurGauche);
  etatCapteurCentre = digitalRead(capteurCentre);
  etatCapteurDroit = digitalRead(capteurDroit);
  
  if(etatCapteurCentre) // Als de sensor in het midden zwrat scant 
  {
    if ((etatCapteurGauche) && (!etatCapteurDroit)) //Als er zwart links en wit rechts is --> Naar links draaien 
    gauche();
    else if ((!etatCapteurGauche) && (etatCapteurDroit)) //Als er wit links en zwart rechts is --> Naar rechts draaien 
    droite();
    else //Als de conditis hierboven niet volstaan --> rechtdoor verder rijden
    avancer();
  }
  else //Als de sensor in het midden wit scant 
  {
    if ((etatCapteurGauche) && (!etatCapteurDroit)) //Als er zwart links en wit rechts is --> Naar links draaien 
    gauche();
    else if ((!etatCapteurGauche) && (etatCapteurDroit)) //Als er wit links en zwart rechts is --> Naar rechts draaien 
    droite();
    else //Als de condities hierboven niet volstaan --> naar achter rijden
    reculer();
  }
}

void lireInfrarouge()
{
  if (irrecv.decode(&irResultat)) //Receptie IR-signaal
  {
    irrecv.resume(); //Accepteren van nieuwe IR-resultaten
    
    if((irResultat.value < 0xFFF000) && (irResultat.value > 0xFF0000)) //Filtreren slechte IR-detecties 
    {
      choixMode = 0;
      
      if (irResultat.value == irAvancer) //Naar voor rijden
      avancer();
      else if (irResultat.value == irReculer) //Naar achter rijden
      reculer();
      else if (irResultat.value == irDroite) //Naar rechts draaien
      droite();
      else if (irResultat.value == irGauche) //Naar links draaien
      gauche();
      else if (irResultat.value == irArreter) //Stoppen
      arreter();
      else if(irResultat.value == irModeSuiveur)
      choixMode = choixModeSuiveur;
      else if(irResultat.value == irModeUltrason)
      choixMode = choixModeUltrason;
      
      irResultat.value = 0;
    }
  }
}

//loop ---------------------------------------------------------------------------------------------------------------------------------------
void loop()
{
  commandeSerie();
  lireInfrarouge();
  
  if(choixMode == choixModeUltrason)
  {
    modeUltrason();
  }
  else if(choixMode == choixModeSuiveur)
  {
    modeSuiveur();
  }
}
