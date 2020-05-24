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
#include <QMap>
#include <QByteArray>

#include "opencv2/opencv.hpp"
#include <windows.h>

//引入qt中串口通信需要的头文件
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "MatchThread.h"
#include "SdkCamera.h"

#define  AVAILABLE_TIME  "31.07.2020"
#define  THREAD_NUM_   4

#define  FRAME_ONE   0x43
#define  FRAME_TWO   0x4e
#define  FRAME_SIZE  5U

enum { CMD_QUERY_STATUS = 0, CMD_RECOGNIZE = 1 };
enum { STATUS_NORMAL, STATUS_ERROR };

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
    void LoadAllFeatureCfg();
    void DealMatchResult(int thread_id, cv::Point pt_lt, cv::Point pt_rb);

    void MatchFeature(cv::Mat &src, cv::Mat &dst);
	void EnableMatchTask();
    void EnableMatchTaskById(int id);
	bool AllThreadFinished();

	bool TestSdkCamera();
	bool OpenSdkCamera();
	void CloseSdkCamera();

    bool TestSerialReceiveDataAvailable(QVector<quint8>& rbuff);
    void DealSerialCmdTask();
    void SendSerialRecgResult(QByteArray &sbuff);
    void PackReturnStatusData(int status);
    void PackReturnRecgResult(QVector<cv::Point>& rresult);
    void CalCheckSumResult();

public:
    typedef struct feature_data_
    {
        int                   feature_num;
        QVector<FeatureInfo>  fea_info_data;
        QVector<cv::Mat>      fea_image_buff;
    }FeatureInfoData;

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

    QMap<int, FeatureInfoData>  fea_info_map_;    // ID与特征储存map
    int   cur_fea_id_;


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

    QVector<quint8>  serial_buff_;
    quint8           function_bit_;
    int              recognize_id_;
    bool             serial_recg_mode_;
    QByteArray       serial_send_buff_;
 };
