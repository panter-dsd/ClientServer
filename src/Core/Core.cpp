#include <QtCore/QThread>

#include <QtNetwork/QAbstractSocket>

namespace Core
{
	QThread *moveToThread (QObject *object)
	{
		QThread *thread = new QThread;
		object->moveToThread (thread);

		QObject::connect (thread, SIGNAL (finished ()), object, SLOT (deleteLater ()));
		QObject::connect (thread, SIGNAL (finished ()), thread, SLOT (deleteLater ()));
		thread->start ();

		return thread;
	}

	void writeNumberToSocket (QAbstractSocket &socket, int number)
	{
		socket.write (QString ("%1\n").arg (number).toUtf8 ());
	}

	int readNumberFromSocket (QAbstractSocket &socket, bool &isRead)
	{
		const QByteArray line = socket.readLine ().trimmed ();

		qDebug () << "Core:" << "received from socket" << line;

		return line.toInt (&isRead);
	}
}
