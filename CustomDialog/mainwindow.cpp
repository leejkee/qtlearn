#include "mainwindow.h"
#include <QCloseEvent>
#include <QItemSelectionModel>
#include <QLabel>
#include <QMessageBox>
#include <QStandardItemModel>
#include "./ui_mainwindow.h"
#include "tdialogsize.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tableColumnCount(4)
    , m_tableRowCount(6)
    , m_dlgSetHeader(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->m_model = new QStandardItemModel(m_tableRowCount, m_tableColumnCount, this);
    m_model->setColumnCount(m_tableColumnCount);
    m_model->setRowCount(m_tableRowCount);
    m_selection = new QItemSelectionModel(m_model);
    const QStringList listHeader{"Name", "Sex", "Degree", "Department"};
    m_model->setHorizontalHeaderLabels(listHeader);
    ui->tableView->setSelectionModel(m_selection);
    ui->tableView->setModel(this->m_model);

    m_labCellPositon = new QLabel("Current Cell:", this);
    m_labCellPositon->setMinimumWidth(180);
    m_labCellPositon->setAlignment(Qt::AlignCenter);

    ui->statusBar->addWidget(m_labCellPositon);
    m_labCellText = new QLabel("Cell:", this);
    m_labCellText->setMinimumWidth(200);
    ui->statusBar->addWidget(m_labCellText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::do_model_currentChanged() Update the status bar when the current cell changes.
 * @param current
 * @param previous
 */
void MainWindow::do_model_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(&previous);
    if (current.isValid()) {
        m_labCellPositon->setText(
            QString::asprintf("Current Cell : %d row, %d column", current.row(), current.column()));
        QStandardItem *aItem;
        aItem = m_model->itemFromIndex(current);
        this->m_labCellText->setText("Cell : " + aItem->text());
    }
}

void MainWindow::on_actionSet_RC_triggered()
{
    TDialogSize *dlgTableSize = new TDialogSize(this);
    dlgTableSize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setValueRowColumn(m_model->rowCount(), m_model->columnCount());

    int ret = dlgTableSize->exec();
    if (ret == QDialog::Accepted) {
        int cols = dlgTableSize->columnInt();
        m_model->setColumnCount(cols);

        int rows = dlgTableSize->rowInt();
        m_model->setColumnCount(rows);
    }
    delete dlgTableSize;
}

void MainWindow::on_actionSet_header_triggered()
{
    if (m_dlgSetHeader == nullptr) {
        m_dlgSetHeader = new TDialogHeaders(this);
    }

    if (m_dlgSetHeader->getHeaderList().size() != m_model->columnCount()) {
        QStringList strList;
        for (int i = 0; i < m_model->columnCount(); ++i) {
            strList.append(m_model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        }
        m_dlgSetHeader->setHeaderList(strList);
    }
    int ret = m_dlgSetHeader->exec();
    if (ret == QDialog::Accepted) {
        QStringList strList = m_dlgSetHeader->getHeaderList();
        m_model->setHorizontalHeaderLabels(strList);
    }
}

void MainWindow::on_actionLocate_cell_triggered() {}

void MainWindow::do_setCellText(int row, int column, QString &text) {}

/**
 * @brief MainWindow::closeEvent()  Runs when the window is closed.
 * @param event 
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resultBtn;
    resultBtn = QMessageBox::question(this, "Yes", "Are you sure you want yo quit?");
    if (resultBtn == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
