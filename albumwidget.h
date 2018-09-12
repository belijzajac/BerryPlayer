#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>
#include <QString>

#include <QListWidgetItem>

namespace Ui {
class AlbumWidget;
}

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();

    void displayTrack(int row, const QString &text);

signals:
    void itemClickedEmitToOfflinePl(QListWidgetItem *item);

public slots:
    void itemClickedToOfflinePl(QListWidgetItem *item);

private:
    Ui::AlbumWidget *ui;
};

#endif // ALBUMWIDGET_H
