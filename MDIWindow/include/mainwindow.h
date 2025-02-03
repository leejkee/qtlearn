#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QMdiSubWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMdiSubWindow *m_activeSubWindow;
    const QString defaultStyle = "border: none;";
    const QString activeStyle = "border: 3px solid red;";

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

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);
};
#endif // MAINWINDOW_H
