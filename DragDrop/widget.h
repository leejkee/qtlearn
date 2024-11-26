#ifndef WIDGET_H
#define WIDGET_H

#include <QAbstractItemView>
#include <QGroupBox>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QAbstractItemView *m_itemView = nullptr;

private:
    int getDropActionIndex(Qt::DropAction actionType);
    Qt::DropAction getDropActionType(int index);
    void refreshToUI(QGroupBox *curGroupBox);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    void on_radioButtonListSrc_clicked();
    void on_radioButtonListWidget_clicked();
    void on_radioButtonTreeWidget_clicked();
    void on_radioButtonTableWidget_clicked();
    void on_checkBoxAcceptDrops_clicked(bool checked);
    void on_checkBoxDragEnabled_clicked(bool checked);
    void on_comboBoxDragDropMode_currentIndexChanged(int index);
    void on_comboBoxDefaultDropAction_currentIndexChanged(int index);
};
#endif // WIDGET_H
