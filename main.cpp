#include "SpreadSheet.hpp"
#include <QApplication>
#include <QLayout>
#include <iostream>

int main(int argc, char **argv)
{
    // TODO: Read where the config files are (standard location)
    // They will contain the init script (runcsv)

    QApplication app(argc, argv);
    SpreadSheet sheet(10, 6);
    sheet.show();
    sheet.layout()->setSizeConstraint(QLayout::SetFixedSize);

    int e = app.exec();
    return e;
}


