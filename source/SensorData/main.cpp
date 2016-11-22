#include "HttpPost.h"
#include <QApplication>
#include "QDir"
#include <QDebug>
#include <QDate>
#include <QTime>

void customMessageHandler(QtMsgType type, const char *msg)  
{  
	QString txt;  
	switch (type) {  
		//������Ϣ��ʾ  
	case QtDebugMsg:  
		txt = QString("Debug: %1").arg(msg);  
		break;  
		//һ���warning��ʾ  
	case QtWarningMsg:  
		txt = QString("Warning: %1").arg(msg);  
		break;  
		//���ش�����ʾ  
	case QtCriticalMsg:  
		txt = QString("Critical: %1").arg(msg);  
		break;  
		//����������ʾ  
	case QtFatalMsg:  
		txt = QString("Fatal: %1").arg(msg);  
		abort();  
	}  

	QFile outFile1("./debuglog1.txt");  
	QFile outFile2("./debuglog2.txt");  

	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");

	QString txt2 = txt.append("(").append(current_date).append(")");

	outFile1.open(QIODevice::WriteOnly | QIODevice::Append);  
	if(outFile1.size() >= 1024*10 )  
	{  
		outFile1.close();  
		outFile2.remove();  
		QFile::copy("./debuglog1.txt","./debuglog2.txt");  
		outFile1.remove();  

		QFile outFile3("./debuglog1.txt");  
		outFile3.open(QIODevice::WriteOnly | QIODevice::Append);  
		QTextStream ts(&outFile3);  
		ts << txt2 << endl;  
	}  
	else  
	{  
		QTextStream ts(&outFile1);  
		ts << txt2 << endl;  
	}  
}  

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QDir dir;
	//qInstallMsgHandler(customMessageHandler);
	qDebug() << dir.currentPath();
	HttpPost post;
	post.show();

	return app.exec();
}