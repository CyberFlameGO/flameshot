#ifndef UPLOADHISTORY_H
#define UPLOADHISTORY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class UploadHistory;
}
QT_END_NAMESPACE

class UploadHistory : public QWidget
{
    Q_OBJECT
public:
    explicit UploadHistory(QWidget* parent = nullptr);
    ~UploadHistory();
private:
    Ui::UploadHistory* ui;
};

/*
 * class UploadHistory : public QWidget
{
    Q_OBJECT
public:
    explicit UploadHistory(QWidget* parent = nullptr);
    ~UploadHistory();

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

*/
#endif // UPLOADHISTORY_H