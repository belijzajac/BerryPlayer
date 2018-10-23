#include "onlineplayer.h"
#include "ui_onlineplayer.h"

OnlinePlayer::OnlinePlayer(const QString &service, QWidget *parent) :
    QWidget(parent),
    m_service(service),
    ui(new Ui::OnlinePlayer)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | " + m_service);

    if(m_service == "SoundCloud")
        ui->webEngineView->load(QUrl("https://soundcloud.com/stream"));
    else if(m_service == "Spotify")
        ui->webEngineView->load(QUrl("https://open.spotify.com"));
    else if(m_service == "YouTube")
        ui->webEngineView->load(QUrl("https://youtube.com"));
}

OnlinePlayer::~OnlinePlayer()
{
    delete ui;
}
