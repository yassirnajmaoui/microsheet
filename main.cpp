#include "spreadsheet.hpp"

#include <QApplication>
#include <QLayout>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    SpreadSheet sheet(10, 6);
    sheet.show();
    sheet.layout()->setSizeConstraint(QLayout::SetFixedSize);
    return app.exec();
}


