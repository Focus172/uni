#ifndef MAKEPOSTPAGE_H
#define MAKEPOSTPAGE_H

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
#include <QtWidgets/QTextBrowser>

#include "../network/post.h"

QT_BEGIN_NAMESPACE

class MakepostPageUi {
public:
  QGridLayout *grid;

  // QLineEdit *title;
  QTextEdit *maininput;
  QPushButton *submit;

  MakepostPageUi(QWidget *MakepostPage) {
    grid = new QGridLayout(MakepostPage);

    // title = new QLineEdit(MakepostPage);
    // grid->addWidget(title, 0, 0);

    maininput = new QTextEdit(MakepostPage);
    grid->addWidget(maininput, 1, 0);

    submit = new QPushButton(MakepostPage);
    grid->addWidget(submit, 2, 0);

    reset();
  }

  void reset() {
    // title->setText("The Title");
    maininput->setText("Whats on your mind?");
    submit->setText("Submit");
  }
};

QT_END_NAMESPACE

class MakepostPage: public QWidget {
  Q_OBJECT

public:
  MakepostPage(QWidget *parent = nullptr) : QWidget(parent), ui(new MakepostPageUi(this)), user(-1) {
    QObject::connect(ui->submit, &QPushButton::clicked, this, &MakepostPage::finish_post);
  }
  ~MakepostPage() { delete ui; }

  void load_page(int id) {
    ui->reset();
    user = id;
  }

  void finish_post() {
    if (user < 0) {
        printf("no user id\n");
        return;
    }
    // QString t = ui->title->text();
    QString i = ui->maininput->toPlainText();

    int id = rand();
    Post *p = new Post(id, user, i.toStdString(), 0);

    emit submit_post(p);
  }

signals:
  void submit_post(Post *post);

private:
  MakepostPageUi *ui;
  int user;
};

#endif // MAKEPOSTPAGE_H
