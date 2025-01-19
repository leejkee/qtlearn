#include "tformdoc.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDialog>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QVBoxLayout>

TFormDoc::TFormDoc(QWidget *parent)
    : QWidget(parent)
{
    localToolBar = new QToolBar("Doc", this);
    actionOpen = new QAction(this);
    actionOpen->setObjectName("actionOpen");
    QIcon icon{};
    icon.addFile(QString::fromUtf8(":/img/icon/file-open.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionOpen->setIcon(icon);
    actionOpen->setMenuRole(QAction::MenuRole::NoRole);
    actionOpen->setText(QCoreApplication::translate("TFormDoc", "Open", nullptr));

    actionFont = new QAction(this);
    actionFont->setObjectName("actionFont");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/font.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionFont->setIcon(icon);
    actionFont->setMenuRole(QAction::MenuRole::NoRole);
    actionFont->setText(QCoreApplication::translate("TFormDoc", "Font", nullptr));

    actionClose = new QAction(this);
    actionClose->setObjectName("actionClose");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/close.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionClose->setIcon(icon);
    actionClose->setMenuRole(QAction::MenuRole::NoRole);
    actionClose->setText(QCoreApplication::translate("TFormDoc", "Close", nullptr));

    actionCopy = new QAction(this);
    actionCopy->setObjectName("actionCopy");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/copy.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionCopy->setIcon(icon);
    actionCopy->setMenuRole(QAction::MenuRole::NoRole);
    actionCopy->setText(QCoreApplication::translate("TFormDoc", "Copy", nullptr));

    actionCut = new QAction(this);
    actionCut->setObjectName("actionCut");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/cut.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionCut->setIcon(icon);
    actionCut->setMenuRole(QAction::MenuRole::NoRole);
    actionCut->setText(QCoreApplication::translate("TFormDoc", "Cut", nullptr));

    actionPaste = new QAction(this);
    actionPaste->setObjectName("actionPaste");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/paste.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionPaste->setIcon(icon);
    actionPaste->setMenuRole(QAction::MenuRole::NoRole);
    actionPaste->setText(QCoreApplication::translate("TFormDoc", "Paste", nullptr));

    actionRedo = new QAction(this);
    actionRedo->setObjectName("actionRedo");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/redo.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionRedo->setIcon(icon);
    actionRedo->setMenuRole(QAction::MenuRole::NoRole);
    actionRedo->setText(QCoreApplication::translate("TFormDoc", "Redo", nullptr));

    actionUndo = new QAction(this);
    actionUndo->setObjectName("actionUndo");
    icon = QIcon();
    icon.addFile(QString::fromUtf8(":/img/icon/undo.png"),
                 QSize(),
                 QIcon::Mode::Normal,
                 QIcon::State::Off);
    actionUndo->setIcon(icon);
    actionUndo->setMenuRole(QAction::MenuRole::NoRole);
    actionUndo->setText(QCoreApplication::translate("TFormDoc", "Undo", nullptr));

    plainTextEdit = new QPlainTextEdit(this);

    localToolBar->addAction(this->actionOpen);
    localToolBar->addAction(this->actionFont);
    localToolBar->addSeparator();
    localToolBar->addAction(this->actionCut);
    localToolBar->addAction(this->actionCopy);
    localToolBar->addAction(this->actionPaste);
    localToolBar->addAction(this->actionUndo);
    localToolBar->addAction(this->actionRedo);
    localToolBar->addSeparator();
    localToolBar->addAction(this->actionClose);
    localToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(localToolBar);
    layout->addWidget(this->plainTextEdit);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(2);
    this->setLayout(layout);
    connect(this->actionOpen, &QAction::triggered, this, &TFormDoc::onActionOpenTriggered);
    connect(this->actionFont, &QAction::triggered, this, &TFormDoc::onActionFontTriggered);
    connect(this->actionClose, &QAction::triggered, this, &QWidget::close);
    connect(this->actionCut, &QAction::triggered, this->plainTextEdit, &QPlainTextEdit::cut);
    connect(this->actionCopy, &QAction::triggered, this->plainTextEdit, &QPlainTextEdit::copy);
    connect(this->actionPaste, &QAction::triggered, this->plainTextEdit, &QPlainTextEdit::paste);
    connect(this->actionRedo, &QAction::triggered, this->plainTextEdit, &QPlainTextEdit::redo);
    connect(this->actionUndo, &QAction::triggered, this->plainTextEdit, &QPlainTextEdit::undo);
}

TFormDoc::~TFormDoc()
{
}

void TFormDoc::loadFromFile(QString &FileName)
{
    QFile file(FileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        this->plainTextEdit->clear();
        while (!stream.atEnd()) {
            QString str = stream.readLine();
            this->plainTextEdit->appendPlainText(str);
        }
        file.close();

        QFileInfo fileInfo(FileName);
        QString shortName{fileInfo.fileName()};
        this->setWindowTitle(shortName);
        emit titleChanged(shortName);
    }
}

void TFormDoc::onActionOpenTriggered()
{
    QString currentPath = QDir::currentPath();
    QString fileName
        = QFileDialog::getOpenFileName(this,
                                       "Open a file",
                                       currentPath,
                                       "C file(*.h *.cpp);;Txt(*.txt);;All files(*.*)");

    if (fileName.isEmpty()) {
        return;
    }
    loadFromFile(fileName);
}

void TFormDoc::onActionFontTriggered()
{
    QFont font{this->plainTextEdit->font()};
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    this->plainTextEdit->setFont(font);
}
