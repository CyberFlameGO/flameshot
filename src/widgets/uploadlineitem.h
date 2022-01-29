#ifndef UPLOADLINEITEM_H
#define UPLOADLINEITEM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class UploadLineItem;
}
QT_END_NAMESPACE

class UploadLineItem : public QWidget
{
    Q_OBJECT
public:
    UploadLineItem(QWidget* parent,
                   QPixmap const& preview,
                   QString const& timestamp,
                   QString const& url);
    ~UploadLineItem();

private:
    Ui::UploadLineItem* ui;
};
#endif // UPLOADLINEITEM_H