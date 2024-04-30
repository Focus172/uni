#include "clickgamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClickGameWindow w;
    w.show();
    return a.exec();
}
