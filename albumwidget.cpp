#include "albumwidget.h"
#include "ui_albumwidget.h"

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget)
{
    ui->setupUi(this);
    //ui->listWidget->addItem("hello?");
}

AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::displayTrack(int row, const QString &text)
{
    ui->listWidget->insertItem(row, text);
}
