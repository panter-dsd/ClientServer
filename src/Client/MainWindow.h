#pragma once

#include <QtGui/QMainWindow>

#include <memory>

namespace Ui
{
	class MainWindow;
	using MainWindowUi = std::unique_ptr<MainWindow>;
}

namespace Core 
{
	class Connection;
	class NumbersGenerator;
}

namespace Gui
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		explicit MainWindow (QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
		virtual ~MainWindow ();

	private:
		Q_DISABLE_COPY (MainWindow)

		void makeRangeCorrector ();
		void moveConnectionToThread ();
		void changeStartStopButtonText(bool isStart);
		
		static int numberGeneratingTimeout ();
		
	private Q_SLOTS:
		void startOrStop (bool isStart);
		void handleClientError (const QString &errorText);
		void showReceivedNumber (int number);

	private:
		Ui::MainWindowUi ui_;
		Core::Connection *connection_;
		Core::NumbersGenerator *numbersGenerator_;
	};
}
