#include "onlinemode.h"
#include "ui_onlinemode.h"

OnlineMode::OnlineMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnlineMode)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | Online");
}

OnlineMode::~OnlineMode()
{
    delete ui;
}
