#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    offline_widget(nullptr),
    online_widget(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(550, 370));

    connect(ui->OfflineButton, &QPushButton::clicked,
            this, &MainWindow::enter_offline);

    connect(ui->OnlineButton, &QPushButton::clicked,
            this, &MainWindow::enter_online);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::enter_offline()
{
    this->hide();

    // Create an offline mode widget and show it
    offline_widget = std::make_unique<OfflineMode>();
    offline_widget->show();
}

void MainWindow::enter_online()
{
    this->hide();

    // Create an online mode widget and show it
    online_widget = std::make_unique<OnlineMode>();
    online_widget->show();
}
