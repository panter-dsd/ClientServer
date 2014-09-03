#include <QtCore/QObject>

class QThread;
class QAbstractSocket;

namespace Core
{
	QThread *moveToThread (QObject *object);
	void writeNumberToSocket (QAbstractSocket &socket, int number);
	int readNumberFromSocket (QAbstractSocket &socket, bool &isRead);
}
