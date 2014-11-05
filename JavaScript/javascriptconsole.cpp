#include "javascriptconsole.h"
#include "ui_javascriptconsole.h"
#include <QStringBuilder>
#include <QScrollBar>

JavaScriptConsole::JavaScriptConsole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JavaScriptConsole)
{
    ui->setupUi(this);
}

JavaScriptConsole::~JavaScriptConsole()
{
    delete ui;
}

void JavaScriptConsole::on_entryField_returnPressed()
{
    // Ignore empty fields
    if(ui->entryField->text().isEmpty()) {
        return;
    }

    // Evaluate, clear, print output
    const QString code = ui->entryField->text();
    const QScriptValue result = engine->evaluate(code);
    ui->entryField->clear();

    ui->historyView->moveCursor(QTextCursor::End);
    ui->historyView->textCursor().insertText("\n");
    ui->historyView->textCursor().insertText(code);
    ui->historyView->textCursor().insertText("\n");

    if(result.isError()) {
        ui->historyView->textCursor().insertHtml(QStringLiteral("=> <span style=\"color:red;\">") % result.toString() % QStringLiteral("</span>"));
    }
    else {
        ui->historyView->textCursor().insertHtml(QStringLiteral("=> ") % result.toString());
    }

    // Scroll to bottom
    ui->historyView->verticalScrollBar()->setValue(ui->historyView->verticalScrollBar()->maximum());
}
