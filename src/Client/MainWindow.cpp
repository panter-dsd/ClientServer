#include <QtCore/QThread>

#include <QtGui/QSpinBox>

#include "Core/Core.h"

#include "Connection.h"
#include "NumbersGenerator.h"

#include "MainWindow.h"
#include "ui_MainWindow.h"

class RangeCorrector : public QObject
{
	Q_OBJECT

public:
	RangeCorrector (QSpinBox *rangeFromeEdit, QSpinBox *rangeToEdit, QObject *parent = nullptr)
		: QObject (parent)
		, rangeFromEdit_ (rangeFromeEdit)
		, rangeToEdit_ (rangeToEdit)
	{
		connect (rangeFromEdit_, SIGNAL (valueChanged (int)), SLOT (correctRangeIfNeed ()));
		connect (rangeToEdit_, SIGNAL (valueChanged (int)), SLOT (correctRangeIfNeed ()));

		correctRangeIfNeed ();
	}

	virtual ~RangeCorrector ()
	{

	}

private Q_SLOTS:
	void correctRangeIfNeed ()
	{
		const int from = rangeFromEdit_->value ();

		if (rangeToEdit_->value () <= from) {
			rangeToEdit_->setValue (from + 2);
		}
	}

private:
	Q_DISABLE_COPY (RangeCorrector)

private:
	QSpinBox *rangeFromEdit_;
	QSpinBox *rangeToEdit_;
};

namespace Gui
{
	MainWindow::MainWindow (QWidget *parent, Qt::WindowFlags flags)
		: QMainWindow (parent, flags)
		, ui_ (new Ui::MainWindow)
		, connection_ (new Core::Connection)
		, numbersGenerator_ (new Core::NumbersGenerator (0, 0, numberGeneratingTimeout (), this))
	{
		ui_->setupUi (this);

		makeRangeCorrector();
		moveConnectionToThread ();

		connect (numbersGenerator_, SIGNAL (numberGenerated (int)), connection_, SLOT (sendNumber (int)));
		connect (connection_, SIGNAL (connected ()), numbersGenerator_, SLOT (start ()));
		connect (connection_, SIGNAL (disconnected ()), numbersGenerator_, SLOT (stop ()));
		connect (connection_, SIGNAL (error (QString)), SLOT (handleClientError (QString)));
		connect (connection_, SIGNAL (numberReceived (int)), SLOT (showReceivedNumber (int)));

		connect (ui_->startStopButton_, SIGNAL (clicked (bool)), SLOT (startOrStop (bool)));
	}

	MainWindow::~MainWindow ()
	{
	}

	void MainWindow::makeRangeCorrector()
	{
		RangeCorrector *rangeCorrector = new RangeCorrector (ui_->rangeFromEdit_, ui_->rangeToEdit_, this);
		Q_UNUSED (rangeCorrector);
	}

	void MainWindow::moveConnectionToThread()
	{
		QThread *thread = Core::moveToThread (connection_);
		connect (this, SIGNAL (destroyed (QObject *)), thread, SLOT (quit ()));
	}

	void MainWindow::changeStartStopButtonText (bool isStart)
	{
		ui_->startStopButton_->setText (isStart ? tr ("Stop") : tr ("Start"));
	}

	int MainWindow::numberGeneratingTimeout()
	{
		return 1000;
	}

	void MainWindow::startOrStop (bool isStart)
	{
		ui_->resultLabel_->setText (QString::null);

		numbersGenerator_->setFrom (ui_->rangeFromEdit_->value ());
		numbersGenerator_->setTo (ui_->rangeToEdit_->value ());
		connection_->setHost (ui_->hostEdit_->displayText ());
		connection_->setPort (ui_->portEdit_->text ().toUInt ());

		QMetaObject::invokeMethod (connection_, isStart ? "connectToServer" : "disconnectFromServer");
		changeStartStopButtonText (isStart);
	}

	void MainWindow::handleClientError (const QString &errorText)
	{
		ui_->resultLabel_->setText (errorText);
		ui_->startStopButton_->setChecked (false);
		changeStartStopButtonText (false);
	}

	void MainWindow::showReceivedNumber (int number)
	{
		ui_->resultLabel_->setText (QString::number (number));
	}
}

#include "MainWindow.moc"
