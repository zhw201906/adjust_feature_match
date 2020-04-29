/********************************************************************************
** Form generated from reading UI file 'LearnFeature.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNFEATURE_H
#define UI_LEARNFEATURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mydisplaylabel.h"

QT_BEGIN_NAMESPACE

class Ui_LearnFeature
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    MyDisplayLabel *label_image;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_3;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_13;
    QComboBox *comboBox_feature;
    QPushButton *btn_del_feature;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QSpinBox *spinBox_x;
    QLabel *label_9;
    QSpinBox *spinBox_y;
    QCheckBox *checkBox_boxline;
    QCheckBox *checkBox_part;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_rec;
    QLabel *label_4;
    QLineEdit *lineEdit_width;
    QLabel *label_5;
    QLineEdit *lineEdit_height;
    QRadioButton *radioButton_cir;
    QLabel *label_6;
    QLineEdit *lineEdit_radius;
    QPushButton *btn_load_image;
    QPushButton *btn_reboot_feature;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_left;
    QLabel *label_10;
    QLineEdit *lineEdit_top;
    QLabel *label_11;
    QLineEdit *lineEdit_right;
    QLabel *label_12;
    QLineEdit *lineEdit_bottom;
    QPushButton *btn_sure_feature;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QTextEdit *text_result;
    QWidget *widget;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QLineEdit *lineEdit_name;
    QPushButton *btn_sure_learn;
    QLabel *label;
    QLineEdit *lineEdit_id;

    void setupUi(QWidget *LearnFeature)
    {
        if (LearnFeature->objectName().isEmpty())
            LearnFeature->setObjectName(QStringLiteral("LearnFeature"));
        LearnFeature->resize(1680, 960);
        LearnFeature->setMinimumSize(QSize(1680, 960));
        LearnFeature->setMaximumSize(QSize(1680, 960));
        gridLayout_3 = new QGridLayout(LearnFeature);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_3 = new QLabel(LearnFeature);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral(""));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(LearnFeature);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_image = new MyDisplayLabel(groupBox_2);
        label_image->setObjectName(QStringLiteral("label_image"));
        label_image->setMinimumSize(QSize(1148, 861));
        label_image->setMaximumSize(QSize(1148, 861));
        label_image->setStyleSheet(QStringLiteral(""));
        label_image->setFrameShape(QFrame::Box);
        label_image->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_image);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 5, 1);

        groupBox_6 = new QGroupBox(LearnFeature);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy1);
        groupBox_6->setMinimumSize(QSize(400, 0));
        groupBox_6->setAlignment(Qt::AlignCenter);
        horizontalLayout_3 = new QHBoxLayout(groupBox_6);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        textBrowser = new QTextBrowser(groupBox_6);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        horizontalLayout_3->addWidget(textBrowser);


        gridLayout_3->addWidget(groupBox_6, 1, 1, 1, 1);

        groupBox_7 = new QGroupBox(LearnFeature);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setAlignment(Qt::AlignCenter);
        horizontalLayout_5 = new QHBoxLayout(groupBox_7);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_13 = new QLabel(groupBox_7);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_13);

        comboBox_feature = new QComboBox(groupBox_7);
        comboBox_feature->setObjectName(QStringLiteral("comboBox_feature"));

        horizontalLayout_5->addWidget(comboBox_feature);

        btn_del_feature = new QPushButton(groupBox_7);
        btn_del_feature->setObjectName(QStringLiteral("btn_del_feature"));

        horizontalLayout_5->addWidget(btn_del_feature);


        gridLayout_3->addWidget(groupBox_7, 2, 1, 1, 1);

        groupBox_4 = new QGroupBox(LearnFeature);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        groupBox_4->setMaximumSize(QSize(400, 16777215));
        groupBox_4->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_8);

        spinBox_x = new QSpinBox(groupBox_3);
        spinBox_x->setObjectName(QStringLiteral("spinBox_x"));

        horizontalLayout->addWidget(spinBox_x);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_9);

        spinBox_y = new QSpinBox(groupBox_3);
        spinBox_y->setObjectName(QStringLiteral("spinBox_y"));

        horizontalLayout->addWidget(spinBox_y);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 2, 1);

        checkBox_boxline = new QCheckBox(groupBox_4);
        checkBox_boxline->setObjectName(QStringLiteral("checkBox_boxline"));

        gridLayout_2->addWidget(checkBox_boxline, 0, 1, 1, 1);

        checkBox_part = new QCheckBox(groupBox_4);
        checkBox_part->setObjectName(QStringLiteral("checkBox_part"));

        gridLayout_2->addWidget(checkBox_part, 1, 1, 1, 1);

        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_rec = new QRadioButton(groupBox);
        radioButton_rec->setObjectName(QStringLiteral("radioButton_rec"));

        gridLayout->addWidget(radioButton_rec, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 1, 1, 1);

        lineEdit_width = new QLineEdit(groupBox);
        lineEdit_width->setObjectName(QStringLiteral("lineEdit_width"));

        gridLayout->addWidget(lineEdit_width, 0, 2, 1, 2);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 4, 1, 1);

        lineEdit_height = new QLineEdit(groupBox);
        lineEdit_height->setObjectName(QStringLiteral("lineEdit_height"));

        gridLayout->addWidget(lineEdit_height, 0, 5, 1, 1);

        radioButton_cir = new QRadioButton(groupBox);
        radioButton_cir->setObjectName(QStringLiteral("radioButton_cir"));

        gridLayout->addWidget(radioButton_cir, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 1, 1, 1, 2);

        lineEdit_radius = new QLineEdit(groupBox);
        lineEdit_radius->setObjectName(QStringLiteral("lineEdit_radius"));

        gridLayout->addWidget(lineEdit_radius, 1, 3, 1, 1);


        gridLayout_2->addWidget(groupBox, 2, 0, 2, 1);

        btn_load_image = new QPushButton(groupBox_4);
        btn_load_image->setObjectName(QStringLiteral("btn_load_image"));

        gridLayout_2->addWidget(btn_load_image, 2, 1, 1, 1);

        btn_reboot_feature = new QPushButton(groupBox_4);
        btn_reboot_feature->setObjectName(QStringLiteral("btn_reboot_feature"));

        gridLayout_2->addWidget(btn_reboot_feature, 3, 1, 1, 1);

        groupBox_8 = new QGroupBox(groupBox_4);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_8);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(groupBox_8);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        lineEdit_left = new QLineEdit(groupBox_8);
        lineEdit_left->setObjectName(QStringLiteral("lineEdit_left"));

        horizontalLayout_4->addWidget(lineEdit_left);

        label_10 = new QLabel(groupBox_8);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_10);

        lineEdit_top = new QLineEdit(groupBox_8);
        lineEdit_top->setObjectName(QStringLiteral("lineEdit_top"));

        horizontalLayout_4->addWidget(lineEdit_top);

        label_11 = new QLabel(groupBox_8);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_11);

        lineEdit_right = new QLineEdit(groupBox_8);
        lineEdit_right->setObjectName(QStringLiteral("lineEdit_right"));

        horizontalLayout_4->addWidget(lineEdit_right);

        label_12 = new QLabel(groupBox_8);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_12);

        lineEdit_bottom = new QLineEdit(groupBox_8);
        lineEdit_bottom->setObjectName(QStringLiteral("lineEdit_bottom"));

        horizontalLayout_4->addWidget(lineEdit_bottom);


        gridLayout_2->addWidget(groupBox_8, 4, 0, 1, 1);

        btn_sure_feature = new QPushButton(groupBox_4);
        btn_sure_feature->setObjectName(QStringLiteral("btn_sure_feature"));

        gridLayout_2->addWidget(btn_sure_feature, 4, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 3, 1, 1, 1);

        groupBox_5 = new QGroupBox(LearnFeature);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        groupBox_5->setMinimumSize(QSize(400, 0));
        groupBox_5->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        text_result = new QTextEdit(groupBox_5);
        text_result->setObjectName(QStringLiteral("text_result"));
        text_result->setTabStopWidth(40);

        verticalLayout->addWidget(text_result);


        gridLayout_3->addWidget(groupBox_5, 4, 1, 1, 1);

        widget = new QWidget(LearnFeature);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(400, 0));
        gridLayout_4 = new QGridLayout(widget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        lineEdit_name = new QLineEdit(widget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        gridLayout_4->addWidget(lineEdit_name, 0, 1, 1, 1);

        btn_sure_learn = new QPushButton(widget);
        btn_sure_learn->setObjectName(QStringLiteral("btn_sure_learn"));
        btn_sure_learn->setMinimumSize(QSize(50, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(11);
        btn_sure_learn->setFont(font1);
        btn_sure_learn->setStyleSheet(QStringLiteral("color: rgb(0, 170, 0);"));

        gridLayout_4->addWidget(btn_sure_learn, 0, 2, 2, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label, 1, 0, 1, 1);

        lineEdit_id = new QLineEdit(widget);
        lineEdit_id->setObjectName(QStringLiteral("lineEdit_id"));

        gridLayout_4->addWidget(lineEdit_id, 1, 1, 1, 1);


        gridLayout_3->addWidget(widget, 5, 1, 1, 1);


        retranslateUi(LearnFeature);

        QMetaObject::connectSlotsByName(LearnFeature);
    } // setupUi

    void retranslateUi(QWidget *LearnFeature)
    {
        LearnFeature->setWindowTitle(QApplication::translate("LearnFeature", "\347\211\271\345\276\201\345\255\246\344\271\240", Q_NULLPTR));
        label_3->setText(QApplication::translate("LearnFeature", "\345\267\245\344\273\266\347\211\271\345\276\201\345\255\246\344\271\240", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("LearnFeature", "\347\211\271\345\276\201\345\233\276", Q_NULLPTR));
        label_image->setText(QString());
        groupBox_6->setTitle(QApplication::translate("LearnFeature", "\345\267\245\344\273\266\345\255\246\344\271\240\344\275\277\347\224\250\350\257\264\346\230\216", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("LearnFeature", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">\345\255\246\344\271\240\346\255\245\351\252\244\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">1\343\200\201\350\275\275\345\205\245\347\211\271\345\276\201\345\233\276\347\211\207\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">2\343\200\201\351\200\211"
                        "\346\213\251\347\211\271\345\276\201\345\275\242\347\212\266\345\217\212\345\244\247\345\260\217\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">3\343\200\201\347\202\271\345\207\273\347\211\271\345\276\201\345\233\276\344\270\255\347\233\256\346\240\207\347\211\271\345\276\201\344\270\255\345\277\203\344\275\215\347\275\256\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">4\343\200\201\351\200\232\350\277\207X\343\200\201Y\345\235\220\346\240\207\345\257\271\344\270\255\345\277\203\344\275\215\347\275\256\347\273\206\345\256\232\344\275\215\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">5\343\200\201\347\241\256\345\256"
                        "\232\346\227\240\350\257\257\345\220\216\357\274\214\347\202\271\345\207\273\347\241\256\345\256\232\347\211\271\345\276\201\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">6\343\200\201\345\244\232\344\270\252\347\211\271\345\276\201\346\227\266\351\207\215\345\244\215\346\255\245\351\252\2442--5\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">7\343\200\201\350\207\252\345\212\250\347\224\237\346\210\220\347\232\204\347\211\271\345\276\201\351\200\211\345\217\226\347\273\223\346\236\234\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">8\343\200\201\350\276\223\345\205\245\345\267\245\344\273\266\345\236\213\345\217\267"
                        "\357\274\210\344\270\215\345\217\257\351\207\215\345\244\215\357\274\211\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">9\343\200\201\347\241\256\345\256\232\345\255\246\344\271\240\357\274\214\347\211\271\345\276\201\345\255\246\344\271\240\345\256\214\346\210\220\343\200\202</span></p></body></html>", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("LearnFeature", "\347\211\271\345\276\201\345\210\227\350\241\250", Q_NULLPTR));
        label_13->setText(QApplication::translate("LearnFeature", "\346\234\272\350\212\257\347\211\271\345\276\201\357\274\232", Q_NULLPTR));
        btn_del_feature->setText(QApplication::translate("LearnFeature", "\345\210\240\351\231\244\347\211\271\345\276\201", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("LearnFeature", "\347\211\271\345\276\201\351\200\211\345\217\226", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("LearnFeature", "\344\270\255\345\277\203\345\235\220\346\240\207", Q_NULLPTR));
        label_8->setText(QApplication::translate("LearnFeature", "X\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("LearnFeature", "Y\357\274\232", Q_NULLPTR));
        checkBox_boxline->setText(QApplication::translate("LearnFeature", "\346\230\276\347\244\272\346\241\206\347\272\277", Q_NULLPTR));
        checkBox_part->setText(QApplication::translate("LearnFeature", "\345\210\206\345\214\272", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LearnFeature", "\347\211\271\345\276\201\345\275\242\347\212\266\345\217\212\345\244\247\345\260\217", Q_NULLPTR));
        radioButton_rec->setText(QApplication::translate("LearnFeature", "\347\237\251\345\275\242", Q_NULLPTR));
        label_4->setText(QApplication::translate("LearnFeature", "\351\225\277\357\274\232", Q_NULLPTR));
        lineEdit_width->setText(QApplication::translate("LearnFeature", "50", Q_NULLPTR));
        label_5->setText(QApplication::translate("LearnFeature", "\345\256\275\357\274\232", Q_NULLPTR));
        lineEdit_height->setText(QApplication::translate("LearnFeature", "40", Q_NULLPTR));
        radioButton_cir->setText(QApplication::translate("LearnFeature", "\345\234\206", Q_NULLPTR));
        label_6->setText(QApplication::translate("LearnFeature", "\345\215\212\345\276\204\357\274\232", Q_NULLPTR));
        lineEdit_radius->setText(QApplication::translate("LearnFeature", "50", Q_NULLPTR));
        btn_load_image->setText(QApplication::translate("LearnFeature", "\350\275\275\345\205\245\345\233\276\347\211\207", Q_NULLPTR));
        btn_reboot_feature->setText(QApplication::translate("LearnFeature", "\351\207\215\347\275\256\347\211\271\345\276\201", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("LearnFeature", "\345\210\206\345\214\272\345\214\272\345\237\237", Q_NULLPTR));
        label_2->setText(QApplication::translate("LearnFeature", "\345\267\246\357\274\232", Q_NULLPTR));
        lineEdit_left->setText(QApplication::translate("LearnFeature", "0", Q_NULLPTR));
        label_10->setText(QApplication::translate("LearnFeature", "\344\270\212\357\274\232", Q_NULLPTR));
        lineEdit_top->setText(QApplication::translate("LearnFeature", "0", Q_NULLPTR));
        label_11->setText(QApplication::translate("LearnFeature", "\345\217\263\357\274\232", Q_NULLPTR));
        lineEdit_right->setText(QApplication::translate("LearnFeature", "100", Q_NULLPTR));
        label_12->setText(QApplication::translate("LearnFeature", "\344\270\213\357\274\232", Q_NULLPTR));
        lineEdit_bottom->setText(QApplication::translate("LearnFeature", "100", Q_NULLPTR));
        btn_sure_feature->setText(QApplication::translate("LearnFeature", "\347\241\256\345\256\232\347\211\271\345\276\201", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("LearnFeature", "\347\211\271\345\276\201\351\200\211\345\217\226\347\273\223\346\236\234", Q_NULLPTR));
        label_7->setText(QApplication::translate("LearnFeature", "\345\267\245\344\273\266\345\236\213\345\217\267\357\274\232", Q_NULLPTR));
        btn_sure_learn->setText(QApplication::translate("LearnFeature", "\347\241\256\345\256\232\345\255\246\344\271\240", Q_NULLPTR));
        label->setText(QApplication::translate("LearnFeature", "\345\267\245\344\273\266ID\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LearnFeature: public Ui_LearnFeature {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNFEATURE_H
