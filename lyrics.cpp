#include "lyrics.h"

Lyrics::Lyrics(QObject *parent) : QObject(parent)
{
    view = new QWebEngineView();
}

void Lyrics::showLyrics(const QString &track_info)
{
    view->load(QUrl("https://www.azlyrics.com/lyrics/" + track_info + ".html"));
    view->show();
}
