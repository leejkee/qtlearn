#include "tcomboboxdelegate.h"
#include <QComboBox>



TComboBoxDelegate::TComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_isEditable(false)
{
}

QWidget *TComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *editor = new QComboBox(parent);
    editor->setEditable(m_isEditable);
    for (const QString &item : m_items) {
        editor->addItem(item);
    }
    return editor;
}
void TComboBoxDelegate::setItems(const QStringList &items, bool isEditable)
{
    m_items = items;
    m_isEditable = isEditable;
}

void TComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    comboBox->setCurrentText(str);
}

void TComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void TComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}