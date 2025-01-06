#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QMainWindow>
#include <QTableWidget>
#include <QtCore/QVariant>
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
#include <stack>

QT_BEGIN_NAMESPACE

class ProfilePageUi {
public:
  QVBoxLayout *vbox;

  /// Root widget of the tab bar
  QWidget *wtab;
  /// Layout of the tab bar
  QHBoxLayout *htab;
  /// Widgets on the tab bar
  QPushButton *makepost;
  QPushButton *addFriend;
  QPushButton *returnHome;

  /// Root widget of the friends display
  QWidget *wfri;
  /// Layout of the friends
  QHBoxLayout *hfri;

  /// Widgets of the firends display
  QLabel *personProfile;
  QTableWidget *userFriends;
  QLabel *friendSuggestionsLabel;
  QTableWidget *friendSuggestions;

  QLabel *recentPosts;
  QTableWidget *postsTable;

  ProfilePageUi(QWidget *);

  ~ProfilePageUi() {
    delete personProfile;
    delete userFriends;
  }

  void reset();
};

QT_END_NAMESPACE

class ProfilePage : public QWidget {
  Q_OBJECT

public:
  // pre: none
  // post: creates the window for the ui
  ProfilePage(Network *network, QWidget *parent = nullptr);

  // pre: none
  // post: deletes the window
  ~ProfilePage();

  // MOTIFICATION MEMBER FUNCTIONS

  /// Function called when a user logs in. This display is not active before
  /// this function is called.
  void login(User *u);

  // pre: none
  // post: goes to home profile page
  void goToHome();

  // pre: none
  // post: goes to friend profile page
  void goToFriend(int row, int column);

  // pre: none
  // post: adds a person as a friend
  void addAsFriend();

  // pre: none
  // post: goes to the profile page of the friend suggestion
  void goToFriendSuggestion(int row, int column);

  // pre: none
  // post: likes the post, does nothing if post is already liked by user
  void likePost(int row, int messageId, int userId);

signals:
  void gomakepost();

private:
  ProfilePageUi *ui;
  Network *n;
  User *initialUser;
  User *mostRecentUser;
};

#endif // PROFILEPAGE_H
