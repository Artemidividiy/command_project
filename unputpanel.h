#ifndef INPUTPANEL_H
#define INPUTPANEL_H

#include <QWidget>
#include <QSignalMapper>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLineEdit>
#include <QPushButton>

class BtnDescr {
public:
    QString text;
    int id;
    BtnDescr() { id=0; };
    BtnDescr(const QString &str, int i): text(str), id(i) {};
};

class InputPanel: public QWidget
{
    Q_OBJECT
public:
    InputPanel();
    ~InputPanel();

    void initVector();
    void setBtns();
    QVBoxLayout* getLayout() { return layout; };


private:
    QVector<BtnDescr> btnVector;
    QLineEdit *edit = nullptr;
    QSignalMapper *mapper = nullptr;
    QGridLayout *gridLayout = nullptr;
    QHBoxLayout *bccKeysLayout = nullptr;
    QHBoxLayout *mainKeysLayout = nullptr;
    QVBoxLayout *layout = nullptr;

private slots:
    void clicked(QString name) {
        //QString sId;
        //sId.setNum(name);
        QString str = edit->text ();
        if( str == "0" )
            str = name;
        else
            str.append( name );
        edit->setText(str);
    }
};

#endif // INPUTPANEL_H
