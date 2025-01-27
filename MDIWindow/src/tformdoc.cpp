#include "tformdoc.h"
#include <QFontDialog>
#include <QPlainTextEdit>
#include <QVBoxLayout>

TFormDoc::TFormDoc(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("New Doc[*]");
    this->setAttribute(Qt::WA_DeleteOnClose);
    plainTextEdit = new QPlainTextEdit(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plainTextEdit);
    setLayout(layout);

    connect(this->plainTextEdit,
            &QPlainTextEdit::modificationChanged,
            this,
            &QWidget::setWindowModified);
}

void TFormDoc::loadFormFile(QString &fileName) {}

void TFormDoc::saveToFile() {}

QString TFormDoc::currentFileName()
{
    return QString("adab");
}

bool TFormDoc::isFileOpened()
{
    return true;
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
