#include "javascriptconsole.h"
#include "ui_javascriptconsole.h"
#include <QStringBuilder>
#include <QScrollBar>
#include <QDebug>

JavaScriptConsole::JavaScriptConsole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JavaScriptConsole),
    consoleInterface(*this)
{
    ui->setupUi(this);
}

JavaScriptConsole::~JavaScriptConsole()
{
    delete ui;
}

void JavaScriptConsole::on_entryField_returnPressed()
{
    if(!engine) {
        return;
    }
    // Ignore empty fields
    if(ui->entryField->text().isEmpty()) {
        return;
    }

    // Clear input, disable input, print input to console, evaluate, print output, enable input
    const QString code = ui->entryField->text();

    ui->entryField->clear();
    ui->entryField->setDisabled(true);

    ui->historyView->moveCursor(QTextCursor::End);
    ui->historyView->textCursor().insertText("\n");
    ui->historyView->textCursor().insertText(code);
    ui->historyView->textCursor().insertText("\n");


    const QScriptValue result = engine->evaluate(code);

    if(result.isError()) {
        ui->historyView->textCursor().insertHtml(QStringLiteral("=> <span style=\"color:red;\">") % result.toString() % QStringLiteral("</span>\n"));
    }
    else {
        ui->historyView->textCursor().insertHtml(QStringLiteral("=> ") % result.toString() % '\n');
    }

    // Scroll to bottom
    ui->historyView->verticalScrollBar()->setValue(ui->historyView->verticalScrollBar()->maximum());

    ui->entryField->setDisabled(false);
    ui->entryField->setFocus();
}

void JavaScriptConsole::setScriptEngine(QScriptEngine* newEngine) {
    engine = newEngine;
    // Set up the engine's console object

    engine->globalObject().setProperty("console", engine->newQObject(&this->consoleInterface));
}

void JavaScriptConsole::log(const QString &text) {
    ui->historyView->moveCursor(QTextCursor::End);
    ui->historyView->textCursor().insertText(text % '\n');
}

void ConsoleInterface::log(const QString& text) {
    console.log(text);
}
