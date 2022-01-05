#include "toolbar.h"

ToolBar::ToolBar(QSignalMapper *sMapper) {
    mapper = sMapper;
    arrButtons = new QPushButton[7];
    //edit = new QLineEdit;
    //edit->setMaximumSize(300, 35);
    //edit->setMinimumSize(250, 30);
    layout = new QVBoxLayout;
    vSpacer = new QSpacerItem(5, 600);

//    QFont font;
//    font.setFamily(QStringLiteral("Nyala"));
//    font.setPointSize(20);
//    font.setBold(true);
//    font.setItalic(true);
//    font.setWeight(50);
//    edit->setFont(font);
    //layout->addWidget(edit);
    customButtons();

};

void ToolBar::customButtons() {
    if (arrButtons) {

        arrButtons[0].setText("Add function");
        arrButtons[6].setText("Close");

        QFont fnt = arrButtons->font();
        fnt.setPointSize( fnt.pointSize() + 4);

        for (int i = 0; i < buttonsAm; i++) {
            arrButtons[i].setMaximumSize(300, 50);
            arrButtons[i].setMinimumSize(250, 40);
            arrButtons[i].setFont(fnt);

            //QFont font("")
            //arrButtons[i].setFont()

            if (i == 5)
                layout->addSpacerItem(vSpacer);
            layout->addWidget(&(arrButtons[i]));
        }
        connect(&(arrButtons[0]), SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(&(arrButtons[0]), arrButtons[0].text());

    }
}

QVBoxLayout* ToolBar::getLayout() {
    return layout;
}

ToolBar::~ToolBar() {
    delete[] arrButtons;
    delete layout;
    delete vSpacer;
}
