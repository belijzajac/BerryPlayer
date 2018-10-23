#ifndef ONLINEMODE_H
#define ONLINEMODE_H

#include "onlineplayer.h"
#include "memory"

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

public slots:
    void onServiceBtnClicked(const QString &service_choosen);

private:
    Ui::OnlineMode *ui;
    std::unique_ptr<OnlinePlayer> onlinePlayerWidget;
};

#endif // ONLINEMODE_H
