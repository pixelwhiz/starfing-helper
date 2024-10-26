#ifndef APP_H
#define APP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class app;
}
QT_END_NAMESPACE

class app : public QWidget
{
    Q_OBJECT

public:
    app(QWidget *parent = nullptr);
    ~app();

private:
    Ui::app *ui;
};
#endif // APP_H
