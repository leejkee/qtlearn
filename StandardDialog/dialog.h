#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButtonOpenFile_clicked();

    void on_pushButtonOpenFiles_clicked();

    void on_pushButtonSaveFile_clicked();

    void on_pushButtonSelFDir_clicked();

    void on_pushButtonSelColor_clicked();

    void on_pushButtonSelFont_clicked();

    void on_pushButtonProgressBarDialog_clicked();

private:
    Ui::Dialog *ui;
private slots:
    void do_progress_canceled();
    void on_pushButtonString_clicked();
    void on_pushButtonINT_clicked();
    void on_pushButtonFloat_clicked();
    void on_pushButtonSel_clicked();
    void on_pushButtonQuestion_clicked();
    void on_pushButtoninformation_clicked();
    void on_pushButtonWarning_clicked();
    void on_pushButtonCritical_clicked();
    void on_pushButtonAbout_clicked();
    void on_pushButtonAboutQt_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonQuit_clicked();
};
#endif // DIALOG_H
