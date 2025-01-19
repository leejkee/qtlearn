#ifndef TDIALOGSIZE_H
#define TDIALOGSIZE_H

#include <QDialog>

namespace Ui {
class TDialogSize;
}

class TDialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit TDialogSize(QWidget *parent = nullptr);
    ~TDialogSize();

public:
    int getSpinBoxRowInt();
    int getSpinBoxColumnInt();
    void setValueRowColumn(int row, int column);

private:
    Ui::TDialogSize *ui;
};

#endif // TDIALOGSIZE_H
