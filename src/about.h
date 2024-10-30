#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class about; }
QT_END_NAMESPACE

class about : public QWidget {
Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about() override;

private:
    Ui::about *ui;
};


#endif //ABOUT_H
