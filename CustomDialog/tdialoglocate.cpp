#include "tdialoglocate.h"
#include "ui_tdialoglocate.h"

TDialogLocate::TDialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogLocate)
{
    ui->setupUi(this);
}

TDialogLocate::~TDialogLocate()
{
    delete ui;
}

void TDialogLocate::setSpinRange(int rowCount, int colCount) {}

void TDialogLocate::closeEvent() {}

void TDialogLocate::showEvent() {}

void TDialogLocate::setSpinValue(int row, int column) {}
