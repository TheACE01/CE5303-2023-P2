Para configurar el toolchain de compilación cruzada, el tipo de arquitectura
de destino y el modelo de la RaspberryPi, usar el siguiente comando:

```
./configure -r 3
```
Esto debe generar un archivo `Config.mk` con el siguiente contenido, que puede
ser modificado según los requisitos:

```
PREFIX = /path/to/your/toolchain/bin/arm-none-eabi-
AARCH = 32
RASPPI = 2
```

Para desarrollar una aplicación, se debe entrar a la carpeta `app/` y crear una 
nueva carpeta con cualquier nombre. En esta, se deben incluir al menos los 
archivos `main.cpp` y un `makefile`. Al terminar de desarrollar la aplicación, 
se realiza la compilación cruzada y la generación de la imagen como `kernel7.img`
con el comando:

```
make
```

Es archivo `.img` es el que se puede incluir en la tarjeta SD junto con los 
archivos de booteo para ser ejecutado en la RaspberryPi.