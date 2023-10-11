#!/bin/bash

while true; do
    echo "Seleccione una opción:"
    echo "1. Copiar los archivos para la aplicación bare-metal."
    echo "2. Copir los archivos para la desmostración de u-boot."
    echo "S. Salir."

    read -p "Ingrese su elección: " choice

    case $choice in
        1)
            # Montar la particion de la SD en una particion local
            #sudo mount /dev/sda1 /mnt/sdcard
            sudo mount /dev/mmcblk0 /mnt/sdcard 
            # Eliminar el config.txt actual
            sudo rm /mnt/sdcard/config.txt
            # Copiar el config.txt de la carpeta bare-metal
            sudo cp bare-metal/config.txt /mnt/sdcard
            # Desmontar la partición de la SD
            sudo umount /mnt/sdcard
            ;;
        2)
            # Montar la particion de la SD en una particion local
            #sudo mount /dev/sda1 /mnt/sdcard
            sudo mount /dev/mmcblk0 /mnt/sdcard 
            # Eliminar el config.txt actual
            sudo rm /mnt/sdcard/config.txt 
            # Copiar el config.txt de la carpeta bare-metal
            sudo cp u-boot/config.txt /mnt/sdcard
            # Desmontar la partición de la SD
            sudo umount /mnt/sdcard
            ;;

        [Ss])
            echo "Saliendo del programa."
            exit 0
            ;;
        *)
            echo "Opción no válida. Por favor, seleccione 1, 2 o S."
            ;;
    esac
done
