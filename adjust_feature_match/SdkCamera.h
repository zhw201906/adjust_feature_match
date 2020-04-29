#pragma once

#include <QWidget>
#include "GenICam/System.h"
#include "Media/ImageConvert.h"
#include "MessageQue.h"
#include <QElapsedTimer>
#include <QMutex>

/* ״̬��ͳ����Ϣ */
struct FrameStatInfo
{
	quint32     m_nFrameSize;       // ֡��С, ��λ: �ֽ�
	qint64      m_nPassTime;         // ���յ���֡ʱ������������
	FrameStatInfo(int nSize, qint64 nTime) : m_nFrameSize(nSize), m_nPassTime(nTime)
	{
	}
};

/* ֡��Ϣ */
class CFrameInfo : public Dahua::Memory::CBlock
{
public:
	CFrameInfo()
	{
		m_pImageBuf = NULL;
		m_nBufferSize = 0;
		m_nWidth = 0;
		m_nHeight = 0;
		m_ePixelType = Dahua::GenICam::gvspPixelMono8;
		m_nPaddingX = 0;
		m_nPaddingY = 0;
		m_nTimeStamp = 0;
	}

	~CFrameInfo()
	{
	}

public:
	BYTE		*m_pImageBuf;
	int			m_nBufferSize;
	int			m_nWidth;
	int			m_nHeight;
	Dahua::GenICam::EPixelType	m_ePixelType;
	int			m_nPaddingX;
	int			m_nPaddingY;
	uint64_t	m_nTimeStamp;
};


class SdkCamera : public QWidget
{
	Q_OBJECT
public:
	SdkCamera(QWidget *parent);
	~SdkCamera();

	/* ö�ٴ�����ʽ */
	enum ETrigType
	{
		trigContinous = 0,	// ��������
		trigSoftware = 1,	// �������
		trigLine = 2,		// �ⲿ����		
	};

	// �����
	bool CameraOpen(void);
	// �ر����
	bool CameraClose(void);
	// ��ʼ�ɼ�
	bool CameraStart(void);
	// ֹͣ�ɼ�
	bool CameraStop(void);
	// ȡ���ص�����
	void FrameCallback(const Dahua::GenICam::CFrame & frame);
	// �л��ɼ���ʽ��������ʽ �������ɼ����ⲿ���������������
	bool CameraChangeTrig(ETrigType trigType = trigContinous);
	// ִ��һ������        
	bool ExecuteSoftTrig(void);
	// �����ع�
	bool SetExposeTime(double dExposureTime);
	// ��������
	bool SetAdjustPlus(double dGainRaw);
	// ���õ�ǰ���     
	void SetCemera(const QString& strKey);

	/* ״̬��ͳ����Ϣ */
	void resetStatistic();
	QString getStatistic();

	void recvNewFrame(const CFrame& pBuf);
	void updateStatistic();


	// ��ʾ�߳�
	void DisplayThreadProc(Dahua::Infra::CThreadLite& lite);

	// ������ʾƵ�ʣ�Ĭ��һ������ʾ30֡
	void setDisplayFPS(int nFPS);

	// �����֡�Ƿ���ʾ
	bool isTimeToDisplay();

	// ���ڹر���Ӧ����
	void closeEvent(QCloseEvent * event);



public slots:
	// ��ʾһ֡ͼ��
	//bool ShowImage(uint8_t* pRgbFrameBuf, int nWidth, int nHeight, uint64_t nPixelFormat);

signals:
	// ��ʾͼ����źţ���displayThread�з��͸��źţ������߳�����ʾ
	bool signalShowImage(uint8_t* pRgbFrameBuf, int nWidth, int nHeight, uint64_t nPixelFormat);

private:

	Dahua::GenICam::ICameraPtr m_pCamera;							// ��ǰ���
	Dahua::GenICam::IStreamSourcePtr m_pStreamSource;				// ������

	Dahua::Infra::CThreadLite           m_thdDisplayThread;			// ��ʾ�߳�      
	TMessageQue<CFrameInfo>				m_qDisplayFrameQueue;		// ��ʾ����

	/* ������ʾ֡�� */
	Dahua::Infra::CMutex				m_mxTime;
	int									m_nDisplayInterval;         // ��ʾ���
	uintmax_t							m_nFirstFrameTime;          // ��һ֡��ʱ���
	uintmax_t							m_nLastFrameTime;           // ��һ֡��ʱ���
	QElapsedTimer						m_elapsedTimer;				// ������ʱ��������ʾ֡��

	/* ״̬��ͳ����Ϣ */
	typedef std::list<FrameStatInfo> FrameList;
	FrameList   m_listFrameStatInfo;
	QMutex      m_mxStatistic;
	quint64     m_nTotalFrameCount;		// �յ�����֡��
	QString     m_strStatistic;			// ͳ����Ϣ, ����������
	bool		m_bNeedUpdate;

};
