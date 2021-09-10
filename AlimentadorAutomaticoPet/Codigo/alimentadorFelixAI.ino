//Biblioteca Json
#include <ArduinoJson.h>
//Valor constante pro Json
const int TAMANHO = 100;
//Biblioteca do sensor Ultrasonic
#include <Ultrasonic.h>

//Declaração do sensor Ultrasonic de comida nas portas 0 e 1 
HC_SR04 sensorComida(0, 1);
//Declaração do sensor Ultrasonic de comida nas portas 3 e 4 
HC_SR04 sensorAgua(3, 4);

//Declaração das variaveis de distancia
int distanceComida, distanceAgua;

//Declaração do servo de comida na porta 10
int servoComida = 10;
//Declaração do servo de comida na porta 11
int servoAgua = 11;

void setup() {
	Serial.begin(9600);
	//Setando os pinos de saida
	pinMode(servoComida, OUTPUT);
	pinMode(servoAgua, OUTPUT);
}

void loop() {
	//Iniciando o Json no loop
	StaticJsonDocument<TAMANHO> json;

	//faz a leitura da distância dos sensores e atribui nas variaveis
	distanceComida = sensorComida.distance();
	distanceAgua = sensorAgua.distance();

	//coloca cada servo na posição 0
	servoPos(servoComida, 0);
	servoPos(servoAgua, 0);

	//CONDICIONAL DA COMIDA
	if (distanceComida >= 2 && distanceComida <= 109) {
		servoPos(servoComida, 200);
    		delay(2000);
	} else if (distanceComida >= 110 && distanceComida <= 254) {
    		servoPos(servoComida, 200);
    		delay(4000);
	} else if (distanceComida >= 255 && distanceComida <= 395) {
    		servoPos(servoComida, 200);
    		delay(6000);
  	} else if (distanceComida >= 396 && distanceComida <= 450) {
    		servoPos(servoComida, 200);
    		delay(8000);
  	} else if (distanceComida >= 451) {
    		servoPos(servoComida, 200);
    		delay(10000);
  	}

	/*CONDICIONAL DA AGUA*/
	if (distanceAgua >= 2 && distanceAgua <= 109) {
    		servoPos(servoAgua, 200);
    		delay(2000);
  	} else if (distanceAgua >= 110 && distanceAgua <= 254) {
   	 	servoPos(servoAgua, 200);
	    delay(4000);
  	} else if (distanceAgua >= 255 && distanceAgua <= 395) {
    		servoPos(servoAgua, 200);
   		delay(6000);
  	} else if (distanceAgua >= 396 && distanceAgua <= 450) {
    		servoPos(servoAgua, 200);
		delay(8000);
  	} else if (distanceAgua >= 451) {
    		servoPos(servoAgua, 200);
    		delay(10000);
  	}

	//Envio do objeto Json na porta Serial com chave e valor das distancias de água e comida
	json["distanciaAgua"] = distanceAgua;
	json["distanciaComida"] = distanceComida;
	serializeJson(json, Serial);
}

//Função que seta a posição do servo
void servoPos (int servo, int pos) {
	int microPulso = map(pos, 0, 180, 1000, 2000);
	digitalWrite(servo, HIGH);
	delayMicroseconds(microPulso);
	digitalWrite(servo, LOW);
	delay(10);
}