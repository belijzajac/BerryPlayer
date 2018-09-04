#ifndef ONLINEMODE_H
#define ONLINEMODE_H

#include <QWidget>

namespace Ui {
class OnlineMode;
}

class OnlineMode : public QWidget
{
    Q_OBJECT

public:
    explicit OnlineMode(QWidget *parent = nullptr);
    ~OnlineMode();

private:
    Ui::OnlineMode *ui;
};

#endif // ONLINEMODE_H
