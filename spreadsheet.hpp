#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QLineEdit;
class QToolBar;
class QTableWidgetItem;
class QTableWidget;
QT_END_NAMESPACE

class SpreadSheet : public QMainWindow {
    Q_OBJECT
public:
    SpreadSheet(int rows, int cols, QWidget* parent = nullptr);

public slots:
    void updateStatus(QTableWidgetItem* item);
    void updateColor(QTableWidgetItem* item);
    void updateLineEdit(QTableWidgetItem* item);
    void returnPressed();
    void selectColor();
    void selectFont();
    void clear();
    void showAbout();

protected:
    void setupContextMenu();
    void setupContents();

    void setupMenuBar();
    void createActions();

    void actionMath_helper(const QString& title, const QString& op);
    bool runInputDialog(const QString& title, const QString& c1Text,
        const QString& c2Text, const QString& opText,
        const QString& outText, QString* cell1, QString* cell2,
        QString* outCell);

private:
    QToolBar* toolBar;
    QAction* colorAction;
    QAction* fontAction;
    QAction* firstSeparator;
    QAction* secondSeparator;
    QAction* clearAction;
    QAction* aboutSpreadSheet;
    QAction* exitAction;

    QLabel* cellLabel;
    QTableWidget* table;
    QLineEdit* formulaInput;
};

#endif // SPREADSHEET_H
