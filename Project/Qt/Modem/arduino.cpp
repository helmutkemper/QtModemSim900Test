#include "arduino.h"
#include "ui_arduino.h"

Arduino::Arduino(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Arduino)
{
  ui->setupUi(this);
}

Arduino::~Arduino()
{
  delete ui;
}
