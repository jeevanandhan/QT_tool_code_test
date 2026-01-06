#include "calsidlg.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <functional>

CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QWidget(parent), logic(this)
{
    // Labels
    num1Label = new QLabel(tr("NUM1:"), this);
    num2Label = new QLabel(tr("NUM2:"), this);
    resultLabel = new QLabel(tr("Result:"), this);

    // LineEdits
    num1Edit = new QLineEdit(this);
    num2Edit = new QLineEdit(this);
    resultEdit = new QLineEdit(this);
    resultEdit->setReadOnly(true);

    // Validator for input fields (accepts double values)
    validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    num1Edit->setValidator(validator);
    num2Edit->setValidator(validator);

    // Buttons
    addButton = new QPushButton(tr("Add"), this);
    subButton = new QPushButton(tr("Sub"), this);
    mulButton = new QPushButton(tr("Mul"), this);
    divButton = new QPushButton(tr("Div"), this);

    // Layout
    auto *grid = new QGridLayout;
    grid->addWidget(num1Label, 0, 0);
    grid->addWidget(num1Edit, 0, 1);
    grid->addWidget(num2Label, 1, 0);
    grid->addWidget(num2Edit, 1, 1);
    grid->addWidget(resultLabel, 2, 0);
    grid->addWidget(resultEdit, 2, 1);

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(subButton);
    buttonLayout->addWidget(mulButton);
    buttonLayout->addWidget(divButton);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(grid);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Qt Calculator"));

    // Connect buttons to slots
    connect(addButton, &QPushButton::clicked, this, &CalculatorWidget::onAddClicked);
    connect(subButton, &QPushButton::clicked, this, &CalculatorWidget::onSubClicked);
    connect(mulButton, &QPushButton::clicked, this, &CalculatorWidget::onMulClicked);
    connect(divButton, &QPushButton::clicked, this, &CalculatorWidget::onDivClicked);
}

bool CalculatorWidget::getInputValues(double &num1, double &num2)
{
    // Ensure both fields are not empty and valid
    QString num1Text = num1Edit->text().trimmed();
    QString num2Text = num2Edit->text().trimmed();

    int pos = 0;
    if (validator->validate(num1Text, pos) != QValidator::Acceptable ||
        validator->validate(num2Text, pos) != QValidator::Acceptable) {
        resultEdit->setText("Error: Invalid input");
        return false;
    }

    num1 = num1Text.toDouble();
    num2 = num2Text.toDouble();
    return true;
}

void CalculatorWidget::performOperation(std::function<double(double, double)> op)
{
    double num1, num2;
    if (!getInputValues(num1, num2))
        return;

    double result = op(num1, num2);
    resultEdit->setText(QString::number(result));
}

void CalculatorWidget::onAddClicked()
{
    performOperation([this](double a, double b){ return logic.add(a, b); });
}

void CalculatorWidget::onSubClicked()
{
    performOperation([this](double a, double b){ return logic.sub(a, b); });
}

void CalculatorWidget::onMulClicked()
{
    performOperation([this](double a, double b){ return logic.mul(a, b); });
}

void CalculatorWidget::onDivClicked()
{
    double num1, num2;
    if (!getInputValues(num1, num2))
        return;

    double result;
    QString errorMsg;
    if (!logic.div(num1, num2, result, errorMsg)) {
        resultEdit->setText(errorMsg);
    } else {
        resultEdit->setText(QString::number(result));
    }
}
