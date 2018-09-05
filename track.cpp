#include "track.h"

#include <taglib/taglib.h>
#include <taglib/fileref.h>

Track::Track(const QString &file_location) :
    m_file_location(file_location),
    curr_min(0),
    curr_sec(0)
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
        m_minutes = (audio->length() - m_seconds) / 60;
    }
}
