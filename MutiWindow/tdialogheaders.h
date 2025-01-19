#ifndef TDIALOGHEADERS_H
#define TDIALOGHEADERS_H

#include <QDialog>

namespace Ui {
class TDialogHeaders;
}

class QStringListModel;
class TDialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit TDialogHeaders(QWidget *parent = nullptr);
    ~TDialogHeaders();

    void setHeaderList(QStringList &headers);
    QStringList getHeaderList();

private:
    Ui::TDialogHeaders *ui;

private:
    QStringListModel *m_model;
};

#endif // TDIALOGHEADERS_H
