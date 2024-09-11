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

uint8_t rx_mac_address[6] = {0xCC, 0x50, 0xE3, 0x07, 0x2D, 0x2F}; // Dirección del receptor
uint8_t mensaje = 3;											  // Mensaje que se enviará al receptor
size_t mensaje_tam = 1;
uint8_t modo = 0;	//Modo de funcionamiento

bool conexion = false; // Variable para ver el estado de la conexión
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
}

void loop()
{
	//Verificamos en el puerto serie si ya nos conectamos
	if (conexion == true)
	{
		Serial.println("Hola transmisor");
	}
	else
	{
		Serial.println("Sin conexion");
	}

	// Cambios de modo de funcionamiento
	if(digitalRead(pulsador_modo) == 1)
	{
		Serial.println("Cambio de modo: ");

		if(modo == 0)
		{
			Serial.println(" Pulsador\n");
		}
		else if(modo == 1)
		{
			Serial.println(" Llave\n");
		}
	}


	// Enviamos un paquete al receptor
	if (digitalRead(pulsador) == 1) // Leemos el estado del pulsador
	{
		WifiEspNow.send(rx_mac_address, (uint8_t *)&mensaje, mensaje_tam);
		Serial.println("Mensaje enviado");
	}
	// Chequeamos el estado del envío
	// estado_actual = WifiEspNow.getSendStatus();
	mensaje++;




	/*	Serial.print("ESP Board MAC Address:  ");
		Serial.println(WiFi.macAddress());*/
	delay(1000);
}

/*
boolean antirebote(int pin) { //funcion para evitar el rebote de los botones
  int contador = 0;
  boolean estado;               //guarda el estado del boton
  boolean estadoAnterior;       //guarda el ultimo estado del boton

  do {
    estado = digitalRead(pin);
    if (estado != estadoAnterior) { //comparamos el estado actual con el anterior
      contador = 0;                 //reiniciamos el contador
      estadoAnterior = estado;
    }
    else {
      contador = contador + 1;      //aumentamos el contador en 1
    }
    delay(1);
  } while (contador < tiempoAntirebote);

  return estado;

}
*/