#ifndef DTMF_H
#define DTMF_H

#include <QDialog>

namespace Ui {
class Dtmf;
}

class Dtmf : public QDialog
{
  Q_OBJECT

public:
  explicit Dtmf(QWidget *parent = 0);
  ~Dtmf();

private slots:
  void on_pb1_clicked();

  void on_pb2_clicked();

  void on_pb3_clicked();

  void on_pb4_clicked();

  void on_pb5_clicked();

  void on_pb6_clicked();

  void on_pb7_clicked();

  void on_pb8_clicked();

  void on_pb9_clicked();

  void on_pbA_clicked();

  void on_pb0_clicked();

  void on_pbB_clicked();

private:
  Ui::Dtmf *ui;
};

#endif // DTMF_H
