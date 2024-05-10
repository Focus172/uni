#include "socialnetworkwindow.h"
#include "postwidget.h"
#include "socialnetworkwindowui.h"
#include "util.h"
#include <cstdlib>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent), id(-1), user() {
  int ret = network.readUsers("users.txt");
  if (ret < 0) throw;
  ret = network.readPosts("posts.txt");
  if (ret < 0) throw;

  ui = new SocialNetworkWindowUi(this);

  ui->login_error->hide();
  ui->profile_friends_table->setColumnCount(1);

  ui->profile_home->hide();
  ui->profile_add->hide();

  auto p = new Post();
  auto post = new postwidget(p, &id, ui->loginpage);
  ui->gridLayout_2->addWidget(post);

  // auto func = []() {};
  // login ports
  QObject::connect(ui->login_button, &QPushButton::clicked, this,
                   &SocialNetworkWindow::login);

  // profile ports
  QObject::connect(ui->profile_home, &QPushButton::clicked, this,
                   &SocialNetworkWindow::gohome);
  QObject::connect(ui->profile_add, &QPushButton::clicked, this,
                   &SocialNetworkWindow::addfriend);
  QObject::connect(ui->profile_friends_table, &QTableWidget::cellClicked, this,
                   &SocialNetworkWindow::gofriend);
  QObject::connect(ui->profile_suggested_table, &QTableWidget::cellClicked,
                   this, &SocialNetworkWindow::addsuggestedfriend);
}

SocialNetworkWindow::~SocialNetworkWindow() { delete ui; }

void SocialNetworkWindow::login() {
  auto t = this->ui->login_input->text();
  std::string s = t.toStdString();

  int id = network.getId(s);
  if (id < 0) {
    this->ui->login_error->show();
    this->ui->login_error->setText(
        QString::asprintf("User %s doesn't exists.", s.c_str()));
  } else {
    this->id = id;
    SocialNetworkWindow::showprofile(id);
    ui->main_view->setCurrentIndex(1);
  }
};

void SocialNetworkWindow::showprofile(int newuser) {
  User *u = network.getUser(newuser);

  this->user.select(u, this->id);

  if (newuser == this->id) {
    // this user
    ui->profile_label->setText(QString("My Profile"));
    ui->profile_home->hide();

    ui->profile_add->hide();

    ui->profile_suggested_lable->show();
    ui->profile_suggested_table->show();
    int score;
    auto suggestions = this->network.suggestFriends(newuser, score);
    ui->profile_suggested_table->setRowCount(suggestions.size());

    int index = 0;
    for (auto f : suggestions) {
      User *uf = this->network.getUser(f);
      auto it = new QTableWidgetItem(QString::fromStdString(uf->getName()));
      ui->profile_suggested_table->setItem(index, 0, it);
      index += 1;
    }

  } else {
    // other user
    ui->profile_label->setText(
        QString::asprintf("%s's Profile", u->getName().c_str()));
    ui->profile_home->show();

    ui->profile_suggested_lable->hide();
    ui->profile_suggested_table->hide();

    auto me = this->network.getUser(this->id);
    auto myfr = me->getFriends();
    if (myfr.find(newuser) == myfr.end()) {
      ui->profile_add->show();
    } else {
      ui->profile_add->hide();
    }
  }

  ui->profile_friends_table->clear();

  auto fr = u->getFriends();
  ui->profile_friends_table->setRowCount(fr.size());

  int index = 0;
  for (auto f : fr) {
    // printf("thing %d\n", index);
    User *uf = this->network.getUser(f);

    // this call takes owevership of the object
    auto it = new QTableWidgetItem(QString::fromStdString(uf->getName()));
    ui->profile_friends_table->setItem(index, 0, it);
    index += 1;
  }

  ui->profile_post_list->setModel(user.model);
}

void SocialNetworkWindow::gohome() {
  SocialNetworkWindow::showprofile(this->id);
}

void SocialNetworkWindow::gofriend(int row, int col) {
  assert(col == 0);

  User *u = this->network.getUser(this->user.id);
  auto fr = u->getFriends();

  int show = -1;
  int index = 0;
  for (int f : fr) {
    if (index == row) {
      show = f;
      break;
    }
    index += 1;
  }
  if (show < 0)
    return;

  SocialNetworkWindow::showprofile(show);
  // printf("wassup poss %d, %d\n", row, col);
}

void SocialNetworkWindow::addsuggestedfriend(int row, int col) {
  User *u = this->network.getUser(this->user.id);
  thrownull(u);

  auto it = ui->profile_suggested_table->item(row, col);
  auto text = it->text();
  int s = this->network.getId(text.toStdString());

  User *f = this->network.getUser(s);
  thrownull(u);

  u->addFriend(s);
  f->addFriend(u->getId());

  this->network.writeUsers("users.txt");

  SocialNetworkWindow::showprofile(this->user.id);
}

void SocialNetworkWindow::addfriend() {
  User *u = this->network.getUser(this->id);
  thrownull(u);
  User *f = this->network.getUser(this->user.id);
  thrownull(f);

  u->addFriend(this->user.id);
  f->addFriend(this->id);

  this->network.writeUsers("users.txt");

  this->ui->profile_add->hide();

  SocialNetworkWindow::showprofile(this->user.id);
}
