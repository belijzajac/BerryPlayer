#include "lyrics.h"

Lyrics::Lyrics(QObject *parent) : QObject(parent)
{
    view = new QWebEngineView();

    // Load JavaScript library
    QFile file;
    file.setFileName(":/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();
}

void Lyrics::showLyrics(const QString &track_info)
{
    view->load(QUrl("https://www.azlyrics.com/lyrics/" + track_info + ".html"));

    // Connect a slot that will be executed as soon as the page fully loads
    connect(view->page(), SIGNAL(loadFinished(bool)), this, SLOT(modify_page(bool)));
}

void Lyrics::modify_page(bool ok)
{
    // do stuff with JS:
    view->page()->runJavaScript(jQuery);

    runJScommand(QStringLiteral("qt.jQuery('iframe').remove()")); // Remove iframes
    runJScommand(QStringLiteral("qt.jQuery('script').remove()")); // Remove scripts

    // Remove a whole bunch of divs
    runJScommand(QStringLiteral("qt.jQuery('.ringtone').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.div-share').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.lboard-wrap noprint').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.div-share noprint').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.noprint').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.panel songlist-panel noprint').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.lboard-wrap noprint').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.container text-center').remove()"));
    runJScommand(QStringLiteral("qt.jQuery('.footer-wrap').remove()"));

    view->show();
}

void Lyrics::runJScommand(const QString &str)
{
    view->page()->runJavaScript(str);
}
