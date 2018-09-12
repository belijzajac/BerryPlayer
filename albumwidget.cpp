#include "albumwidget.h"
#include "ui_albumwidget.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(itemClickedToOfflinePl(QListWidgetItem*)));
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::displayTrack(int row, const QString &text)
{
    ui->listWidget->addItem(text);
    ui->listWidget->update();
}

void AlbumWidget::itemClickedToOfflinePl(QListWidgetItem *item)
{
    emit itemClickedEmitToOfflinePl(item);
}
