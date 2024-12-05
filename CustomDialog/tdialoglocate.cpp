#include "tdialoglocate.h"
#include <QMessageBox>
#include "ui_tdialoglocate.h"

TDialogLocate::TDialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogLocate)
{
    ui->setupUi(this);
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &QDialog::close);
}

TDialogLocate::~TDialogLocate()
{
    QMessageBox::information(this, "Cue", "TDialogLocate dialog is deleted.");
    delete ui;
}

void TDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBoxR->setMaximum(rowCount - 1);
    ui->spinBoxC->setMaximum(colCount - 1);
}

void TDialogLocate::closeEvent(QEvent *e)
{
    e->accept();
    emit changeActionEnable(true);
}

void TDialogLocate::showEvent(QEvent *e)
{
    e->accept();
    emit changeActionEnable(false);
}

/**
 * @brief TDialogLocate::setSpinValue() Set value
 * @param row
 * @param column
 */
void TDialogLocate::setSpinValue(int row, int column)
{
    ui->spinBoxC->setValue(column);
    ui->spinBoxR->setValue(row);
}

void TDialogLocate::on_pushButtonSet_clicked()
{
    int row = ui->spinBoxR->value();
    int col = ui->spinBoxC->value();

    QString text = ui->lineEdit->text();

    emit changeCellText(row, col, text);
    if (ui->checkBoxCInc->isChecked()) {
        ui->spinBoxC->setValue(ui->spinBoxC->value() + 1);
    }
    if (ui->checkBoxRInc->isChecked()) {
        ui->spinBoxR->setValue(ui->spinBoxR->value() + 1);
    }
}
