#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "tcomboboxdelegate.h"

namespace Ui {
class MainWindow;
}

class QSqlTableModel;
class QItemSelectionModel;
class QDataWidgetMapper;
class TComboBoxDelegate;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // QSqlDatabase db;
    QSqlTableModel *model;
    QItemSelectionModel *selectionModel;
    QDataWidgetMapper *dataMapper;
    TComboBoxDelegate comboBoxDelegateSex;
    TComboBoxDelegate comboBoxDelegateDepartment;

    void openTable();
    void getFieldNames();
    void showRecordCount();

    void getDBInfo();
    void initDB();
    QByteArray convertPictureToBOLB(QString fileName);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void do_currentChanged(const QModelIndex &currnent, const QModelIndex &previous);
    void do_currentRowChanged(const QModelIndex &currnent, const QModelIndex &previous);

    void on_actionOpenDB_triggered();
    void on_actionRecAppend_triggered();
    void on_actionRecInsert_triggered();
    void on_actionRecDelete_triggered();
    void on_actionSubmit_triggered();
    void on_actionRevert_triggered();
    void on_actionPhoto_triggered();
    void on_actionPhotoClear_triggered();
    void on_actionScan_triggered();
    void on_comboBoxSortField_currentIndexChanged(int index);
    void on_radioButtonASC_clicked();
    void on_radioButtonDESC_clicked();
    void on_radioButtonGenderMale_clicked();
    void on_radioButtonGenderFemale_clicked();
    void on_radioButtonGenderAll_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
