#include "javascriptevaluator.h"
#include <QFile>
#include <QDialog>
#include <stdexcept>
#include <QCoreApplication>

JavaScriptEvaluator::JavaScriptEvaluator(Simulation &simulation) :
    gripper(simulation)
{
    // Set up global gripper object
    const QScriptValue gripperValue = engine_.newQObject(&this->gripper);
    engine_.globalObject().setProperty("gripper", gripperValue);

    // Set up global functions
    const QScriptValue yieldValue = engine_.newFunction(&JavaScriptEvaluator::yield_js);
    const QScriptValue sleepValue = engine_.newFunction(&JavaScriptEvaluator::sleep_js, 1);

    engine_.globalObject().setProperty("yield", yieldValue);
    engine_.globalObject().setProperty("sleep", sleepValue);
}

void JavaScriptEvaluator::setScriptFile(const QString& path) {
    // Read the file
    QFile file(path);
    bool success = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!success) {
        throw std::runtime_error("Could not open script file");
    }

    program = QScriptProgram(file.readAll(), file.fileName());
}
bool JavaScriptEvaluator::hasScriptFile() const {
    return !program.isNull();
}
QString JavaScriptEvaluator::scriptFile() const {
    return program.fileName();
}

QScriptValue JavaScriptEvaluator::executeScriptFile() {
    return engine_.evaluate(program);
}

QScriptValue JavaScriptEvaluator::evaluate(const QString &program, const QString &fileName, int lineNumber) {
    return engine_.evaluate(program, fileName, lineNumber);
}

QScriptEngine& JavaScriptEvaluator::engine() {
    return engine_;
}


void JavaScriptEvaluator::yield() {
    QCoreApplication::processEvents();
}

void JavaScriptEvaluator::sleep(int milliseconds) {
    QCoreApplication::processEvents(QEventLoop::WaitForMoreEvents, milliseconds);
}
