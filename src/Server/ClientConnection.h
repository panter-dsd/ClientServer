#pragma once

#include <QtCore/QObject>

class QTcpSocket;

namespace Core
{
	class ClientConnection : public QObject
	{
		Q_OBJECT
	public:
		explicit ClientConnection (QTcpSocket *socket, QObject *parent = 0);
		virtual ~ClientConnection ();

	private:
		Q_DISABLE_COPY (ClientConnection)

		void generateAndSendAnswer (int number);
		static int generateAnswer (int number);

	private Q_SLOTS:
		void readSocket ();

	private:
		QTcpSocket *socket_;
	};
}
