#include "uploadlineitem.h"
#include "./ui_uploadlineitem.h"
#include "src/core/flameshotdaemon.h"
#include "src/widgets/notificationwidget.h"

#include <QDesktopServices>
#include <QUrl>
#include <QWidget>

UploadLineItem::UploadLineItem(QWidget* parent,
                               QPixmap const& preview,
                               QString const& timestamp,
                               QString const& url)
  : QWidget(parent)
  , ui(new Ui::UploadLineItem)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->imagePreview->setPixmap(preview);
    ui->uploadTimestamp->setText(timestamp);

    connect(ui->copyUrl, &QPushButton::clicked, this, [=]() {
        FlameshotDaemon::copyToClipboard(url);
    });

    connect(ui->openBrowser, &QPushButton::clicked, this, [=]() {
        QDesktopServices::openUrl(QUrl(url));
    });
}

UploadLineItem::~UploadLineItem()
{
    delete ui;
}
