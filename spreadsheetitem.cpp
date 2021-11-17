#include "spreadsheetitem.hpp"
#include <iostream>

QTableWidgetItem* SpreadSheetItem::clone() const
{
    SpreadSheetItem* item = new SpreadSheetItem;
    *item = *this;
    return item;
}

QVariant SpreadSheetItem::data(int role) const
{
    if (role == Qt::EditRole || role == Qt::StatusTipRole)
        return getSource();

    if (role == Qt::DisplayRole)
        return getRepr();

    const QString t = getRepr().toString();

    // These should be more sophisticated at some point...
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

    return QTableWidgetItem::data(role);// All of the other roles
}

void SpreadSheetItem::setData(int role, const QVariant& value)
{
    QTableWidgetItem::setData(role, value);
    if (role == Qt::EditRole) {
        setSource(value.toString());
    } else if (role == Qt::DisplayRole) {
        setRepr(value.toString());
    }
    if (tableWidget())
        tableWidget()->viewport()->update();
}
