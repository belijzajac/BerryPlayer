#ifndef OFFLINEMODE_H
#define OFFLINEMODE_H

#include "track.h"

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

public slots:
    void playPause();

private slots:
    void on_progressSlider_sliderMoved(int position);
    void on_positionChanged(int position);
    void on_durationChanged(int position);

private:
    Ui::OfflineMode *ui;

    int m_volume;
    std::unique_ptr<QMediaPlayer> m_player;

    // Holds tracks
    std::vector<std::unique_ptr<Track>> m_tracks;
};

#endif // OFFLINEMODE_H
