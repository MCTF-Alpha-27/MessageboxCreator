#include "messageboxcreator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MessageboxCreator w;
    w.show();
    return a.exec();
}
