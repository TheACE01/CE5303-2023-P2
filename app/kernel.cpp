#include "kernel.h"
#include <circle/string.h>
#include <circle/debug.h>
#include <assert.h>

static const char FromKernel[] = "kernel";

CKernel::CKernel (void)
	//Setear la interfaz con el HDMI
:	m_Screen (m_Options.GetWidth (), m_Options.GetHeight ()),	
	// Setear CTimer que utiliza interrupciones (IRQ) para implementar un 
	// tick de sistema de 100 Hz
	m_Timer (&m_Interrupt),
	// Setear el system logging
	m_Logger (m_Options.GetLogLevel ()) 
{
	// Encender el led de la RaspberryPI para verificar la inicialización del 
	// kernel
	m_ActLED.Blink (5);	
}

CKernel::~CKernel (void) {}

boolean CKernel::Initialize (void) {
	boolean bOK = TRUE;

	// Inicializa el componente de pantalla (HDMI)
    if (bOK) {
        bOK = m_Screen.Initialize();
    }

    // Inicializa el componente de interfaz serie (UART) con una velocidad de 
	//! 115200 baudios (esta debe coincidir con la velocudad de UART del Arduino)
    if (bOK) {
        bOK = m_Serial.Initialize(115200);
    }

    // Obtiene el dispositivo de registro (log) especificado en las opciones o 
	// utiliza la pantalla como destino
    if (bOK) {
        // Obtiene el dispositivo de registro (log) a partir de las opciones del kernel
        CDevice *pTarget = m_DeviceNameService.GetDevice(m_Options.GetLogDevice(), FALSE);

        // Si no se encuentra un dispositivo de registro específico, se utiliza 
		// la pantalla como destino
        if (pTarget == 0) {
            pTarget = &m_Screen;
        }

        // Inicializa el componente de registro (log) con el dispositivo objetivo
        bOK = m_Logger.Initialize(pTarget);
    }

    // Inicializa el sistema de interrupciones
    if (bOK){
        bOK = m_Interrupt.Initialize();
    }

    // Inicializa el temporizador del sistema
    if (bOK){
        bOK = m_Timer.Initialize();
    }

	// Devuelve TRUE si todas las inicializaciones se realizaron con éxito
    return bOK; 
}

// Función que recorre el búfer y establece cada byte en 0 (limpia el búfer)
void clearBuffer(void* pBuffer, size_t nSize) {
    char* pChar = static_cast<char*>(pBuffer);
    for (size_t i = 0; i < nSize; i++) {
        *pChar++ = 0;
    }
}

// Función que itera sobre una cadena para retornar su número de caracteres
size_t my_strlen(const char* str) {
    size_t len = 0;
    while (*str != '\0') {
        ++len;
        ++str;
    }
    return len;
}

// Acá se define la lógica de la aplicación como tal
TShutdownMode CKernel::Run(void)
{
    // Registrar y escribir información sobre la hora de compilación
    m_Logger.Write (FromKernel, LogNotice, " ");
	m_Logger.Write (FromKernel, LogNotice, "Instituto Tecnologico de Costa Rica");
	m_Logger.Write (FromKernel, LogNotice, "Proyecto II: Introduccion a los Sistemas Embebidos");
	m_Logger.Write (FromKernel, LogNotice, "Profesor: Luis Chavarria Zamora");
	m_Logger.Write (FromKernel, LogNotice, "Estudiantes: Julian Camacho, Kevin Acevedo, Sebastian Yock");
	m_Logger.Write (FromKernel, LogNotice, " ");

    // Define una cadena de mensaje
    const char* message = "Distancia medida desde el sensor: \n";

    // Calcula la longitud de algunas cadenas fijas
    size_t cursorMovelength = my_strlen("\033[A\033[A");
    size_t clearLength = my_strlen("\033[J");
    size_t messageLength = my_strlen(message);

    bool firstWrite = true;

    while (1) {
		// Definir tamaño del búfer de 64
        const size_t BUFFER_SIZE = 64;
        char buffer[BUFFER_SIZE];
        size_t bytesRead = 0;

        // Limpiar el búfer
        clearBuffer(buffer, BUFFER_SIZE);

        // Lee datos desde el Arduino por medio del protocolo UART al búfer
        if ((bytesRead = m_Serial.Read(buffer, BUFFER_SIZE - 1)) > 0)
        {
            // Establece el terminador nulo en la cadena
            buffer[bytesRead] = '\0';

            if (!firstWrite) {
                // Mueve el cursor en la pantalla
                m_Screen.Write("\033[A\033[A", cursorMovelength);
                // Borra desde la posición del cursor hasta el final de la pantalla
                m_Screen.Write("\033[J", clearLength);
            } else {
                firstWrite = false;
            }

            // Escribe el mensaje y los datos leídos en la pantalla
            m_Screen.Write(message, messageLength);
            m_Screen.Write(buffer, BUFFER_SIZE);
            m_Screen.Write(" cm", 3);
            m_Screen.Write("\n", 1);
        }

        // Uso del timer para el manejo temporal
		// Se espera medio segundo antes de repetir una nueva medición
        m_Timer.MsDelay(500);
    }

    // Devuelve "ShutdownHalt" para indicar que el programa debe apagar el sistema
    return ShutdownHalt;
}
