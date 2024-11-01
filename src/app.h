#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

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


private:
    Ui::app *ui;
};
#endif // APP_H
