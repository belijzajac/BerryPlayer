#ifndef LYRICS_H
#define LYRICS_H

#include <QObject>
#include <QWebEngineView>
#include <QCloseEvent>

class Lyrics : public QObject
{
    Q_OBJECT
public:
    explicit Lyrics(QObject *parent = nullptr);
    void showLyrics(const QString &track_info = "nightlovell/joanofarc");

private:
    QWebEngineView *view;
};

#endif // LYRICS_H
