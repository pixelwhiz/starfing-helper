#include "src/app.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <windows.h>
#include <thread>
#include <atomic>

void home(app &w);
void about(app &w);
void program(std::atomic<bool> &run, QLineEdit *inputLineEdit);

std::atomic<bool> runFlag(false);
std::thread runThread;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    app w;

    QPushButton* startButton = w.findChild<QPushButton*>("pushButton");
    QLineEdit* inputLineEdit = w.findChild<QLineEdit*>("inputKeybind");
    QPushButton* homeButton = w.findChild<QPushButton*>("home");
    QPushButton* aboutButton = w.findChild<QPushButton*>("about");

    if (homeButton) {
        QObject::connect(homeButton, &QPushButton::clicked, [&]() {
            home(w);
        });
    }

    if (aboutButton) {
        QObject::connect(aboutButton, &QPushButton::clicked, [&]() {
            about(w);
        });
    }

    if (startButton) {
        QObject::connect(startButton, &QPushButton::clicked, [&]() {
            if (!runFlag) {
                runFlag = true;
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

    runFlag = false;
    if (runThread.joinable()) {
        runThread.join();
    }

    return result;
}

void about(app &w) {
    QPushButton* homeButton = w.findChild<QPushButton*>("home");
    QPushButton* aboutButton = w.findChild<QPushButton*>("about");
    QLabel* textWalkKeybind = w.findChild<QLabel*>("textWalkKeybind");
    QLabel* info = w.findChild<QLabel*>("info");
    QLineEdit* inputKeybind = w.findChild<QLineEdit*>("inputKeybind");
    QPushButton* pushButton = w.findChild<QPushButton*>("pushButton");

    homeButton->setStyleSheet("background-color: transparent;");
    aboutButton->setStyleSheet("background-color: #555;");

    info->setText("Version: 1.0\nAuthor: pixelwhiz\nWebsite: https://github.com/pixelwhiz/strafe-helper");
    textWalkKeybind->hide();
    inputKeybind->hide();
    pushButton->hide();
}

void home(app &w) {
    QPushButton* homeButton = w.findChild<QPushButton*>("home");
    QPushButton* aboutButton = w.findChild<QPushButton*>("about");
    QLabel* textWalkKeybind = w.findChild<QLabel*>("textWalkKeybind");
    QLabel* info = w.findChild<QLabel*>("info");
    QLineEdit* inputKeybind = w.findChild<QLineEdit*>("inputKeybind");
    QPushButton* pushButton = w.findChild<QPushButton*>("pushButton");

    homeButton->setStyleSheet("background-color: #555;");
    aboutButton->setStyleSheet("background-color: transparent;");

    info->setText("Please follow these steps:\n1. Launch Valorant\n2. Open Settings > Controls > Actions\n3. Add new walk keybinds, example: 0\n4. Set the 'Walk Keybind' below, same as step 3,\nnexample: 0\n4. Done, Start the program");
    textWalkKeybind->show();
    inputKeybind->show();
    pushButton->show();
}

void program(std::atomic<bool> &run, QLineEdit *inputLineEdit) {
    while (run) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            QString text = inputLineEdit->text();
            if (!text.isEmpty()) {
                char c = text.at(0).toLatin1();
                keybd_event(VkKeyScan(c), 0, 0, 0); // Key down
            }
        } else {
            keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0); // Key up for '0'
        }

        Sleep(10);
    }

    keybd_event(0x30, 0, KEYEVENTF_KEYUP, 0);
}
