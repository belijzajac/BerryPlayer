#include "offlinemode.h"
#include "ui_offlinemode.h"

#include <QTimer>
#include <QDir>
#include <QFileDialog>
#include <QDirIterator>
#include <QStandardPaths>

int OfflineMode::play_pause_count = 0;

OfflineMode::OfflineMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfflineMode),
    m_volume(30),
    m_song_index(0),
    m_player(nullptr),
    m_albumList(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("BerryPlayer | Offline");
    this->setFixedSize(QSize(600, 530));

    // Set up default stuff
    setUp();

    // Player
    m_player = std::make_unique<QMediaPlayer>();
    m_player->setVolume(m_volume);

    // Album tracks list widget
    m_albumList = std::make_unique<AlbumWidget>();

    // Connecting media player
    connect(m_player.get(), &QMediaPlayer::positionChanged, this, &OfflineMode::on_positionChanged);
    connect(m_player.get(), &QMediaPlayer::durationChanged, this, &OfflineMode::on_durationChanged);

    // Connect play button
    connect(ui->playButton, &QPushButton::clicked,
            this, &OfflineMode::playPause);

    // Connect next track button
    connect(ui->nextButton, &QPushButton::clicked,
            this, &OfflineMode::nextButtonClicked);

    // Connect previous track button
    connect(ui->previousButton, &QPushButton::clicked,
            this, &OfflineMode::previousButtonClicked);

    // Connect album selection button
    connect(ui->selectAlbumButton, &QPushButton::clicked,
            this, &OfflineMode::selectAlbumLocation);
}

OfflineMode::~OfflineMode()
{
    delete ui;
}

void OfflineMode::selectAlbumLocation()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 QDir::homePath(),
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    // Go through files recursively
    int track_num = 0;
    QDirIterator it(dir, QStringList() << "*.mp3", QDir::Files);
    while(it.hasNext()){
        m_tracks.push_back(std::make_unique<Track>(it.next()));

        // Connect a track with its states
        connect(m_tracks[track_num].get(), &Track::stateChanged,
                this, &OfflineMode::updateState);

        m_albumList->displayTrack(m_tracks.size() - 1, it.next());
        track_num++;
    }
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

// 1st click ==> play, 2nd click ==> stop
void OfflineMode::play_pause_state()
{
    ++play_pause_count;

    if(play_pause_count == 1){
        m_tracks[m_song_index]->setState( Track::State::PLAYING );
    }
    else if(play_pause_count == 2){
        play_pause_count = 0;
        m_tracks[m_song_index]->setState( Track::State::STOPPED );
    }
}

// Play button
void OfflineMode::playPause()
{
    if(m_tracks.size() > 0){
        play_pause_state();
    }
}

void OfflineMode::nextButtonClicked()
{
    if(m_tracks.size() > 0 && m_song_index + 1 < m_tracks.size()){

        ++m_song_index;
        m_tracks[m_song_index]->setState( Track::State::PLAYING );
    }
}

void OfflineMode::previousButtonClicked()
{
    if(m_tracks.size() > 0 && m_song_index - 1 >= 0){

        --m_song_index;
        m_tracks[m_song_index]->setState( Track::State::PLAYING );
    }
}

void OfflineMode::updateState(const Track::State &state)
{
    switch (state) {
        case Track::State::PLAYING:
          ui->playButton->setIcon(QIcon(":/icons/pause.png"));
          playTrack(*m_tracks[m_song_index].get());
          break;

        case Track::State::STOPPED:
            ui->playButton->setIcon(QIcon(":/icons/play.png"));
            m_player->stop();
            break;
    }
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
