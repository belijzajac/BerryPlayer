#ifndef OFFLINEMODE_H
#define OFFLINEMODE_H

#include <QWidget>

namespace Ui {
class OfflineMode;
}

class OfflineMode : public QWidget
{
    Q_OBJECT

public:
    explicit OfflineMode(QWidget *parent = nullptr);
    ~OfflineMode();

public slots:
    void play_sth_fun();

private:
    Ui::OfflineMode *ui;
};

#endif // OFFLINEMODE_H
