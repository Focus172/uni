#ifndef FEEDPAGE_H
#define FEEDPAGE_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

#include "../network/network.h"
#include "../widgets/post.hpp"

/* 8888888888888 88888888888888888888888888888 888888888 */
QT_BEGIN_NAMESPACE

class FeedPageUi {
public:
  QVBoxLayout *vbox;

  std::vector<postwidget_t *> posts;

  FeedPageUi(QWidget *FeedPage) {
    vbox = new QVBoxLayout(FeedPage);
    posts = {};
  }

  ~FeedPageUi() {
    delete vbox;
    // TODO: delete widgets
  }

  void add_post(postwidget_t *pw) {
    vbox->addWidget(pw);
    posts.push_back(pw);
  }

  void reset();
};

QT_END_NAMESPACE
/* 888888888 88888888888888888888888888888 888888888 */

class FeedPage : public QWidget {
  Q_OBJECT

public:
  FeedPage(Network *network, QWidget *parent = nullptr)
      : QWidget(parent), ui(new FeedPageUi(this)), n(network) {}

  void show_user(User *u) {
    for (auto f : u->getFriends()) {
      User *fr = n->getUser(f);
      if (fr == nullptr)
        continue;

      for (auto post : fr->getPosts()) {
        auto pw = new postwidget_t(post, this);
        ui->add_post(pw);
      }
    }
  }

  // qt makes this for you
  // ~FeedPage();

signals:

private:
  FeedPageUi *ui;
  Network *n;
};

#endif // FEEDPAGE_H
