#include "AutoAdjust.h"
#include "style_sheet_define.h"
#include <QRadioButton>
#include <QDebug>
#include <QStringList>
#include <QPushButton>
#include <QComboBox>
#include <QImage>
#include <QTimer>
#include <QFileDialog>
#include <QDir>
#include <vector>

//等比缩放图像
//参数1：图像路径（IN）
//参数2：控件宽度（IN）
//参数3：控件高度（IN）
//参数4：缩放后结果图（OUT）
static void Geometric_Scaling_Image(const QString path, const int control_width, const int control_height, QPixmap &dst_pix)
{
    QPixmap pix;
    pix.load(path);

    double ratio_w = pix.width() * 1.0 / control_width;
    double ratio_h = pix.height() * 1.0 / control_height;

    if (ratio_w >= ratio_h)
        pix = pix.scaled(pix.width() / ratio_w, pix.height() / ratio_w);
    else
        pix = pix.scaled(pix.width() / ratio_h, pix.height() / ratio_h);

    dst_pix = pix;
}

static cv::Mat QImage2Mat(QImage image)
{
	cv::Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.bits(), image.bytesPerLine());
		break;
	case QImage::Format_Grayscale8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;

}

static QImage  Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if (cvImg.channels() == 3)                             //3 channels color image
    {

        cv::cvtColor(cvImg, cvImg, CV_BGR2RGB);
        qImg = QImage((const unsigned char*)(cvImg.data),
            cvImg.cols, cvImg.rows,
            cvImg.cols*cvImg.channels(),
            QImage::Format_RGB888);
    }
    else if (cvImg.channels() == 1)                    //grayscale image
    {
        qImg = QImage((const unsigned char*)(cvImg.data),
            cvImg.cols, cvImg.rows,
            cvImg.cols*cvImg.channels(),
            QImage::Format_Indexed8);
    }
    else
    {
        qImg = QImage((const unsigned char*)(cvImg.data),
            cvImg.cols, cvImg.rows,
            cvImg.cols*cvImg.channels(),
            QImage::Format_RGB888);
    }

    return qImg;

}

static cv::Mat convertTo3Channels(const cv::Mat& binImg)
{
	cv::Mat three_channel = cv::Mat::zeros(binImg.rows, binImg.cols, CV_8UC3);
	std::vector<cv::Mat> channels;
	for (int i = 0; i < 3; i++)
	{
		channels.push_back(binImg);
	}
	merge(channels, three_channel);
	return three_channel;
}

AutoAdjust::AutoAdjust(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	QDateTime curt = current_time_.currentDateTime();
	if (curt > QDateTime::fromString(AVAILABLE_TIME, "dd.MM.yyyy"))
	{
		msg_box.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("系统被损坏！"));
		return;
	}
		
    //ui.label_picture->setStyleSheet(LABEL_STYLE_BLACK_BORDER);

    p_learn_feature_ = NULL;
    p_serial_port_ = NULL;
    match_thread_ = NULL;
	pSdk_camera_ = NULL;
	camera_flag_ = false;
	recognize_flag_ = false;
	last_frame_finished_ = false;

	ui.text_log->moveCursor(QTextCursor::End);  //log自动滚动到底
	pSdk_camera_ = new SdkCamera(this);
    
	//连接相机sdk显示图像信号
	connect(pSdk_camera_, &SdkCamera::signalShowImage, [=](uint8_t* pRgbFrameBuf, int nWidth, int nHeight, uint64_t nPixelFormat) {
		//current_picture_stream_
		QImage image;
		if (NULL == pRgbFrameBuf || nWidth == 0 || nHeight == 0)
		{
			ui.text_log->append("Image stream is invalid.\n");
			return false;
		}
		if (Dahua::GenICam::gvspPixelMono8 == nPixelFormat)
		{
			image = QImage(pRgbFrameBuf, nWidth, nHeight, QImage::Format_Grayscale8);
		}
		else
		{
			image = QImage(pRgbFrameBuf, nWidth, nHeight, QImage::Format_RGB888);
		}
		cv::Mat img = QImage2Mat(image);
		capfream = img.clone();
		//ui.text_log->append("get frame success!");

		//识别未完成时，显示相机实时图像
		if (!last_frame_finished_)
		{
			//将QImage的大小收缩或拉伸，与label的大小保持一致。这样label中能显示完整的图片
			QImage imageScale = image.scaled(QSize(ui.label_picture->width(), ui.label_picture->height()));
			QPixmap pixmap = QPixmap::fromImage(imageScale);
			ui.label_picture->setPixmap(pixmap);
		}
		
		//启动识别
		if (recognize_flag_ && last_frame_finished_) //识别开启，并且上一帧识别完成
		{
			ui.text_log->append("begin match feature!");
			source_img_ = convertTo3Channels(capfream).clone();
			EnableMatchTask();
			last_frame_finished_ = false;
		}

		free(pRgbFrameBuf);
	});

	
    ui.rbtn_ascll->setChecked(true);
    ui.box_baud->setCurrentText("115200");
    code_type_ = "ascll";
    serial_status_ = false;
    ui.box_baud->setEnabled(true);
    ui.box_serial_id->setEnabled(true);

    match_loc_buff_.clear();
    match_loc_buff_.resize(THREAD_NUM_);

    if (!p_serial_port_)
    {
        p_serial_port_ = new QSerialPort;
    }

    //扫描可用串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString serial_info = info.portName();
        ui.box_serial_id->addItem(serial_info);
        qDebug() << "availablePorts:" << info.portName();
    }

    //初始化后---打开/关闭串口
    connect(ui.btn_open_serial, &QPushButton::clicked, [=]() {
		SerialInit();      
    });

    //串口服务函数
    connect(p_serial_port_, &QSerialPort::readyRead, [=]() {
 /*       QByteArray buff;
        qDebug() << "reciver data:" << buff << "\n";
        buff = p_serial_port_->readAll();
        if (!buff.isEmpty())
        {
            QString str = buff;
            p_serial_port_->write(str.toUtf8());
        }
        buff.clear();*/
        DealSerialMsg();
    });

	//串口编码格式
	connect(ui.rbtn_ascll, &QRadioButton::clicked, [=]() {
		qDebug() << "selesct radio id:" << ui.rbtn_ascll->isChecked();
		code_type_ = "ascll";
	});
	connect(ui.rbtn_hex, &QRadioButton::clicked, [=]() {
		qDebug() << "selesct radio id:" << ui.rbtn_hex->isChecked();
		code_type_ = "hex";
	});

	
	//创建并开启多线程
	match_thread_ = new MatchThread[THREAD_NUM_];
	for (int i = 0; i < THREAD_NUM_; i++)
	{
		connect(&match_thread_[i], &MatchThread::match_result, [=](cv::Point pos_lt, cv::Point pos_rb) {
			match_thread_[i].quit();
			match_thread_[i].wait();

			DealMatchResult(i, pos_lt, pos_rb);
		});
    
		/*connect(&match_thread_[i], &MatchThread::finished, [=]() {
			qDebug() << "thread finished:" << i;
		});*/
	}

    //特征学习界面
    connect(ui.btn_learn_feature, &QPushButton::clicked, [=]() {

        //特征学习界面        
        if (p_learn_feature_ == NULL)
        {
            p_learn_feature_ = new LearnFeature;
        }

        this->hide();
        p_learn_feature_->show();

        //关闭按钮
        connect(p_learn_feature_, &LearnFeature::closeUi, [=]() {
            delete p_learn_feature_;
            p_learn_feature_ = NULL;
            this->show();
            RefreshFeatureType();
        });
    });
    
    //机芯选择
    connect(ui.cbox_feature, &QComboBox::currentTextChanged, [=](QString current_fea) {
        select_feature_ = current_fea;
		LoadFeatureCfg();
        //ui.text_log->append(select_feature_);
    });

	//初始化--机芯特征列表
	RefreshFeatureType();

    //开始按钮----启动视频流识别
    connect(ui.btn_ctrl_status, &QPushButton::clicked, [=]() {  
		if (!camera_flag_)
		{
			msg_box.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("相机未打开！"));
			return;
		}

		if(!recognize_flag_)  //启动视频流识别
			recognize_flag_ = true;

		last_frame_finished_ = true;
		//QString pic_path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图片"), OPEN_IMAGE_PATH,
		//	tr("Images (*.png *.jpg *.bmp);; All files (*.*)"));
		//if (pic_path.isEmpty())
		//	return;

		//source_img_ = cv::imread(pic_path.toStdString());

		//ui.text_log->append(QString("snap image size:%1 * %2").arg(capfream.cols).arg(capfream.rows));
		//if (!capfream.empty())
		//	//capfream.convertTo(source_img_, 16);
		//	source_img_ = convertTo3Channels(capfream).clone();

		//ui.text_log->append(QString("image size:%1 * %2").arg(source_img_.cols).arg(source_img_.rows));
		//if (!source_img_.empty())
		//{
		//	ui.text_log->append("begin match");
		//	//cv::imshow("img", source_img_);
		//	EnableMatchTask();
		//	//cv::Mat dst;
		//	//MatchFeature(source_img_, dst);
		//	//ui.text_log->append(QString("source image type:%1").arg(source_img_.type()));
		//	//
		//	//cv::Mat redst;
		//	//cv::resize(dst, redst, cv::Size(ui.label_picture->width(), ui.label_picture->height()));

		//	//QImage qfream = Mat2QImage(redst);
		//	//ui.label_picture->setPixmap(QPixmap::fromImage(qfream));

		//	//cv::Mat redst;
		//	//cv::resize(source_img_, redst, cv::Size(ui.label_picture->width(), ui.label_picture->height()));

		//	//QImage qfream = Mat2QImage(redst);
		//	//ui.label_picture->setPixmap(QPixmap::fromImage(qfream));
		//}
		



 /*       QString pic_path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图片"), OPEN_IMAGE_PATH,
            tr("Images (*.png *.jpg *.bmp);; All files (*.*)"));

		if (pic_path.isEmpty())
			return;

		QImage qimg(pic_path);
		cv::Mat img = QImage2Mat(qimg);
		ui.text_log->append(QString("img size:%1*%2").arg(img.cols).arg(img.rows));
		cv::imshow("img", img);*/

        //QPixmap pix;
        //Geometric_Scaling_Image(picture_path_, ui.label_image->width(), ui.label_image->height(), pix);
        //ui.label_image->setPixmap(pix);

        //qDebug() << picture_path_ << endl;
        //origin_feature_pic_ = cv::imread(picture_path_.toStdString());
        //cv::imshow("image", origin_feature_pic_);
        //scale_para_ = ui.label_image->width()*1.0f / origin_feature_pic_.cols;
        
        //cv::Mat img = cv::imread(pic_path.toStdString());
        //cv::Mat dst;
        //MatchFeature(img, dst);
        //cv::Mat redst;
        //cv::resize(dst, redst, cv::Size(ui.label_picture->width(), ui.label_picture->height()));
        //QImage qfream = Mat2QImage(redst);

        //ui.label_picture->setPixmap(QPixmap::fromImage(qfream));
        //cv::imshow("image", dst);
        //source_img_ = cv::imread(pic_path.toStdString());
  //      ui.label_fea1->clear();
  //      ui.label_fea2->clear();
  //      ui.label_fea3->clear();
  //      ui.label_fea4->clear();

		//thread_flag_.clear();
		//area_image_buff_.clear();		
  //      for (int i = 0; i < feature_img_buff_.size(); i++)
  //      {
  //          cv::Mat null_mat;
  //          area_image_buff_.push_back(null_mat);
  //          if (curt_feature_info_[i].part == 1)
  //          {
  //              cv::Rect roi = cv::Rect(cv::Point(curt_feature_info_[i].left, curt_feature_info_[i].top),
  //                  cv::Point(curt_feature_info_[i].right, curt_feature_info_[i].bottom));
  //              area_image_buff_[i] = source_img_(roi);
  //              match_thread_[i].SetImageData(area_image_buff_[i], feature_img_buff_[i], 1);
  //          }
  //          else
  //          {
  //              match_thread_[i].SetImageData(source_img_, feature_img_buff_[i], 0.5);
  //          }
  //          match_thread_[i].start();

  //          thread_flag_.push_back(false);
  //      }
  
    });

	//打开相机按钮----连接相机
	connect(ui.btn_open_camera, &QPushButton::clicked, [=]() {
		if (!camera_flag_)
			OpenSdkCamera();
	});

    //停止按钮------断开相机
	connect(ui.btn_stop, &QPushButton::clicked, [=]() {
		if (!camera_flag_)
		{
			msg_box.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("相机未打开！"));
			return;
		}

		CloseSdkCamera();
		recognize_flag_ = false;
		camera_flag_ = false;
	});
    
	//捕获按钮----抓取当前图像
	connect(ui.btn_catch_pic, &QPushButton::clicked, [=]() {
		if (!camera_flag_)
		{
			msg_box.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("相机未打开！"));
			return;
		}

		QDateTime curt = current_time_.currentDateTime();
		QString catch_pic_path = OPEN_IMAGE_PATH + QString('\\') + QString("%1.bmp").
			arg(curt.currentDateTime().toTime_t());

		if (!capfream.empty())
		{			
			cv::imwrite(catch_pic_path.toStdString(), capfream);
			ui.text_log->append(QString("snap image %1 success!").arg(curt.currentDateTime().toTime_t()));
		}
	});

	//清除log----清空log框
	connect(ui.btn_clear_log, &QPushButton::clicked, [=]() {
		ui.text_log->clear();
	});
/*
    //diaplay_timer_ = new QTimer(this);
    //diaplay_timer_->setInterval(33);
    //cv::Mat fream;

    //cv::VideoCapture *capture = new cv::VideoCapture(0);
    //if (!capture->isOpened()) 
    //{
    //    ui.text_log->append("open camera failed!");
    //    return;
    //}
    //else
    //{
    //    ui.text_log->append("open camera success!");

    //    (*capture) >> fream;
    //    if (!fream.empty())
    //    {
    //        QImage qfream = Mat2QImage(fream);
    //        ui.label_picture->setPixmap(QPixmap::fromImage(qfream));
    //    }
    //    diaplay_timer_->start(50);
    //}


    //connect(diaplay_timer_, &QTimer::timeout, [=]() {
    //    //ui.text_log->append("show image");

    //    (*capture) >> capfream;
    //    if (!capfream.empty())
    //    {
    //        QImage qfream = Mat2QImage(capfream);
    //        ui.label_picture->setPixmap(QPixmap::fromImage(qfream));
    //    }

    //});
*/
}
//
//void PlayerVideo() {
//    *capture >> capfream;
//}

//刷新机芯列表
void AutoAdjust::RefreshFeatureType()
{
    ui.cbox_feature->clear();
    feature_index_.clear();
    QDir dir(FEATURE_PATH);
    dir.setFilter(QDir::Dirs);
    foreach(QFileInfo fullDir, dir.entryInfoList())
    {
        if (fullDir.fileName() == "." || fullDir.fileName() == "..") continue;
        feature_index_.push_back(fullDir.fileName());
    }
    auto it = feature_index_.begin();
    while (it != feature_index_.end())
    {
        ui.cbox_feature->addItem(*it);
        ++it;
    }
	if(!feature_index_.isEmpty())
		ui.cbox_feature->setCurrentText(*feature_index_.begin());
}

//关闭窗口事件
void AutoAdjust::closeEvent(QCloseEvent * event)
{
	CloseSdkCamera();
}

//处理串口消息
void AutoAdjust::DealSerialMsg()
{
    QByteArray reciver = p_serial_port_->readAll();
    qDebug() << "serial reciver data:" << reciver;
    

}

//串口初始化
void AutoAdjust::SerialInit()
{
	if (!serial_status_)
	{
		QString serial_name = ui.box_serial_id->currentText();
		qint32  serial_baud = ui.box_baud->currentText().toInt();

		if (serial_name.isEmpty()) {
			msg_box.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("串口列表为空"));
			return;
		}
		//设置串口名
		p_serial_port_->setPortName(serial_name);
		//设置波特率
		p_serial_port_->setBaudRate(serial_baud);
		//设置数据为
		p_serial_port_->setDataBits(QSerialPort::Data8);
		//设置校验位
		p_serial_port_->setParity(QSerialPort::NoParity);
		//设置停止为
		p_serial_port_->setStopBits(QSerialPort::OneStop);
		//设置流控制
		p_serial_port_->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制
		 //打开串口
		if (!p_serial_port_->open(QIODevice::ReadWrite))
		{
			qDebug() << serial_name << serial_baud;
			qDebug() << p_serial_port_->error();
			msg_box.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("串口:%1打开失败").arg(serial_name));
		}
		else
		{
			ui.box_baud->setEnabled(false);
			ui.box_serial_id->setEnabled(false);
			ui.btn_open_serial->setText(QString::fromLocal8Bit("关闭串口"));
			serial_status_ = true;
			ui.text_log->append(QString::fromLocal8Bit("串口:%1连接成功").arg(serial_name));
			ui.text_log->append(QString::fromLocal8Bit("串口号：%1").arg(serial_name));
			ui.text_log->append(QString::fromLocal8Bit("波特率：%1").arg(serial_baud));
			ui.text_log->append(QString::fromLocal8Bit("编  码：%1").arg(code_type_));
		}
	}
	else
	{
		serial_status_ = false;
		ui.box_baud->setEnabled(true);
		ui.box_serial_id->setEnabled(true);
		ui.btn_open_serial->setText(QString::fromLocal8Bit("打开串口"));
		p_serial_port_->close();
	}
}

//载入特征配置文件
void AutoAdjust::LoadFeatureCfg()
{
	curt_feature_path_ = QString(FEATURE_PATH) + QString('\\') + select_feature_;
	QString cfg_path = curt_feature_path_ + QString('\\') + select_feature_ + QString("_cfg.ini");

	feature_img_buff_.clear();
	//match_loc_buff_.clear();
	curt_feature_info_.clear();
	curt_faeture_num_ = 0;

	QSettings readcfg(cfg_path, QSettings::IniFormat);
	curt_faeture_num_ = readcfg.value("fea_num").toInt();
	curt_feature_id_ = readcfg.value("cfg_id").toInt();

	for (int i = 0; i < curt_faeture_num_; i++)
	{
		FeatureInfo fea;
		fea.id = readcfg.value(QString("fea%1_id").arg(i + 1)).toInt();
		fea.type = readcfg.value(QString("fea%1_type").arg(i + 1)).toInt();
		fea.x = readcfg.value(QString("cen%1_x").arg(i + 1)).toInt();
		fea.y = readcfg.value(QString("cen%1_y").arg(i + 1)).toInt();

		if (fea.type == RECTANGLE)
		{
			fea.h = readcfg.value(QString("rtg%1_height").arg(i + 1)).toInt();
			fea.w = readcfg.value(QString("rtg%1_width").arg(i + 1)).toInt();
		}
		else if (fea.type == CIRCLE)
		{
			fea.r = readcfg.value(QString("cir%1_radius").arg(i + 1)).toInt();
		}

		fea.part = readcfg.value(QString("part%1_status").arg(i + 1)).toInt();
		if (fea.part == 1)
		{
			fea.left = readcfg.value(QString("part%1_left").arg(i + 1)).toInt();
			fea.top = readcfg.value(QString("part%1_top").arg(i + 1)).toInt();
			fea.right = readcfg.value(QString("part%1_right").arg(i + 1)).toInt();
			fea.bottom = readcfg.value(QString("part%1_bottom").arg(i + 1)).toInt();
		}
		curt_feature_info_.push_back(fea);
	}

	ui.label_fea_id->setText(QString("%1").arg(curt_feature_id_));

	QDir dir(curt_feature_path_);
	QStringList ImageList;
	ImageList << "*.bmp";             //向字符串列表添加图片类型
	dir.setNameFilters(ImageList);    //获得文件夹下图片的名字
	int ImageCount = dir.count();     //获得dir里名字的个数，也表示文件夹下图片的个数
	for (int i = 0; i < ImageCount; i++)
	{
        qDebug() << "name:" << dir[i];
		QString ImageName = curt_feature_path_ + QString('\\') + dir[i];
		cv::Mat cur_img = cv::imread(ImageName.toStdString());
		feature_img_buff_.push_back(cur_img);
	}
	qDebug() << "load feature image " << feature_img_buff_.size() << "th finished!" << endl;

	if (feature_img_buff_.size() != curt_faeture_num_)
	{
		msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("特征文件或者特征已被损坏！"));
		return;
	}
}

//处理匹配结果
void AutoAdjust::DealMatchResult(int i, cv::Point pos_lt, cv::Point pos_rb)
{
    if (pos_lt == cv::Point(0, 0) || pos_rb == cv::Point(0, 0))
    {
        match_thread_[i].quit();
        match_thread_[i].wait();
        ui.text_log->append(QString("feature %1 recognize failed!").arg(i + 1));
        match_loc_buff_[i] = cv::Point(0, 0);
    }
    else
    {
        cv::Point res_loc;
        if (curt_feature_info_[i].part == 1)
        {
            res_loc = (pos_lt + pos_rb)*0.5;
            res_loc.x += curt_feature_info_[i].left;
            res_loc.y += curt_feature_info_[i].top;

            cv::Point tmp_lt = cv::Point(curt_feature_info_[i].left + pos_lt.x, curt_feature_info_[i].top + pos_lt.y);
            cv::Point tmp_rb = cv::Point(curt_feature_info_[i].left + pos_rb.x, curt_feature_info_[i].top + pos_rb.y);
            cv::rectangle(source_img_, tmp_lt, tmp_rb, cvScalar(0, 0, 255, 0), 4, 8, 0);
        }
        else
        {
            res_loc = (pos_lt + pos_rb)*0.5;
            cv::rectangle(source_img_, pos_lt, pos_rb, cvScalar(0, 0, 255, 0), 4, 8, 0);
        }
        match_loc_buff_[i] = res_loc;
    }

    
    thread_flag_[i] = true;
	if (AllThreadFinished())
	{
		ui.text_log->append("match finished");
		cv::Mat dst;
		cv::resize(source_img_, dst, cv::Size(ui.label_picture->width(), ui.label_picture->height()));
		QImage qfream = Mat2QImage(dst);
		ui.label_picture->setPixmap(QPixmap::fromImage(qfream));

		if (curt_faeture_num_ > 0)      ui.label_fea1->setText(QString("(%1,%2)").arg(match_loc_buff_[0].x).arg(match_loc_buff_[0].y));
		if (curt_faeture_num_ > 1)		ui.label_fea2->setText(QString("(%1,%2)").arg(match_loc_buff_[1].x).arg(match_loc_buff_[1].y));
		if (curt_faeture_num_ > 2)		ui.label_fea3->setText(QString("(%1,%2)").arg(match_loc_buff_[2].x).arg(match_loc_buff_[2].y));
		if (curt_faeture_num_ > 3)		ui.label_fea4->setText(QString("(%1,%2)").arg(match_loc_buff_[3].x).arg(match_loc_buff_[3].y));

		last_frame_finished_ = true;
	}
}

//匹配任务，暂时未用到
void AutoAdjust::MatchFeature(cv::Mat &src, cv::Mat &dst)
{
    if (feature_img_buff_.isEmpty())
    {
        msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("获取特征图片失败！"));
        return;
    }

    cv::Mat cpy_img(src);
    //cpy_img.copyTo(src);

    match_loc_buff_.clear();
    for (int i = 0; i < feature_img_buff_.size(); i++)
    {
		ui.text_log->append(QString("feature image type:%1").arg(feature_img_buff_[i].type()));
        int result_cols = src.cols - feature_img_buff_[i].cols + 1;
        int result_rows = src.rows - feature_img_buff_[i].rows + 1;

        double minVal, maxVal;
        cv::Point minLoc, maxLoc, matchLoc;

        char temp[16];

        cv::Mat OutResult;
        OutResult.create(result_cols, result_rows, CV_32FC1);

        //cv::matchTemplate(src, feature_img_buff_[i], OutResult, cv::TM_SQDIFF);
        normalize(OutResult, OutResult, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
        minMaxLoc(OutResult, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

        matchLoc = minLoc;
        int LocX = 0, LocY = 0;
        LocX = matchLoc.x + feature_img_buff_[i].cols / 2;
        LocY = matchLoc.y + feature_img_buff_[i].rows / 2;
        match_loc_buff_.push_back(cv::Point(LocX, LocY));

        LocX = matchLoc.x + feature_img_buff_[i].cols;
        LocY = matchLoc.y + feature_img_buff_[i].rows;
        cv::rectangle(cpy_img, matchLoc, cv::Point(LocX, LocY), cvScalar(0, 0, 255, 0), 2, 8, 0);
    }
    dst = cpy_img;
}

//使能多线程识别特征位置
void AutoAdjust::EnableMatchTask()
{
	//ui.label_fea1->clear();
	//ui.label_fea2->clear();
	//ui.label_fea3->clear();
	//ui.label_fea4->clear();

	thread_flag_.clear();
	area_image_buff_.clear();
	for (int i = 0; i < feature_img_buff_.size(); i++)
	{
		cv::Mat null_mat;
		area_image_buff_.push_back(null_mat);
		if (curt_feature_info_[i].part == 1)
		{
			cv::Rect roi = cv::Rect(cv::Point(curt_feature_info_[i].left, curt_feature_info_[i].top),
				cv::Point(curt_feature_info_[i].right, curt_feature_info_[i].bottom));
			area_image_buff_[i] = source_img_(roi).clone();
			match_thread_[i].SetImageData(area_image_buff_[i], feature_img_buff_[i], 1);
		}
		else
		{
			match_thread_[i].SetImageData(source_img_, feature_img_buff_[i], 0.5);
		}
		match_thread_[i].start();

		thread_flag_.push_back(false);
	}
}

//判断多线程识别特征是否完成
bool AutoAdjust::AllThreadFinished()
{
	auto it = thread_flag_.begin();
    int i = 0;
    while (it != thread_flag_.end() && i < curt_faeture_num_)
	{
		if (!*it)
			return false;
		++it;
        ++i;
	}
	return true;
}

//检测相机是否连接
bool AutoAdjust::TestSdkCamera()
{
	CSystem &systemObj = CSystem::getInstance();
	if (false == systemObj.discovery(m_vCameraPtrList))
	{
		ui.text_log->append("Discovered camera failed");
		return false;
	}

	if (m_vCameraPtrList.size() < 1)
	{
		ui.text_log->append("No camera is discovered ");
		return false;
	}
	else
	{
		ui.text_log->append(QString("A camera is discovered :%1").arg(m_vCameraPtrList[0]->getKey()));
		pSdk_camera_->SetCemera(m_vCameraPtrList[0]->getKey());
	}
	camera_flag_ = true;
	return true;
}

//打开相机
bool AutoAdjust::OpenSdkCamera()
{
	if (TestSdkCamera())
	{
		if (!pSdk_camera_->CameraOpen())
		{
			msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开相机失败！"));
			return false;
		}
		ui.text_log->append("Open camera success");
	}
	else
	{
		msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未检测到相机！"));
		return false;
	}

	if (camera_flag_)
	{
		pSdk_camera_->CameraChangeTrig(SdkCamera::trigContinous);
		pSdk_camera_->CameraStart();
	}

	return true;
}

//关闭相机
void AutoAdjust::CloseSdkCamera()
{
	pSdk_camera_->CameraStop();
	ui.text_log->append("Close camera success");
}



AutoAdjust::~AutoAdjust()
{
	CloseSdkCamera();
    if (p_learn_feature_ != NULL)
    {
        delete p_learn_feature_;
        p_learn_feature_ = NULL;
    }
    if (p_serial_port_ != NULL)
    {
        delete p_serial_port_;
        p_serial_port_ = NULL;
    }
    delete[]match_thread_;
}
