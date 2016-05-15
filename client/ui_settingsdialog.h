/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *serverAddressLabel;
    QLineEdit *serverAddress;
    QSpinBox *portBox;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *userNameEdit;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(210, 270, 166, 22));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        serverAddressLabel = new QLabel(SettingsDialog);
        serverAddressLabel->setObjectName(QStringLiteral("serverAddressLabel"));
        serverAddressLabel->setGeometry(QRect(10, 10, 96, 16));
        serverAddress = new QLineEdit(SettingsDialog);
        serverAddress->setObjectName(QStringLiteral("serverAddress"));
        serverAddress->setGeometry(QRect(112, 10, 261, 22));
        portBox = new QSpinBox(SettingsDialog);
        portBox->setObjectName(QStringLiteral("portBox"));
        portBox->setGeometry(QRect(112, 38, 70, 23));
        portBox->setWrapping(false);
        portBox->setFrame(true);
        portBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        portBox->setMinimum(1024);
        portBox->setMaximum(65525);
        portBox->setValue(6000);
        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 40, 29, 16));
        label_3 = new QLabel(SettingsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 70, 81, 20));
        userNameEdit = new QLineEdit(SettingsDialog);
        userNameEdit->setObjectName(QStringLiteral("userNameEdit"));
        userNameEdit->setGeometry(QRect(112, 67, 261, 22));

        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Configure", 0));
        serverAddressLabel->setText(QApplication::translate("SettingsDialog", "Server Address: ", 0));
        serverAddress->setText(QApplication::translate("SettingsDialog", "127.0.0.1", 0));
        label_2->setText(QApplication::translate("SettingsDialog", "Port:", 0));
        label_3->setText(QApplication::translate("SettingsDialog", "User Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
