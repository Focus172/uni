#ifndef POSTWIDGET_H
#define POSTWIDGET_H

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include "post.h"

namespace ui {
  class postwidget {
  public:
    QHBoxLayout *div;
    QPushButton *like;
    QLabel      *text;

    postwidget(QWidget *parent) {
      div = new QHBoxLayout();


      text = new QLabel(parent);
      text->setText(QString("hellow worl"));
      div->addWidget(text);

      like = new QPushButton(parent);
      div->addWidget(like);

    }
  };
};


class postwidget : public QWidget
{
    Q_OBJECT

public:
    explicit postwidget(Post *post, int *id, QWidget *parent = nullptr);
    ~postwidget();

// signals:
//     void liked(int id);

private:
    void postliked();

    Post *post;

    int *id;
    ui::postwidget *ui;
};

#endif // POSTWIDGET_H
