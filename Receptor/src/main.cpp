/**
 * @brief Pulsador inalámbrico: Receptor
 *
 * @author Bruno Enzo Benítez
 */
#include <Arduino.h>
#include <WifiEspNow.h>

/* mac addres de ambos ESP01*/
// tx_mac_adress = {B4, E6, 2D, 1A, 2B, A5}
// rx_mac_adress = {CC, 50, E3, 07, 2D, 2F}

uint8_t tx_mac_address[6] = {0xB4, 0xE6, 0x2D, 0x1A, 0x2B, 0xA5};
uint8_t mensaje = 3;	//Mensaje que se espera recibir
size_t mensaje_tam = sizeof(mensaje);

bool conexion = false;	// Variable para ver el estado de la conexión WIFI
bool estado_led = false;

/* Función de Callback*/
/* Se ejecuta al recibir un mensaje del emisor*/
void printReceivedMessage(const uint8_t mac[WIFIESPNOW_ALEN], const uint8_t* buf, size_t count, void* arg)
{
	Serial.printf("Message from %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3],
				  mac[4], mac[5]);
	for (int i = 0; i < (int)(count); ++i)
	{
		Serial.print((buf[i]));
	}
	Serial.println();
	
	if (buf[0] == 3)	//Modo llave
	{
		Serial.println("Modo llave\n");
		// Cambia el estado del led
		if (estado_led == false)
		{
			estado_led = true;
		}
		else
		{
			estado_led = false;
		}
	}
	if (buf[0] == 4)
	{
		Serial.println("Modo pulsador: ON");
		estado_led = true;
	}
	if (buf[0] == 5)
	{
		Serial.println("Modo pulsador: OFF");
		estado_led = false;
	}
	digitalWrite(LED_BUILTIN + 1, estado_led);
}

void setup()
{

	// Inicializamos el monitor serie
	Serial.begin(115200);
	Serial.println();
	Serial.println("Hola Unitec");

	WiFi.mode(WIFI_STA);
	WifiEspNow.onReceive(printReceivedMessage, nullptr);
	conexion = WifiEspNow.begin();
	// Añadimos una conexión
	WifiEspNow.addPeer(tx_mac_address, 0, nullptr);

	if (conexion != true)
	{
		Serial.println("No se pudo inicializar ESP NOW");
	}
	else
	{
		Serial.println("Felicidades");
	}
	pinMode(OUTPUT, LED_BUILTIN);
}

void loop()
{
	Serial.println("Hola loop");
	// put your main code here, to run repeatedly:
	if(conexion == true)
	  {
		  Serial.println("Hola receptor");
	  }
	  else
		  {Serial.println("Sin conexion");}

	  delay(1000);
	  
}