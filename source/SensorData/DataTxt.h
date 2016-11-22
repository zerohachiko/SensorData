#include <string>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#define PATH "./doData/day"
#define INDEX 288

class DataTxt: public QObject
{
	Q_OBJECT
public:
	DataTxt();
	//获取一条需要发送的数据
	QString getOneData();
	void init();

private slots:
	void checkTime();
	void doGet();
	void finishedGet(QNetworkReply* reply);
private:
	//存放txt中的数据
	QVector< QVector<QString> > m_pounds;

	//当前的日期天
	int m_day;

	//当前启动程序的时候的时间点，折算成vector中的索引号
	int m_number;

	//监测日期是否变化
	QTimer* m_checkTimer;

	//用来获取天气数据
	QNetworkAccessManager* m_manager;
	QTimer* m_weatherTimer;
	QNetworkRequest* m_request;

	//温度信息
	int m_air_temp;
	int m_water_temp;

};