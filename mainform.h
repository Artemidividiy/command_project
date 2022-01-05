#ifndef MAINFORM_H
#define MAINFORM_H

#include <QDialog>
#include <QSignalMapper>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLineEdit>
#include <QPushButton>
#include <toolbar.h>
#include <inputpanel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE



class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();

private:
    Ui::MainForm *ui;
    ToolBar* toolBar;
    InputPanel* inputPanel;

private slots:
    void stdClicked(QString name);
    void addClicked() {};
    void d3Clicked() {};
    void polarClicked() {};
    void saveClicked() {};
    void closeClicked() {};
};
#endif // MAINFORM_H
