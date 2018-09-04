#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "offlinemode.h"
#include "onlinemode.h"

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void enter_offline();
    void enter_online();

private:
    Ui::MainWindow *ui;

    std::unique_ptr<OfflineMode> offline_widget;
    std::unique_ptr<OnlineMode> online_widget;
};

#endif // MAINWINDOW_H
