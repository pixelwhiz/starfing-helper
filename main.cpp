#include "src/app.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <windows.h>
#include <thread>
#include <atomic>

void initWindow(app &w);
void program(std::atomic<bool> &run, QLineEdit *inputLineEdit);

// Global atomic variable to control the thread execution
std::atomic<bool> runFlag(false);
std::thread runThread;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    app w;

    initWindow(w);

    // Find the start button and line edit for input
    QPushButton* startButton = w.findChild<QPushButton*>("pushButton");
    QLineEdit* inputLineEdit = w.findChild<QLineEdit*>("lineEdit");

    if (startButton) {
        QObject::connect(startButton, &QPushButton::clicked, [&]() {
            if (!runFlag) {
                runFlag = true;
                // Start the thread with the line edit as parameter
                runThread = std::thread(program, std::ref(runFlag), inputLineEdit);
                startButton->setText("Stop");
                startButton->setStyleSheet(QString("background-color: red;"));
                inputLineEdit->setReadOnly(true); // Disable editing
            } else {
                runFlag = false;
                if (runThread.joinable()) {
                    runThread.join();
                }
                startButton->setText("Start");
                startButton->setStyleSheet(QString("background-color: green;"));
                inputLineEdit->setReadOnly(false); // Enable editing
            }
        });
    }

    w.show();
    int result = a.exec();

    // Ensure the thread is stopped on application exit
    runFlag = false;
    if (runThread.joinable()) {
        runThread.join();
    }

    return result;
}

void initWindow(app &w) {
    w.setFixedSize(500, 300);
    w.setWindowIcon(QIcon(":/assets/icon.png"));
    w.setWindowTitle("Strafe Helper");

    // Disable maximize button
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

void program(std::atomic<bool> &run, QLineEdit *inputLineEdit) {
    while (run) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            QString text = inputLineEdit->text();
            if (!text.isEmpty()) {
                // Send the key corresponding to the first character
                char c = text.at(0).toLatin1();
                keybd_event(VkKeyScan(c), 0, 0, 0); // Key down
            }
        } else {
            // Release the key when the mouse button is not pressed
            keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0); // Key up for '0'
        }

        Sleep(10); // Sleep to reduce CPU usage
    }

    // Ensure the key is released when exiting
    keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
}
