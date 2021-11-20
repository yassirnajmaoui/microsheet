#pragma once

#include "SpreadSheet.hpp"

#include <QTableWidgetItem>

class SpreadSheetItem : public QTableWidgetItem {
public:
    using QTableWidgetItem::QTableWidgetItem;

    QTableWidgetItem* clone() const override;

    QVariant data(int role) const override;
    void setData(int role, const QVariant& value) override;

    inline QVariant getRepr() const
    {
        return repr;
    }
    inline QString getSource() const
    {
        return source;
    }
    inline void setRepr(QString p_repr)
    {
        repr = p_repr;
    }
    inline void setSource(QString p_source)
    {
        source = p_source;
    }

private:
    QString repr;
    QString source;
};
