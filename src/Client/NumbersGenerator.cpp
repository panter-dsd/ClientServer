#include <QtCore/QTimer>
#include <QtCore/QDateTime>

#include "NumbersGenerator.h"

namespace Core
{
	NumbersGenerator::NumbersGenerator (int from, int to, int interval, QObject *parent)
		: QObject (parent)
		, from_ (from)
		, to_ (to)
		, timer_ (new QTimer (this))
	{
		timer_->setSingleShot (false);
		timer_->setInterval (interval);
		connect (timer_, SIGNAL (timeout ()), SLOT (generateNextNumber ()));

		qsrand (QDateTime::currentDateTime ().toTime_t ());
	}

	NumbersGenerator::~NumbersGenerator ()
	{

	}

	void NumbersGenerator::start ()
	{
		timer_->start ();
		generateNextNumber ();
	}

	void NumbersGenerator::stop ()
	{
		timer_->stop ();
	}

	void NumbersGenerator::generateNextNumber ()
	{
		const int number = qrand () % to_ + from_;
		emit numberGenerated (number);
	}

	void NumbersGenerator::setTo (int to)
	{
		to_ = to;
	}

	void NumbersGenerator::setFrom (int from)
	{
		from_ = from;
	}
}
