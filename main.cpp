#include <QCoreApplication>

#include "application.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Application application;

    application.init(argc, argv);
    application.exec();

    return a.exec();
}
