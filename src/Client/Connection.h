#pragma once

#include <QtCore/QObject>

#include <QtNetwork/QAbstractSocket>

namespace Core
{
	class Connection : public QObject
	{
		Q_OBJECT
	public:
		explicit Connection (QObject *parent = 0);
		virtual ~Connection ();

		void setHost (const QString &host);
		void setPort (const quint16 &port);

	Q_SIGNALS:
		void connected ();
		void disconnected ();
		void error (const QString &errorText);
		void numberReceived (int number);

	public Q_SLOTS:
		void connectToServer ();
		void disconnectFromServer ();
		void sendNumber (int number);

	private:
		Q_DISABLE_COPY (Connection)
		
	private Q_SLOTS:
		void readSocket ();
		void handleSocketError (QAbstractSocket::SocketError socketError);

	private:
		QString host_;
		quint16 port_;
		class QTcpSocket *socket_;
	};
}
