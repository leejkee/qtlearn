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
    if (!db.open())
    {
        ui->plainTextEdit->appendPlainText(QString("Error: %1").arg(db.lastError().text()));
        return;
    }
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
QByteArray MainWindow::convertPictureToBOLB(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        ui->plainTextEdit->appendPlainText(QString("Error: %1").arg(file.errorString()));
        return QByteArray();
    }
    QByteArray data = file.readAll();
    file.close();
    return data;
}

void MainWindow::initDB() {
    if (!db.open())
    {
        ui->plainTextEdit->appendPlainText(QString("Error: %1").arg(db.lastError().text()));
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO employees (employeeNo, Name, Gender, Birthday, Province, Department, Salary, Photo, Memo) "
                  "VALUES (?,?,?,?,?,?,?,?,?)");
    QVariantList Nos = {1001, 1002, 1004, 1230, 3006, 2005, 2006, 2007};
    QVariantList Names = {"王五", "李四", "张三", "小雅", "小芳", "小明", "马克", "美丽"};
    QVariantList Genders = {"男", "男", "男", "女", "女", "男", "男", "女"};
    QVariantList Birthdays = {"1987-04-24", "1990-02-03", "1992-03-04", "1992-03-18", "1998-03-10", "1992-03-13", "1999-02-18", "2001-02-20"};
    QVariantList Provinces = {"河北", "湖南", "上海", "重庆", "湖北", "安徽", "重庆", "河南"};
    QVariantList Departments = {"行政部", "销售部", "技术部", "技术部", "行政部", "技术部", "生产部", "行政部"};
    QVariantList Salaries = {5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000};
    QVariantList Photos = {convertPictureToBOLB(":/Photo/pictures/1.jpg"),
                   convertPictureToBOLB(":/Photo/pictures/2.jpg"),
                   convertPictureToBOLB(":/Photo/pictures/3.png"),
                   convertPictureToBOLB(":/Photo/pictures/4.png"),
                   convertPictureToBOLB(":/Photo/pictures/5.jpg"),
                   convertPictureToBOLB(":/Photo/pictures/6.png"),
                   convertPictureToBOLB(":/Photo/pictures/7.png"),
                   convertPictureToBOLB(":/Photo/pictures/8.jpg")};

    QVariantList Memos = {"", "", "", "", "", "", "", ""};
    for (int i = 0; i < Nos.size(); i++)
    {
        query.bindValue(0, Nos.at(i));
        query.bindValue(1, Names.at(i));
        query.bindValue(2, Genders.at(i));
        query.bindValue(3,Birthdays.at(i));
        query.bindValue(4,Provinces.at(i));
        query.bindValue(5,Departments.at(i));
        query.bindValue(6,Salaries.at(i));
        query.bindValue(7,Photos.at(i));
        query.bindValue(8,Memos.at(i));
        if (!query.exec())
        {
            ui->plainTextEdit->appendPlainText(QString("Error: %1").arg(query.lastError().text()));
            db.close();
            return;
        }
        else
        {
            ui->plainTextEdit->appendPlainText(QString("Insert Record: %1").arg(i));
        }
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

    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBName);
    this->getDBInfo();
    // this->openTable();
    this->initDB();
}
