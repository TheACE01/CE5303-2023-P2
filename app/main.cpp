// Incluye los encabezados necesarios
#include "kernel.h"
#include <circle/startup.h>

// Función principal del programa
int main (void)
{
        // Crea una instancia del Kernel de Circle
        CKernel Kernel;
        
        // Inicializa el Kernel de Circle. Si la inicialización falla, 
        // se ejecuta "halt" y se devuelve EXIT_HALT.
        if (!Kernel.Initialize ())
        {
                halt();
                return EXIT_HALT;
        }

        // Ejecuta el Kernel de Circle y se obtiene el modo de apagado
        TShutdownMode ShutdownMode = Kernel.Run();

        // Realizar acciones específicas según el modo de apagado
        switch (ShutdownMode)
        {
        // Si el modo de apagado es ShutdownReboot, ejecuta "reboot" y devuelve 
        // EXIT_REBOOT.
        case ShutdownReboot:
                reboot();
                return EXIT_REBOOT;

        // Si el modo de apagado es ShutdownHalt (apagado) o cualquier otro 
        // valor, ejecuta "halt" y devuelve EXIT_HALT.
        case ShutdownHalt:
        default:
                halt();
                return EXIT_HALT;
        }
}
