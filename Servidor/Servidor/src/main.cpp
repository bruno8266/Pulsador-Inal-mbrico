#include <Arduino.h>
#include <WifiEspNow.h>

//tx_mac_adress = {B4, E6, 2D, 1A, 2B, A5}
//rx_mac_adress = {CC, 50, E3, 07, 2D, 2F}

uint8_t rx_mac_address[6] = {0xCC, 0x50, 0xE3, 0x07, 0x2D, 0x2F};
uint8_t mensaje = 3;
size_t mensaje_tam = 1;

bool conexion = false;
WifiEspNowSendStatus estado_actual;

#define pulsador 0

void setup() {

 	 // Inicializamos el monitor serie
	 Serial.begin(115200);
	 Serial.println();
 	 Serial.println("Hola Unitec");
	
	WiFi.mode(WIFI_STA);
	
	conexion = WifiEspNow.begin();
	// Añadimos una conexión
	WifiEspNow.addPeer(rx_mac_address, 0, nullptr);

	if(conexion != true)
	{
		Serial.println("No se pudo inicializar ESP NOW");
	}
	else
	{
		Serial.println("Felicidades");
	}

	pinMode(pulsador, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(conexion == true)
	{
		Serial.println("Hola transmisor");
 	}
	else
		{Serial.println("Sin conexion");}

	// Enviamos un paquete al receptor
	if(digitalRead(pulsador) == 1) // Leemos el estado del pulsador
	{
		WifiEspNow.send(rx_mac_address, (uint8_t *) &mensaje, mensaje_tam);
		Serial.println("Mensaje enviado");
	}
	// Chequeamos el estado del envío
	//estado_actual = WifiEspNow.getSendStatus();
	mensaje++;

/*	Serial.print("ESP Board MAC Address:  ");
 	Serial.println(WiFi.macAddress());*/
 	delay(1000);
}

