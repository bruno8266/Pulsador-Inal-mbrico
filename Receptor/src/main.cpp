#include <Arduino.h>
#include <WifiEspNow.h>

//tx_mac_adress = {B4, E6, 2D, 1A, 2B, A5}
//rx_mac_adress = {CC, 50, E3, 07, 2D, 2F}

uint8_t tx_mac_address[6] = {0xB4, 0xE6, 0x2D, 0x1A, 0x2B, 0xA5};
uint8_t mensaje = 3;
size_t mensaje_tam = sizeof(mensaje);

bool conexion = false;

bool estado_led = false;

void
printReceivedMessage(const uint8_t mac[WIFIESPNOW_ALEN], const uint8_t* buf, size_t count,
                     void* arg)
{
  Serial.printf("Message from %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3],
                mac[4], mac[5]);
  for (int i = 0; i < (int) (count); ++i) {
    Serial.print( (buf[i]));
  }
	Serial.println();

	if(buf[0] == 3)
	  	{
			Serial.println("Andando");
			if(estado_led == false)
			{
				estado_led = true;
			}
			else
			{
				estado_led = false;
			}
		}
		digitalWrite(LED_BUILTIN,estado_led);
}

void setup() {

 	 // Inicializamos el monitor serie
	 Serial.begin(115200);
	 Serial.println();
 	 Serial.println("Hola Unitec");
	
	WiFi.mode(WIFI_STA);
  WifiEspNow.onReceive(printReceivedMessage, nullptr);
	conexion = WifiEspNow.begin();
  // Añadimos una conexión
	WifiEspNow.addPeer(tx_mac_address, 0, nullptr);

	if(conexion != true)
	{
		Serial.println("No se pudo inicializar ESP NOW");
	}
	else
	{
		Serial.println("Felicidades");
	}
	pinMode(OUTPUT, LED_BUILTIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(conexion == true)
	{
		Serial.println("Hola receptor");
 	}
	else
		{Serial.println("Sin conexion");}

 	delay(100);
	*/
}