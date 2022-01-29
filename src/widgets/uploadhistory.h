#ifndef UPLOADHISTORY_H
#define UPLOADHISTORY_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class UploadHistory;
}
QT_END_NAMESPACE

void scaleThumbnail(QPixmap &input);

class UploadHistory : public QWidget
{
    Q_OBJECT
public:
    explicit UploadHistory(QWidget* parent = nullptr);
    ~UploadHistory();

    void loadHistory();

private:
    void clearHistoryLayout(QLayout* layout);
    void setEmptyMessage();
    void addLine(QString const&, QString const&);

    Ui::UploadHistory* ui;
};

/*
private:
    void addLine(const QString&, const QString&);
    void removeItem(QLayout* pl,
                    const QString& s3FileName,
                    const QString& deleteToken);
    void removeLayoutItem(QLayout* pl);
    void removeCacheFile(const QString& fullFileName);
};

*/
#endif // UPLOADHISTORY_H