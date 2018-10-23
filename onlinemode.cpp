#include "onlinemode.h"
#include "ui_onlinemode.h"

OnlineMode::OnlineMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OnlineMode),
    onlinePlayerWidget(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | Online");

    connect(ui->soundcloudBtn, &QPushButton::clicked,
            this, [this]{ onServiceBtnClicked("SoundCloud"); });

    connect(ui->spotifyBtn, &QPushButton::clicked,
            this, [this]{ onServiceBtnClicked("Spotify"); });

    connect(ui->youtubeBtn, &QPushButton::clicked,
            this, [this]{ onServiceBtnClicked("YouTube"); });
}

OnlineMode::~OnlineMode()
{
    delete ui;
}

void OnlineMode::onServiceBtnClicked(const QString &service_choosen){
    if(service_choosen == "SoundCloud" || service_choosen == "Spotify" || service_choosen == "YouTube"){
        onlinePlayerWidget = std::make_unique<OnlinePlayer>(service_choosen);
        this->hide();
        onlinePlayerWidget->show();
    }
}
