
/**
 * @brief Pulsador inalámbrico: Emisor
 *
 * @author Bruno Enzo Benítez
 */
#include <Arduino.h>
#include <WifiEspNow.h>

/* mac addres de ambos ESP01*/
// tx_mac_adress = {B4, E6, 2D, 1A, 2B, A5}
// rx_mac_adress = {CC, 50, E3, 07, 2D, 2F}

uint8_t rx_mac_address[6] = {0xB4, 0xE6, 0x2D, 0x1A, 0x2B, 0xA5}; // Dirección del receptor
uint8_t mensaje = 4;											  // Mensaje que se enviará al receptor
#define MENSAJE_LLAVE 3
#define MENSAJE_PULSADOR 4
size_t mensaje_tam = 1;

#define pulsador_modo 2
bool modo = LOW;	//Modo de funcionamiento

bool conexion = false; // Variable para ver el estado de la conexión
bool chequeo_mensaje = false;
WifiEspNowSendStatus estado_actual;

#define pulsador 0

void setup()
{

	// Inicializamos el monitor serie
	Serial.begin(115200);
	Serial.println();
	Serial.println("Hola Unitec");

	// Iniciamos el WIFI
	WiFi.mode(WIFI_STA);
	conexion = WifiEspNow.begin();

	// Añadimos una conexión
	WifiEspNow.addPeer(rx_mac_address, 0, nullptr);

	if (conexion != true)
	{
		Serial.println("No se pudo inicializar ESP NOW");
	}
	else
	{
		Serial.println("Felicidades");
	}

	pinMode(pulsador, INPUT);
	pinMode(pulsador_modo, INPUT);
}

void loop()
{
/*
	//Verificamos en el puerto serie si ya nos conectamos
	if (conexion == true)
	{
		Serial.println("Hola transmisor");
	}
	else
	{
		Serial.println("Sin conexion");
	}
*/
	// Chequeamos si se debe cambiar el modo de funcionamiento
	if (digitalRead(pulsador_modo) == HIGH)
/*	{
		
		modo = !modo;
	}

	// Modo pulsador
	if (modo == HIGH)
	*/
	{
		if (digitalRead(pulsador) == LOW ) // Leemos el estado del pulsador
		{
			mensaje = MENSAJE_PULSADOR;
			WifiEspNow.send(rx_mac_address, (uint8_t *)&mensaje, mensaje_tam);
			Serial.println("Mensaje enviado: ON");
		}
		else
		{
			mensaje = MENSAJE_PULSADOR + 1;
			WifiEspNow.send(rx_mac_address, (uint8_t *)&mensaje, mensaje_tam);
			Serial.println("Mensaje enviado: OFF");
		}
	}
	// Modo SWITCH
	else
	{
		if(digitalRead(pulsador) == LOW) // Leemos el estado del pulsador
			{
				mensaje = MENSAJE_LLAVE;
				Serial.print("Estado del envio:");
				chequeo_mensaje = WifiEspNow.send(rx_mac_address, (uint8_t *) &mensaje, mensaje_tam);
				Serial.println(chequeo_mensaje);
				//digitalWrite(LED_BUILTIN, HIGH);
			}
	}
	// Chequeamos el estado del envío
	// estado_actual = WifiEspNow.getSendStatus();




	/*	Serial.print("ESP Board MAC Address:  ");
		Serial.println(WiFi.macAddress());*/
	delay(500);
}
