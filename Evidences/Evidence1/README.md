# Evidencia 1: Procesamiento, Ordenamiento y Búsqueda de Logs
Instrucciones del funcionamiento del programa
Proyecto de aplicación de ordenamiento de logs por fecha con 7 algoritmos de ordenamiento.
Igual se puede realizar busqueda por rangos de fecha utilizando busqueda binaria.

# Ejecución
El programa está diseñado para encontrar automáticamente los archivos de datos (`log607-1.txt` y `log607-2.txt`) siempre y cuando se mantenga la estructura de carpetas original (con una carpeta `data/` y los archivos fuente en `src/`).

El codigo esta listo para ejecutarse con compile run o desde la terminar .\ev.exe en windows y su equivalente en linux.

# Formato de fechas
El formato se maneja en ingles, primera letra siempre mayuscula y solo los primeros 3 caracteres. 
Dia unicamente numeros enteros
Hora en formato 24 horas -> HH:MM:SS

# Uso de IA
Durante este proyecto se utilizo la IA como herramienta de apoyo en los siguientes aspectos.
    LO QUE SI SE PERMITIO
Asistencia de debugging para entender errores, como por ejemplo errores complejos de memoria durante el QuickSort.
Asistencia de adaptacion de codigo, la IA fue de gran ayuda para revisar errores durante la reutilizacion de codigo pasado, al tener el archivo abierto facilito e hizo mas rapido el proceso de este proyecto adaptando el codigo.
Entendimiento de conceptos teoricos, la IA me ayudo a comprender de mejor manera la teoria detras del porque algunos algoritmos que teoricamente son mas lentos fue incluso mas rapido que QuickSort con un archivo semi ordenado.

    LO QUE NO SE PERMITIO
Generacion de codigo desde cero, ni que resolviera el proyecto, y tampoco que creara una clase o el menu completamente por su cuenta.
Aceptacion ciega de implementaciones, el codigo que se llego a cambiar o generar automaticamente esta revisado para ver si es eficiente o si de verdad es correcto lo que la IA propuso. Por ejemplo la IA no tenia idea de donde se ubicaban los archivos de logs porque no los tenia abiertos, entonces al generar el codigo para leer archivos este deducio ciegamente que los logs estabam en la misma carpeta que el codigo fuente, lo cual era incorrecto y esto se corrigio para el correcto funcionamiento del programa.

# Video explicativo
https://youtu.be/Zj0SWLWNbJc 