#include "application.h"

Application::Application(QObject *parent) : QObject(parent)
{

}

void Application::init(int argc, char **argv)
{
    this->argc = argc;
    this->argv = argv;
}

void Application::exec()
{
    QTextStream salida(stdout);

    QString MAC = "";
    QString iface = "";

    for (int i = 1 ; i < argc ; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            iface = argv[i + 1];
        }

        else if (strcmp(argv[i], "-m") == 0)
        {
            MAC = argv[i + 1];
        }

        else if (strcmp(argv[i], "-l") == 0)
        {
            salida << "------------------ Interfaces de red detectadas ------------------" << endl;

            getInterfaces();

            salida << "------------------------------------------------------------------" << endl;
        }

        else if (strcmp(argv[i], "-h") == 0)
        {
            salida << "-------------------- Comandos para el manejo ---------------------" << endl;

            salida << "Esta es una aplicación simple para hacer Wake On Lan en un entorno de consola. Esto es apto para servidores de monitorieo de bajo consumo IoT, etc." << Qt::endl;

            salida << "\n" << endl;

            salida << "-m MAC_ADDRES se utiliza para especificar la direccion del equipo destino." << endl;

            salida << "-i IFACE especifica la interfaz con la cual se esta conectada a la RED local." << endl;

            salida << "-l hace un listado de las interfaces de red disponible en el equipo." << endl;

            salida << "-h muestra exactamente esta ayuda :)." << endl;

            salida << "\n" << endl;

            salida << "Un ejemplo seria: ./WOL_nogui -m 10:20:30:40:50:60 -i eth0" << endl;

            salida << "------------------------------------------------------------------" << endl;
        }
    }

    if (MAC != "" && iface != "")
    {
        salida << "Despertando " << MAC << " conectado a " << iface << endl;

        sendMagicPackage(MAC, iface);
    }

    exit(0);
}

void Application::getInterfaces()
{
    QTextStream salida(stdout);

    // Se obtienen las interfaces de red
    QList<QNetworkInterface> interfaces(QNetworkInterface::allInterfaces());

    for (QNetworkInterface iface : interfaces)
    {
        salida << iface.name() << endl;
    }
}

void Application::sendMagicPackage(QString MAC, QString iface)
{
    /* Para poder despertar un dispositivo mediante el protocolo Wake On Lan (WOL),
     * se debe enviar una cadena de 6 bytes con el valor de 255 y luego 16 veces
     * la dirección MAC del dispositivo a encender.
     *
     * Quedaria algo asi:
     *
     * FF:FF:FF:FF:FF:FF
     * 10:20:30:50:40:60
     * ................. <- 14 veces restantes la MAC
     * 10:20:30:50:40:60
     *
     * Este paquete se manda mediante UDP al broadcast de la red por el puerto 9.
    */

    QTextStream salida(stdout);

    MAC.remove(":");

    QByteArray data1MAC = QByteArray::fromHex(MAC.toLocal8Bit());
    QByteArray data6FF = QByteArray::fromHex("FFFFFFFFFFFF");

    QByteArray data16MAC;

    for (int i = 0; i < 16; i++)
    {
        data16MAC += data1MAC;
    }

    QByteArray magicPackage = data6FF + data16MAC;

    // Se crea un scoket UDP
    QUdpSocket qudpsocket;

    // Se envia el paquete mágico al broadcast asi todos los equipor en la red lo escucharan
    QNetworkInterface interface = QNetworkInterface::allInterfaces().at(QNetworkInterface::interfaceIndexFromName(iface) - 1);
    QHostAddress address;

    for (QNetworkAddressEntry addressEntrie : interface.addressEntries())
    {
        if (addressEntrie.ip().toString().count(".") == 3)
        {
            address = addressEntrie.ip();
        }
    }

    QString broadcastIP(address.toString().left(address.toString().lastIndexOf('.')).append(".255"));

    salida << "Broadcast " << broadcastIP << endl;

    qudpsocket.writeDatagram(magicPackage, magicPackage.size(), QHostAddress(broadcastIP), 9);
}
