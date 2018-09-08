#include "track.h"

#include <taglib/taglib.h>
#include <taglib/fileref.h>

#include <QDir>
#include <QProcess>

Track::Track(const QString &file_location, QObject *parent) :
    QObject(parent),
    m_file_location(file_location),
    curr_min(0),
    curr_sec(0),
    m_state(State::STOPPED)
{
    QByteArray ba = file_location.toLatin1();
    const char *_file = ba.data();

    TagLib::FileRef file(_file);
    if(!file.isNull() && file.tag()){
        TagLib::Tag *tag = file.tag();

        // Read basic tags
        m_title = QString::fromStdWString(tag->title().toWString());
        m_artist = QString::fromStdWString(tag->artist().toWString());
        m_album = QString::fromStdWString(tag->album().toWString());

        // Read audio properties
        TagLib::AudioProperties *audio = file.audioProperties();
        m_seconds = audio->length() % 60;
        m_minutes = audio->length() / 60;

        // Try to read cover art
        getCoverArt();
    }
}

// ffmpeg -i input.mp3 -an -vcodec copy cover.jpg
void Track::getCoverArt()
{
    QString dir = QDir::homePath() + "/_berryPlayer/";
    QString file_name = m_artist + m_title + ".jpg";

    // Check if file exists and it's not a directory
    if(!QFileInfo::exists(dir + file_name) && !QFileInfo(dir + file_name).isFile()){

        QString program = "ffmpeg";
        QStringList arguments;
        arguments << "-i" << m_file_location << "-an" << "-vcodec" << "copy" << dir + file_name;

        QProcess *process = new QProcess();
        process->start(program, arguments);
    }

    // Set art cover location
    m_art_location = dir + file_name;
}

void Track::setState(Track::State state)
{
    m_state = state;
    emit stateChanged(m_state);
}
