#include <pybind11/embed.h>
#include <pybind11/eval.h>

#include "spreadsheet.hpp"
#include <QApplication>
#include <QLayout>
#include <iostream>

namespace py = pybind11;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    SpreadSheet sheet(10, 6);
    sheet.show();
    sheet.layout()->setSizeConstraint(QLayout::SetFixedSize);

    int e = app.exec();
    return e;
}


