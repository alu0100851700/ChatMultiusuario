/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *outputTextEdit;
    QLineEdit *inputTextEdit;
    QVBoxLayout *verticalLayout_2;
    QPushButton *connectButton;
    QPushButton *setupButton;
    QPushButton *exitButton;
    QPushButton *aboutButton;
    QSpacerItem *verticalSpacer;
    QPushButton *Avatar;

    void setupUi(QDialog *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(419, 259);
        horizontalLayout = new QHBoxLayout(MainWindow);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        outputTextEdit = new QPlainTextEdit(MainWindow);
        outputTextEdit->setObjectName(QStringLiteral("outputTextEdit"));
        outputTextEdit->setReadOnly(true);

        verticalLayout->addWidget(outputTextEdit);

        inputTextEdit = new QLineEdit(MainWindow);
        inputTextEdit->setObjectName(QStringLiteral("inputTextEdit"));

        verticalLayout->addWidget(inputTextEdit);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        connectButton = new QPushButton(MainWindow);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setMinimumSize(QSize(80, 0));
        connectButton->setAutoDefault(false);

        verticalLayout_2->addWidget(connectButton);

        setupButton = new QPushButton(MainWindow);
        setupButton->setObjectName(QStringLiteral("setupButton"));
        setupButton->setAutoDefault(false);

        verticalLayout_2->addWidget(setupButton);

        exitButton = new QPushButton(MainWindow);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setAutoDefault(false);

        verticalLayout_2->addWidget(exitButton);

        aboutButton = new QPushButton(MainWindow);
        aboutButton->setObjectName(QStringLiteral("aboutButton"));
        aboutButton->setAutoDefault(false);

        verticalLayout_2->addWidget(aboutButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        Avatar = new QPushButton(MainWindow);
        Avatar->setObjectName(QStringLiteral("Avatar"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Avatar->sizePolicy().hasHeightForWidth());
        Avatar->setSizePolicy(sizePolicy);
        Avatar->setLayoutDirection(Qt::LeftToRight);
        Avatar->setIconSize(QSize(16, 16));
        Avatar->setFlat(true);

        verticalLayout_2->addWidget(Avatar);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QDialog *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Talk GUI", 0));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", 0));
        setupButton->setText(QApplication::translate("MainWindow", "Configure...", 0));
        exitButton->setText(QApplication::translate("MainWindow", "Exit", 0));
        aboutButton->setText(QApplication::translate("MainWindow", "About", 0));
        Avatar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
