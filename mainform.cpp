#include "mainform.h"
#include "./ui_mainform.h"

#include <QOpenGLWidget>

MainForm::MainForm(QWidget *parent): QDialog(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);

    QSignalMapper *signalMapper = new QSignalMapper;
    toolBar = new ToolBar(signalMapper);
    inputPanel = new InputPanel();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QOpenGLWidget *glWidget = new QOpenGLWidget;
    glWidget->setMinimumSize(1000, 500);
    glWidget->setMaximumSize(2000, 700);

    rightLayout->addWidget(glWidget);
    rightLayout->addLayout(inputPanel->getLayout());
    mainLayout->addLayout(toolBar->getLayout());
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    connect(signalMapper, SIGNAL(mapped(QString)),this, SLOT(stdClicked(QString)));
}

void MainForm::stdClicked(QString name) {
//    QString str = toolBar->edit->text();
//       str.append(name);
//    toolBar->edit->setText(str);
}

MainForm::~MainForm()
{
    //delete signalMapper;
    delete toolBar;
    delete inputPanel;

    delete ui;
}
