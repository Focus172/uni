#pragma once

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

#include "../network/post.h"

/* ***************************** */
namespace ui {
QT_BEGIN_NAMESPACE

class postwidget_t {
public:
  QWidget *root;
  QVBoxLayout *vbox;

  /// Root of the info bar
  QWidget *winfo;
  QHBoxLayout *hinfo;

  QLabel *author_lable;
  QLabel *date_lable;

  /// Root of the info bar
  QWidget *wbody;
  QHBoxLayout *hbody;

  QLabel *text_lable;
  QPushButton *like_button;

  postwidget_t(Post *p, QWidget *parent = nullptr) {
    root = new QWidget(parent);
    vbox = new QVBoxLayout(root);
    {
      winfo = new QWidget(root);
      hinfo = new QHBoxLayout(winfo);

      author_lable = new QLabel(winfo);
      author_lable->setText(QString::fromStdString(p->getAuthor()));
      hinfo->addWidget(author_lable);

      date_lable = new QLabel(winfo);
      date_lable->setText(QString::fromStdString(p->getHumanDate()));
      hinfo->addWidget(date_lable);

      vbox->addWidget(winfo);
    }

    {
      wbody = new QWidget(root);
      hbody = new QHBoxLayout(wbody);

      text_lable = new QLabel(wbody);
      hbody->addWidget(text_lable);
      like_button = new QPushButton(wbody);
      hinfo->addWidget(date_lable);

      hbody->addWidget(winfo);
    }
  }
};

QT_END_NAMESPACE
} // namespace ui
/* ***************************** */

class postwidget_t : public QWidget {
  Q_OBJECT

public:
  ui::postwidget_t *ui;
  Post *post;

  postwidget_t(Post *p, QWidget *parent = nullptr)
      : QWidget(parent), ui(new ui::postwidget_t(p)), post(p) {
    reset();

    // QObject::connect
  }

  ~postwidget_t() { delete ui; }

  void reset() {}
};
