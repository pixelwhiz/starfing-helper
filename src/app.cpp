#include "app.h"
#include "./ui_app.h"
#include "about.h"

app::app(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::app)
    , about_widget(nullptr)
{
    ui->setupUi(this);
    ui->lineEdit->setMaxLength(1);
}

app::~app()
{
    delete ui;
}

void app::on_pushButton_3_clicked() {
    about_widget = new about(this);
    about_widget->show();
}

