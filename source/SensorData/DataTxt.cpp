#include "DataTxt.h"
#include <QTime>
#include <QDate>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QUrl>

DataTxt::DataTxt()
{
	//�����������ʱ������
	QDate nowdate = QDate::currentDate();
	m_day = nowdate.day();
	//��ú��ʵ�����
	QTime nowtime = QTime::currentTime();
	int hour = nowtime.hour();
	int minute = nowtime.minute();
	m_number = (((hour * 60) + minute) / 5) + 1;
	m_pounds.reserve(7);
	for(int i = 0; i < 7; ++i)
	{
		m_pounds.push_back( QVector<QString>());
	}

	//��ʼ�����ʱ��
	m_checkTimer = new QTimer;
	connect(m_checkTimer, SIGNAL(timeout()), this, SLOT(checkTime()));
	m_checkTimer->start(5000);
	//��ʼ��http
	m_manager = new QNetworkAccessManager;
	m_weatherTimer = new QTimer;
	m_request = new QNetworkRequest;
	connect(m_weatherTimer, SIGNAL(timeout()), this, SLOT(doGet()));
	connect(m_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedGet(QNetworkReply*)));
	m_weatherTimer->start(3000);

}

void DataTxt::init()
{
	//��ȡ��ʼ������Ŀ�������
	for (int i = 1; i < 8; ++i)
	{
		//QString path = PATH + QString::number(i, 10) + "/date" + QString::number(m_day, 10) + ".txt";
		QString path = PATH + QString::number(m_day,10)+"/pound0"+QString::number(i, 10)+".txt";
		QFile file(path);
		if ( !file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "open file error: " + path;
		}
		while (!file.atEnd())
		{
			m_pounds[i-1].push_back( QString(file.readLine()) );
		}
	}
}

QString DataTxt::getOneData()
{
	//����Json����
	QString data("Jsondata=[");
	for (int i = 0; i < 7; ++i)
	{
		QString record = m_pounds[i][m_number];
		QStringList strlist = record.split(",");
		//ˮ������
		data.append("{'type':'0', 'unit':'ppm', 'value':'");
		data.append(strlist[0]);
		data.append("', 'id':'");
		data.append(QString::number(i,10));
		data.append("', 'companyid':'1601'},");
		//�����¶�
		data.append("{'type':'2', 'unit':'du', 'value':'");
		data.append(strlist[1]);
		data.append("', 'id':'");
		data.append(QString::number(i, 10));
		data.append("', 'companyid':'1601'},");
		//ˮ��
		data.append("{'type':'5', 'unit':'du', 'value':'");
		data.append(strlist[2]);
		data.append("', 'id':'");
		data.append(QString::number(i, 10));
		data.append("', 'companyid':'1601'},");
		//����
		data.append("{'type':'8', 'unit':'lm', 'value':'");
		data.append(strlist[3]);
		data.append("', 'id':'");
		data.append(QString::number(i, 10));
		data.append("', 'companyid':'1601'},");
		//ph
		data.append("{'type':'9', 'unit':' ', 'value':'");
		data.append(strlist[4]);
		data.append("', 'id':'");
		data.append(QString::number(i, 10));
		data.append("', 'companyid':'1601'},");


	}

	data[data.length()-1] = ']';

	m_number++;
	qDebug()<<"this index is : "+QString::number(m_number, 10);
	if( INDEX == m_number )
	{
		//˵���µ�һ�쿪ʼ��
		qDebug()<<"a new day======================================================================"<<m_day;
		QDate nowdate = QDate::currentDate();
		int day = nowdate.day();
		m_day = day;
		m_number = 0;
		init();

	}
	//qDebug()<<data;

	return data;
}

void DataTxt::checkTime()
{
	QDate nowdate = QDate::currentDate();
	int day = nowdate.day();
	if( day != m_day)
	{
		//��Ҫ���³�ʼ��
		m_day = day;
		qDebug()<<"a new day======================================================================"<<m_day;
		for (int i = 0; i < 7; ++i)
		{
			m_pounds[i].clear();
		}

		init();
		m_number = 0;
	}
}

void DataTxt::doGet()
{
	m_request->setUrl( QUrl(QString("http://api.36wu.com/Weather/GetWeather?district=����&authkey=5f68217df073462881cfc449ef24fcc8&format=json").toUtf8()) );
	QNetworkReply* reply = m_manager->get(*m_request);
}

void DataTxt::finishedGet(QNetworkReply* reply)
{
	qDebug()<<reply->readAll();
}