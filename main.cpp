#include "src/app.h"
#include <QApplication>
#include <QPushButton>
#include <windows.h>
#include <thread>
#include <atomic>

void initWindow(app &w);
void program(std::atomic<bool> &run);

std::atomic<bool> runFlag(false);
std::thread runThread;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app w;

    initWindow(w);

    QPushButton* startButton = w.findChild<QPushButton*>("pushButton");
    if (startButton) {
        QObject::connect(startButton, &QPushButton::clicked, [&]() {
            if (!runFlag) {
                runFlag = true;
                runThread = std::thread(program, std::ref(runFlag));
                startButton->setText("Stop");
                startButton->setStyleSheet(QString("background-color: red;"));
            } else {
                runFlag = false;
                if (runThread.joinable()) {
                    runThread.join();
                }
                startButton->setText("Start");
                startButton->setStyleSheet(QString("background-color: green;"));
            }
        });
    }

    w.show();

    int result = a.exec();

    runFlag = false;
    if (runThread.joinable()) {
        runThread.join();
    }

    return result;
}

void about() {

}

void initWindow(app &w) {
    w.setFixedSize(500, 300);
    w.setWindowIcon(QIcon(":/assets/icon.png"));
    w.setWindowTitle("Strafe Helper");
    
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void program(std::atomic<bool> &run) {
    while (run) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            keybd_event(0x30, 0, 0, 0);
        } else {
            keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
        }

        Sleep(10);
    }

    keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
}
