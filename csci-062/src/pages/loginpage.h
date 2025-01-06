#ifndef LOGINWINDOW_H_
#define LOGINWINDOW_H_

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

#include "../network/network.h"

QT_BEGIN_NAMESPACE
/* ******************* */

class LoginPageUi {
public:
  QGridLayout *centergrid;

  QLabel *login_label;
  QLineEdit *login_input;
  QPushButton *button;
  QLabel *errortext;

  QSpacerItem *spacer_left;
  QSpacerItem *spacer_top;
  QSpacerItem *spacer_right;
  QSpacerItem *spacer_bot;

  LoginPageUi(QWidget *loginpage);

private:
  void reset();
};

QT_END_NAMESPACE
/* ******************* */

class LoginPage : public QWidget {
  Q_OBJECT

public:
  LoginPage(Network *const network, QWidget *parent = nullptr);
  ~LoginPage();

  void login();

signals:
  void loggedin(int id);

private:
  LoginPageUi *ui;
  Network *const network;
};

#endif // LOGINWINDOW_H_
