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
	m_request->setUrl(QUrl("http://112.21.191.49:8088/zhny/api/sensor.info") );
	m_request->setRawHeader("Content-Type", "application/x-www-form-urlencoded");

	//×¢²áÐÅºÅ²Û
	connect(m_timer, SIGNAL(timeout()), SLOT(postData()));
	connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedPost(QNetworkReply*)));

	m_timer->start(60000);
}

void HttpPost::postData()
{
	QString oneData = m_data->getOneData();
	QString data;
	m_manager->post(*m_request, data.toUtf8());
}

void HttpPost::finishedPost(QNetworkReply* reply )
{
	qDebug() << reply->readAll();
}