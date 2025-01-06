#include "loginpage.h"

/* ******************************* */
QT_BEGIN_NAMESPACE

LoginPageUi::LoginPageUi(QWidget *loginpage) {
  // LoginPage->setObjectName("LoginPage");

  centergrid = new QGridLayout(loginpage);

  // first two numbers are x y
  // so these items are order vertically in row 1

  /* ********** Login Items *********** */
  login_label = new QLabel(loginpage);
  centergrid->addWidget(login_label, 1, 1, 1, 1);

  login_input = new QLineEdit(loginpage);
  centergrid->addWidget(login_input, 2, 1, 1, 1);

  button = new QPushButton(loginpage);
  button->setEnabled(true);
  centergrid->addWidget(button, 3, 1, 1, 1);

  errortext = new QLabel(loginpage);
  centergrid->addWidget(errortext, 4, 1, 1, 1);
  /* ******* End Login Items ********** */

  /* ********** Spacers *********** */
  spacer_top =
      new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  centergrid->addItem(spacer_top, 0, 1, 1, 1);
  spacer_bot =
      new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  centergrid->addItem(spacer_bot, 5, 1, 1, 1);

  spacer_left =
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  centergrid->addItem(spacer_left, 4, 0, 1, 1);
  spacer_right =
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  centergrid->addItem(spacer_right, 4, 2, 1, 1);
  /* ************* End ************ */

  reset();
}

void LoginPageUi::reset() {
  login_label->setText(QCoreApplication::translate("SocialNetworkWindow",
                                                   "Enter Username", nullptr));
  login_input->setText(QString());
  button->setText(
      QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));

  // hide error
  errortext->hide();
}

QT_END_NAMESPACE
/* ******************************* */

LoginPage::LoginPage(Network *const n, QWidget *parent)
    : QWidget(parent), ui(new LoginPageUi(this)), network(n) {

  QObject::connect(ui->button, &QPushButton::clicked, this, &LoginPage::login);
}

LoginPage::~LoginPage() { delete ui; }

void LoginPage::login() {
  auto t = this->ui->login_input->text();
  std::string s = t.toStdString();

  int id = network->getId(s);
  if (id < 0) {
    ui->errortext->setText(QString::asprintf("No user: %s", s.c_str()));
    ui->errortext->show();
  } else {
    ui->errortext->hide();
    emit loggedin(id);
  }
}
