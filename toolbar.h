#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QSignalMapper>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLineEdit>
#include <QPushButton>

class ToolBar: public QWidget {
    Q_OBJECT

private:
    int buttonsAm = 7;
    QPushButton* arrButtons = nullptr;

    QVBoxLayout* layout = nullptr;
    QSpacerItem* vSpacer = nullptr;
    QSignalMapper* mapper = nullptr;
    void customButtons();

public:
    ToolBar(QSignalMapper*);
    ~ToolBar();

    QLineEdit* edit = nullptr;
//    QLineEdit* getEdit() {return edit;}
//    QPushButton* getButtons() {
//        return arrButtons;
//    }
    QVBoxLayout* getLayout();

public slots:

};

#endif // TOOLBAR_H