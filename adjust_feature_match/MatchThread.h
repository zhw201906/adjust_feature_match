#pragma once

#include <QObject>
#include <QWidget>
#include <QThread>
#include "LearnFeature.h"

#define  MATCH_THRESHOLD   30000000

class MatchThread : public QThread
{
    Q_OBJECT

public:
    MatchThread();
    MatchThread(QWidget *parent, cv::Mat &src, cv::Mat &mask);
    ~MatchThread();

    void run();
    void MatchTask(cv::Mat &src, cv::Mat &mask);
    void SetImageData(cv::Mat &src, cv::Mat &mask, float scale = 1);

    float scale_;
signals:
    void match_result(cv::Point leftTop, cv::Point rightBottom);

private:
    cv::Mat src_img_;
    cv::Mat src_kernal_;

    cv::Point match_position_lt;
    cv::Point match_position_rb;

};
