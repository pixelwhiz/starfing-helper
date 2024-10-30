#ifndef APP_H
#define APP_H

#include <QWidget>

#include "about.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class app;
}
QT_END_NAMESPACE

class app : public QWidget
{
    Q_OBJECT

public:
    explicit app(QWidget *parent = nullptr);
    ~app() override;

    private slots:
    void on_pushButton_3_clicked();

private:
    Ui::app *ui;
    about* about_widget;
};
#endif // APP_H
