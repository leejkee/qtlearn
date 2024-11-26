#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

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

private slots:
    void on_actionSet_RC_triggered();

    void on_actionSet_header_triggered();

    void on_actionLocate_cell_triggered();

private:
    Ui::MainWindow *ui;

private:
    QStandardItemModel *m_model;
    const unsigned m_tableColumnCount;
    const unsigned m_tableRowCount;
};
#endif // MAINWINDOW_H
