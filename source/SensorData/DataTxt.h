#include <string>
#include <QString>
#include <QVector>
#include <QTimer>

#define PATH "./do/pound0"
#define INDEX 288

class DataTxt
{
public:
	DataTxt();
	//��ȡһ����Ҫ���͵�����
	QString getOneData();
	void init();

private slots:
	void checkTime();
private:
	//���txt�е�����
	QVector< QVector<QString> > m_pounds;

	//��ǰ��������
	int m_day;

	//��ǰ���������ʱ���ʱ��㣬�����vector�е�������
	int m_number;

	//��������Ƿ�仯
	QTimer* m_checkTimer;

};