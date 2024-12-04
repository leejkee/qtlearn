#ifndef TDIALOGLOCATE_H
#define TDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class TDialogLocate;
}
class TDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit TDialogLocate(QWidget *parent = nullptr);
    ~TDialogLocate();
    void setSpinRange(int rowCount, int colCount);

protected:
    void closeEvent();
    void showEvent();

private:
    Ui::TDialogLocate *ui;

public slots:
    void setSpinValue(int row, int column);

signals:
    void changeCellText(int row, int column, QString &text);
    void changeActionEnable(bool en);
};

#endif // TDIALOGLOCATE_H
