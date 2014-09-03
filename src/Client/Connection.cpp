#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "Core/Core.h"

#include "Connection.h"

namespace Core
{
	Connection::Connection (QObject *parent)
		: QObject (parent)
		, port_ (0)
		, socket_ (nullptr)
	{
	}

	Connection::~Connection()
	{

	}

	void Connection::setHost (const QString &host)
	{
		host_ = host;
	}

	void Connection::setPort (const quint16 &port)
	{
		port_ = port;
	}

	void Connection::connectToServer ()
	{
		if (socket_) {
			disconnectFromServer ();
		}

		socket_ = new QTcpSocket (this);
		connect (socket_, SIGNAL (connected ()), SIGNAL (connected ()));
		connect (socket_, SIGNAL (disconnected ()), SIGNAL (disconnected ()));
		connect (socket_, SIGNAL (readyRead ()), SLOT (readSocket ()));
		connect (socket_,
				 SIGNAL (error (QAbstractSocket::SocketError)),
				 SLOT (handleSocketError (QAbstractSocket::SocketError)));
		socket_->connectToHost (host_, port_);

		qDebug () << "Connection:" << "try connect to host" << host_ << "port" << port_;
	}

	void Connection::disconnectFromServer()
	{
		qDebug () << "Connection:" << "disconnect";

		if (socket_) {
			socket_->disconnectFromHost ();
			socket_->deleteLater ();
			socket_ = nullptr;
		}
	}

	void Connection::sendNumber (int number)
	{
		qDebug () << "Connection:" << "send number" << number;

		if (socket_) {
			writeNumberToSocket (*socket_, number);
		}
	}

	void Connection::readSocket()
	{
		while (socket_->canReadLine ()) {
			bool isRead = false;

			const int number = readNumberFromSocket (*socket_, isRead);

			if (isRead) {
				emit numberReceived (number);
			}
		}
	}

	void Connection::handleSocketError (QAbstractSocket::SocketError socketError)
	{
		Q_UNUSED (socketError);

		emit error (socket_->errorString ());
		disconnectFromServer ();
	}
}
