#pragma once

#include <QMainWindow>
#include "GLWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		Ui::MainWindow* getUi();


		void setMainWindowTitle(const QString& value);

	public slots:
		void updateModelData();
		void setTitle(const QString& title);

	private slots:
		void on_actionQuit_triggered();

		void on_XspnBox_valueChanged(double arg1);

		void on_YspnBox_valueChanged(double arg1);

		void on_ZspnBox_valueChanged(double arg1);

		void on_AddModelBtn_clicked();

		void on_RemoveModelBtn_clicked();

		void on_StartPhysicsBtn_clicked();

		void on_StopPhysicsBtn_clicked();

		void on_ResumePhysicsBtn_clicked();

		void on_PausePhysicsBtn_clicked();

		void on_ModelList_currentRowChanged(int currentRow);

	private:
		Ui::MainWindow *ui;
		GLWidget* glWidget = nullptr;
		QString musicPath = "Resources/Music/track_01_main.mp3";
		QString mainWindowTitle;
};
