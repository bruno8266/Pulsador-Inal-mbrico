
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
#define MENSAJE_PULSADOR_OFF 4
#define MENSAJE_PULSADOR_ON 5

size_t mensaje_tam = 1;
#define pulsador 0
#define pulsador_modo 2		//OJO: hay que usar resistencia de pull-up con este pin 
bool modo = HIGH;	//Modo de funcionamiento
bool lectura_modo;
bool lectura_modo_anterior;
bool lectura_pulsador;
bool lectura_pulsador_anterior;

bool conexion = false; // Variable para ver el estado de la conexión
bool chequeo_mensaje = false;
WifiEspNowSendStatus estado_actual;

#define maximo_tiempo_rebote 20

//Funciones
bool lectura_antirebote(int pin);


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
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
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
	lectura_modo = lectura_antirebote(pulsador_modo);
	// Chequeamos si se debe cambiar el modo de funcionamiento
	if (lectura_modo == LOW && lectura_modo_anterior != LOW)	// Porque GPIO2 tiene que tener resistencia de pull-up
	{
		modo = !modo;
		digitalWrite(LED_BUILTIN, modo);
	}	

	lectura_pulsador = lectura_antirebote(pulsador);
	// Chequeamos si se debe cambiar el modo de funcionamiento
	if (modo == HIGH)
	{
		if (lectura_pulsador == LOW && lectura_pulsador_anterior !=LOW) // Leemos el estado del pulsador
		{
			mensaje = MENSAJE_PULSADOR_ON;
			WifiEspNow.send(rx_mac_address, (uint8_t *)&mensaje, mensaje_tam);
			Serial.println("Mensaje enviado: ON");
		}
		else if (lectura_pulsador == HIGH && lectura_pulsador_anterior != HIGH)
		{
			mensaje = MENSAJE_PULSADOR_OFF;
			WifiEspNow.send(rx_mac_address, (uint8_t *)&mensaje, mensaje_tam);
			Serial.println("Mensaje enviado: OFF");
		}
	}
	// Modo SWITCH
	else
	{
		if(lectura_pulsador == LOW && lectura_pulsador_anterior != LOW) // Leemos el estado del pulsador
			{
				mensaje = MENSAJE_LLAVE;
				Serial.print("Estado del envio:");
				chequeo_mensaje = WifiEspNow.send(rx_mac_address, (uint8_t *) &mensaje, mensaje_tam);
				Serial.println(chequeo_mensaje);
				//digitalWrite(LED_BUILTIN, HIGH);
			}
	}
	lectura_modo_anterior = lectura_modo;
	lectura_pulsador_anterior = lectura_pulsador;
	// Chequeamos el estado del envío
	// estado_actual = WifiEspNow.getSendStatus();

	/*	Serial.print("ESP Board MAC Address:  ");
		Serial.println(WiFi.macAddress());*/
}


bool lectura_antirebote(int pin) { //funcion para evitar el rebote de los botones
  int contador = 0;
  boolean estado;               //guarda el estado del boton
  boolean estadoAnterior = HIGH;       //guarda el ultimo estado del boton

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
  } while (contador < maximo_tiempo_rebote);

  return estado;

}

