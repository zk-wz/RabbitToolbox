#include <octoon\editor\mainwindow.h>
#include <QApplication>
#include <QFile>

QString getQssContent(const QString &path)
{
	QFile styleSheet(path);
	if (!styleSheet.open(QIODevice::ReadOnly))
	{
		qWarning("Can't open the style sheet file.");
		return "";
	}
	return styleSheet.readAll();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	a.setStyleSheet(getQssContent(":/qss/default_qss.qss"));

	return a.exec();
}
