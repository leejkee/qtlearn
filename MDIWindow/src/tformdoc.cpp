#include "tformdoc.h"
#include <QFontDialog>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QStatusBar>

TFormDoc::TFormDoc(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("New Doc[*]");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // set up UI
    plainTextEdit = new QPlainTextEdit(this);
    // statusBar = new QStatusBar(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plainTextEdit);
    // layout->addWidget(statusBar);
    setLayout(layout);

    connect(this->plainTextEdit,
            &QPlainTextEdit::modificationChanged,
            this,
            &QWidget::setWindowModified);
}

void TFormDoc::loadFormFile(QString &fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        this->plainTextEdit->clear();
        this->plainTextEdit->setPlainText(stream.readAll());
        file.close();

        this->m_fileName = fileName;
        QFileInfo fileInfo(fileName);
        QString baseName = fileInfo.fileName();
        this->setWindowTitle(baseName + "[*]");
        this->m_fileOpened = true;
    }
}

void TFormDoc::saveToFile() {
    this->setWindowModified(false);
}

QString TFormDoc::currentFileName()
{
    return this->m_fileName;
}

bool TFormDoc::isFileOpened()
{
    return this->m_fileOpened;
}

void TFormDoc::setEditFont()
{
    QFont font = plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    plainTextEdit->setFont(font);
}

void TFormDoc::textCut()
{
    plainTextEdit->cut();
}

void TFormDoc::textCopy()
{
    plainTextEdit->copy();
}

void TFormDoc::textPaste()
{
    plainTextEdit->paste();
}
