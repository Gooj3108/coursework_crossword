#include "JapaneseCrossword.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    JapaneseCrossword window;
    window.show();
    return app.exec();
}
