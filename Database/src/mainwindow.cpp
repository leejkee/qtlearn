#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getDBInfo()
{
    QSqlQuery query;
    query.prepare("PRAGMA table_info(employees)");
    if (!query.exec())
    {
        ui->plainTextEdit->appendPlainText(QString("Error: %1").arg(query.lastError().text()));
        db.close();
        return;
    }

    while(query.next())
    {
        int column = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString type = query.value(2).toString();
        bool notnull = query.value(3).toBool();
        bool ispk = query.value(5).toBool();
        ui->plainTextEdit->appendPlainText(QString("Column: %1, Name: %2, Type: %3, Not Null: %4, Primary Key: %5\n")
                                           .arg(column).arg(name).arg(type).arg(notnull).arg(ispk));
    }
    db.close();
}

void MainWindow::openTable() {
    this->model = new QSqlTableModel(this, db);
    model->setTable("employees");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(model->fieldIndex("id"), Qt::AscendingOrder);
    if (!(model->select()))
    {
        ui->plainTextEdit->appendPlainText(QString("Open Table Error: %1").arg(model->lastError().text()));
        return;
    }
    showRecordCount();
}

void MainWindow::getFieldNames() {
}

void MainWindow::showRecordCount() {
    // Function body
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    // Function body
}

void MainWindow::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous) {
    // Function body
}

void MainWindow::on_actionOpenDB_triggered()
{
    QString DBName = QFileDialog::getOpenFileName(this, tr("Open DB"), "", tr("DB Files (*.db)"));
    if (DBName.isEmpty()) {
        return;
    }

    ui->plainTextEdit->appendPlainText(QString("Debug Output:\nOpening DB: %1").arg(DBName));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBName);
    if (!db.open()) {
        ui->plainTextEdit->appendPlainText(QString("Error: %1").arg(db.lastError().text()));
    }
    else
    {
        ui->plainTextEdit->appendPlainText("DB opened successfully");
        this->getDBInfo();
        // this->openTable();
    }
}