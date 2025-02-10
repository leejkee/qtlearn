#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QItemSelectionModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include "ui_mainwindow.h"
#include "tcomboboxdelegate.h"
#include <QModelIndex>
#include <QSqlRecord>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
    connect(ui->actionGetInfo, &QAction::triggered, this, &MainWindow::getDBInfo);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::getDBInfo()
{
    if (!db.open())
    {
        QMessageBox::information(this, "Error", QString("Error: %1").arg(db.lastError().text()));
        return;
    }
    QSqlQuery query;
    query.prepare("PRAGMA table_info(employees)");
    if (!query.exec())
    {
        QMessageBox::information(this, "Error", QString("Error: %1").arg(query.lastError().text()));
        db.close();
        return;
    }

    QString info;
    while(query.next())
    {
        int column = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString type = query.value(2).toString();
        bool notnull = query.value(3).toBool();
        bool ispk = query.value(5).toBool();
        info.append(QString("Column: %1, Name: %2, Type: %3, Not Null: %4, Primary Key: %5\n")
                    .arg(column).arg(name).arg(type).arg(notnull).arg(ispk));
    }
    db.close();
    QMessageBox::information(this, "Info", info);
}

// Function to convert picture to BLOB 
QByteArray MainWindow::convertPictureToBOLB(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Error", QString("Error: %1").arg(file.errorString()));
        return QByteArray();
    }
    QByteArray data = file.readAll();
    file.close();
    return data;
}

void MainWindow::initDB() {
    if (!db.open())
    {
        QMessageBox::information(this, "Error", QString("Error: %1").arg(db.lastError().text()));
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

    QVariantList Memos = {"111", "222", "333", "444", "555", "666", "777", "888"};
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
            QMessageBox::information(this, "Error", QString("Error: %1").arg(query.lastError().text()));
            db.close();
            return;
        }
        else
        {
            QMessageBox::information(this, "Info", QString("Insert Record: %1").arg(i));
        }
    }
    db.close();
}
void MainWindow::openTable() {
    if (!db.open())
    {
        QMessageBox::information(this, "Error", QString("Error: %1").arg(db.lastError().text()));
        return;
    }
    this->model = new QSqlTableModel(this, db);
    model->setTable("employees");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(model->fieldIndex("employeeNo"), Qt::AscendingOrder);
    if (!(model->select()))
    {
        QMessageBox::critical(this, "Error", QString("Open Table Error: %1").arg(model->lastError().text()));
        return;
    }
    showRecordCount();

    model->setHeaderData(model->fieldIndex("employeeNo"), Qt::Horizontal, "工号");
    model->setHeaderData(model->fieldIndex("Name"), Qt::Horizontal, "姓名");
    model->setHeaderData(model->fieldIndex("Gender"), Qt::Horizontal, "性别");
    model->setHeaderData(model->fieldIndex("Birthday"), Qt::Horizontal, "出生日期");
    model->setHeaderData(model->fieldIndex("Province"), Qt::Horizontal, "省份");
    model->setHeaderData(model->fieldIndex("Department"), Qt::Horizontal, "部门");
    model->setHeaderData(model->fieldIndex("Salary"), Qt::Horizontal, "工资");

    model->setHeaderData(model->fieldIndex("Memo"), Qt::Horizontal, "备注");
    model->setHeaderData(model->fieldIndex("Photo"), Qt::Horizontal, "照片");

    this->selectionModel = new QItemSelectionModel(model, this);
    connect(selectionModel,
            &QItemSelectionModel::currentChanged,
            this,
            &MainWindow::do_currentChanged);
    connect(selectionModel,
            &QItemSelectionModel::currentRowChanged,
            this,
            &MainWindow::do_currentRowChanged);

    ui->tableView->setModel(this->model);
    ui->tableView->setSelectionModel(this->selectionModel);
    ui->tableView->setColumnHidden(model->fieldIndex("Memo"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("Photo"), true);

    QStringList delegateList;
    delegateList << "男" << "女";
    bool isEidtable = false;
    comboBoxDelegateSex.setItems(delegateList, isEidtable);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("Gender"), &comboBoxDelegateSex);

    delegateList.clear();
    delegateList << "销售部" << "技术部" << "生产部" << "行政部";
    isEidtable = true;
    comboBoxDelegateDepartment.setItems(delegateList, isEidtable);
    ui->tableView->setItemDelegateForColumn(model->fieldIndex("Department"), &comboBoxDelegateDepartment);

    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(model);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataMapper->addMapping(ui->DBspinBoxEmpNo, model->fieldIndex("employeeNo"));
    dataMapper->addMapping(ui->DBlineEditName, model->fieldIndex("Name"));
    dataMapper->addMapping(ui->DBcomboBoxGender, model->fieldIndex("Gender"));
    dataMapper->addMapping(ui->DBdateEdit, model->fieldIndex("Birthday"));
    dataMapper->addMapping(ui->DBcomboBoxProvince, model->fieldIndex("Province"));
    dataMapper->addMapping(ui->DBcomboBoxDepartment, model->fieldIndex("Department"));
    dataMapper->addMapping(ui->DBspinBoxSalary, model->fieldIndex("Salary"));
    dataMapper->addMapping(ui->plainTextEdit, model->fieldIndex("Memo"));
    dataMapper->toFirst();

    // init comboBox
    getFieldNames();
    QStringList list;
    list << "男" << "女";
    ui->DBcomboBoxGender->addItems(list);
    list.clear();
    list << "销售部" << "技术部" << "生产部" << "行政部";
    ui->DBcomboBoxDepartment->addItems(list);
    list.clear();
    list << "河北" << "湖南" << "上海" << "重庆" << "湖北" << "安徽" << "河南";
    ui->DBcomboBoxProvince->addItems(list);
    list.clear();

    ui->actionOpenDB->setEnabled(false);
    ui->actionRecAppend->setEnabled(true);
    ui->actionRecInsert->setEnabled(true);
    ui->actionRecDelete->setEnabled(true);
    ui->actionScan->setEnabled(true);
    ui->groupBoxSort->setEnabled(true);
    ui->groupBoxFilter->setEnabled(true);
    // db.close();
}

void MainWindow::getFieldNames() {
    QSqlRecord record = model->record();
    for (int i = 0; i < record.count(); i++)
    {
        ui->comboBoxSortField->addItem(record.fieldName(i));
    }
}

void MainWindow::showRecordCount() {
    ui->statusbar->showMessage(QString("Total: %1 records").arg(model->rowCount()));
}

void MainWindow::do_currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    Q_UNUSED(previous);
    Q_UNUSED(current);
    ui->actionSubmit->setEnabled(model->isDirty());
    ui->actionRevert->setEnabled(model->isDirty());
}

void MainWindow::do_currentRowChanged(const QModelIndex &current, const QModelIndex &previous) {
    Q_UNUSED(previous);
    ui->actionRecDelete->setEnabled(current.isValid());
    ui->actionPhoto->setEnabled(current.isValid());
    ui->actionPhotoClear->setEnabled(current.isValid());

    if (!current.isValid())
    {
        ui->labelPhoto->clear();
        return;
    }

    dataMapper->setCurrentIndex(current.row());
    int currentRow = current.row();
    QSqlRecord record = model->record(currentRow);
    if (record.isNull("Photo"))
    {
        ui->labelPhoto->clear();
    }
    else
    {
        QByteArray data = record.value("Photo").toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(data);
        ui->labelPhoto->setPixmap(pixmap.scaled(ui->labelPhoto->size(), Qt::KeepAspectRatio));
    }
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
    // this->initDB();
    this->openTable();
}

void MainWindow::on_actionRecAppend_triggered()
{
    QSqlRecord record = model->record();
    record.setValue(model->fieldIndex("employeeNo"), 2000+model->rowCount());
    record.setValue(model->fieldIndex("Gender"), "男");
    model->insertRecord(model->rowCount(), record);

    selectionModel->clearSelection();
    QModelIndex currentIndex = model->index(model->rowCount()-1, 1);
    selectionModel->setCurrentIndex(currentIndex, QItemSelectionModel::Select);
    showRecordCount();
}

void MainWindow::on_actionRecInsert_triggered()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    QSqlRecord record = model->record();
    model->insertRecord(currentIndex.row(), record);
    selectionModel->clearSelection();
    selectionModel->setCurrentIndex(currentIndex, QItemSelectionModel::Select);
    showRecordCount();
}

void MainWindow::on_actionRecDelete_triggered()
{
    QModelIndex currentIndex = ui->tableView->currentIndex();
    model->removeRow(currentIndex.row());
    showRecordCount();
}

// void MainWindow::on_actionSubmit_triggered()
// {
//     if (model->submitAll()) // submit successfully
//     {
//         ui->actionSubmit->setEnabled(false);
//         ui->actionRevert->setEnabled(false);
//     }
//     else
//     {
//         QMessageBox::information(this, "Error", QString("Error: %1").arg(model->lastError().text()));
//     }
//     showRecordCount();
// }
void MainWindow::on_actionSubmit_triggered()
{
    bool yes = model->submitAll();
    if (!yes) // submit successfully
    {
        QMessageBox::information(this, "Error", "ERROR" + model->lastError().text());
    }
    else
    {
        ui->actionSubmit->setEnabled(false);
        ui->actionRevert->setEnabled(false);
    }
    showRecordCount();
}
void MainWindow::on_actionRevert_triggered()
{
    model->revertAll();
    ui->actionSubmit->setEnabled(false);
    ui->actionRevert->setEnabled(false);
    showRecordCount();
}

void MainWindow::on_actionPhoto_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Photo"), "", tr("Photo Files (*.jpg *.png)"));
    if (fileName.isEmpty())
    {
        return;
    }
    QByteArray data = convertPictureToBOLB(fileName);
    auto indexR = ui->tableView->currentIndex().row();
    auto indexC = model->fieldIndex("Photo");
    model->setData(model->index(indexR, indexC), data);
    ui->labelPhoto->setPixmap(QPixmap(fileName).scaled(ui->labelPhoto->size(), Qt::KeepAspectRatio));
}

void MainWindow::on_actionPhotoClear_triggered()
{
    auto indexR = ui->tableView->currentIndex().row();
    auto indexC = model->fieldIndex("Photo");
    model->setData(model->index(indexR, indexC), QVariant());
    ui->labelPhoto->clear();
}


void MainWindow::on_actionScan_triggered()
{
    // no record
    if (model->rowCount() == 0)
    {
        return;
    }

    for (int i = 0; i < model->rowCount(); i++)
    {
        QSqlRecord record = model->record(i);
        float salary = record.value("Salary").toFloat();
        salary *= 1.1;
        record.setValue("Salary", salary);
        model->setRecord(i, record);
    }
    if (model->submitAll())
    {
        QMessageBox::information(this, "Info", "Scan Successfully");
    }
    else
    {
        QMessageBox::information(this, "Error", QString("Error: %1").arg(model->lastError().text()));
    }
}

void MainWindow::on_comboBoxSortField_currentIndexChanged(int index)
{
    if (ui->radioButtonASC->isChecked())
    {
        model->setSort(index, Qt::AscendingOrder);
    }
    else
    {
        model->setSort(index, Qt::DescendingOrder);
    }
    model->select();
}

void MainWindow::on_radioButtonASC_clicked()
{
    model->setSort(ui->comboBoxSortField->currentIndex(), Qt::AscendingOrder);
    model->select();
}

void MainWindow::on_radioButtonDESC_clicked()
{
    model->sort(ui->comboBoxSortField->currentIndex(), Qt::DescendingOrder);
}

void MainWindow::on_radioButtonGenderMale_clicked()
{
    model->setFilter("Gender = '男'");
    showRecordCount();
}

void MainWindow::on_radioButtonGenderFemale_clicked()
{
    model->setFilter("Gender = '女'");
    showRecordCount();
}

void MainWindow::on_radioButtonGenderAll_clicked()
{
    model->setFilter("");
    showRecordCount();
}