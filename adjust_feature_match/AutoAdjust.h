#pragma once

#include <QtWidgets/QWidget>
#include "ui_AutoAdjust.h"
#include "LearnFeature.h"
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>
#include <vector>
#include <iostream>
#include <QVector>
#include <QDateTime>
#include <QDate>
#include <QImage>

#include "opencv2/opencv.hpp"
#include <windows.h>

//引入qt中串口通信需要的头文件
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "MatchThread.h"
#include "SdkCamera.h"

#define  AVAILABLE_TIME  "31.07.2020"
#define  THREAD_NUM_   4

class AutoAdjust : public QWidget
{
    Q_OBJECT

public:
    AutoAdjust(QWidget *parent = Q_NULLPTR);
    ~AutoAdjust();

    void RefreshFeatureType();
    void closeEvent(QCloseEvent *event);
    void DealSerialMsg();
	void SerialInit();
	void LoadFeatureCfg();
    void DealMatchResult(int thread_id, cv::Point pt_lt, cv::Point pt_rb);

    void MatchFeature(cv::Mat &src, cv::Mat &dst);
	void EnableMatchTask();
	bool AllThreadFinished();

	bool TestSdkCamera();
	bool OpenSdkCamera();
	void CloseSdkCamera();

private:
    Ui::AutoAdjustClass ui;

    QMessageBox msg_box;

	QDateTime current_time_;
    QString  code_type_;
    QSerialPort *p_serial_port_ = NULL;
    bool  serial_status_;
	bool  thread_begin_flag_ = false;

    cv::VideoCapture *capture = NULL;
    cv::Mat           capfream;

    QTimer *diaplay_timer_ = NULL;

    LearnFeature *p_learn_feature_ = NULL;

    QVector<QString> feature_index_;
    QString select_feature_;

    QMessageBox msg_box_;
    cv::Mat source_img_;

	int         curt_faeture_num_;
	int         curt_feature_id_;
	QVector<FeatureInfo>  curt_feature_info_;    //当前特征信息
	QString     curt_feature_path_;    //当前特征地址
    QVector<cv::Mat> feature_img_buff_;   //特征图
	QVector<cv::Mat> area_image_buff_;
    QVector<cv::Point> match_loc_buff_;   //识别结果

    MatchThread *match_thread_;
	QVector<bool> thread_flag_;

	bool   last_frame_finished_;
	bool   recognize_flag_;
	bool   camera_flag_;
	Dahua::Infra::TVector<Dahua::GenICam::ICameraPtr> m_vCameraPtrList;	// 发现的相机列表
	SdkCamera  *pSdk_camera_;
	QImage   current_picture_stream_;

 };
