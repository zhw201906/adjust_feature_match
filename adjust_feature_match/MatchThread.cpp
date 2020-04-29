#include "MatchThread.h"

//float MatchThread::scale_ = 0.5;

MatchThread::MatchThread(QWidget *parent, cv::Mat &src, cv::Mat &mask)
    : QThread(parent), src_img_(src), src_kernal_(mask)
{
    match_position_lt = cv::Point(0, 0);
    match_position_rb = cv::Point(0, 0);
	scale_ = 1;
}

MatchThread::MatchThread()
{
    src_img_ = NULL;
    src_kernal_ = NULL;
}

MatchThread::~MatchThread()
{

}

void MatchThread::run()
{
    MatchTask(src_img_, src_kernal_);
    emit match_result(match_position_lt, match_position_rb);  
}

void MatchThread::MatchTask(cv::Mat & src, cv::Mat & mask)
{    
    if (src.empty() || mask.empty())
        return;

    int result_cols = src.cols - mask.cols + 1;
    int result_rows = src.rows - mask.rows + 1;

    double minVal, maxVal;
    cv::Point minLoc, maxLoc, matchLoc;

    char temp[16];

    cv::Mat OutResult;
    OutResult.create(result_cols, result_rows, CV_32FC1);

    cv::matchTemplate(src, mask, OutResult, cv::TM_SQDIFF);
    //normalize(OutResult, OutResult, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    minMaxLoc(OutResult, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    if (minVal > MATCH_THRESHOLD)
    {
        match_position_lt = cv::Point(0, 0);
        match_position_rb = cv::Point(0, 0);
        return;
    }

    matchLoc = minLoc;
    int LocX = 0, LocY = 0;
    LocX = matchLoc.x + mask.cols;
    LocY = matchLoc.y + mask.rows;

    match_position_lt = cv::Point(matchLoc.x / scale_, matchLoc.y / scale_);;
    match_position_rb = cv::Point(LocX / scale_, LocY / scale_);
}

void MatchThread::SetImageData(cv::Mat & src, cv::Mat & mask, float scale)
{
	scale_ = scale;
    cv::resize(src, src_img_, cv::Size(0, 0), scale_, scale_);
    cv::resize(mask, src_kernal_, cv::Size(0, 0), scale_, scale_);
    //src_img_ = src(0.5);
    //src_kernal_ = mask;
}
