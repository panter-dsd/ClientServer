#include <QtCore/QThread>

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "Core/Core.h"

#include "ClientConnection.h"

#include "Server.h"

namespace Core
{
	Server::Server (QObject *parent)
		: QObject (parent)
		, server_ (new QTcpServer (this))
	{
		connect (server_, SIGNAL (newConnection ()), SLOT (appendClientConnection ()));
	}

	Server::~Server()
	{

	}

	bool Server::listen()
	{
		const bool result = server_->listen (QHostAddress::Any, port ());

		if (!result) {
			qCritical () << "Server:" << "error creating server" << server_->errorString ();
		}

		return result;
	}

	quint16 Server::port()
	{
		return 33333;
	}

	void Server::appendClientConnection ()
	{
		qDebug () << "Server:" << "new connection";

		QTcpSocket *socket = server_->nextPendingConnection ();

		ClientConnection *clientConnection = new ClientConnection (socket);

		QThread *thread = Core::moveToThread (clientConnection);
		socket->setParent (nullptr);
		socket->moveToThread (thread);
		
		connect (socket, SIGNAL (disconnected ()), thread, SLOT (quit ()));
		connect (this, SIGNAL (destroyed (QObject *)), thread, SLOT (quit ()));
	}
}
