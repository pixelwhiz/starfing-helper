#include "app.h"
#include "./ui_app.h"

app::app(QWidget *parent) : QWidget(parent)
    , ui(new Ui::app)
{
    ui->setupUi(this);
    ui->inputKeybind->setMaxLength(1);

    setFixedSize(500, 300);
    setWindowIcon(QIcon(":/assets/icon.png"));
    setWindowTitle("Strafe Helper");
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}

app::~app()
{
    delete ui;
}

