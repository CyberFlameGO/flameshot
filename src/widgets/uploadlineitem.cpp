#include "uploadlineitem.h"
#include "./ui_uploadlineitem.h"
#include "src/widgets/notificationwidget.h"
#include "src/core/flameshotdaemon.h"

#include <QWidget>

UploadLineItem::UploadLineItem(QWidget* parent, QPixmap const& preview, QString const& timestamp, QString const& url)
  : QWidget(parent)
  , ui(new Ui::UploadLineItem)
  , m_notification(new NotificationWidget(parent))
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->imagePreview->setPixmap(preview);
    ui->uploadTimestamp->setText(timestamp);

    connect(ui->copyUrl, &QPushButton::clicked, this, [=]() {
        FlameshotDaemon::copyToClipboard(url);
        m_notification->showMessage(tr("URL copied to clipboard."));
    });


}

UploadLineItem::~UploadLineItem(){
    delete ui;
}
