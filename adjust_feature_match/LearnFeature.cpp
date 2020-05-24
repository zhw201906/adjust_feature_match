#include "LearnFeature.h"
#include "style_sheet_define.h"
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QTextEdit>
#include "MyDisplayLabel.h"
#include <QDebug>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>

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

LearnFeature::LearnFeature(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //ui.label_image->setStyleSheet(LABEL_STYLE_BLACK_BORDER);
    ui.spinBox_x->setRange(0, 10000);
    ui.spinBox_y->setRange(0, 10000);

    ui.checkBox_boxline->setCheckState(Qt::Checked);
    display_box_line_flag_ = true;
    diaplay_pic_flag_ = false;
	part_match_boxline_dsp_ = false;

    ui.radioButton_rec->setChecked(true);
    display_sharp_ = RECTANGLE;
    radius_ = ui.lineEdit_radius->text().toInt();

    width_ = ui.lineEdit_width->text().toInt();
    height_ = ui.lineEdit_height->text().toInt();
    radius_ = ui.lineEdit_radius->text().toInt();

	pt_left_ = ui.lineEdit_left->text().toInt();
	pt_top_ = ui.lineEdit_top->text().toInt();
	pt_right_ = ui.lineEdit_right->text().toInt();
	pt_bottom_ = ui.lineEdit_bottom->text().toInt();

    feature_center_x_ = 0;
    feature_center_y_ = 0;
    feature_num = 0;
	part_match_flag_ = false;
	pt_move_status_ = 0;

    move_flag_ = false;
    //offset_x_ = 0;
    //offset_y_ = 0;

    ui.label_image->installEventFilter(this);

    //this->grabKeyboard();

	//刷新特征列表
	RefreshFeatureList();

    //显示框线状态
    connect(ui.checkBox_boxline, &QCheckBox::stateChanged, [=](int status) {
        if (status == Qt::Unchecked)
            display_box_line_flag_ = false;
        else if (Qt::Checked == status)
            display_box_line_flag_ = true;

        update();
    });

	//添加分区识别
	connect(ui.checkBox_part, &QCheckBox::stateChanged, [=](int status) {
		if (status == Qt::Unchecked)
			part_match_flag_ = false;
		else if (Qt::Checked == status)
		{
			part_match_flag_ = true;
			part_match_boxline_dsp_ = true;
		}
					
		update();
	});

    //修改特征形状
    connect(ui.radioButton_cir, &QRadioButton::clicked, [=]() {
        //qDebug() << "selesct radio id:" << ui.rbtn_ascll->isChecked();
        display_sharp_ = CIRCLE;
        radius_ = ui.lineEdit_radius->text().toInt();
        update();
    });
    connect(ui.radioButton_rec, &QRadioButton::clicked, [=]() {
        //qDebug() << "selesct radio id:" << ui.rbtn_hex->isChecked();
        display_sharp_ = RECTANGLE;
        width_ = ui.lineEdit_width->text().toInt();
        height_ = ui.lineEdit_height->text().toInt();
        update();
    });

    //载入特征图片
    connect(ui.btn_load_image, &QPushButton::clicked, [=]() {
        QString pic_path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图片"), OPEN_IMAGE_PATH,
            tr("Images (*.png *.jpg *.bmp);; All files (*.*)"));

        //ui.text_result->append(pic_path);
        if (!pic_path.isEmpty())
        {
            picture_path_ = pic_path;
            diaplay_pic_flag_ = true;
            QPixmap pix(picture_path_);
            source_picture_ = pix.copy();
            Geometric_Scaling_Image(picture_path_, ui.label_image->width(), ui.label_image->height(), pix);

            //QPixmap showPix = pix.copy(QRect(offset_x_, offset_y_, ui.label_image->width(), ui.label_image->height()));
            ui.label_image->setPixmap(pix);

            qDebug() << picture_path_ << endl;
            origin_feature_pic_ = cv::imread(picture_path_.toStdString());
            //cv::imshow("image", origin_feature_pic_);
            scale_para_ = ui.label_image->width()*1.0f / origin_feature_pic_.cols;
            //scale_min_ = scale_para_;
        }      
    });

    //中心坐标粗定位
    connect(ui.label_image, &MyDisplayLabel::mousePress, [=]() {
        move_pt_head_.setX(ui.label_image->x());
        move_pt_head_.setY(ui.label_image->y());


		if (!diaplay_pic_flag_)
			return;

		if (!part_match_flag_)   //选择特征
        {
            feature_center_x_ = ui.label_image->x() / scale_para_;
            feature_center_y_ = ui.label_image->y() / scale_para_;
            //feature_center_y_ = ui.label_image->height() - ui.label_image->y();
            ui.spinBox_x->setValue(feature_center_x_);
            ui.spinBox_y->setValue(feature_center_y_);
            update();
        }
		else   //设置识别选区
		{
			pt_move_status_++;
			if (pt_move_status_ % 2 == 1)
			{
				pt_left_ = ui.label_image->x() / scale_para_;
				pt_top_ = ui.label_image->y() / scale_para_;
				pt_right_ = ui.label_image->x() / scale_para_;
				pt_bottom_ = ui.label_image->y() / scale_para_;

				ui.lineEdit_left->setText(QString::number(pt_left_));
				ui.lineEdit_top->setText(QString::number(pt_top_));
			}			
			update();
		}
    });

	//鼠标移动画矩形框
	connect(ui.label_image, &MyDisplayLabel::mouseMove, [=]() {
		if (!diaplay_pic_flag_)
			return;

		if (part_match_flag_&&pt_move_status_ % 2 == 1)  //画矩形框
		{
			pt_right_ = ui.label_image->x() / scale_para_;
			pt_bottom_ = ui.label_image->y() / scale_para_;
			update();
		}
	});

	//鼠标释放确定选区
	connect(ui.label_image, &MyDisplayLabel::mouseRelease, [=]() {
        qDebug() << "mouse have release";
        move_pt_tail_.setX(ui.label_image->x());
        move_pt_tail_.setY(ui.label_image->y());

        if (move_flag_)
        {           
            //offset_x_ += (move_pt_head_.x() - move_pt_tail_.x());
            //offset_y_ += (move_pt_head_.y() - move_pt_tail_.y());

            //qDebug() << "move finished! x:" << offset_x_ << " y:" << offset_y_;
            //ShowPictureTask(source_picture_, QPoint(offset_x_, offset_y_));
            return;
        }

        if (!diaplay_pic_flag_)
            return;

		if (part_match_flag_&&pt_move_status_ % 2 == 1)  //画矩形框
		{
			pt_right_ = ui.label_image->x() / scale_para_;
			pt_bottom_ = ui.label_image->y() / scale_para_;
			ui.lineEdit_right->setText(QString::number(pt_right_));
			ui.lineEdit_bottom->setText(QString::number(pt_bottom_));

			pt_move_status_ = 0;
			update();
		}
	});

    void(QSpinBox::*pValueChanged)(int) =  &QSpinBox::valueChanged;
    //中心x坐标细定位
    connect(ui.spinBox_x, pValueChanged, [=](int x) {
        if (diaplay_pic_flag_)
        {       
            feature_center_x_ = x;
            update();
        }
    });

    //中心y坐标细定位
    connect(ui.spinBox_y, pValueChanged, [=](int y) {
        if (diaplay_pic_flag_)
        {
            feature_center_y_ = y;            
            update();
        }       
    });

    //编辑特征尺寸，长宽以及半径
    connect(ui.lineEdit_width, &QLineEdit::editingFinished, [=]() {
        width_ = ui.lineEdit_width->text().toInt();
        update();
    });
    connect(ui.lineEdit_height, &QLineEdit::editingFinished, [=]() {
        height_ = ui.lineEdit_height->text().toInt();
        update();
    });
    connect(ui.lineEdit_radius, &QLineEdit::editingFinished, [=]() {
        radius_ = ui.lineEdit_radius->text().toInt();
        update();
    });

	//修改选区尺寸
	connect(ui.lineEdit_left, &QLineEdit::editingFinished, [=]() {
		pt_left_ = ui.lineEdit_left->text().toInt();		
		update();
	});
	connect(ui.lineEdit_top, &QLineEdit::editingFinished, [=]() {
		pt_top_ = ui.lineEdit_top->text().toInt();
		update();
	});
	connect(ui.lineEdit_right, &QLineEdit::editingFinished, [=]() {
		pt_right_ = ui.lineEdit_right->text().toInt();
		update();
	});
	connect(ui.lineEdit_bottom, &QLineEdit::editingFinished, [=]() {
		pt_bottom_ = ui.lineEdit_bottom->text().toInt();
		update();
	});

	//删除特征按钮
	connect(ui.btn_del_feature, &QPushButton::clicked, [=]() {
		QString feature_name = ui.comboBox_feature->currentText();
		if (feature_name.isEmpty())
			return;
		QString dir_path = QString(FEATURE_PATH) + QString('\\') + feature_name;
	
		QDir dir;
		dir.setPath(dir_path);
		dir.removeRecursively();
		msg_box_.information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("删除特征%1成功！").arg(feature_name));
		RefreshFeatureList();
	});

    //确定特征按钮
    connect(ui.btn_sure_feature, &QPushButton::clicked, [=]() {
		DealEnsureFeature();
    });

    //确定学习按钮
    connect(ui.btn_sure_learn, &QPushButton::clicked, [=]() {
        QString fea_text = "{\n" + ui.text_result->toPlainText() + "\n}";
		if (fea_text.isEmpty())
		{
			msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("未选中任何特征！"));
			return;
		}

        if (ui.lineEdit_name->text().isEmpty() || ui.lineEdit_id->text().isEmpty())
        {
            msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("工件型号或者工件id为空！"));
            return;
        }
        feature_name_ = ui.lineEdit_name->text();
        feature_id_ = ui.lineEdit_id->text().toInt();

        QString pack_path = QString(FEATURE_PATH) + QString('\\') + feature_name_;
		QDir dir;
		if (!dir.exists(pack_path))
		{
			bool res = dir.mkpath(pack_path);
		}
		else
		{
			msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("特征%1已存在！").arg(feature_name_));
			return;
		}

        //解析特征文本成功，开始保存特征
        if (FeatureTextParsing(fea_text))
        {
			SaveFeaturePicture(pack_path);
			SaveFeatureConfigText(pack_path);
        }
        else
            return;

        msg_box_.information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("学习工件特征成功！"));
		RefreshFeatureList();
    });

    //重置特征信息
    connect(ui.btn_reboot_feature, &QPushButton::clicked, [=]() {
        feature_num = 0;
        ui.text_result->clear();
    });
}

LearnFeature::~LearnFeature()
{
}

//发送关闭界面信号
void LearnFeature::closeEvent(QCloseEvent * event)
{
    emit closeUi();
}

void LearnFeature::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Alt)
    {
        qDebug() << "alt have pressed";
        move_flag_ = true;
        this->setCursor(Qt::PointingHandCursor);
        return;
    }      
}

void LearnFeature::keyReleaseEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Alt)
    {
        qDebug() << "alt have released";
        move_flag_ = false;
        this->setCursor(Qt::ArrowCursor);
        return;
    }
}

void LearnFeature::wheelEvent(QWheelEvent *event)    // 滚轮事件
{
    //if (event->delta() > 0) {                    // 当滚轮远离使用者时
    //    if (scale_para_ < 1)
    //        scale_para_ += 0.1;
    //    //ui->textEdit->zoomIn();                // 进行放大
    //}
    //else {                                     // 当滚轮向使用者方向旋转时
    //    if(scale_para_> scale_min_)
    //        scale_para_ -= 0.1;
    //    //ui->textEdit->zoomOut();               // 进行缩小
    //}
    //ShowPictureTask(source_picture_, QPoint(offset_x_, offset_y_));
}

//过滤绘图事件
bool LearnFeature::eventFilter(QObject * watched, QEvent * event)
{
    if (watched == ui.label_image && event->type() == QEvent::Paint)
    {
        ui.label_image->paintEvent((QPaintEvent*)event);
        paintTask();
        return true;
    }
    //else if()
    return QWidget::eventFilter(watched, event);
}

//绘图任务
void LearnFeature::paintTask(void)
{
	if (!diaplay_pic_flag_)
		return;

	
	
	if (part_match_flag_)   //显示选区框
	{
		if ((pt_right_ - pt_left_ < 0) || (pt_bottom_ - pt_top_ < 0))
			return;

		QPainter painter(ui.label_image);
		QPen pen;
		pen.setWidth(2);
		pen.setColor(QColor(0, 255, 0));
		painter.setPen(pen);

		painter.drawRect(pt_left_*scale_para_, pt_top_*scale_para_, (pt_right_ - pt_left_)*scale_para_, (pt_bottom_ - pt_top_)*scale_para_);
	}	
	else if (display_box_line_flag_)  //显示特征框线
    {
        QPainter painter(ui.label_image);
        QPen pen;
        pen.setWidth(5);
        pen.setColor(QColor(255, 0, 0));
        painter.setPen(pen);
        painter.drawPoint(feature_center_x_*scale_para_, feature_center_y_*scale_para_);
        pen.setWidth(1);
        painter.setPen(pen);
        if (display_sharp_ == RECTANGLE)
        {
            int x, y;
            x = feature_center_x_ - width_ / 2;
            y = feature_center_y_ - height_ / 2;

            painter.drawRect(x*scale_para_, y*scale_para_, width_*scale_para_, height_*scale_para_);
        }
        else if (display_sharp_ == CIRCLE)
        {
            int x = feature_center_x_ * scale_para_;
            int y = feature_center_y_ * scale_para_;
            int r = radius_ * scale_para_;
            painter.drawEllipse(QPoint(x, y), r, r);
        }
    }
}

//刷新特征列表
void LearnFeature::RefreshFeatureList()
{
	ui.comboBox_feature->clear();
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
		ui.comboBox_feature->addItem(*it);
		++it;
	}
}

//点击确定当前选中的特征
void LearnFeature::DealEnsureFeature()
{
	feature_num++;
	if (feature_num <= 1)
	{
		ui.text_result->append(QString("  \"fea%1_id\":%2,").arg(feature_num).arg(feature_num));
	}
	else
	{
		ui.text_result->append(QString(",\n  \"fea%1_id\":%2,").arg(feature_num).arg(feature_num));
	}


	if (display_sharp_ == RECTANGLE)
	{
		ui.text_result->append(QString("  \"fea%1_type\":\"rectangle\",").arg(feature_num));
	}
	else if (display_sharp_ == CIRCLE)
	{
		ui.text_result->append(QString("  \"fea%1_type\":\"circle\",").arg(feature_num));
	}

	ui.text_result->append(QString("  \"cen%1_x\":%2,").arg(feature_num).arg(feature_center_x_));
	ui.text_result->append(QString("  \"cen%1_y\":%2,").arg(feature_num).arg(feature_center_y_));
	if (display_sharp_ == RECTANGLE)
	{
		ui.text_result->append(QString("  \"rtg%1_height\":%2,").arg(feature_num).arg(height_));
		ui.text_result->append(QString("  \"rtg%1_width\":%2,").arg(feature_num).arg(width_));
	}
	else if (display_sharp_ == CIRCLE)
	{
		ui.text_result->append(QString("  \"cir%1_radius\":%2,").arg(feature_num).arg(radius_));
	}
	
	if (part_match_flag_)
	{		
		ui.text_result->append(QString("  \"part%1_left\":%2,").arg(feature_num).arg(pt_left_));
		ui.text_result->append(QString("  \"part%1_top\":%2,").arg(feature_num).arg(pt_top_));
		ui.text_result->append(QString("  \"part%1_right\":%2,").arg(feature_num).arg(pt_right_));
		ui.text_result->append(QString("  \"part%1_bottom\":%2,").arg(feature_num).arg(pt_bottom_));
	}
	ui.text_result->append(QString("  \"part%1_status\":%2").arg(feature_num).arg((int)(part_match_flag_)));
}

bool LearnFeature::FeatureTextParsing(QString feaText)
{
    QJsonParseError complex_json_error;
    QJsonDocument complex_parse_doucment = QJsonDocument::fromJson(feaText.toUtf8(), &complex_json_error);
    if (complex_json_error.error != QJsonParseError::NoError)
    {
        msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("特征选取结果格式错误！"));
        return false;
    }
 
    //开始解析json对象
    QJsonObject jsonObject = complex_parse_doucment.object();
    for (int i = 1; i <= feature_num; ++i)
    {       
        FeatureInfo feature_info;
        QString json_str = QString("fea%1_id").arg(i);
        if (jsonObject.contains(json_str))
        {
            feature_info.id = jsonObject[json_str].toInt();
        }
        else
        {
			msg_box_.critical(this, QString::fromLocal8Bit("错误"), json_str + QString::fromLocal8Bit("不存在！"));
			return false;
        }

        json_str = QString("fea%1_type").arg(i);
        if (jsonObject.contains(json_str))
        {
            QString str = jsonObject[json_str].toString();

            if (!str.compare(QString("circle")))
            {
                feature_info.type = CIRCLE;
                QString jsonr = QString("cir%1_radius").arg(i);
                if (jsonObject.contains(jsonr))
                {
                    feature_info.r = jsonObject[jsonr].toInt();

                }
                else
                {
                    msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsonr+QString::fromLocal8Bit("不存在！"));
                    return false;
                }
            }
            else if (!str.compare(QString("rectangle")))
            {
                feature_info.type = RECTANGLE;
                QString jsonw = QString("rtg%1_width").arg(i);
                if (jsonObject.contains(jsonw))
                {
                    feature_info.w = jsonObject[jsonw].toInt();
                }
                else
                {
                    msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsonw+QString::fromLocal8Bit("不存在！"));
                    return false;
                }

                QString jsonh = QString("rtg%1_height").arg(i);
                if (jsonObject.contains(jsonh))
                {
                    feature_info.h = jsonObject[jsonh].toInt();
                }
                else
                {
                    msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsonh+QString::fromLocal8Bit("不存在！"));
                    return false;
                }
            }
        }
        else
        {
            msg_box_.critical(this, QString::fromLocal8Bit("错误"), json_str+QString::fromLocal8Bit("不存在！"));
            return false;
        }

        json_str = QString("cen%1_y").arg(i);
        if (jsonObject.contains(json_str))
        {
            feature_info .y = jsonObject[json_str].toInt();
        }
        else
        {
            msg_box_.critical(this, QString::fromLocal8Bit("错误"), json_str+QString::fromLocal8Bit("不存在！"));
            return false;
        }

        json_str = QString("cen%1_x").arg(i);
        if (jsonObject.contains(json_str))
        {
            feature_info.x = jsonObject[json_str].toInt();
        }
        else
        {
            msg_box_.critical(this, QString::fromLocal8Bit("错误"), json_str+QString::fromLocal8Bit("不存在！"));
            return false;
        }

		json_str = QString("part%1_status").arg(i);
		if (jsonObject.contains(json_str))
		{
			feature_info.part = jsonObject[json_str].toInt();
			if (feature_info.part == 1)   //存在选取
			{
				QString jsontmp = QString("part%1_left").arg(i);
				if (jsonObject.contains(jsontmp))
				{
					feature_info.left = jsonObject[jsontmp].toInt();
				}
				else
				{
					msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsontmp + QString::fromLocal8Bit("不存在！"));
					return false;
				}

				jsontmp = QString("part%1_top").arg(i);
				if (jsonObject.contains(jsontmp))
				{
					feature_info.top = jsonObject[jsontmp].toInt();
				}
				else
				{
					msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsontmp + QString::fromLocal8Bit("不存在！"));
					return false;
				}

				jsontmp = QString("part%1_right").arg(i);
				if (jsonObject.contains(jsontmp))
				{
					feature_info.right = jsonObject[jsontmp].toInt();
				}
				else
				{
					msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsontmp + QString::fromLocal8Bit("不存在！"));
					return false;
				}

				jsontmp = QString("part%1_bottom").arg(i);
				if (jsonObject.contains(jsontmp))
				{
					feature_info.bottom = jsonObject[jsontmp].toInt();
				}
				else
				{
					msg_box_.critical(this, QString::fromLocal8Bit("错误"), jsontmp + QString::fromLocal8Bit("不存在！"));
					return false;
				}
			}			
		}
		else
		{
			msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("不存在！"));
			return false;
		}

        selete_fea_info_.push_back(feature_info);
    }
    return true;
}

void LearnFeature::SaveFeaturePicture(QString &pack_path)
{
	for (int i = 0; i < selete_fea_info_.size(); i++)
	{
		if (selete_fea_info_[i].type == CIRCLE)
		{
			int xl = selete_fea_info_[i].x - selete_fea_info_[i].r;
			xl = xl < 0 ? 0 : xl;
			int xr = selete_fea_info_[i].x + selete_fea_info_[i].r;
			xr = xr > origin_feature_pic_.cols ? origin_feature_pic_.cols : xr;

			int yt = selete_fea_info_[i].y - selete_fea_info_[i].r;
			yt = yt < 0 ? 0 : yt;
			int yb = selete_fea_info_[i].y + selete_fea_info_[i].r;
			yb = yb > origin_feature_pic_.rows ? origin_feature_pic_.rows : yb;

			cv::Rect roi = cv::Rect(cv::Point(xl, yt), cv::Point(xr, yb));
			cv::Mat roi_img = origin_feature_pic_(roi);
			QString roi_path = pack_path + QString('\\') + QString("%1.bmp").arg(selete_fea_info_[i].id);
			cv::imwrite(roi_path.toStdString(), roi_img);
		}
		else if (selete_fea_info_[i].type == RECTANGLE)
		{
			int xl = selete_fea_info_[i].x - selete_fea_info_[i].w / 2;
			xl = xl < 0 ? 0 : xl;
			int xr = selete_fea_info_[i].x + selete_fea_info_[i].w / 2;
			xr = xr > origin_feature_pic_.cols ? origin_feature_pic_.cols : xr;

			int yt = selete_fea_info_[i].y - selete_fea_info_[i].h / 2;
			yt = yt < 0 ? 0 : yt;
			int yb = selete_fea_info_[i].y + selete_fea_info_[i].h / 2;
			yb = yb > origin_feature_pic_.rows ? origin_feature_pic_.rows : yb;

			cv::Rect roi = cv::Rect(cv::Point(xl, yt), cv::Point(xr, yb));
			cv::Mat roi_img = origin_feature_pic_(roi);
			QString roi_path = pack_path + QString('\\') + QString("%1.bmp").arg(selete_fea_info_[i].id);            
			cv::imwrite(roi_path.toStdString(), roi_img);
		}
	}
}

void LearnFeature::SaveFeatureConfigText(QString &path)
{
	QString cfg_path = path + QString('\\') + feature_name_ + QString("_cfg.ini");

	QSettings settings(cfg_path, QSettings::IniFormat);

	settings.setValue("cfg_id", feature_id_);
	settings.setValue("fea_num", feature_num);
	for (int i = 0; i < (feature_num > selete_fea_info_.size() ? selete_fea_info_.size() : feature_num); ++i)
	{
		settings.setValue(QString("fea%1_id").arg(i+1), selete_fea_info_[i].id);
		settings.setValue(QString("fea%1_type").arg(i + 1), selete_fea_info_[i].type);
		settings.setValue(QString("cen%1_x").arg(i + 1), selete_fea_info_[i].x);
		settings.setValue(QString("cen%1_y").arg(i + 1), selete_fea_info_[i].y);
		if (selete_fea_info_[i].type == RECTANGLE)
		{
			settings.setValue(QString("rtg%1_height").arg(i + 1), selete_fea_info_[i].h);
			settings.setValue(QString("rtg%1_width").arg(i + 1), selete_fea_info_[i].w);
		}
		else if (selete_fea_info_[i].type == CIRCLE)
		{
			settings.setValue(QString("cir%1_radius").arg(i + 1), selete_fea_info_[i].r);
		}
		
		settings.setValue(QString("part%1_status").arg(i + 1), selete_fea_info_[i].part);
		if (selete_fea_info_[i].part == 1)
		{
			settings.setValue(QString("part%1_left").arg(i + 1), selete_fea_info_[i].left);
			settings.setValue(QString("part%1_top").arg(i + 1), selete_fea_info_[i].top);
			settings.setValue(QString("part%1_right").arg(i + 1), selete_fea_info_[i].right);
			settings.setValue(QString("part%1_bottom").arg(i + 1), selete_fea_info_[i].bottom);
		}
	}
	
}

void LearnFeature::ShowPictureTask(QPixmap & pix, QPoint offset_pt)
{
    if (offset_pt.x() + ui.label_image->width() > pix.width() || offset_pt.y() + ui.label_image->height() > pix.height())
    {
        msg_box_.critical(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("移动到底！"));
        return;
    }

    QPixmap showPix = pix.copy(QRect(offset_pt.x(), offset_pt.y(), ui.label_image->width(), ui.label_image->height()));
    ui.label_image->setPixmap(showPix);
}






