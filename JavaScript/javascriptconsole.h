#ifndef JAVASCRIPTCONSOLE_H
#define JAVASCRIPTCONSOLE_H

#include <QObject>
#include <QWidget>
#include <QScriptEngine>

class JavaScriptConsole;

class ConsoleInterface : public QObject
{
    Q_OBJECT
public:
    ConsoleInterface(JavaScriptConsole& console) : console(console) {}
public slots:
    void log(const QString &text);
private:
    JavaScriptConsole& console;
};

namespace Ui {
class JavaScriptConsole;
}

class JavaScriptConsole : public QWidget
{
    Q_OBJECT

public:
    explicit JavaScriptConsole(QWidget *parent = 0);
    ~JavaScriptConsole();

    void setScriptEngine(QScriptEngine* newEngine);

    /// Prints something to the console
    void log(const QString& text);

private slots:
    void on_entryField_returnPressed();

private:
    Ui::JavaScriptConsole *ui;

    QScriptEngine* engine = nullptr;

    ConsoleInterface consoleInterface;

};

#endif // JAVASCRIPTCONSOLE_H
