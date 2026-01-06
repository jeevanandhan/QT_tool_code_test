#ifndef CALSIDLG_H
#define CALSIDLG_H

#include <QDialog>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDoubleValidator>
#include "callogic.h"

// CalculatorWidget: Handles UI and connects to CalculatorLogic.
class CalculatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorWidget(QWidget *parent = nullptr);

private slots:
    void onAddClicked();
    void onSubClicked();
    void onMulClicked();
    void onDivClicked();

private:
    void performOperation(std::function<double(double, double)> op);
    bool getInputValues(double &num1, double &num2);

    QLineEdit *num1Edit;
    QLineEdit *num2Edit;
    QLineEdit *resultEdit;
    QLabel *num1Label;
    QLabel *num2Label;
    QLabel *resultLabel;
    QPushButton *addButton;
    QPushButton *subButton;
    QPushButton *mulButton;
    QPushButton *divButton;
    QDoubleValidator *validator;
    CalculatorLogic logic;
};

#endif // CALSIDLG_H
