#include <string>
#include <QString>
#include <QVector>

#define PATH "./do/pound0"

class DataTxt
{
public:
	DataTxt();
	//��ȡһ����Ҫ���͵�����
	QString getOneData();
	void init();

private:
	//���txt�е�����
	QVector< QVector<QString> > m_pounds;

	//��ǰ��������
	int m_day;

};