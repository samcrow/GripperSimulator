#ifndef JAVASCRIPTCONSOLE_H
#define JAVASCRIPTCONSOLE_H

#include <QWidget>
#include <QScriptEngine>

namespace Ui {
class JavaScriptConsole;
}

class JavaScriptConsole : public QWidget
{
    Q_OBJECT

public:
    explicit JavaScriptConsole(QWidget *parent = 0);
    ~JavaScriptConsole();

    void setScriptEngine(QScriptEngine* newEngine) {
        engine = newEngine;
    }

private slots:
    void on_entryField_returnPressed();

private:
    Ui::JavaScriptConsole *ui;

    QScriptEngine* engine = nullptr;

};

#endif // JAVASCRIPTCONSOLE_H
