#ifndef TRACK_H
#define TRACK_H

#include <QObject>

#include <QString>
#include <QImage>

class Track : public QObject
{
    Q_OBJECT
public:
    enum class State {
        STOPPED,
        PLAYING
    };

    Track(const QString &file_location, QObject *parent = 0);

    const QString getFileLocation() const { return m_file_location; }
    const QString getArtLocation() const { return m_art_location; }
    const QString getTitle() const { return m_title; }
    const QString getArtist() const { return m_artist; }
    const QString getAlbum() const { return m_album; }
    int getTotalMinutes() const { return m_minutes; }
    int getTotalSeconds() const { return m_seconds; }
    void getCoverArt();

    State getState() const { return m_state; }

signals:
    void stateChanged(State state);

public:
    void setState(State state);

private:
    // Basic information about track
    QString m_file_location, m_art_location;
    QString m_title, m_artist, m_album;
    int m_minutes, m_seconds;
    int curr_min, curr_sec;

    State m_state;
};

#endif // TRACK_H
