#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include "post.h"
#include <QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

namespace ui {
class postwidget {
public:
  QHBoxLayout *div;
  QPushButton *like;
  QLabel *text;

  postwidget(QWidget *parent) {
    div = new QHBoxLayout();

    text = new QLabel(parent);
    text->setText(QString("hellow world"));
    div->addWidget(text);

    like = new QPushButton(parent);
    div->addWidget(like);
  }
};
}; // namespace ui

class postwidget : public QWidget {
  Q_OBJECT

public:
  explicit postwidget(Post *post, int *id, QWidget *parent = nullptr);
  ~postwidget();

private:
  void postliked();

  Post *post;

  int *id;
  ui::postwidget *ui;
};

#endif // POSTWIDGET_H
