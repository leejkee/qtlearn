#include "dialog.h"
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressDialog>
#include "./ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonOpenFile_clicked()
{
    QString curPath = QDir::currentPath();
    QString dialogTitle = "Select a file";
    QString filter = "Text files(*.txt);;Image files(*.jpg *.gif *.png);;All files(*.*)";
    QString fileName = QFileDialog::getOpenFileName(this, dialogTitle, curPath, filter);

    if (!fileName.isEmpty()) {
        ui->plainTextEdit->appendPlainText(fileName);
    }
}

void Dialog::on_pushButtonOpenFiles_clicked()
{
    QString curPath = QDir::currentPath();
    QString dialogTitle = "Open files";
    QString filter = "Text files(*.txt);;Image files(*.jpg *.gif *.png);;All files(*.*)";
    QStringList fileNameList = QFileDialog::getOpenFileNames(this, dialogTitle, curPath, filter);

    for (int i = 0; i < fileNameList.size(); i++) {
        ui->plainTextEdit->appendPlainText(fileNameList.at(i));
    }
}

void Dialog::on_pushButtonSaveFile_clicked()
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString dialogTitle = "Save files";
    QString filter
        = "Text files(*.txt);;C++ header files(*.h);;C++ source files(*.cpp);;All files(*.*)";
    QString fileName = QFileDialog::getSaveFileName(this, dialogTitle, currentPath, filter);

    if (!fileName.isEmpty()) {
        ui->plainTextEdit->appendPlainText(fileName);
    }
}

void Dialog::on_pushButtonSelFDir_clicked()
{
    QString currentPath = QCoreApplication::applicationDirPath();
    QString dialogTitle = "Select a directory";
    QString selectDir = QFileDialog::getExistingDirectory(this, dialogTitle, currentPath);

    if (!selectDir.isEmpty()) {
        ui->plainTextEdit->appendPlainText(selectDir);
    }
}

void Dialog::on_pushButtonSelColor_clicked()
{
    QPalette currentPalette = ui->plainTextEdit->palette();
    QColor initColor = currentPalette.color(QPalette::Text);
    QColor curColor = QColorDialog::getColor(initColor, this, "Select color");
    if (curColor.isValid()) {
        currentPalette.setColor(QPalette::Text, curColor);
        ui->plainTextEdit->setPalette(currentPalette);
    }
}

void Dialog::on_pushButtonSelFont_clicked()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool isOk = false;
    QFont font = QFontDialog::getFont(&isOk, iniFont);
    if (isOk) {
        ui->plainTextEdit->setFont(font);
    }
}

void Dialog::on_pushButtonProgressBarDialog_clicked()
{
    QString labText = "Copying files...";
    QString btnText = "Cancel";
    int minV = 0, maxV = 200;
    QProgressDialog dlgProgress(labText, btnText, minV, maxV, this);
    connect(&dlgProgress, &QProgressDialog::canceled, this, &Dialog::do_progress_canceled);
    dlgProgress.setWindowTitle("Copy files");
    dlgProgress.setWindowModality(Qt::WindowModal);
    dlgProgress.setAutoReset(true);
    dlgProgress.setAutoClose(true);

    QElapsedTimer msCouter;
    for (int i = minV; i < maxV; i++) {
        dlgProgress.setValue(i);
        dlgProgress.setLabelText(QString::asprintf("Copying files... the %dth file.", i));
        msCouter.start();
        while (true) {
            if (msCouter.elapsed() > 30) {
                break;
            }
        }
        if (dlgProgress.wasCanceled()) {
            break;
        }
    }
}

void Dialog::do_progress_canceled()
{
    ui->plainTextEdit->appendPlainText("**The progress was canceled**");
}

void Dialog::on_pushButtonString_clicked()
{
    QString dlgTitle = "Input Text Dialog";
    QString txtLabel = "Please input file name";
    QString iniInput = "Newfile.txt";
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;
    bool ok = false;
    QString text = QInputDialog::getText(this, dlgTitle, txtLabel, echoMode, iniInput, &ok);
    if (ok && !text.isEmpty()) {
        ui->plainTextEdit->appendPlainText(text);
    }
}

void Dialog::on_pushButtonINT_clicked()
{
    QString dlgTitle = "Input INT Dialog";
    QString txtLabel = "Set font size";
    int defalutFontValue = ui->plainTextEdit->font().pointSize();
    int minValue = 6, maxValue = 50, stepValue = 1;
    bool ok = false;
    int inputValue = QInputDialog::getInt(this,
                                          dlgTitle,
                                          txtLabel,
                                          defalutFontValue,
                                          minValue,
                                          maxValue,
                                          stepValue,
                                          &ok);
    if (ok) {
        QString str = QString("The size of text box is %1").arg(inputValue);
        ui->plainTextEdit->appendPlainText(str);
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
}

void Dialog::on_pushButtonFloat_clicked()
{
    QString dlgTitle = "Input Float Dialog";
    QString txtLabel = "Input a float number";
    float defalutValue = 3.14;
    float minValue = 0.0, maxValue = 100.0;
    int decimals = 2;
    bool ok = false;
    float inputValue = QInputDialog::getDouble(this,
                                               dlgTitle,
                                               txtLabel,
                                               defalutValue,
                                               minValue,
                                               maxValue,
                                               decimals,
                                               &ok);
    if (ok) {
        QString str = QString::asprintf("The float number is %.2f", inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Dialog::on_pushButtonSel_clicked()
{
    QStringList items;
    items << "A" << "B" << "C" << "D";
    QString dlgTitle = "Button Selection Box";
    QString txtLabel = "Select the grade";
    int curIndex = 0;
    bool editable = true;
    bool ok = false;
    QString text = QInputDialog::getItem(this, dlgTitle, txtLabel, items, curIndex, editable, &ok);
    if (ok && !text.isEmpty()) {
        ui->plainTextEdit->appendPlainText(text);
    }
}

void Dialog::on_pushButtonQuestion_clicked()
{
    QString dlgTitle = "question message box";
    QString strInfo = "The file has unsaved changes, do u want to save it?";
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
    QMessageBox::StandardButton resultBtn;
    resultBtn = QMessageBox::question(this,
                                      dlgTitle,
                                      strInfo,
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                      defaultBtn);
    if (resultBtn == QMessageBox::Yes) {
        ui->plainTextEdit->appendPlainText("Question Box: Yes is selected");
    } else if (resultBtn == QMessageBox::No) {
        ui->plainTextEdit->appendPlainText("Question Box: No is selected");

    } else if (resultBtn == QMessageBox::Cancel) {
        ui->plainTextEdit->appendPlainText("Question Box: Cancel is selected");

    } else {
        ui->plainTextEdit->appendPlainText("Question Box: None is selected");
    }
}

void Dialog::on_pushButtoninformation_clicked()
{
    QString dlgTitle = "information message box";
    QString strInfo = "The file is opened, plz check";
    QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
}

void Dialog::on_pushButtonWarning_clicked()
{
    QString dlgTitle = "Warning message box";
    QString strInfo = "The file was changed";
    QMessageBox::warning(this, dlgTitle, strInfo);
}

void Dialog::on_pushButtonCritical_clicked()
{
    QString dlgTitle = "Critical message box";
    QString strInfo = "There is a unkown application accessing the network";
    QMessageBox::critical(this, dlgTitle, strInfo);
}

void Dialog::on_pushButtonAbout_clicked()
{
    QString dlgTitle = "About message box";
    QString strInfo = "SEGY file check software v1.0 \nDesigned by Alan";
    QMessageBox::about(this, dlgTitle, strInfo);
}

void Dialog::on_pushButtonAboutQt_clicked()
{
    QString dlgTitle = "About Qt box";
    QMessageBox::aboutQt(this, dlgTitle);
}

void Dialog::on_pushButtonClear_clicked()
{
    ui->plainTextEdit->clear();
}

void Dialog::on_pushButtonQuit_clicked()
{
    this->close();
}
