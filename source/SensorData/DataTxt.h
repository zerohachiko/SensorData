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
	//��ȡһ����Ҫ���͵�����
	QString getOneData();
	void init();

private slots:
	void checkTime();
	void doGet();
	void finishedGet(QNetworkReply* reply);
private:
	//���txt�е�����
	QVector< QVector<QString> > m_pounds;

	//��ǰ��������
	int m_day;

	//��ǰ���������ʱ���ʱ��㣬�����vector�е�������
	int m_number;

	//��������Ƿ�仯
	QTimer* m_checkTimer;

	//������ȡ��������
	QNetworkAccessManager* m_manager;
	QTimer* m_weatherTimer;
	QNetworkRequest* m_request;

	//�¶���Ϣ
	int m_air_temp;
	int m_water_temp;

};