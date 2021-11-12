#include "spreadsheetitem.hpp"

QTableWidgetItem* SpreadSheetItem::clone() const
{
    SpreadSheetItem* item = new SpreadSheetItem;
    *item = *this;
    return item;
}

QVariant SpreadSheetItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::StatusTipRole)
        return formula();

    if (role == Qt::DisplayRole)
        return display();

    const QString t = display().toString();

    if (role == Qt::ForegroundRole) {
        bool isNumber = false;
        const int number = t.toInt(&isNumber);
        QColor color = Qt::black;
        if (isNumber)
            color = (number < 0) ? Qt::red : Qt::blue;
        return QVariant::fromValue(color);
    }

    if (role == Qt::TextAlignmentRole)
        if (!t.isEmpty() && (t.at(0).isNumber() || t.at(0) == '-'))
            return int(Qt::AlignRight | Qt::AlignVCenter);

    return QTableWidgetItem::data(role);
}

void SpreadSheetItem::setData(int role, const QVariant& value)
{
    QTableWidgetItem::setData(role, value);
    if (tableWidget())
        tableWidget()->viewport()->update();
}

QVariant SpreadSheetItem::display() const
{
    // avoid circular dependencies
    if (isResolving)
        return QVariant();

    isResolving = true;
    QVariant result = computeFormula(formula(), tableWidget(), this);
    isResolving = false;
    return result;
}

QVariant SpreadSheetItem::computeFormula(const QString& formula,
    const QTableWidget* widget,
    const QTableWidgetItem* self)
{
    // check if the string is actually a formula or not
    // Something here...
    return formula;
}
