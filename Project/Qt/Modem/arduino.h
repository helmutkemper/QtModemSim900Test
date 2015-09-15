#ifndef ARDUINO_H
#define ARDUINO_H

#include <QDialog>

namespace Ui {
class Arduino;
}

class Arduino : public QDialog
{
  Q_OBJECT

public:
  explicit Arduino(QWidget *parent = 0);
  ~Arduino();

private:
  Ui::Arduino *ui;
};

#endif // ARDUINO_H
