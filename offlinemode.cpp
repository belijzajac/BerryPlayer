#include "offlinemode.h"
#include "ui_offlinemode.h"

#include <QTimer>

OfflineMode::OfflineMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfflineMode),
    m_volume(30),
    m_player(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | Offline");

    m_player = std::make_unique<QMediaPlayer>();
    m_player->setVolume(m_volume);

    // Add some tracks to play
    m_tracks.push_back(std::make_unique<Track>("/home/tautvydas/Music/input with spaces.mp3"));

    // Connect play button
    connect(ui->playButton, &QPushButton::clicked,
            this, &OfflineMode::playPause);
}

OfflineMode::~OfflineMode()
{
    delete ui;
}

// Play button
void OfflineMode::playPause()
{
    // testing
    playTrack(*m_tracks[0].get());
}

void OfflineMode::playTrack(const Track& track)
{
    // Locate the song
    m_player->setMedia(QUrl::fromLocalFile(track.getFileLocation()));

    // UI
    ui->artistLabel->setText(track.getArtist() + " - " + track.getTitle());
    ui->albumLabel->setText(track.getAlbum());
    ui->totalTime->setText(QString::number(track.getTotalMinutes()) + ":" + QString::number(track.getTotalSeconds()));

    // Play the song
    m_player->play();
}
