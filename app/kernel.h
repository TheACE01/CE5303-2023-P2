#ifndef _kernel_h
#define _kernel_h

#include <circle/actled.h>
#include <circle/koptions.h>
#include <circle/devicenameservice.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/exceptionhandler.h>
#include <circle/interrupt.h>
#include <circle/timer.h>
#include <circle/logger.h>
#include <circle/types.h>

enum TShutdownMode
{
        ShutdownNone,
        ShutdownHalt,
        ShutdownReboot
};

class CKernel
{
public:
        // Constructor: inicialización de las variables de la clase
        CKernel (void);
        // Destructor     
        ~CKernel (void);    

        // Initialize completa la inicialización de las variables de la clase
        // Retorna TRUE si la inicialización fue exitosa
        boolean Initialize (void);

        /* Run se ejecuta para comenzar la ejecución de la aplicación
         * Cuando devuelve un valor, la aplicación se detiene o el sistema se 
         * reinicia, dependiendo del valor devuelto de tipo TShutdownMode 
         */
        TShutdownMode Run (void);

private:
        // Se utiliza para mostrar la función de los temporizadores del kernel 
        // implementados por la clase CTimer.
        static void TimerHandler (TKernelTimerHandle hTimer,
                                  void *pParam, void *pContext);

private:
        // Variables de instancia de la clase para acceder a los componentes del sistema
        CActLED                 m_ActLED;            // Acceso al LED de actividad
        CKernelOptions          m_Options;           // Opciones del kernel
        CDeviceNameService      m_DeviceNameService; // Mapeo de nombres de dispositivos
        CScreenDevice           m_Screen;            // Acceso a la pantalla HDMI
        CSerialDevice           m_Serial;            // Acceso a la interfaz serie (UART)
        CExceptionHandler       m_ExceptionHandler;  // Manejo de excepciones de abort
        CInterruptSystem        m_Interrupt;         // Manejo de interrupciones
        CTimer                  m_Timer;             // Temporizador del sistema
        CLogger                 m_Logger;            // Facilidad de registro
};

#endif
