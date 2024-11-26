#include "widget.h"
#include <QKeyEvent>
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_itemView = ui->listWidgetSource;
    const QStringList listActionDrop = {"CopyAction", "MoveAction", "LinkAction", "IgnoreAction"};
    const QStringList listDragDropMode = {"NoDragDrop",
                                          "DragOnly",
                                          "DropOnly",
                                          "DragDrop",
                                          "InternalMove"};

    // disconnect(ui->comboBoxDragDropMode,
    //            &QComboBox::currentIndexChanged,
    //            this,
    //            &Widget::on_comboBoxDragDropMode_currentIndexChanged);
    // disconnect(ui->comboBoxDefaultDropAction,
    //            &QComboBox::currentIndexChanged,
    //            this,
    //            &Widget::on_comboBoxDefaultDropAction_currentIndexChanged);
    ui->comboBoxDragDropMode->addItems(listDragDropMode);
    ui->comboBoxDefaultDropAction->addItems(listActionDrop);
    // connect(ui->comboBoxDragDropMode,
    //         &QComboBox::currentIndexChanged,
    //         this,
    //         &Widget::on_comboBoxDragDropMode_currentIndexChanged);
    // connect(ui->comboBoxDefaultDropAction,
    //         &QComboBox::currentIndexChanged,
    //         this,
    //         &Widget::on_comboBoxDefaultDropAction_currentIndexChanged);

    ui->radioButtonListSrc->setChecked(true);
    ui->listWidgetSource->installEventFilter(this);
    ui->listWidgetWidget->installEventFilter(this);
    ui->treeWidget->installEventFilter(this);
    ui->tableWidget->installEventFilter(this);

    ui->listWidgetSource->setAcceptDrops(true);
    ui->listWidgetSource->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidgetSource->setDragEnabled(true);
    ui->listWidgetSource->setDefaultDropAction(Qt::CopyAction);

    ui->treeWidget->setAcceptDrops(true);
    ui->treeWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->setDefaultDropAction(Qt::CopyAction);

    ui->listWidgetWidget->setAcceptDrops(true);
    ui->listWidgetWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidgetWidget->setDragEnabled(true);
    ui->listWidgetWidget->setDefaultDropAction(Qt::CopyAction);

    ui->tableWidget->setAcceptDrops(true);
    ui->tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->tableWidget->setDragEnabled(true);
    ui->tableWidget->setDefaultDropAction(Qt::CopyAction);
    refreshToUI(ui->groupBoxListSrc);
    // qDebug() << "DragDropMode: "
    //          << (QAbstractItemView::DragDropMode) ui->comboBoxDragDropMode->currentIndex();
}

Widget::~Widget()
{
    delete ui;
}

int Widget::getDropActionIndex(Qt::DropAction actionType)
{
    switch (actionType) {
    case Qt::CopyAction:
        return 0;
    case Qt::MoveAction:
        return 1;
    case Qt::LinkAction:
        return 2;
    case Qt::IgnoreAction:
        return 3;
    default:
        return 0;
    }
}
Qt::DropAction Widget::getDropActionType(int index)
{
    switch (index) {
    case 0:
        return Qt::CopyAction;
    case 1:
        return Qt::MoveAction;
    case 2:
        return Qt::LinkAction;
    case 3:
        return Qt::IgnoreAction;
    default:
        return Qt::CopyAction;
    }
}

void Widget::refreshToUI(QGroupBox *curGroupBox)
{
    ui->checkBoxAcceptDrops->setChecked(m_itemView->acceptDrops());
    ui->checkBoxDragEnabled->setChecked(m_itemView->dragEnabled());
    // ui->comboBoxDragDropMode->setCurrentIndex((int) m_itemView->dragDropMode());
    int index = m_itemView->dragDropMode();
    ui->comboBoxDragDropMode->setCurrentIndex(index);
    index = getDropActionIndex(m_itemView->defaultDropAction());
    ui->comboBoxDefaultDropAction->setCurrentIndex(index);
    // ui->comboBoxDefaultDropAction->setCurrentIndex(
    //     getDropActionIndex(m_itemView->defaultDropAction()));

    QFont font = ui->groupBoxListSrc->font();
    font.setBold(false);
    ui->groupBoxListSrc->setFont(font);
    ui->groupBoxListWidget->setFont(font);
    ui->groupBoxTreeWidget->setFont(font);
    ui->groupBoxTableWidget->setFont(font);
    font.setBold(true);
    curGroupBox->setFont(font);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != QEvent::KeyPress) {
        return QWidget::eventFilter(watched, event);
    }
    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
    if (keyEvent->key() != Qt::Key_Delete) {
        return QWidget::eventFilter(watched, event);
    }

    if (watched == ui->listWidgetSource) {
        QListWidgetItem *item = ui->listWidgetSource->takeItem(ui->listWidgetSource->currentRow());
        delete item;
    } else if (watched == ui->listWidgetWidget) {
        QListWidgetItem *item = ui->listWidgetWidget->takeItem(ui->listWidgetWidget->currentRow());
        delete item;
    } else if (watched == ui->treeWidget) {
        QTreeWidgetItem *currentItem = ui->treeWidget->currentItem();
        if (currentItem->parent() != nullptr) {
            QTreeWidgetItem *parentItem = currentItem->parent();
            // Removes the given item indicated by child. The removed item will not be deleted.
            parentItem->removeChild(currentItem);
        } else {
            int index = ui->treeWidget->indexOfTopLevelItem(currentItem);
            // Removes the top-level item at the given index in the tree and returns it, otherwise returns nullptr;
            ui->treeWidget->takeTopLevelItem(index);
        }
        delete currentItem;
    } else if (watched == ui->tableWidget) {
        QTableWidgetItem *item = ui->tableWidget->takeItem(ui->tableWidget->currentRow(),
                                                           ui->tableWidget->currentColumn());
        delete item;
    }
    return true;
}

// Get the pointer of the clicked button
// Update the settings UI based on the properties of the selected widget
// start
void Widget::on_radioButtonListSrc_clicked()
{
    m_itemView = ui->listWidgetSource;
    refreshToUI(ui->groupBoxListSrc);
}

void Widget::on_radioButtonListWidget_clicked()
{
    m_itemView = ui->listWidgetWidget;
    refreshToUI(ui->groupBoxListWidget);
}

void Widget::on_radioButtonTreeWidget_clicked()
{
    m_itemView = ui->treeWidget;
    refreshToUI(ui->groupBoxTreeWidget);
}

void Widget::on_radioButtonTableWidget_clicked()
{
    m_itemView = ui->tableWidget;
    refreshToUI(ui->groupBoxTableWidget);
}
// end

// config for the widgets
void Widget::on_checkBoxAcceptDrops_clicked(bool checked)
{
    m_itemView->setAcceptDrops(checked);
}

void Widget::on_checkBoxDragEnabled_clicked(bool checked)
{
    m_itemView->setDragEnabled(checked);
}

// set the property of widgets based on the currentIndex of comboBox
void Widget::on_comboBoxDragDropMode_currentIndexChanged(int index)
{
    QAbstractItemView::DragDropMode mode = (QAbstractItemView::DragDropMode) index;
    m_itemView->setDragDropMode(mode);
}

void Widget::on_comboBoxDefaultDropAction_currentIndexChanged(int index)
{
    Qt::DropAction actionType = getDropActionType(index);
    m_itemView->setDefaultDropAction(actionType);
}
