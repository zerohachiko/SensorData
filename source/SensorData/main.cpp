#include "HttpPost.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	HttpPost post;
	post.show();

	return app.exec();
}