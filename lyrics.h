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
    void showLyrics(const QString &track_info);
    void runJScommand(const QString &str);

public slots:
    void modify_page(bool ok);

private:
    QWebEngineView *view;
    QString jQuery;
};

#endif // LYRICS_H
