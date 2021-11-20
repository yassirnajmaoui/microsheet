#include <QProcess>

PythonProcess::PythonProcess()
{
    // Initialize Python
    Py_Initialize();
}
PythonProcess::~PythonProcess()
{
    Py_Finalize();
}
