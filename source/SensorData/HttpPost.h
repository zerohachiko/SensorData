#include <QWidget>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include "DataTxt.h"

class HttpPost : public QMainWindow
{
	Q_OBJECT
public:
	explicit HttpPost(QWidget* parent = 0);

private slots:
	void finishedPost( QNetworkReply* reply);

private:
	void postData();

private:
	QTimer* m_timer;
	QNetworkAccessManager* m_manager;
	QNetworkRequest* m_request;
	DataTxt* m_data;

};