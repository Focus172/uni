#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QAbstractItemView>
#include <QMainWindow>
#include <QStringListModel>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "network/network.h"
#include "pages/feedpage.h"
#include "pages/loginpage.h"
#include "pages/makepostpage.h"
#include "pages/profilepage.h"

QT_BEGIN_NAMESPACE

class SocialNetworkWindowUi {
public:
  QWidget *centralwidget;
  QGridLayout *grid;

  QStackedWidget *viewstack;
  LoginPage *loginpage;
  ProfilePage *profilepage;
  MakepostPage *makepostpage;
  FeedPage *feedpage;

  QMenuBar *menubar;
  QStatusBar *statusbar;

  SocialNetworkWindowUi(QMainWindow *, Network *);
};

QT_END_NAMESPACE

/* *********************************************************************** */

class SelectedUser {
public:
  SelectedUser() : id(-1), model(new QStringListModel) {}
  ~SelectedUser() { delete model; }

  void select(User *user, int uid) {
    // assert(u != nullptr);
    auto strs = QStringList();

    for (auto post : user->getPosts()) {
      // if the current user is the displayed user OR the post is public
      if (uid == user->getId() || post->getIsPublic()) {
        strs.append(QString::fromStdString(post->toString()));
      }
    }

    this->id = user->getId();
    delete this->model;
    this->model = new QStringListModel(strs);
  }

  int id;
  QStringListModel *model;
};

struct CurrentUser {
public:
  /// id of the logged in user
  int id;
};

class SocialNetworkWindow : public QMainWindow {
  Q_OBJECT

public:
  SocialNetworkWindow();
  ~SocialNetworkWindow();

  void showprofile(int user);
  void show_makepost();

  void add_post(Post *p);

private:
  SocialNetworkWindowUi *ui;
  Network network;

  CurrentUser curr;
  SelectedUser user;
};

#endif // SOCIALNETWORKWINDOW_H
