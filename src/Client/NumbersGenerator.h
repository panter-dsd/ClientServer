#pragma once

#include <QtCore/QObject>

namespace Core
{
	class NumbersGenerator : public QObject
	{
		Q_OBJECT
		
	public:
		explicit NumbersGenerator (int from, int to, int interval, QObject *parent = nullptr);
		virtual ~NumbersGenerator ();
		
		void setFrom (int from);
		void setTo (int to);
		
	Q_SIGNALS:
		void numberGenerated (int number);
		
	public Q_SLOTS:
		void start ();
		void stop ();

	private:
		Q_DISABLE_COPY (NumbersGenerator)
		
	private Q_SLOTS:
		void generateNextNumber ();
		
	private:
		int from_;
		int to_;
		class QTimer *timer_;
	};
}
