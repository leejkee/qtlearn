#include "tdialogheaders.h"
#include <QMessageBox>
#include <QStringListModel>
#include "ui_tdialogheaders.h"
TDialogHeaders::TDialogHeaders(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogHeaders)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    ui->listView->setModel(m_model);
}

TDialogHeaders::~TDialogHeaders()
{
    QMessageBox::information(this, "Cue", "TDialogHeaders Dialog is deleted.");
    delete ui;
}

void TDialogHeaders::setHeaderList(QStringList &headers)
{
    m_model->setStringList(headers);
}

QStringList TDialogHeaders::getHeaderList()
{
    return m_model->stringList();
}
