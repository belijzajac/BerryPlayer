#ifndef OFFLINEMODE_H
#define OFFLINEMODE_H

#include "track.h"

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <memory>
#include <vector>
#include <QListWidgetItem>

namespace Ui {
class OfflineMode;
}

class OfflineMode : public QWidget
{
    Q_OBJECT

public:
    explicit OfflineMode(QWidget *parent = nullptr);
    ~OfflineMode();

    void playTrack(const Track& track);
    void setCurrentTime(int position);
    void setUp();
    void setCoverArt(const Track& track);

    static int play_pause_count;
    void play_pause_state();
    bool isTrackGood(Track &track);

public slots:
    void playPause();
    void selectAlbumLocation();
    void nextButtonClicked();
    void previousButtonClicked();
    void onTrackSingleClicked(QListWidgetItem* item);
    void onBufferChanged(int percentage);

private slots:
    void on_progressSlider_sliderMoved(int position);
    void on_positionChanged(int position);
    void on_durationChanged(int position);
    void updateState(const Track::State &state);

private:
    Ui::OfflineMode *ui;

    // Music player
    int m_volume,     // volume of QMediaPlayer
        m_song_index; // index of a currently playing track
    std::unique_ptr<QMediaPlayer> m_player;

    std::vector<std::unique_ptr<Track>> m_tracks; // Holds tracks
};

#endif // OFFLINEMODE_H
