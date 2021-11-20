#include "SpreadSheetDelegate.hpp"

#include <QtWidgets>

SpreadSheetDelegate::SpreadSheetDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

QWidget* SpreadSheetDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem&,
    const QModelIndex& index) const
{

    QLineEdit* editor = new QLineEdit(parent);

    // create a completer with the strings in the column as model
    QStringList allStrings;
    for (int i = 1; i < index.model()->rowCount(); i++) {
        QString strItem(index.model()
                            ->data(index.sibling(i, index.column()), Qt::EditRole)
                            .toString());

        if (!allStrings.contains(strItem))
            allStrings.append(strItem);
    }

    QCompleter* autoComplete = new QCompleter(allStrings);
    editor->setCompleter(autoComplete);
    connect(editor, &QLineEdit::editingFinished, this,
        &SpreadSheetDelegate::commitAndCloseEditor);
    return editor;
}

void SpreadSheetDelegate::commitAndCloseEditor()
{
    QLineEdit* editor = qobject_cast<QLineEdit*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void SpreadSheetDelegate::setEditorData(QWidget* editor,
    const QModelIndex& index) const
{
    QLineEdit* edit = qobject_cast<QLineEdit*>(editor);
    if (edit) {
        edit->setText(index.model()->data(index, Qt::EditRole).toString());
        return;
    } else {
        throw std::runtime_error("The current cell's editor is of the wrong type...");
    }
}

void SpreadSheetDelegate::setModelData(QWidget* editor,
    QAbstractItemModel* model,
    const QModelIndex& index) const
{
    QLineEdit* edit = qobject_cast<QLineEdit*>(editor);
    if (edit) {
        model->setData(index, edit->text());
        return;
    } else {
        throw std::runtime_error("The current cell's editor is of the wrong type...");
    }
}
