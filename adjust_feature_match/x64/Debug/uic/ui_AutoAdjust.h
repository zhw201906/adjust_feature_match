/********************************************************************************
** Form generated from reading UI file 'AutoAdjust.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOADJUST_H
#define UI_AUTOADJUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoAdjustClass
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *box_serial_id;
    QLabel *label_2;
    QComboBox *box_baud;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbtn_ascll;
    QRadioButton *rbtn_hex;
    QPushButton *btn_open_serial;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_picture;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *label_fea1;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *label_fea2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_10;
    QLabel *label_fea3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_12;
    QLabel *label_fea4;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *cbox_feature;
    QLabel *label_fea_id;
    QPushButton *btn_learn_feature;
    QLabel *label_3;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout;
    QPushButton *btn_open_camera;
    QPushButton *btn_catch_pic;
    QPushButton *btn_ctrl_status;
    QPushButton *btn_stop;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QTextBrowser *text_log;
    QPushButton *btn_catch_log;
    QPushButton *btn_clear_log;

    void setupUi(QWidget *AutoAdjustClass)
    {
        if (AutoAdjustClass->objectName().isEmpty())
            AutoAdjustClass->setObjectName(QStringLiteral("AutoAdjustClass"));
        AutoAdjustClass->resize(1413, 914);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AutoAdjustClass->sizePolicy().hasHeightForWidth());
        AutoAdjustClass->setSizePolicy(sizePolicy);
        AutoAdjustClass->setMinimumSize(QSize(1413, 914));
        AutoAdjustClass->setMaximumSize(QSize(1413, 914));
        gridLayout_3 = new QGridLayout(AutoAdjustClass);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(AutoAdjustClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(340, 180));
        groupBox->setMaximumSize(QSize(400, 180));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        box_serial_id = new QComboBox(groupBox);
        box_serial_id->setObjectName(QStringLiteral("box_serial_id"));

        gridLayout->addWidget(box_serial_id, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        box_baud = new QComboBox(groupBox);
        box_baud->setObjectName(QStringLiteral("box_baud"));

        gridLayout->addWidget(box_baud, 1, 1, 1, 1);

        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rbtn_ascll = new QRadioButton(widget);
        rbtn_ascll->setObjectName(QStringLiteral("rbtn_ascll"));

        horizontalLayout->addWidget(rbtn_ascll);

        rbtn_hex = new QRadioButton(widget);
        rbtn_hex->setObjectName(QStringLiteral("rbtn_hex"));

        horizontalLayout->addWidget(rbtn_hex);


        gridLayout->addWidget(widget, 2, 0, 1, 2);

        btn_open_serial = new QPushButton(groupBox);
        btn_open_serial->setObjectName(QStringLiteral("btn_open_serial"));

        gridLayout->addWidget(btn_open_serial, 3, 0, 1, 2);


        gridLayout_3->addWidget(groupBox, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(AutoAdjustClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_picture = new QLabel(groupBox_2);
        label_picture->setObjectName(QStringLiteral("label_picture"));
        label_picture->setMinimumSize(QSize(960, 720));
        label_picture->setMaximumSize(QSize(960, 720));
        label_picture->setStyleSheet(QStringLiteral(""));
        label_picture->setFrameShape(QFrame::Box);
        label_picture->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_picture);

        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(75, 30));
        label_5->setMaximumSize(QSize(75, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_5);

        label_fea1 = new QLabel(groupBox_5);
        label_fea1->setObjectName(QStringLiteral("label_fea1"));
        label_fea1->setMinimumSize(QSize(120, 30));
        label_fea1->setMaximumSize(QSize(120, 30));
        label_fea1->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(label_fea1);

        horizontalSpacer = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(75, 30));
        label_7->setMaximumSize(QSize(75, 30));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_7);

        label_fea2 = new QLabel(groupBox_5);
        label_fea2->setObjectName(QStringLiteral("label_fea2"));
        label_fea2->setMinimumSize(QSize(120, 30));
        label_fea2->setMaximumSize(QSize(120, 30));
        label_fea2->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(label_fea2);

        horizontalSpacer_2 = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(75, 30));
        label_10->setMaximumSize(QSize(75, 30));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_10);

        label_fea3 = new QLabel(groupBox_5);
        label_fea3->setObjectName(QStringLiteral("label_fea3"));
        label_fea3->setMinimumSize(QSize(120, 30));
        label_fea3->setMaximumSize(QSize(120, 30));
        label_fea3->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(label_fea3);

        horizontalSpacer_3 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(75, 30));
        label_12->setMaximumSize(QSize(75, 30));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_12);

        label_fea4 = new QLabel(groupBox_5);
        label_fea4->setObjectName(QStringLiteral("label_fea4"));
        label_fea4->setMinimumSize(QSize(120, 30));
        label_fea4->setMaximumSize(QSize(120, 30));
        label_fea4->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(label_fea4);


        verticalLayout_2->addWidget(groupBox_5);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 4, 1);

        groupBox_6 = new QGroupBox(AutoAdjustClass);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(80, 35));
        label_4->setMaximumSize(QSize(80, 35));
        QFont font1;
        font1.setFamily(QStringLiteral("04b_21"));
        font1.setPointSize(11);
        label_4->setFont(font1);

        horizontalLayout_2->addWidget(label_4);

        cbox_feature = new QComboBox(groupBox_6);
        cbox_feature->setObjectName(QStringLiteral("cbox_feature"));
        cbox_feature->setMinimumSize(QSize(170, 25));
        cbox_feature->setMaximumSize(QSize(170, 25));

        horizontalLayout_2->addWidget(cbox_feature);


        gridLayout_4->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        label_fea_id = new QLabel(groupBox_6);
        label_fea_id->setObjectName(QStringLiteral("label_fea_id"));
        label_fea_id->setMinimumSize(QSize(30, 25));
        label_fea_id->setMaximumSize(QSize(30, 25));
        label_fea_id->setFrameShape(QFrame::Box);
        label_fea_id->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_fea_id, 0, 1, 1, 1);

        btn_learn_feature = new QPushButton(groupBox_6);
        btn_learn_feature->setObjectName(QStringLiteral("btn_learn_feature"));
        btn_learn_feature->setMinimumSize(QSize(255, 35));
        btn_learn_feature->setMaximumSize(QSize(250, 35));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        btn_learn_feature->setFont(font2);

        gridLayout_4->addWidget(btn_learn_feature, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 2, 1, 1, 1);

        label_3 = new QLabel(AutoAdjustClass);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font3.setPointSize(24);
        font3.setBold(true);
        font3.setWeight(75);
        label_3->setFont(font3);
        label_3->setStyleSheet(QStringLiteral(""));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(AutoAdjustClass);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        formLayout = new QFormLayout(groupBox_4);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        btn_open_camera = new QPushButton(groupBox_4);
        btn_open_camera->setObjectName(QStringLiteral("btn_open_camera"));
        btn_open_camera->setMinimumSize(QSize(180, 35));
        btn_open_camera->setMaximumSize(QSize(180, 35));

        formLayout->setWidget(0, QFormLayout::LabelRole, btn_open_camera);

        btn_catch_pic = new QPushButton(groupBox_4);
        btn_catch_pic->setObjectName(QStringLiteral("btn_catch_pic"));
        btn_catch_pic->setMinimumSize(QSize(180, 35));
        btn_catch_pic->setMaximumSize(QSize(180, 35));

        formLayout->setWidget(0, QFormLayout::FieldRole, btn_catch_pic);

        btn_ctrl_status = new QPushButton(groupBox_4);
        btn_ctrl_status->setObjectName(QStringLiteral("btn_ctrl_status"));
        btn_ctrl_status->setMinimumSize(QSize(180, 35));
        btn_ctrl_status->setMaximumSize(QSize(180, 35));

        formLayout->setWidget(1, QFormLayout::LabelRole, btn_ctrl_status);

        btn_stop = new QPushButton(groupBox_4);
        btn_stop->setObjectName(QStringLiteral("btn_stop"));
        btn_stop->setMinimumSize(QSize(180, 35));
        btn_stop->setMaximumSize(QSize(180, 35));

        formLayout->setWidget(1, QFormLayout::FieldRole, btn_stop);


        gridLayout_3->addWidget(groupBox_4, 3, 1, 1, 1);

        groupBox_3 = new QGroupBox(AutoAdjustClass);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        text_log = new QTextBrowser(groupBox_3);
        text_log->setObjectName(QStringLiteral("text_log"));

        gridLayout_2->addWidget(text_log, 0, 0, 1, 2);

        btn_catch_log = new QPushButton(groupBox_3);
        btn_catch_log->setObjectName(QStringLiteral("btn_catch_log"));

        gridLayout_2->addWidget(btn_catch_log, 1, 0, 1, 1);

        btn_clear_log = new QPushButton(groupBox_3);
        btn_clear_log->setObjectName(QStringLiteral("btn_clear_log"));

        gridLayout_2->addWidget(btn_clear_log, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 4, 1, 1, 1);


        retranslateUi(AutoAdjustClass);

        QMetaObject::connectSlotsByName(AutoAdjustClass);
    } // setupUi

    void retranslateUi(QWidget *AutoAdjustClass)
    {
        AutoAdjustClass->setWindowTitle(QApplication::translate("AutoAdjustClass", "\350\207\252\345\212\250\350\260\203\346\240\241\347\263\273\347\273\237", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("AutoAdjustClass", "\344\270\262\345\217\243\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("AutoAdjustClass", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("AutoAdjustClass", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        box_baud->clear();
        box_baud->insertItems(0, QStringList()
         << QApplication::translate("AutoAdjustClass", "4800", Q_NULLPTR)
         << QApplication::translate("AutoAdjustClass", "9600", Q_NULLPTR)
         << QApplication::translate("AutoAdjustClass", "57600", Q_NULLPTR)
         << QApplication::translate("AutoAdjustClass", "115200", Q_NULLPTR)
        );
        rbtn_ascll->setText(QApplication::translate("AutoAdjustClass", "ASCLL", Q_NULLPTR));
        rbtn_hex->setText(QApplication::translate("AutoAdjustClass", "HEX", Q_NULLPTR));
        btn_open_serial->setText(QApplication::translate("AutoAdjustClass", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("AutoAdjustClass", "\345\256\236\346\227\266\350\247\206\351\242\221", Q_NULLPTR));
        label_picture->setText(QString());
        groupBox_5->setTitle(QApplication::translate("AutoAdjustClass", "\345\256\236\346\227\266\346\225\260\346\215\256\345\214\272", Q_NULLPTR));
        label_5->setText(QApplication::translate("AutoAdjustClass", "\347\211\271\345\276\2011\357\274\232", Q_NULLPTR));
        label_fea1->setText(QString());
        label_7->setText(QApplication::translate("AutoAdjustClass", "\347\211\271\345\276\2012\357\274\232", Q_NULLPTR));
        label_fea2->setText(QString());
        label_10->setText(QApplication::translate("AutoAdjustClass", "\347\211\271\345\276\2013\357\274\232", Q_NULLPTR));
        label_fea3->setText(QString());
        label_12->setText(QApplication::translate("AutoAdjustClass", "\347\211\271\345\276\2014\357\274\232", Q_NULLPTR));
        label_fea4->setText(QString());
        groupBox_6->setTitle(QApplication::translate("AutoAdjustClass", "\347\211\271\345\276\201\347\202\271", Q_NULLPTR));
        label_4->setText(QApplication::translate("AutoAdjustClass", "\351\200\211\345\217\226\346\234\272\350\212\257:", Q_NULLPTR));
        label_fea_id->setText(QString());
        btn_learn_feature->setText(QApplication::translate("AutoAdjustClass", "\345\255\246\344\271\240\347\211\271\345\276\201", Q_NULLPTR));
        label_3->setText(QApplication::translate("AutoAdjustClass", "\350\207\252\345\212\250\350\260\203\346\240\241\347\263\273\347\273\237", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("AutoAdjustClass", "\347\233\270\346\234\272", Q_NULLPTR));
        btn_open_camera->setText(QApplication::translate("AutoAdjustClass", "\346\211\223\345\274\200\347\233\270\346\234\272", Q_NULLPTR));
        btn_catch_pic->setText(QApplication::translate("AutoAdjustClass", "\346\215\225\350\216\267\345\233\276\345\203\217", Q_NULLPTR));
        btn_ctrl_status->setText(QApplication::translate("AutoAdjustClass", "\345\274\200\345\247\213", Q_NULLPTR));
        btn_stop->setText(QApplication::translate("AutoAdjustClass", "\345\201\234\346\255\242", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("AutoAdjustClass", "\346\227\245\345\277\227", Q_NULLPTR));
        btn_catch_log->setText(QApplication::translate("AutoAdjustClass", "\344\277\235\345\255\230\346\227\245\345\277\227", Q_NULLPTR));
        btn_clear_log->setText(QApplication::translate("AutoAdjustClass", "\346\270\205\347\251\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AutoAdjustClass: public Ui_AutoAdjustClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOADJUST_H
