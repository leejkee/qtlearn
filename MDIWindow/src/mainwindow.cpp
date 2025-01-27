#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mdiArea->setTabsClosable(true);
    ui->mdiArea->setTabsMovable(true);
    setCentralWidget(ui->mdiArea);
    setWindowState(Qt::WindowMaximized);
    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MDI Application", nullptr));
}

MainWindow::~MainWindow()
{
    delete ui;
}
