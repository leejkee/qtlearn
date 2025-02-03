#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tformdoc.h"
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_activeSubWindow(nullptr)
{
    ui->setupUi(this);
    ui->mdiArea->setTabsClosable(true);
    ui->mdiArea->setTabsMovable(true);
    setCentralWidget(ui->mdiArea);
    setWindowState(Qt::WindowMaximized);
    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MDI Application", nullptr));

    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionFontSettings->setEnabled(false);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onActionOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onActionSave);
    connect(ui->actionClose_all, &QAction::triggered, this, &MainWindow::onActionCloseAll);
    connect(ui->actionCut, &QAction::triggered, this, &MainWindow::onActionCut);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::onActionCopy);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::onActionPaste);
    connect(ui->actionFontSettings, &QAction::triggered, this, &MainWindow::onActionFontSettings);
    connect(ui->actionMDI, &QAction::triggered, this, &MainWindow::onActionMDIMode);
    connect(ui->actionCascading, &QAction::triggered, this, &MainWindow::onActionCasadingMode);
    connect(ui->actionTile, &QAction::triggered, this, &MainWindow::onActionTileMode);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::onActionQuit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onActionNew()
{
    TFormDoc *doc = new TFormDoc(this);
    ui->mdiArea->addSubWindow(doc);
    doc->show();
    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionFontSettings->setEnabled(true);
    doc->setAttribute(Qt::WA_DeleteOnClose);
}
void MainWindow::onActionOpen()
{
    /**
     * @brief Check if a new window is needed 
     */
    bool newWindowNeeded = false;
    TFormDoc *doc;
    if (ui->mdiArea->subWindowList().size() > 0) {
        doc = (TFormDoc *)ui->mdiArea->activeSubWindow()->widget();
        newWindowNeeded = doc->isFileOpened();
    }
    else {
        newWindowNeeded = true;
    }

    QString currentPath = QDir::currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", currentPath, "Text Files (*.txt);;All Files (*.*)");
    // If the user cancels the dialog, return
    if (fileName.isEmpty()) {
        return;
    }
    // If a new window is needed, create a new window
    if (newWindowNeeded) {
        doc = new TFormDoc(this);
        ui->mdiArea->addSubWindow(doc);
    }
    // Load the file
    doc->loadFormFile(fileName);
    doc->show();
    ui->actionCopy->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    ui->actionSave->setEnabled(true);
}
void MainWindow::onActionSave()
{ 
    TFormDoc *doc = (TFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    doc->saveToFile();

}
void MainWindow::onActionCloseAll()
{
    ui->mdiArea->closeAllSubWindows();
}
void MainWindow::onActionCut()
{
    TFormDoc *doc = (TFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    doc->textCut();
}
void MainWindow::onActionCopy()
{
    TFormDoc *doc = (TFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    doc->textCopy();
}
void MainWindow::onActionPaste()
{
    TFormDoc *doc = (TFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    doc->textPaste();
}
void MainWindow::onActionFontSettings()
{
    TFormDoc *doc = (TFormDoc *)ui->mdiArea->activeSubWindow()->widget();
    doc->setEditFont();
}
void MainWindow::onActionMDIMode(bool checked)
{
    if (checked) {
        ui->mdiArea->setViewMode(QMdiArea::ViewMode::TabbedView);
    }
    else {
        ui->mdiArea->setViewMode(QMdiArea::ViewMode::SubWindowView);
    }
    ui->mdiArea->setTabsClosable(true);
    ui->actionCascading->setEnabled(!checked);
    ui->actionTile->setEnabled(!checked);
}
void MainWindow::onActionCasadingMode()
{
    ui->mdiArea->cascadeSubWindows();
}
void MainWindow::onActionTileMode()
{
    ui->mdiArea->tileSubWindows();
}
void MainWindow::onActionQuit()
{
    // Close the application
    qApp->quit();
}

void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1) {
    if (ui->mdiArea->subWindowList().size() == 0) {
        ui->actionCopy->setEnabled(false);
        ui->actionCut->setEnabled(false);
        ui->actionPaste->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->actionFontSettings->setEnabled(false);
        ui->statusbar->clearMessage();
    }
    else {
        TFormDoc *doc = static_cast<TFormDoc *>(arg1->widget());
        ui->statusbar->showMessage(doc->currentFileName());

        // Set the active subwindow
        if (m_activeSubWindow != nullptr) {
            m_activeSubWindow->setStyleSheet(defaultStyle);
        }
        if (arg1 != nullptr) {
            arg1->setStyleSheet(activeStyle);
        }
        m_activeSubWindow = arg1;
    }
}

