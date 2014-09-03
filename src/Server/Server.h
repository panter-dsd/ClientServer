#pragma once

#include <QtCore/QObject>

namespace Core
{
	class Server : public QObject
	{
		Q_OBJECT

	public:
		explicit Server (QObject *parent = 0);
		virtual ~Server ();
		
		bool listen ();

	private:
		Q_DISABLE_COPY (Server)
		
		static quint16 port ();
		
	private Q_SLOTS:
		void appendClientConnection ();
		
	private:
		class QTcpServer *server_;
	};
}
