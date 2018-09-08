#ifndef OFFLINEMODE_H
#define OFFLINEMODE_H

#include "track.h"
#include "albumwidget.h"

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <memory>
#include <vector>

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

public slots:
    void playPause();
    void selectAlbumLocation();
    void nextButtonClicked();
    void previousButtonClicked();

private slots:
    void on_progressSlider_sliderMoved(int position);
    void on_positionChanged(int position);
    void on_durationChanged(int position);
    void updateState(const Track::State &state);

private:
    Ui::OfflineMode *ui;

    // Music player
    int m_volume, m_song_index;
    std::unique_ptr<QMediaPlayer> m_player;

    std::vector<std::unique_ptr<Track>> m_tracks; // Holds tracks
    std::unique_ptr<AlbumWidget> m_albumList;     // To display tracks next to the player
};

#endif // OFFLINEMODE_H
