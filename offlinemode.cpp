#include "offlinemode.h"
#include "ui_offlinemode.h"

#include <QSoundEffect>
#include <QFileDialog>
#include <QDebug>

OfflineMode::OfflineMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfflineMode)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | Offline");

    // Connect play button
    connect(ui->playButton, &QPushButton::clicked,
            this, &OfflineMode::play_sth_fun);
}

OfflineMode::~OfflineMode()
{
    delete ui;
}

void OfflineMode::play_sth_fun()
{

}
