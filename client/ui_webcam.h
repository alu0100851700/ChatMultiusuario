/********************************************************************************
** Form generated from reading UI file 'webcam.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBCAM_H
#define UI_WEBCAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Webcam
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *CapturePushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Webcam)
    {
        if (Webcam->objectName().isEmpty())
            Webcam->setObjectName(QStringLiteral("Webcam"));
        Webcam->resize(400, 300);
        verticalLayout = new QVBoxLayout(Webcam);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        CapturePushButton = new QPushButton(Webcam);
        CapturePushButton->setObjectName(QStringLiteral("CapturePushButton"));

        verticalLayout->addWidget(CapturePushButton);

        scrollArea = new QScrollArea(Webcam);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 380, 224));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(Webcam);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Webcam);
        QObject::connect(buttonBox, SIGNAL(accepted()), Webcam, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Webcam, SLOT(reject()));

        QMetaObject::connectSlotsByName(Webcam);
    } // setupUi

    void retranslateUi(QDialog *Webcam)
    {
        Webcam->setWindowTitle(QApplication::translate("Webcam", "Dialog", 0));
        CapturePushButton->setText(QApplication::translate("Webcam", "Capture", 0));
    } // retranslateUi

};

namespace Ui {
    class Webcam: public Ui_Webcam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBCAM_H
