#include "HttpPost.h"
#include <QApplication>
#include "QDir"
#include <QDebug>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QDir dir;
	qDebug() << dir.currentPath();
	HttpPost post;
	post.show();

	return app.exec();
}