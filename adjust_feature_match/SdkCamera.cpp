#include "SdkCamera.h"
#include "GenICam/System.h"
#include "GenICam/Camera.h"
#include "GenICam/StreamSource.h"

#define DEFAULT_SHOW_RATE (1) // Ĭ����ʾ֡��
#define DEFAULT_ERROR_STRING ("N/A") 
#define MAX_FRAME_STAT_NUM (50) 
#define MIN_LEFT_LIST_NUM (2) 
#define MAX_STATISTIC_INTERVAL (5000000000) // List�ĸ���ʱ������һ֡��ʱ�������

using namespace Dahua::GenICam;
using namespace Dahua::Infra;

SdkCamera::SdkCamera(QWidget *parent)
	: QWidget(parent)
//	, ui(new Ui::CammerWidget)
	, m_thdDisplayThread(CThreadLite::ThreadProc(&SdkCamera::DisplayThreadProc, this), "Display")
	, m_nDisplayInterval(0)
	, m_nFirstFrameTime(0)
	, m_nLastFrameTime(0)
	, m_bNeedUpdate(true)
	, m_nTotalFrameCount(0)
{
	qRegisterMetaType<uint64_t>("uint64_t");
	//connect(this, SIGNAL(signalShowImage(uint8_t*, int, int, uint64_t)), this, SLOT(ShowImage(uint8_t*, int, int, uint64_t)));

	// Ĭ����ʾ30֡
	setDisplayFPS(DEFAULT_SHOW_RATE);

	m_elapsedTimer.start();

	// ������ʾ�߳�
	if (!m_thdDisplayThread.isThreadOver())
	{
		m_thdDisplayThread.destroyThread();
	}
	m_thdDisplayThread.createThread();
}

SdkCamera::~SdkCamera()
{
	//�ر���ʾ�߳�
	if (!m_thdDisplayThread.isThreadOver())
	{
		m_thdDisplayThread.destroyThread();
	}
}

// ȡ���ص�����
void SdkCamera::FrameCallback(const CFrame& frame)
{
	CFrameInfo frameInfo;
	frameInfo.m_nWidth = frame.getImageWidth();
	frameInfo.m_nHeight = frame.getImageHeight();
	frameInfo.m_nBufferSize = frame.getImageSize();
	frameInfo.m_nPaddingX = frame.getImagePadddingX();
	frameInfo.m_nPaddingY = frame.getImagePadddingY();
	frameInfo.m_ePixelType = frame.getImagePixelFormat();
	frameInfo.m_pImageBuf = (BYTE *)malloc(sizeof(BYTE)* frameInfo.m_nBufferSize);
	frameInfo.m_nTimeStamp = frame.getImageTimeStamp();

	/* �ڴ�����ʧ�ܣ�ֱ�ӷ��� */
	if (frameInfo.m_pImageBuf != NULL)
	{
		memcpy(frameInfo.m_pImageBuf, frame.getImage(), frame.getImageSize());

		if (m_qDisplayFrameQueue.size() > 16)
		{
			CFrameInfo frameOld;
			m_qDisplayFrameQueue.get(frameOld);
			free(frameOld.m_pImageBuf);
		}

		m_qDisplayFrameQueue.push_back(frameInfo);
	}

	recvNewFrame(frame);
}

// �����ع�
bool SdkCamera::SetExposeTime(double dExposureTime)
{
	if (NULL == m_pCamera)
	{
		printf("Set ExposureTime fail. No camera or camera is not connected.\n");
		return false;
	}

	CDoubleNode nodeExposureTime(m_pCamera, "ExposureTime");

	if (false == nodeExposureTime.isValid())
	{
		printf("get ExposureTime node fail.\n");
		return false;
	}

	if (false == nodeExposureTime.isAvailable())
	{
		printf("ExposureTime is not available.\n");
		return false;
	}

	if (false == nodeExposureTime.setValue(dExposureTime))
	{
		printf("set ExposureTime value = %f fail.\n", dExposureTime);
		return false;
	}

	return true;
}

// ��������
bool SdkCamera::SetAdjustPlus(double dGainRaw)
{
	if (NULL == m_pCamera)
	{
		printf("Set GainRaw fail. No camera or camera is not connected.\n");
		return false;
	}

	CDoubleNode nodeGainRaw(m_pCamera, "GainRaw");

	if (false == nodeGainRaw.isValid())
	{
		printf("get GainRaw node fail.\n");
		return false;
	}

	if (false == nodeGainRaw.isAvailable())
	{
		printf("GainRaw is not available.\n");
		return false;
	}

	if (false == nodeGainRaw.setValue(dGainRaw))
	{
		printf("set GainRaw value = %f fail.\n", dGainRaw);
		return false;
	}

	return true;
}

// �����
bool SdkCamera::CameraOpen(void)
{
	if (NULL == m_pCamera)
	{
		printf("connect camera fail. No camera.\n");
		return false;
	}

	if (true == m_pCamera->isConnected())
	{
		printf("camera is already connected.\n");
		return true;
	}

	if (false == m_pCamera->connect())
	{
		printf("connect camera fail.\n");
		return false;
	}

	return true;
}


// �ر����
bool SdkCamera::CameraClose(void)
{
	if (NULL == m_pCamera)
	{
		printf("disconnect camera fail. No camera.\n");
		return false;
	}

	if (false == m_pCamera->isConnected())
	{
		printf("camera is already disconnected.\n");
		return true;
	}

	if (false == m_pCamera->disConnect())
	{
		printf("disconnect camera fail.\n");
		return false;
	}

	return true;
}

// ��ʼ�ɼ�
bool SdkCamera::CameraStart()
{
	if (NULL == m_pStreamSource)
	{
		m_pStreamSource = CSystem::getInstance().createStreamSource(m_pCamera);
	}

	if (NULL == m_pStreamSource)
	{
		return false;
	}

	if (m_pStreamSource->isGrabbing())
	{
		return true;
	}

	bool bRet = m_pStreamSource->attachGrabbing(IStreamSource::Proc(&SdkCamera::FrameCallback, this));
	if (!bRet)
	{
		return false;
	}

	if (!m_pStreamSource->startGrabbing())
	{
		return false;
	}

	return true;
}

// ֹͣ�ɼ�
bool SdkCamera::CameraStop()
{
	if (m_pStreamSource != NULL)
	{
		m_pStreamSource->detachGrabbing(IStreamSource::Proc(&SdkCamera::FrameCallback, this));

		m_pStreamSource->stopGrabbing();
		m_pStreamSource.reset();
	}

	/* �����ʾ���� */
	m_qDisplayFrameQueue.clear();

	return true;
}


// �л��ɼ���ʽ��������ʽ �������ɼ����ⲿ���������������
bool SdkCamera::CameraChangeTrig(ETrigType trigType)
{
	if (NULL == m_pCamera)
	{
		printf("Change Trig fail. No camera or camera is not connected.\n");
		return false;
	}

	if (trigContinous == trigType)
	{
		//���ô���ģʽ
		CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
		if (false == nodeTriggerMode.isValid())
		{
			printf("get TriggerMode node fail.\n");
			return false;
		}
		if (false == nodeTriggerMode.setValueBySymbol("Off"))
		{
			printf("set TriggerMode value = Off fail.\n");
			return false;
		}
	}
	else if (trigSoftware == trigType)
	{
		//���ô�����
		CEnumNode nodeTriggerSelector(m_pCamera, "TriggerSelector");
		if (false == nodeTriggerSelector.isValid())
		{
			printf("get TriggerSelector node fail.\n");
			return false;
		}
		if (false == nodeTriggerSelector.setValueBySymbol("FrameStart"))
		{
			printf("set TriggerSelector value = FrameStart fail.\n");
			return false;
		}

		//���ô���ģʽ
		CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
		if (false == nodeTriggerMode.isValid())
		{
			printf("get TriggerMode node fail.\n");
			return false;
		}
		if (false == nodeTriggerMode.setValueBySymbol("On"))
		{
			printf("set TriggerMode value = On fail.\n");
			return false;
		}

		//���ô���ԴΪ����
		CEnumNode nodeTriggerSource(m_pCamera, "TriggerSource");
		if (false == nodeTriggerSource.isValid())
		{
			printf("get TriggerSource node fail.\n");
			return false;
		}
		if (false == nodeTriggerSource.setValueBySymbol("Software"))
		{
			printf("set TriggerSource value = Software fail.\n");
			return false;
		}
	}
	else if (trigLine == trigType)
	{
		//���ô�����
		CEnumNode nodeTriggerSelector(m_pCamera, "TriggerSelector");
		if (false == nodeTriggerSelector.isValid())
		{
			printf("get TriggerSelector node fail.\n");
			return false;
		}
		if (false == nodeTriggerSelector.setValueBySymbol("FrameStart"))
		{
			printf("set TriggerSelector value = FrameStart fail.\n");
			return false;
		}

		//���ô���ģʽ
		CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
		if (false == nodeTriggerMode.isValid())
		{
			printf("get TriggerMode node fail.\n");
			return false;
		}
		if (false == nodeTriggerMode.setValueBySymbol("On"))
		{
			printf("set TriggerMode value = On fail.\n");
			return false;
		}

		//���ô���ԴΪLine1����
		CEnumNode nodeTriggerSource(m_pCamera, "TriggerSource");
		if (false == nodeTriggerSource.isValid())
		{
			printf("get TriggerSource node fail.\n");
			return false;
		}
		if (false == nodeTriggerSource.setValueBySymbol("Line1"))
		{
			printf("set TriggerSource value = Line1 fail.\n");
			return false;
		}
	}

	return true;
}

// ִ��һ������
bool SdkCamera::ExecuteSoftTrig(void)
{
	if (NULL == m_pCamera)
	{
		printf("Set GainRaw fail. No camera or camera is not connected.\n");
		return false;
	}

	CCmdNode nodeTriggerSoftware(m_pCamera, "TriggerSoftware");
	if (false == nodeTriggerSoftware.isValid())
	{
		printf("get TriggerSoftware node fail.\n");
		return false;
	}
	if (false == nodeTriggerSoftware.execute())
	{
		printf("set TriggerSoftware fail.\n");
		return false;
	}

	printf("ExecuteSoftTrig success.\n");
	return true;
}


// ���õ�ǰ���  
void SdkCamera::SetCemera(const QString& strKey)
{
	CSystem &systemObj = CSystem::getInstance();
	m_pCamera = systemObj.getCameraPtr(strKey.toStdString().c_str());
}

// ��ʾ�߳�
void SdkCamera::DisplayThreadProc(Dahua::Infra::CThreadLite& lite)
{
	while (lite.looping())
	{
		CFrameInfo frameInfo;

		if (false == m_qDisplayFrameQueue.get(frameInfo, 500))
		{
			continue;
		}

		// �ж��Ƿ�Ҫ��ʾ��������ʾ���ޣ�30֡�����Ͳ���ת�롢��ʾ����
		if (!isTimeToDisplay())
		{
			/* �ͷ��ڴ� */
			free(frameInfo.m_pImageBuf);
			continue;
		}

		/* mono8��ʽ�ɲ���ת�룬ֱ����ʾ��������ʽ��Ҫ����ת�������ʾ */
		if (Dahua::GenICam::gvspPixelMono8 == frameInfo.m_ePixelType)
		{
			//��ʾ�߳��з�����ʾ�źţ������߳�����ʾͼ��
			emit signalShowImage(frameInfo.m_pImageBuf, frameInfo.m_nWidth, frameInfo.m_nHeight, frameInfo.m_ePixelType);

		}
		else
		{
			/* ת�� */
			uint8_t *pRGBbuffer = NULL;
			int nRgbBufferSize = 0;
			nRgbBufferSize = frameInfo.m_nWidth * frameInfo.m_nHeight * 3;
			pRGBbuffer = (uint8_t *)malloc(nRgbBufferSize);
			if (pRGBbuffer == NULL)
			{
				/* �ͷ��ڴ� */
				free(frameInfo.m_pImageBuf);
				printf("RGBbuffer malloc failed.\n");
				continue;
			}

			IMGCNV_SOpenParam openParam;
			openParam.width = frameInfo.m_nWidth;
			openParam.height = frameInfo.m_nHeight;
			openParam.paddingX = frameInfo.m_nPaddingX;
			openParam.paddingY = frameInfo.m_nPaddingY;
			openParam.dataSize = frameInfo.m_nBufferSize;
			openParam.pixelForamt = frameInfo.m_ePixelType;

			IMGCNV_EErr status = IMGCNV_ConvertToRGB24(frameInfo.m_pImageBuf, &openParam, pRGBbuffer, &nRgbBufferSize);
			if (IMGCNV_SUCCESS != status)
			{
				/* �ͷ��ڴ� */
				printf("IMGCNV_ConvertToRGB24 failed.\n");
				free(frameInfo.m_pImageBuf);
				free(pRGBbuffer);
				return;
			}

			/* �ͷ��ڴ� */
			free(frameInfo.m_pImageBuf);

			//��ʾ�߳��з�����ʾ�źţ������߳�����ʾͼ��
			emit signalShowImage(pRGBbuffer, openParam.width, openParam.height, openParam.pixelForamt);

		}
	}
}

bool SdkCamera::isTimeToDisplay()
{
	CGuard guard(m_mxTime);

	// ����ʾ
	if (m_nDisplayInterval <= 0)
	{
		return false;
	}

	// ��һ֡������ʾ
	if (m_nFirstFrameTime == 0 || m_nLastFrameTime == 0)
	{
		m_nFirstFrameTime = m_elapsedTimer.nsecsElapsed();
		m_nLastFrameTime = m_nFirstFrameTime;

		return true;
	}

	// ��ǰ֡����һ֡�ļ�����������ʾ�������ʾ
	uint64_t nCurTimeTmp = m_elapsedTimer.nsecsElapsed();
	uint64_t nAcquisitionInterval = nCurTimeTmp - m_nLastFrameTime;
	if (nAcquisitionInterval > m_nDisplayInterval)
	{
		m_nLastFrameTime = nCurTimeTmp;
		return true;
	}

	// ��ǰ֡����ڵ�һ֡��ʱ����
	uint64_t nPre = (m_nLastFrameTime - m_nFirstFrameTime) % m_nDisplayInterval;
	if (nPre + nAcquisitionInterval > m_nDisplayInterval)
	{
		m_nLastFrameTime = nCurTimeTmp;
		return true;
	}

	return false;
}

// ������ʾƵ��
void SdkCamera::setDisplayFPS(int nFPS)
{
	if (nFPS > 0)
	{
		CGuard guard(m_mxTime);

		m_nDisplayInterval = 1000 * 1000 * 1000.0 / nFPS;
	}
	else
	{
		CGuard guard(m_mxTime);
		m_nDisplayInterval = 0;
	}
}

// ���ڹر���Ӧ����
void SdkCamera::closeEvent(QCloseEvent * event)
{
	if (NULL != m_pStreamSource && m_pStreamSource->isGrabbing())
		m_pStreamSource->stopGrabbing();
	if (NULL != m_pCamera && m_pCamera->isConnected())
		m_pCamera->disConnect();
}


/* ״̬��ͳ����Ϣ start */
void SdkCamera::resetStatistic()
{
	QMutexLocker locker(&m_mxStatistic);
	m_nTotalFrameCount = 0;
	m_listFrameStatInfo.clear();
	m_bNeedUpdate = true;
}

QString SdkCamera::getStatistic()
{
	if (m_mxStatistic.tryLock(30))
	{
		if (m_bNeedUpdate)
		{
			updateStatistic();
		}

		m_mxStatistic.unlock();
		return m_strStatistic;
	}
	return "";
}

void SdkCamera::updateStatistic()
{
	size_t nFrameCount = m_listFrameStatInfo.size();
	QString strFPS = DEFAULT_ERROR_STRING;
	QString strSpeed = DEFAULT_ERROR_STRING;

	if (nFrameCount > 1)
	{
		quint64 nTotalSize = 0;
		FrameList::const_iterator it = m_listFrameStatInfo.begin();

		if (m_listFrameStatInfo.size() == 2)
		{
			nTotalSize = m_listFrameStatInfo.back().m_nFrameSize;
		}
		else
		{
			for (++it; it != m_listFrameStatInfo.end(); ++it)
			{
				nTotalSize += it->m_nFrameSize;
			}
		}

		const FrameStatInfo& first = m_listFrameStatInfo.front();
		const FrameStatInfo& last = m_listFrameStatInfo.back();

		qint64 nsecs = last.m_nPassTime - first.m_nPassTime;

		if (nsecs > 0)
		{
			double dFPS = (nFrameCount - 1) * ((double)1000000000.0 / nsecs);
			double dSpeed = nTotalSize * ((double)1000000000.0 / nsecs) / (1000.0) / (1000.0) * (8.0);
			strFPS = QString::number(dFPS, 'f', 2);
			strSpeed = QString::number(dSpeed, 'f', 2);
		}
	}

	m_strStatistic = QString("Stream: %1 images   %2 FPS   %3 Mbps")
		.arg(m_nTotalFrameCount)
		.arg(strFPS)
		.arg(strSpeed);
	m_bNeedUpdate = false;
}
void SdkCamera::recvNewFrame(const CFrame& pBuf)
{
	QMutexLocker locker(&m_mxStatistic);
	if (m_listFrameStatInfo.size() >= MAX_FRAME_STAT_NUM)
	{
		m_listFrameStatInfo.pop_front();
	}
	m_listFrameStatInfo.push_back(FrameStatInfo(pBuf.getImageSize(), m_elapsedTimer.nsecsElapsed()));
	++m_nTotalFrameCount;

	if (m_listFrameStatInfo.size() > MIN_LEFT_LIST_NUM)
	{
		FrameStatInfo infoFirst = m_listFrameStatInfo.front();
		FrameStatInfo infoLast = m_listFrameStatInfo.back();
		while (m_listFrameStatInfo.size() > MIN_LEFT_LIST_NUM && infoLast.m_nPassTime - infoFirst.m_nPassTime > MAX_STATISTIC_INTERVAL)
		{
			m_listFrameStatInfo.pop_front();
			infoFirst = m_listFrameStatInfo.front();
		}
	}

	m_bNeedUpdate = true;
}
/* ״̬��ͳ����Ϣ end */
