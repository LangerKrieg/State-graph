#include "canvas.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    eventGraph g;
    Canvas w(&g);
    w.show();

    return a.exec();
}
