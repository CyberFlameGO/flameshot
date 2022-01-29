#ifndef UPLOADHISTORYWIDGET_H
#define UPLOADHISTORYWIDGET_H

#include <QDialog>

class QString;
class QLayout;
class QVBoxLayout;
class NotificationWidget;
class ImgUploader;

class UploadHistoryWidget : public QDialog
{
    Q_OBJECT
public:
    explicit UploadHistoryWidget(QWidget* parent = nullptr);
    ~UploadHistoryWidget();

    void loadHistory();

private:
    void clearHistoryLayout(QLayout* layout);

    void addLine(const QString&, const QString&);
    void setEmptyMessage();
    void removeItem(QLayout* pl,
                    const QString& s3FileName,
                    const QString& deleteToken);
    void removeLayoutItem(QLayout* pl);
    void removeCacheFile(const QString& fullFileName);

private:
    QVBoxLayout* m_pVBox;
    NotificationWidget* m_notification;
};

#endif // UPLOADHISTORYWIDGET_H
