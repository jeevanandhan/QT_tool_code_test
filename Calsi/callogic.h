#ifndef CALLOGIC_H
#define CALLOGIC_H

#include <QObject>

// CalculatorLogic: Encapsulates arithmetic operations and error handling.
class CalculatorLogic : public QObject
{
    Q_OBJECT
public:
    explicit CalculatorLogic(QObject *parent = nullptr);

    // Performs addition
    double add(double a, double b) const;

    // Performs subtraction
    double sub(double a, double b) const;

    // Performs multiplication
    double mul(double a, double b) const;

    // Performs division; returns false if division by zero
    bool div(double a, double b, double &result, QString &errorMsg) const;
};



#endif // CALLOGIC_H
