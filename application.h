#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QByteArray>
#include <QNetworkInterface>
#include <QList>
#include <QFile>
#include <QTextStream>

class Application : public QObject
{
        Q_OBJECT
    public:
        explicit Application(QObject *parent = nullptr);

        void init(int argc, char **argv);
        void exec();

    private:
        int argc = 0;
        char **argv = nullptr;

        void sendMagicPackage(QString MAC, QString iface);
        void getInterfaces();
};

#endif // APPLICATION_H
