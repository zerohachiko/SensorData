#include "HttpPost.h"
#include <QUrl>
#include <QDebug>
#include <string>

HttpPost::HttpPost(QWidget* parent) :QMainWindow(parent)
{
	m_timer = new QTimer(this);
	m_request = new QNetworkRequest;
	m_manager = new QNetworkAccessManager;
	m_data = new DataTxt;
	m_data->init();

	m_request->setUrl(QUrl("http://112.21.191.49:8088/zhny/api/sensor.info") );
	m_request->setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	//×¢²áÐÅºÅ²Û
	connect(m_timer, SIGNAL(timeout()), SLOT(postData()));
	connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedPost(QNetworkReply*)));

	m_timer->start(300000);
}

void HttpPost::postData()
{
	QString oneData = m_data->getOneData();
	m_manager->post(*m_request, oneData.toUtf8());
}

void HttpPost::finishedPost(QNetworkReply* reply )
{
	qDebug() << reply->readAll();
}