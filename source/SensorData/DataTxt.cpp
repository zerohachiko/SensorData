﻿#include "DataTxt.h"
#include <QTime>
#include <QDate>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QUrl>
#include <iostream>
#include <QtScript>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>

DataTxt::DataTxt()
{
	//获得启动程序时的日期
	QDate nowdate = QDate::currentDate();
	m_day = nowdate.day();
	//获得合适的索引
	QTime nowtime = QTime::currentTime();
	int hour = nowtime.hour();
	int minute = nowtime.minute();
	m_number = (((hour * 60) + minute) / 5) + 1;
	m_pounds.reserve(7);
	for(int i = 0; i < 7; ++i)
	{
		m_pounds.push_back( QVector<QString>());
	}

	//初始化监测时间
	m_checkTimer = new QTimer;
	connect(m_checkTimer, SIGNAL(timeout()), this, SLOT(checkTime()));
	m_checkTimer->start(5000);
	//初始化http
	m_manager = new QNetworkAccessManager;
	m_weatherTimer = new QTimer;
	m_request = new QNetworkRequest;
	m_request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	connect(m_weatherTimer, SIGNAL(timeout()), this, SLOT(doGet()));
	connect(m_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedGet(QNetworkReply*)));
	m_weatherTimer->start(180000);

}

void DataTxt::init()
{
	//读取初始化当天的可用数据
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
	//构建Json数据
	QString data("Jsondata=[");
	for (int i = 0; i < 7; ++i)
	{
		QString record = m_pounds[i][m_number];
		QStringList strlist = record.split(",");
		//水中融氧
		data.append("{'type':'0', 'unit':'ppm', 'value':'");
		data.append(strlist[0]);
		data.append("', 'id':'");
		data.append(QString::number(i,10));
		data.append("', 'companyid':'1601'},");
		//空气温度
		data.append("{'type':'2', 'unit':'du', 'value':'");
		data.append(QString::number(m_air_temp, 10));
		data.append("', 'id':'");
		data.append(QString::number(i, 10));
		data.append("', 'companyid':'1601'},");
		//水温
		data.append("{'type':'5', 'unit':'du', 'value':'");
		data.append(QString::number(m_water_temp, 10));
		data.append("', 'id':'");
		data.append(QString::number(i, 10));
		data.append("', 'companyid':'1601'},");
		//光照
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
		//说明新的一天开始了
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
		//需要重新初始化
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

	QString strUrl("https://api.thinkpage.cn/v3/weather/now.json?key=xzir1neqw2fcxgq1&location=changzhou&language=zh-Hans&unit=c");
	qDebug()<<strUrl;
	QUrl url(strUrl);
	m_request->setUrl( url );
	QNetworkReply* reply = m_manager->get(*m_request);
}

void DataTxt::finishedGet(QNetworkReply* reply)
{

	QString jsonStr(reply->readAll());
	QScriptEngine engine;
	QScriptValue sc =  engine.evaluate("value=" + jsonStr);
	if (sc.property("results").isArray())   //解析数组
	{
		QScriptValueIterator it(sc.property("results"));
		while(it.hasNext())
		{
			it.next();
			if (!it.value().property("now").toString().isEmpty())
			{
				m_air_temp =  it.value().property("now").property("temperature").toInteger();
				m_water_temp = m_air_temp + 2;
				qDebug()<<"空气温度为： "<<m_air_temp;
			}
		}
	}

}