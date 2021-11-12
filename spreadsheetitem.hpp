#ifndef SPREADSHEETITEM_H
#define SPREADSHEETITEM_H

#include "spreadsheet.hpp"

#include <QTableWidgetItem>

class SpreadSheetItem : public QTableWidgetItem
{
public:
    using QTableWidgetItem::QTableWidgetItem;

    QTableWidgetItem *clone() const override;

    QVariant data(int role) const override;
    void setData(int role, const QVariant &value) override;
    QVariant display() const;

    inline QString formula() const
    {
        return QTableWidgetItem::data(Qt::DisplayRole).toString();
    }

    static QVariant computeFormula(const QString &formula,
                                   const QTableWidget *widget,
                                   const QTableWidgetItem *self = nullptr);

private:
    mutable bool isResolving = false;
};

#endif // SPREADSHEETITEM_H

