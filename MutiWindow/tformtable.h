#ifndef TFORMTABLE_H
#define TFORMTABLE_H

#include <QMainWindow>
#include "tdialogheaders.h"

class QStandardItemModel;
class QItemSelectionModel;
class QTableView;

class TFormTable : public QMainWindow
{
    Q_OBJECT
private:
    QAction *actionTableCellSize;
    QAction *actionTableHeaderSetting;
    QAction *actionExit;
    QToolBar *toolBar;

    TDialogHeaders *dialogSetHeaders = nullptr;
    QStandardItemModel *m_model;
    QItemSelectionModel *m_selection;
    QTableView *tableView;

public:
    explicit TFormTable(QWidget *parent = nullptr);

private slots:
    void onActionTableCellSize();
    void onActionTableHeaderSetting();

signals:
};

#endif // TFORMTABLE_H
