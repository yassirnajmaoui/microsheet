#include "spreadsheet.hpp"
#include "spreadsheetdelegate.hpp"
#include "spreadsheetitem.hpp"

#include <QtWidgets>

SpreadSheet::SpreadSheet(int rows, int cols, QWidget* parent)
    : QMainWindow(parent)
    , toolBar(new QToolBar(this))
    , cellLabel(new QLabel(toolBar))
    , table(new QTableWidget(rows, cols, this))
    , formulaInput(new QLineEdit(this))
{
    addToolBar(toolBar);

    cellLabel->setMinimumSize(80, 0);

    toolBar->addWidget(cellLabel);
    toolBar->addWidget(formulaInput);

    table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    for (int c = 0; c < cols; ++c) {
        QString character(QChar('A' + c));
        table->setHorizontalHeaderItem(c, new QTableWidgetItem(character));
    }

    table->setItemPrototype(table->item(rows - 1, cols - 1));
    table->setItemDelegate(new SpreadSheetDelegate());

    createActions();
    updateColor(nullptr);
    setupMenuBar();
    setupContents();
    setupContextMenu();
    setCentralWidget(table);

    statusBar();
    connect(table, &QTableWidget::currentItemChanged, this, &SpreadSheet::updateStatus);
    connect(table, &QTableWidget::currentItemChanged, this, &SpreadSheet::updateColor);
    connect(table, &QTableWidget::currentItemChanged, this, &SpreadSheet::updateLineEdit);
    connect(table, &QTableWidget::itemChanged, this, &SpreadSheet::updateStatus);
    connect(formulaInput, &QLineEdit::returnPressed, this, &SpreadSheet::returnPressed);
    connect(table, &QTableWidget::itemChanged, this, &SpreadSheet::updateLineEdit);

    setWindowTitle(tr("Spreadsheet"));
}

void SpreadSheet::createActions()
{
    fontAction = new QAction(tr("Font..."), this);
    fontAction->setShortcut(Qt::CTRL | Qt::Key_F);
    connect(fontAction, &QAction::triggered, this, &SpreadSheet::selectFont);

    colorAction = new QAction(QPixmap(16, 16), tr("Background &Color..."), this);
    connect(colorAction, &QAction::triggered, this, &SpreadSheet::selectColor);

    clearAction = new QAction(tr("Clear"), this);
    clearAction->setShortcut(Qt::Key_Delete);
    connect(clearAction, &QAction::triggered, this, &SpreadSheet::clear);

    aboutSpreadSheet = new QAction(tr("About Spreadsheet"), this);
    connect(aboutSpreadSheet, &QAction::triggered, this, &SpreadSheet::showAbout);

    exitAction = new QAction(tr("E&xit"), this);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    firstSeparator = new QAction(this);
    firstSeparator->setSeparator(true);

    secondSeparator = new QAction(this);
    secondSeparator->setSeparator(true);
}

void SpreadSheet::setupMenuBar()
{
    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAction);

    QMenu* cellMenu = menuBar()->addMenu(tr("&Cell"));
    cellMenu->addAction(colorAction);
    cellMenu->addAction(fontAction);

    menuBar()->addSeparator();

    QMenu* aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutSpreadSheet);
}

void SpreadSheet::updateStatus(QTableWidgetItem* item)
{
    if (item && item == table->currentItem()) {
        statusBar()->showMessage(item->data(Qt::DisplayRole).toString(), 1000); // Show current selection range here too
        cellLabel->setText(
            tr("Cell: (%1,%2)")
                .arg(table->row(item))
                .arg(table->column(item)));
    }
}

void SpreadSheet::updateColor(QTableWidgetItem* item)
{
    // Think about this later...
    QPixmap pix(16, 16);
    QColor col;
    if (item)
        col = item->background().color();
    if (!col.isValid())
        col = palette().base().color();

    QPainter pt(&pix);
    pt.fillRect(0, 0, 16, 16, col);

    QColor lighter = col.lighter();
    pt.setPen(lighter);
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    pt.drawPolyline(lightFrame, 3);

    pt.setPen(col.darker());
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
    pt.drawPolyline(darkFrame, 3);

    pt.end();

    colorAction->setIcon(pix);
}

void SpreadSheet::updateLineEdit(QTableWidgetItem* item)
{
    if (item != table->currentItem())
        return;
    if (item)
        formulaInput->setText(item->data(Qt::EditRole).toString());
    else
        formulaInput->clear();
}

void SpreadSheet::returnPressed()
{
    QString text = formulaInput->text();
    int row = table->currentRow();
    int col = table->currentColumn();
    QTableWidgetItem* item = table->item(row, col);
    if (!item)
        table->setItem(row, col, new SpreadSheetItem(text));
    else
        item->setData(Qt::EditRole, text);
    table->viewport()->update();
}

void SpreadSheet::selectColor()
{
    QTableWidgetItem* item = table->currentItem();
    QColor col = item ? item->background().color() : table->palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    const QList<QTableWidgetItem*> selected = table->selectedItems();
    if (selected.isEmpty())
        return;

    for (QTableWidgetItem* i : selected) {
        if (i)
            i->setBackground(col);
    }

    updateColor(table->currentItem());
}

void SpreadSheet::selectFont()
{
    const QList<QTableWidgetItem*> selected = table->selectedItems();
    if (selected.isEmpty())
        return;

    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);

    if (!ok)
        return;
    for (QTableWidgetItem* i : selected) {
        if (i)
            i->setFont(fnt);
    }
}

void SpreadSheet::clear()
{
    const QList<QTableWidgetItem*> selectedItems = table->selectedItems();
    for (QTableWidgetItem* i : selectedItems)
        i->setText(QString());
}

void SpreadSheet::setupContextMenu()
{
    addAction(firstSeparator);
    addAction(colorAction);
    addAction(fontAction);
    addAction(secondSeparator);
    addAction(clearAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void SpreadSheet::setupContents()
{
    //QBrush titleBackground(Qt::lightGray);
    //QFont titleFont = table->font();
    //titleFont.setBold(true);

    table->setItem(5, 3, new SpreadSheetItem("some content here"));
    //table->item(9, 5)->setBackground(Qt::lightGray);
}

void SpreadSheet::showAbout()
{
    const char* htmlText = "<HTML>"
                           "Some html text here... I can even put words in <b>bold</b>"
                           "</HTML>";
    QMessageBox::about(this, "About Spreadsheet", htmlText);
}