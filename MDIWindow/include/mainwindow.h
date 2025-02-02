#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void onActionNew();
    void onActionOpen();
    void onActionSave();
    void onActionCloseAll();
    void onActionCut();
    void onActionCopy();
    void onActionPaste();
    void onActionFontSettings();
    void onActionMDIMode(bool);
    void onActionCasadingMode();
    void onActionTileMode();
    void onActionQuit();

};
#endif // MAINWINDOW_H
