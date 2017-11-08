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

	public slots:
		void updateModelData();
		void showWinScreen();

	private slots:
		void on_actionQuit_triggered();

		void on_XspnBox_valueChanged(double value);

		void on_YspnBox_valueChanged(double value);

		void on_ZspnBox_valueChanged(double value);

		void on_AddModelBtn_clicked();

		void on_RemoveModelBtn_clicked();

		void on_StartPhysicsBtn_clicked();

		void on_StopPhysicsBtn_clicked();

		void on_ResumePhysicsBtn_clicked();

		void on_PausePhysicsBtn_clicked();

		void on_ModelList_currentRowChanged(int currentRow);

		void on_actionAbout_triggered();

		void on_remEnergySpinBox_valueChanged(double value);

		void on_horiFrictionSpinBox_valueChanged(double value);

		void on_vertFrictionSpinBox_valueChanged(double value);

		void on_gravitySpinBox_valueChanged(double value);

		void on_simulationPauseSpinBox_valueChanged(int value);

		void on_actionRestart_Scene_triggered();

		void on_actionControls_triggered();

	private:
		Ui::MainWindow *ui;
		GLWidget* glWidget = nullptr;
};
