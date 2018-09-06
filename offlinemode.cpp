#include "offlinemode.h"
#include "ui_offlinemode.h"

#include <QTimer>
#include <QDir>
#include <QStandardPaths>

OfflineMode::OfflineMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfflineMode),
    m_volume(30),
    m_player(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | Offline");
    this->setFixedSize(QSize(350, 530));

    // Set up default stuff
    setUp();

    // Player
    m_player = std::make_unique<QMediaPlayer>();
    m_player->setVolume(m_volume);

    // Connecting media player
    connect(m_player.get(), &QMediaPlayer::positionChanged, this, &OfflineMode::on_positionChanged);
    connect(m_player.get(), &QMediaPlayer::durationChanged, this, &OfflineMode::on_durationChanged);

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

// Set ups various stuff
void OfflineMode::setUp()
{
    // Default cover art
    QPixmap px(350, 350);
    px.fill(QColor("gray"));
    ui->artLabel->setPixmap(px);

    // Directory set up
    QDir dir(QDir::homePath() + "/_berryPlayer");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

// Play button
void OfflineMode::playPause()
{
    // testing
    playTrack(*m_tracks[0].get());
}

// When the slider is manually moved
void OfflineMode::on_progressSlider_sliderMoved(int position)
{
    m_player->setPosition(position);
}

// Constantly change the position
void OfflineMode::on_positionChanged(int position)
{
    ui->progressSlider->setValue(position);
    setCurrentTime(position);
}

const QString intToString(int value)
{
    if(value < 10)
        return '0' + QString::number(value);
    else
        return  QString::number(value);
}

// Updates UI value of current time
void OfflineMode::setCurrentTime(int position)
{
    int minutes = (position / 1000) / 60;
    int seconds = (position / 1000) % 60;

    QString min_str, sec_str;

    min_str = intToString(minutes);
    sec_str = intToString(seconds);

    // Update UI value
    ui->currTime->setText(min_str + ':' + sec_str);
}

// Sets the maximum slider value on audio file loaded
void OfflineMode::on_durationChanged(int position)
{
    ui->progressSlider->setMaximum(position);
}

void OfflineMode::playTrack(const Track& track)
{
    // Locate the song
    m_player->setMedia(QUrl::fromLocalFile(track.getFileLocation()));

    // UI
    ui->artistLabel->setText(track.getArtist() + " - " + track.getTitle());
    ui->albumLabel->setText(track.getAlbum());
    ui->totalTime->setText(QString::number(track.getTotalMinutes()) + ":" + QString::number(track.getTotalSeconds()));

    // Set cover art
    setCoverArt(track);

    // Play the song
    m_player->play();
}

void OfflineMode::setCoverArt(const Track& track)
{
    QPixmap px(track.getArtLocation());
    px = px.scaled(QSize(350, 350));
    ui->artLabel->setPixmap(px);
}
