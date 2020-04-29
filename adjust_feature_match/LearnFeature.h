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

    int feature_center_x_;     //��������x����
    int feature_center_y_;     //��������y����

    bool diaplay_pic_flag_;        //�Ƿ�ʼ��ʾ����
    bool display_box_line_flag_;   //��ʾ���߱�־λ
    int  display_sharp_;           //������״

    int  feature_num;    //��������
	QString feature_name_;
	int  feature_id_;

    float scale_para_;   //ͼ����ʾ����ϵ��

    int  width_;   //������
    int  height_;  //������
    int  radius_;  //�����뾶

	int pt_move_status_;
	int pt_left_;   //ѡ����λ�ö���
	int pt_top_;
	int pt_right_;
	int pt_bottom_;
	bool part_match_flag_;        //�Ƿ���ѡ��ʶ��
	bool part_match_boxline_dsp_; //��ʾѡ����־

    QMessageBox msg_box_;

    QVector<FeatureInfo> selete_fea_info_;  //��ѡ���������Ϣ
	QVector<QString> feature_index_;        //�����б�

};
