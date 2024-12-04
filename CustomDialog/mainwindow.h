#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tdialogheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class QLabel;

#ifdef TDIALOGHEADERS_H
class TDialogHeaders;
#endif

class QItemSelectionModel;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_actionSet_RC_triggered();

    void on_actionSet_header_triggered();

    void on_actionLocate_cell_triggered();

public slots:
    void do_setCellText(int row, int column, QString &text);

signals:
    void cellIndexChanged(int rowNo, int colNo);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

private:
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    const unsigned m_tableColumnCount;
    const unsigned m_tableRowCount;
    QLabel *m_labCellPositon;
    QLabel *m_labCellText;
#ifdef TDIALOGHEADERS_H
    TDialogHeaders *m_dlgSetHeader;
#endif
};
#endif // MAINWINDOW_H
