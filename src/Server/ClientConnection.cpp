#include <QtNetwork/QTcpSocket>

#include "Core/Core.h"

#include "ClientConnection.h"

namespace Core
{
	ClientConnection::ClientConnection (QTcpSocket *socket, QObject *parent)
		: QObject (parent)
		, socket_ (socket)
	{
		connect (socket_, SIGNAL (readyRead ()), SLOT (readSocket ()));
	}

	ClientConnection::~ClientConnection()
	{
		qDebug () << "ClientConnection:" << "disconnected";
	}

	void ClientConnection::generateAndSendAnswer (int number)
	{
		writeNumberToSocket (*socket_, generateAnswer (number));
	}

	int ClientConnection::generateAnswer (int number)
	{
		return number * 2;
	}

	void ClientConnection::readSocket ()
	{
		while (socket_->canReadLine ()) {
			bool isRead = false;

			const int number = readNumberFromSocket (*socket_, isRead);

			if (isRead) {
				generateAndSendAnswer (number);
			}
		}
	}
}
