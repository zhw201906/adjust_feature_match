#pragma once

#include <QWidget>
#include "ui_LearnFeature.h"
#include <QCloseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QVector>
#include <QSettings>

#include "opencv2/opencv.hpp"

enum {RECTANGLE,CIRCLE};

#define  OPEN_IMAGE_PATH  ".\\image"
#define  FEATURE_PATH     ".\\feature"

typedef struct feature_info
{
    int x;
    int y;
    int type;
    int id;
    int w;
    int h;
    int r;
	int part;
	int left;
	int top;
	int right;
	int bottom;
}FeatureInfo;

class LearnFeature : public QWidget
{
    Q_OBJECT

public:
    LearnFeature(QWidget *parent = Q_NULLPTR);
    ~LearnFeature();

    void closeEvent(QCloseEvent *event);
    //void paintEvent(QPaintEvent *event);

    bool eventFilter(QObject *watched, QEvent *event);
    void paintTask(void);

	void RefreshFeatureList();
	void DealEnsureFeature();
    bool FeatureTextParsing(QString feaText);
	void SaveFeaturePicture(QString &path);
	void SaveFeatureConfigText(QString &path);



signals:
    void closeUi(void);

private:
    Ui::LearnFeature ui;
    QString  picture_path_;
    cv::Mat  origin_feature_pic_;

    int feature_center_x_;     //特征中心x坐标
    int feature_center_y_;     //特征中心y坐标

    bool diaplay_pic_flag_;        //是否开始显示框线
    bool display_box_line_flag_;   //显示框线标志位
    int  display_sharp_;           //框线形状

    int  feature_num;    //特征个数
	QString feature_name_;
	int  feature_id_;

    float scale_para_;   //图像显示缩放系数

    int  width_;   //特征长
    int  height_;  //特征宽
    int  radius_;  //特征半径

	int pt_move_status_;
	int pt_left_;   //选区框位置定义
	int pt_top_;
	int pt_right_;
	int pt_bottom_;
	bool part_match_flag_;        //是否开启选区识别
	bool part_match_boxline_dsp_; //显示选区标志

    QMessageBox msg_box_;

    QVector<FeatureInfo> selete_fea_info_;  //已选择的特征信息
	QVector<QString> feature_index_;        //特征列表

};
