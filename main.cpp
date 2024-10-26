#include "app.h"
#include <QApplication>

void initWindow(app &w);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app w;

    initWindow(w);

    w.show();
    return a.exec();
}

void initWindow(app &w) {
    w.setFixedSize(500, 300);
    w.setWindowIcon(QIcon(":/assets/icon.png"));
    w.setWindowTitle("Strafe Helper");

    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

