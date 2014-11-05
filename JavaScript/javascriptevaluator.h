#ifndef JAVASCRIPTEVALUATOR_H
#define JAVASCRIPTEVALUATOR_H
#include "javascriptgripper.h"
#include <QScriptEngine>
#include <QScriptProgram>

class Simulation;

class JavaScriptEvaluator
{
public:
    JavaScriptEvaluator(Simulation& simulation);

    QScriptValue evaluate(const QString& program, const QString& fileName = QString(), int lineNumber = -1);

    void setScriptFile(const QString& path);
    QString scriptFile() const;

    bool hasScriptFile() const;
    QScriptValue executeScriptFile();

    QScriptEngine& engine();

private:

    QScriptEngine engine_;
    JavaScriptGripper gripper;

    QScriptProgram program;



    /// Allows other operations to proceed
    static void yield();
    /// Waits for at least the specified time, in milliseconds
    static void sleep(int milliseconds);

    static inline QScriptValue yield_js(QScriptContext*, QScriptEngine*) {
        yield();
        return QScriptValue::UndefinedValue;
    }
    static inline QScriptValue sleep_js(QScriptContext* context, QScriptEngine*) {
        sleep(context->argument(0).toInt32());
        return QScriptValue::UndefinedValue;
    }
};

#endif // JAVASCRIPTEVALUATOR_H
