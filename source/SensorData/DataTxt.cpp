#include "DataTxt.h"
#include <QTime>
#include <QDate>
#include <QFile>
#include <QDebug>

DataTxt::DataTxt()
{
	//�����������ʱ������
	QDate nowtime = QDate::currentDate();
	m_day = nowtime.day();
	m_pounds.resize(7);

}

void DataTxt::init()
{
	//��ȡ��ʼ������Ŀ�������
	for (int i = 0; i < 7; ++i)
	{
		QString path = PATH + QString::number(i, 10) + "date" + QString::number(m_day, 10) + ".txt";
		QFile file(path);
		if ( !file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "open file error: " + path;
		}
		while (!file.atEnd())
		{
			m_pounds[i].push_back( QString(file.readLine()) );
		}
	}
}

QString DataTxt::getOneData()
{
	return "test";
}