#include <string>
#include <QString>
#include <QVector>

#define PATH "./do/pound0"

class DataTxt
{
public:
	DataTxt();
	//获取一条需要发送的数据
	QString getOneData();
	void init();

private:
	//存放txt中的数据
	QVector< QVector<QString> > m_pounds;

	//当前的日期天
	int m_day;

};