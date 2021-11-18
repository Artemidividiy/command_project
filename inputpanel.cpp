#include "inputpanel.h"

const int TEN = 109;
const int SQR = 108;
const int SQRT = 107;
const int EXP = 106;
const int LG = 105;
const int LN = 104;
const int COS = 103;
const int SIN = 102;
const int LOG = 101;
const int POW = 100;
const int DIV = 10;
const int MUL = 11;
const int MINUS = 12;
const int PLUS = 13;
const int INVERSE = 15;
const int DOT = 16;
const int EQ = 21;
const int BKSP = 30;
const int CLR = 31;
const int CLR_ALL = 32;
const int GRID_KEYS = 20;
const int X = 110;

void InputPanel::initVector() {
    btnVector.push_back(BtnDescr("lg", LG));
    btnVector.push_back(BtnDescr("7", 7));
    btnVector.push_back(BtnDescr("8", 8));
    btnVector.push_back(BtnDescr("9", 9));
    btnVector.push_back(BtnDescr("/", DIV));
    btnVector.push_back(BtnDescr("^", POW));
    btnVector.push_back(BtnDescr("ln", LN));
    btnVector.push_back(BtnDescr("4", 4));
    btnVector.push_back(BtnDescr("5", 5));
    btnVector.push_back(BtnDescr("6", 6));
    btnVector.push_back(BtnDescr("×", MUL));
    btnVector.push_back(BtnDescr("10^", TEN));
    //btnVector.push_back(BtnDescr("sin", SIN));
    btnVector.push_back(BtnDescr("log", LOG));
    btnVector.push_back(BtnDescr("1", 1));
    btnVector.push_back(BtnDescr("2", 2));
    btnVector.push_back(BtnDescr("3", 3));
    btnVector.push_back(BtnDescr("-", MINUS));
    btnVector.push_back(BtnDescr("√", SQRT));
    //btnVector.push_back(BtnDescr("cos", COS));
    btnVector.push_back(BtnDescr("e^", EXP));
    btnVector.push_back(BtnDescr("0", 0));
    btnVector.push_back(BtnDescr("-/+", INVERSE));
    btnVector.push_back(BtnDescr(".", DOT));
    btnVector.push_back(BtnDescr("+", PLUS));
    btnVector.push_back(BtnDescr("X", X));
    btnVector.push_back(BtnDescr("<-", BKSP));
    btnVector.push_back(BtnDescr("Clear" ,CLR));
    btnVector.push_back(BtnDescr("Clear all", CLR_ALL));
    btnVector.push_back(BtnDescr("GO", EQ));
}

void InputPanel::setBtns() {
    for (int i = 0; i < btnVector.size(); i++) {
        QPushButton *button = new QPushButton(btnVector[i].text);

        button->setMaximumHeight(50);
        button->setMinimumHeight(40);
        if (i == btnVector.size() - 1)
            button->setMinimumHeight(150);
        button->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Expanding);

        QFont fnt = button->font();
        fnt.setPointSize( fnt.pointSize() + 4);
        button->setFont(fnt);

        connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(button, btnVector[i].text);

        if (i<GRID_KEYS + 4)
            gridLayout->addWidget(button, i / 6, i % 6);
        else
            if( i < GRID_KEYS + 7)
                bccKeysLayout->addWidget(button);
            else {
                button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                mainKeysLayout->addLayout(gridLayout);
                mainKeysLayout->addWidget(button);
            }
    }
}

InputPanel::InputPanel() {
    //QPushButton *q = ui->pushButton_3;
    //q->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding);
    //initNum();
    initVector();

    edit = new QLineEdit(this);
    //m_pLineEdit->setReadOnly ( true );
    mapper = new QSignalMapper(this);
    gridLayout = new QGridLayout();
    bccKeysLayout = new QHBoxLayout();
    mainKeysLayout = new QHBoxLayout();
    layout = new QVBoxLayout();

    setBtns();

    edit->setMinimumSize(200, 50);
    QFont font;
    font.setFamily(QStringLiteral("Nyala"));
    font.setPointSize(18);
    font.setBold(true);
    font.setItalic(false);
    font.setWeight(50);
    edit->setFont(font);

    connect(mapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString)));
    layout->addWidget(edit);
    layout->addLayout(bccKeysLayout);
    layout->addLayout(mainKeysLayout);
}

InputPanel::~InputPanel() {
    delete edit;
    delete mapper;
    delete gridLayout;
    delete bccKeysLayout;
    delete mainKeysLayout;
    delete layout;
}