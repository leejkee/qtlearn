#include "mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include "./ui_mainwindow.h"
#include "tformdoc.h"
#include "tformtable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowMaximized);
    connect(ui->tabWidget,
            &QTabWidget::tabCloseRequested,
            ui->tabWidget,
            [uiWidget = ui->tabWidget](int index) {
                auto tab = uiWidget->widget(index);
                if (tab) {
                    uiWidget->removeTab(index);
                    tab->close();
                }
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// @brief MainWindow::paintEvent() override the function paintEvent() to display the picture on the background
/// @param e
///
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,
                       ui->toolBar->height(),
                       this->width(),
                       this->height() - ui->toolBar->height() - ui->statusBar->height(),
                       QPixmap(":/background/icon/DarkSouls.png"));
    e->accept();
}

void MainWindow::do_changeTabTitle(QString title)
{
    int index = ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index, title);
}

void MainWindow::on_actionEmbeddedWigget_triggered()
{
    TFormDoc *formDoc = new TFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int curIndex = ui->tabWidget->addTab(formDoc,
                                         QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(curIndex);
    ui->tabWidget->setVisible(true);
    connect(formDoc, &TFormDoc::titleChanged, this, &MainWindow::do_changeTabTitle);
}

void MainWindow::on_actionSeparateWidget_triggered()
{
    TFormDoc *formDoc = new TFormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("The window based on QWidget, no parent, delete on close");
    formDoc->setWindowFlag(Qt::Window, true);
    formDoc->setWindowOpacity(0.8);
    formDoc->show();
}

void MainWindow::on_actionEmbeddedMainWIndow_triggered()
{
    TFormTable *formTable = new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int curIndex = ui->tabWidget->addTab(formTable,
                                         QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(curIndex);
    ui->tabWidget->setVisible(true);
}

void MainWindow::on_actionSeparateMainWindow_triggered()
{
    TFormTable *formTable = new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("The window based on QMainWindow");
    formTable->statusBar();
    formTable->show();
}
