#include "tformtable.h"
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QToolBar>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>
#include "tdialogsize.h"

TFormTable::TFormTable(QWidget *parent)
    : QMainWindow{parent}
{
    actionTableCellSize = new QAction(this);
    actionTableCellSize->setObjectName("actionTableCellSize");
    QIcon icon{};
    icon.addFile(QString::fromUtf8(":/img/icon/table.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionTableCellSize->setIcon(icon);
    actionTableCellSize->setMenuRole(QAction::MenuRole::NoRole);
    actionTableCellSize->setText(
        QCoreApplication::translate("TFormTable", "TableCellSize", nullptr));

    actionTableHeaderSetting = new QAction(this);
    actionTableHeaderSetting->setObjectName("actionTableHeaderSetting");
    icon.addFile(QString::fromUtf8(":/img/icon/table_header.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionTableHeaderSetting->setIcon(icon);
    actionTableHeaderSetting->setMenuRole(QAction::MenuRole::NoRole);
    actionTableHeaderSetting->setText(
        QCoreApplication::translate("TFormTable", "TableHeaderSetting", nullptr));

    actionExit = new QAction(this);
    actionExit->setObjectName("actionExit");
    icon.addFile(QString::fromUtf8(":/img/icon/exit.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionExit->setIcon(icon);
    actionExit->setMenuRole(QAction::MenuRole::NoRole);
    actionExit->setText(QCoreApplication::translate("TFormTable", "Exit", nullptr));

    toolBar = new QToolBar(this);
    toolBar->setObjectName("toolBar");
    toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

    toolBar->addAction(actionTableCellSize);
    toolBar->addAction(actionTableHeaderSetting);
    toolBar->addSeparator();
    toolBar->addAction(actionExit);
    this->addToolBar(toolBar);

    tableView = new QTableView(this);
    m_model = new QStandardItemModel(12, 6, this);
    m_selection = new QItemSelectionModel(m_model, this);
    tableView->setModel(m_model);
    tableView->setSelectionModel(m_selection);
    this->setCentralWidget(tableView);

    connect(this->actionExit, &QAction::triggered, this, &TFormTable::close);
    connect(this->actionTableCellSize,
            &QAction::triggered,
            this,
            &TFormTable::onActionTableCellSize);
    connect(this->actionTableHeaderSetting,
            &QAction::triggered,
            this,
            &TFormTable::onActionTableHeaderSetting);
}

///
/// @brief TFormTable::onActionTableCellSize
/// set the size of the table
///
void TFormTable::onActionTableCellSize()
{
    TDialogSize *dialogTableSize = new TDialogSize(this);
    dialogTableSize->setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    dialogTableSize->setValueRowColumn(m_model->rowCount(), m_model->columnCount());
    int ret = dialogTableSize->exec();
    if (ret == QDialog::Accepted) {
        m_model->setColumnCount(dialogTableSize->getSpinBoxColumnInt());
        m_model->setRowCount(dialogTableSize->getSpinBoxRowInt());
    }
    delete dialogTableSize;
}

void TFormTable::onActionTableHeaderSetting()
{
    if (dialogSetHeaders == nullptr) {
        dialogSetHeaders = new TDialogHeaders(this);
    }
    if (dialogSetHeaders->getHeaderList().count() != m_model->columnCount()) {
        QStringList strList;
        for (int i = 0; i < m_model->columnCount(); i++) {
            strList.append(m_model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
            dialogSetHeaders->setHeaderList(strList);
        }
    }
    int ret = dialogSetHeaders->exec();
    if (ret == QDialog::Accepted) {
        QStringList strList = dialogSetHeaders->getHeaderList();
        m_model->setHorizontalHeaderLabels(strList);
    }
}
