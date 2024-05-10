/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

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

QT_BEGIN_NAMESPACE

class SocialNetworkWindowUi
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *profile_add;
    QPushButton *profile_home;
    QStackedWidget *main_view;
    QWidget *loginpage;
    QGridLayout *gridLayout_2;
    QSpacerItem *login_space_top;
    QLabel *login_label;
    QLineEdit *login_input;
    QPushButton *login_button;
    QSpacerItem *login_space_left;
    QLabel *login_error;
    QSpacerItem *login_space_right;
    QSpacerItem *login_space_bot;
    QWidget *profilepage;
    QGridLayout *gridLayout_3;
    QHBoxLayout *name_div;
    QSpacerItem *profile_name_pad_left;
    QLabel *profile_label;
    QSpacerItem *profile_name_pad_right;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableWidget *profile_friends_table;
    QLabel *profile_suggested_lable;
    QTableWidget *profile_suggested_table;
    QListView *profile_post_list;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    SocialNetworkWindowUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        profile_add = new QPushButton(centralwidget);
        profile_add->setObjectName("profile_add");

        horizontalLayout_2->addWidget(profile_add);

        profile_home = new QPushButton(centralwidget);
        profile_home->setObjectName("profile_home");

        horizontalLayout_2->addWidget(profile_home);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        main_view = new QStackedWidget(centralwidget);
        main_view->setObjectName("main_view");
        loginpage = new QWidget();
        loginpage->setObjectName("loginpage");
        gridLayout_2 = new QGridLayout(loginpage);
        gridLayout_2->setObjectName("gridLayout_2");
        login_space_top = new QSpacerItem(20, 193, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(login_space_top, 0, 1, 1, 1);

        login_label = new QLabel(loginpage);
        login_label->setObjectName("login_label");

        gridLayout_2->addWidget(login_label, 1, 1, 1, 1);

        login_input = new QLineEdit(loginpage);
        login_input->setObjectName("login_input");

        gridLayout_2->addWidget(login_input, 2, 1, 1, 1);

        login_button = new QPushButton(loginpage);
        login_button->setObjectName("login_button");
        login_button->setEnabled(true);

        gridLayout_2->addWidget(login_button, 3, 1, 1, 1);

        login_space_left = new QSpacerItem(212, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(login_space_left, 4, 0, 1, 1);

        login_error = new QLabel(loginpage);
        login_error->setObjectName("login_error");

        gridLayout_2->addWidget(login_error, 4, 1, 1, 1);

        login_space_right = new QSpacerItem(212, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(login_space_right, 4, 2, 1, 1);

        login_space_bot = new QSpacerItem(20, 193, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(login_space_bot, 5, 1, 1, 1);

        main_view->addWidget(loginpage);
        profilepage = new QWidget();
        profilepage->setObjectName("profilepage");
        gridLayout_3 = new QGridLayout(profilepage);
        gridLayout_3->setObjectName("gridLayout_3");
        name_div = new QHBoxLayout();
        name_div->setObjectName("name_div");
        profile_name_pad_left = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        name_div->addItem(profile_name_pad_left);

        profile_label = new QLabel(profilepage);
        profile_label->setObjectName("profile_label");

        name_div->addWidget(profile_label);

        profile_name_pad_right = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        name_div->addItem(profile_name_pad_right);


        gridLayout_3->addLayout(name_div, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(profilepage);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        profile_friends_table = new QTableWidget(profilepage);
        if (profile_friends_table->columnCount() < 1)
            profile_friends_table->setColumnCount(1);
        if (profile_friends_table->rowCount() < 12)
            profile_friends_table->setRowCount(12);
        profile_friends_table->setObjectName("profile_friends_table");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(profile_friends_table->sizePolicy().hasHeightForWidth());
        profile_friends_table->setSizePolicy(sizePolicy);
        profile_friends_table->setAcceptDrops(false);
        profile_friends_table->setAutoFillBackground(true);
        profile_friends_table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        profile_friends_table->setAutoScrollMargin(16);
        profile_friends_table->setProperty("showDropIndicator", QVariant(true));
        profile_friends_table->setDragDropOverwriteMode(false);
        profile_friends_table->setShowGrid(true);
        profile_friends_table->setGridStyle(Qt::SolidLine);
        profile_friends_table->setWordWrap(false);
        profile_friends_table->setRowCount(12);
        profile_friends_table->setColumnCount(1);

        verticalLayout->addWidget(profile_friends_table);

        profile_suggested_lable = new QLabel(profilepage);
        profile_suggested_lable->setObjectName("profile_suggested_lable");

        verticalLayout->addWidget(profile_suggested_lable);

        profile_suggested_table = new QTableWidget(profilepage);
        if (profile_suggested_table->columnCount() < 1)
            profile_suggested_table->setColumnCount(1);
        if (profile_suggested_table->rowCount() < 5)
            profile_suggested_table->setRowCount(5);
        profile_suggested_table->setObjectName("profile_suggested_table");
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(profile_suggested_table->sizePolicy().hasHeightForWidth());
        profile_suggested_table->setSizePolicy(sizePolicy1);
        profile_suggested_table->setLineWidth(1);
        profile_suggested_table->setRowCount(5);
        profile_suggested_table->setColumnCount(1);

        verticalLayout->addWidget(profile_suggested_table);


        horizontalLayout->addLayout(verticalLayout);

        profile_post_list = new QListView(profilepage);
        profile_post_list->setObjectName("profile_post_list");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(profile_post_list->sizePolicy().hasHeightForWidth());
        profile_post_list->setSizePolicy(sizePolicy2);
        QFont font;
        font.setPointSize(23);
        profile_post_list->setFont(font);
        profile_post_list->setWordWrap(true);

        horizontalLayout->addWidget(profile_post_list);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);

        main_view->addWidget(profilepage);

        gridLayout->addWidget(main_view, 1, 0, 1, 1);

        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 19));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "ClickGameWindow", nullptr));
        label->setText(QCoreApplication::translate("SocialNetworkWindow", "Social Network", nullptr));
        profile_add->setText(QCoreApplication::translate("SocialNetworkWindow", "Add", nullptr));
        profile_home->setText(QCoreApplication::translate("SocialNetworkWindow", "Home", nullptr));
        login_label->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter Username", nullptr));
        login_input->setText(QString());
        login_button->setText(QCoreApplication::translate("SocialNetworkWindow", "Login", nullptr));
        login_error->setText(QCoreApplication::translate("SocialNetworkWindow", "User {name} doesn't exists.", nullptr));
        profile_label->setText(QCoreApplication::translate("SocialNetworkWindow", "My Profile", nullptr));
        label_2->setText(QCoreApplication::translate("SocialNetworkWindow", "Friends", nullptr));
        profile_suggested_lable->setText(QCoreApplication::translate("SocialNetworkWindow", "Suggested Friends", nullptr));
    } // retranslateUi

};

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
