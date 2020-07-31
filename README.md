# Wake On Lan (WOL) nogui

Esta es una aplicación simple para hacer Wake On Lan en un entorno de consola. Esto es apto para servidores de monitorieo de bajo consumo IoT, etc.

## Comandos basicos

### Despertar un dispositivo en mi RED

Para poder despertar un dispositivo en mi RED local, se necesita saber la interfaz de red con la cual me estoy conectando, y tambien la MAC ADDRESS del dispositivo a despertar.

El argumento -m MAC_ADDRES se utiliza para especificar la dirección del equipo destino, mientras que -i IFACE especifica la interfaz con la cual se esta conectada a la RED local. Un ejemplo seria:

    ./WOL_nogui -m 10:20:30:40:50:60 -i eth0

Esto causará que se envie la petición de activación al broadcast de la RED a la cual se está conectada por dicha interfaz.

### Listar las interfaces de RED del equipo

Para poder obtener un listado de las interfaces de RED del equipo se utiliza el argumento -l

    ./WOL_nogui -l

### Ayuda con los comando

Esta parte es para mostrarte que esta opción existe simplemente, ya que si leiste este documento la ayuda no aportará nada.

    ./WOL_nogui -h