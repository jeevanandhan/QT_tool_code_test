#include "callogic.h"

CalculatorLogic::CalculatorLogic(QObject *parent)
    : QObject(parent)
{
}

double CalculatorLogic::add(double a, double b) const
{
    return a + b;
}

double CalculatorLogic::sub(double a, double b) const
{
    return a - b;
}

double CalculatorLogic::mul(double a, double b) const
{
    return a * b;
}

bool CalculatorLogic::div(double a, double b, double &result, QString &errorMsg) const
{
    if (b == 0.0) {
        errorMsg = QStringLiteral("Error: Division by zero");
        return false;
    }
    result = a / b;
    return true;
}
