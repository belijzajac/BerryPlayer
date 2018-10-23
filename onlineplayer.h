#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include <QWidget>
#include <QWebEngineView>

namespace Ui {
class OnlinePlayer;
}

class OnlinePlayer : public QWidget
{
    Q_OBJECT

public:
    OnlinePlayer(const QString &service, QWidget *parent = 0);
    ~OnlinePlayer(); 
private:
    Ui::OnlinePlayer *ui;
    QString m_service;
};

#endif // ONLINEPLAYER_H
