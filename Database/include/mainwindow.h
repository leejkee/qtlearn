#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

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
    QSqlDatabase db;
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
