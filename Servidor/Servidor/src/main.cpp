/**
 * @brief Pulsador inalámbrico: Emisor
 *
 * @author Bruno Enzo Benítez
 */
#include <Arduino.h>
#include <WifiEspNow.h>

//rx_mac_adress = {B4, E6, 2D, 1A, 2B, A5}
//tx_mac_adress = {CC, 50, E3, 07, 2D, 2F}

uint8_t rx_mac_address[6] = {0xB4, 0xE6, 0x2D, 0x1A, 0x2B, 0xA5};
uint8_t mensaje = 3;
size_t mensaje_tam = 1;

bool conexion = false;
bool chequeo_mensaje = false;
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
	//pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	//digitalWrite(LED_BUILTIN, LOW);
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
		Serial.print("Estado del envio:");
		chequeo_mensaje = WifiEspNow.send(rx_mac_address, (uint8_t *) &mensaje, mensaje_tam);
		Serial.println(chequeo_mensaje);
		//digitalWrite(LED_BUILTIN, HIGH);
	}
	// Chequeamos el estado del envío
	//estado_actual = WifiEspNow.getSendStatus();
	//mensaje++;

	/*
	Serial.print("ESP Board MAC Address:  ");
 	Serial.println(WiFi.macAddress());
	*/
 	delay(1000);
}