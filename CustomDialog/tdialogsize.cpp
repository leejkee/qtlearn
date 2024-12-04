#include "tdialogsize.h"
#include <QMessageBox>
#include "ui_tdialogsize.h"

TDialogSize::TDialogSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogSize)
{
    ui->setupUi(this);
}

TDialogSize::~TDialogSize()
{
    QMessageBox::information(this, "Cue", "TDialogSize Dialog is deleted.");
    delete ui;
}

int TDialogSize::rowInt()
{
    return ui->spinBoxRow->value();
}

int TDialogSize::columnInt()
{
    return ui->spinBoxColumn->value();
}

void TDialogSize::setValueRowColumn(int row, int column)
{
    ui->spinBoxColumn->setValue(column);
    ui->spinBoxRow->setValue(row);
}
