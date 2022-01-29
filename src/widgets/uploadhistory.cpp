#include "uploadhistory.h"
#include "uploadlineitem.h"
#include "./ui_uploadhistory.h"

#include "src/tools/imgupload/imguploadermanager.h"
#include "src/utils/confighandler.h"
#include "src/utils/globalvalues.h"
#include "src/utils/history.h"
#include <QDateTime>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFileInfo>
#include <QIcon>
#include <QMessageBox>
#include <QPixmap>
#include <QUrl>


void scaleThumbnail(QPixmap &pixmap){
    if (pixmap.height() / HISTORYPIXMAP_MAX_PREVIEW_HEIGHT >=
        pixmap.width() / HISTORYPIXMAP_MAX_PREVIEW_WIDTH) {
        pixmap = pixmap.scaledToHeight(HISTORYPIXMAP_MAX_PREVIEW_HEIGHT,
                                       Qt::SmoothTransformation);
    } else {
        pixmap = pixmap.scaledToWidth(HISTORYPIXMAP_MAX_PREVIEW_WIDTH,
                                      Qt::SmoothTransformation);
    }
}


UploadHistory::UploadHistory(QWidget* parent)
  : QWidget(parent)
  , ui(new Ui::UploadHistory)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.5);
}
UploadHistory::~UploadHistory()
{
    delete ui;
}

void UploadHistory::clearHistoryLayout(QLayout* layout)
{
    QLayoutItem* child;
    while (layout->count() != 0) {
        child = layout->takeAt(0);
        if (child->layout() != 0) {
            clearHistoryLayout(child->layout());
        } else if (child->widget() != 0) {
            delete child->widget();
        }
        delete child;
    }
}

void UploadHistory::loadHistory()
{
    // clear old history if exists
    clearHistoryLayout(ui->historyContainer);

    // read history files
    History history = History();
    QList<QString> historyFiles = history.history();

    if (historyFiles.isEmpty()) {
        setEmptyMessage();
    } else {
        // generate history list
        foreach (QString fileName, historyFiles) {
            addLine(history.path(), fileName);
        }
    }
}


void UploadHistory::setEmptyMessage()
{
    QPushButton* buttonEmpty = new QPushButton;
    buttonEmpty->setText(tr("Screenshots history is empty"));
    buttonEmpty->setMinimumSize(1, HISTORYPIXMAP_MAX_PREVIEW_HEIGHT);
    connect(buttonEmpty, &QPushButton::clicked, this, [=]() { this->close(); });
    ui->historyContainer->addWidget(buttonEmpty);
}

void UploadHistory::addLine(const QString& path, const QString& fileName)
{
    QString fullFileName = path + fileName;

    History history;
    HISTORY_FILE_NAME unpackFileName = history.unpackFileName(fileName);

    QString url = ImgUploaderManager(this).url() + unpackFileName.file;

    // load pixmap
    QPixmap pixmap;
    pixmap.load(fullFileName, "png");
    scaleThumbnail(pixmap);

    // get file info
    QFileInfo* pFileInfo = new QFileInfo(fullFileName);
    QString lastModified =
      pFileInfo->lastModified().toString("yyyy-MM-dd\nhh:mm:ss");

    auto line = new UploadLineItem(this, pixmap, lastModified, url);
    ui->historyContainer->addWidget(line);


    // open in browser
    //connect(buttonOpen, &QPushButton::clicked, this, [=]() {
    //    QDesktopServices::openUrl(QUrl(url));
    //    this->close();
    //});

    //// delete
    //connect(buttonDelete, &QPushButton::clicked, this, [=]() {
    //    if (ConfigHandler().historyConfirmationToDelete() &&
    //        QMessageBox::No ==
    //          QMessageBox::question(
    //            this,
    //            tr("Confirm to delete"),
    //            tr("Are you sure you want to delete a screenshot from the "
    //               "latest uploads and server?"),
    //            QMessageBox::Yes | QMessageBox::No)) {
    //        return;
    //    }

    //    ImgUploaderBase* imgUploaderBase =
    //      ImgUploaderManager(this).uploader(unpackFileName.type);
    //    imgUploaderBase->deleteImage(unpackFileName.file, unpackFileName.token);

    //    removeCacheFile(fullFileName);
    //    removeLayoutItem(phbl);
    //});
}

//  void UploadHistory::removeItem(QLayout* pl,
//                                 const QString& fileName,
//                                 const QString& deleteToken)
//  {
//      /* hide();
//       ImgS3Uploader* imgUploader = new ImgS3Uploader();
//       imgUploader->show();
//       imgUploader->deleteResource(fileName, deleteToken);
//       connect(imgUploader, &QWidget::destroyed, this, [=]() {
//           if (imgUploader->resultStatus) {
//               removeLayoutItem(pl);
//           }
//           imgUploader->deleteLater();
//           show();
//       });*/
//  }
//
//  void UploadHistory::removeLayoutItem(QLayout* pl)
//  {
//      // remove current row or refresh list
//      while (pl->count() > 0) {
//          QLayoutItem* item = pl->takeAt(0);
//          delete item->widget();
//          delete item;
//      }
//      m_pVBox->removeItem(pl);
//      delete pl;
//
//      // set "empty" message if no items left
//      if (m_pVBox->count() == 0) {
//          setEmptyMessage();
//      }
//  }
//
//  void UploadHistory::removeCacheFile(const QString& fullFileName)
//  {
//      // premove history preview
//      QFile file(fullFileName);
//      if (file.exists()) {
//          file.remove();
//      }
//  }