#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_tableColumnCount(4)
    , m_tableRowCount(6)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSet_RC_triggered() {}

void MainWindow::on_actionSet_header_triggered() {}

void MainWindow::on_actionLocate_cell_triggered() {}
