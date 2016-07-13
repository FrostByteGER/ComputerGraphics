#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QList<QKeySequence> shortcuts;
	shortcuts << QKeySequence("ESC") << QKeySequence("Ctrl+Q");
	ui->actionQuit->setShortcuts(shortcuts);


	// OpenGL Version
	const int OPENGL_MAJOR_VERSION       = 3;
	const int OPENGL_MINOR_VERSION       = 3;

	// OpenGL Buffer Sizes
	const int OPENGL_DEPTH_BUFFER_SIZE   = 24;
	const int OPENGL_STENCIL_BUFFER_SIZE = 8;
	const int OPENGL_RED_BUFFER_SIZE     = 8;
	const int OPENGL_GREEN_BUFFER_SIZE   = 8;
	const int OPENGL_BLUE_BUFFER_SIZE    = 8;
	const int OPENGL_ALPHA_BUFFER_SIZE   = -1;
	const int OPENGL_MSAA_COUNT          = 8;


	QSurfaceFormat format;

	// Set all required Information
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setVersion(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION);
	format.setSamples(OPENGL_MSAA_COUNT); // 8x MSAA
	format.setDepthBufferSize(OPENGL_DEPTH_BUFFER_SIZE);
	format.setStencilBufferSize(OPENGL_STENCIL_BUFFER_SIZE);
	format.setRedBufferSize(OPENGL_RED_BUFFER_SIZE);
	format.setGreenBufferSize(OPENGL_GREEN_BUFFER_SIZE);
	format.setBlueBufferSize(OPENGL_BLUE_BUFFER_SIZE);
	format.setAlphaBufferSize(OPENGL_ALPHA_BUFFER_SIZE);

	glWidget = ui->renderWidget;
	glWidget->setFormat(format);

	qWarning() << "### BUFFER SIZE INFORMATION ###";
	qWarning() << qPrintable("Depth Buffer:   " + QString::number(format.depthBufferSize()));
	qWarning() << qPrintable("Stencil Buffer: " + QString::number(format.stencilBufferSize()));
	qWarning() << qPrintable("Red Buffer:     " + QString::number(format.redBufferSize()));
	qWarning() << qPrintable("Green Buffer:   " + QString::number(format.greenBufferSize()));
	qWarning() << qPrintable("Blue Buffer:    " + QString::number(format.blueBufferSize()));
	qWarning() << qPrintable("Alpha Buffer:   " + QString::number(format.alphaBufferSize()));
	qWarning() << "### END ###";
	connect(glWidget,SIGNAL(updateModels()),this, SLOT(updateModelData()));
	connect(&(glWidget->physicsSimulation),SIGNAL(initiateWin()),this, SLOT(showWinScreen()));

	playlist = new QMediaPlaylist();
	playlist->addMedia(QUrl(musicPath));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	mediaPlayer.setPlaylist(playlist);
	mediaPlayer.setVolume(35);
	mediaPlayer.play();
}

MainWindow::~MainWindow()
{
	delete ui;
}

Ui::MainWindow* MainWindow::getUi()
{
	return ui;
}

void MainWindow::updateModelData()
{
	for(Model* m :glWidget->models){
		ui->ModelList->addItem(new QListWidgetItem(m->getName()));
	}
	ui->ModelList->item(0)->setSelected(true);
	auto pos = glWidget->models.at(0)->getLocation();
	ui->XspnBox->setValue(pos.x());
	ui->YspnBox->setValue(pos.y());
	ui->ZspnBox->setValue(pos.z());
}

void MainWindow::on_actionQuit_triggered()
{
	QApplication::instance()->quit();
}

void MainWindow::on_XspnBox_valueChanged(double value)
{
	int row = ui->ModelList->currentRow();
	if(row == -1){
		return;
	}
	auto model = glWidget->models.at(row);
	model->setLocation(value, model->getLocation().y(), model->getLocation().z());
}

void MainWindow::on_YspnBox_valueChanged(double value)
{
	int row = ui->ModelList->currentRow();
	if(row == -1){
		return;
	}
	auto model = glWidget->models.at(row);
	model->setLocation(model->getLocation().x(),value, model->getLocation().z());
}

void MainWindow::on_ZspnBox_valueChanged(double value)
{
	int row = ui->ModelList->currentRow();
	if(row == -1){
		return;
	}
	auto model = glWidget->models.at(row);
	model->setLocation(model->getLocation().x(), model->getLocation().y(), value);
}

void MainWindow::on_AddModelBtn_clicked()
{
	Model* model = new Model(glWidget->cubePath.toStdString(),QString("Dynamic Obstacle"),glWidget->shader, &(glWidget->physicsSimulation),COLLISION_BOX,MODEL_BOX); //filename.toStdString()
	model->setModelColor(QColor(255,255,255));
	model->setLocation(0,0,0);
	if(model->isValid()){
		glWidget->models.append(model);
		qDebug() << model->getName();
		ui->ModelList->addItem(new QListWidgetItem(model->getName()));

	}
}

void MainWindow::on_RemoveModelBtn_clicked()
{
	int row = ui->ModelList->currentRow();
	auto item =  ui->ModelList->takeItem(row);
	if(!item || row == -1){
		qDebug() << "NO ITEM OR ROW FOUND";
		return;
	}
	auto model =  glWidget->models.at(row);
	qDebug() << model->getName();
	delete model;
	glWidget->models.remove(row);
}

void MainWindow::on_StartPhysicsBtn_clicked()
{
	if(glWidget->models.empty()){
		qDebug() << "NO OBJECTS IN SCENE FOUND";
		QMessageBox::critical(this->centralWidget(),QString("No objects in scene found!"),QString("There are no objects in the scene, please restart application!"),QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}

	float x = ui->VelocityXSpinBox->value()/-100.0f;
	float y = ui->VelocityYSpinBox->value()/-100.0f;
	float z = ui->VelocityZSpinBox->value()/-100.0f;
	Model* model = glWidget->models.at(0);
	bool error = false;
	if(model){
		auto id = model->getCollider()->getID();
		if(id == 1){
			auto player = static_cast<PhysicsSphere*>(model->getCollider());
			if(player){
				player->setVelocity(x,y,z);
			}else{
				error = true;
			}
			Model* model2 = glWidget->models.at(1);
			auto id2 = model2->getCollider()->getID();
			if(id2 != 2){
				error = true;
			}
		}else{
			error = true;
		}
	}else{
		error = true;
	}
	if(error){
		qWarning() << "WARNING: PLAYER SPHERE OR WIN-BOX NOT FOUND!";
		QMessageBox::critical(this->centralWidget(),QString("Player Sphere or Win-Box not found!"),QString("There is no Player Sphere or Win-Box in the scene, please restart application!"),QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
	ui->RemoveModelBtn->setEnabled(false);
	glWidget->physicsSimulation.start();
	ui->StartPhysicsBtn->setEnabled(false);
	ui->PausePhysicsBtn->setEnabled(true);
	ui->StopPhysicsBtn->setEnabled(true);
}

void MainWindow::on_StopPhysicsBtn_clicked()
{
	glWidget->physicsSimulation.quit();
	ui->ResumePhysicsBtn->setEnabled(false);
	ui->PausePhysicsBtn->setEnabled(false);
	ui->StopPhysicsBtn->setEnabled(false);
}

void MainWindow::on_ResumePhysicsBtn_clicked()
{
	glWidget->physicsSimulation.TogglePause();
	ui->ResumePhysicsBtn->setEnabled(false);
	ui->PausePhysicsBtn->setEnabled(true);
}

void MainWindow::on_PausePhysicsBtn_clicked()
{
	glWidget->physicsSimulation.TogglePause();
	ui->ResumePhysicsBtn->setEnabled(true);
	ui->PausePhysicsBtn->setEnabled(false);
}

void MainWindow::on_ModelList_currentRowChanged(int currentRow)
{
	if(currentRow == -1){
		return;
	}
	auto pos = glWidget->models.at(currentRow)->getLocation();
	ui->XspnBox->setValue(pos.x());
	ui->YspnBox->setValue(pos.y());
	ui->ZspnBox->setValue(pos.z());
}

void MainWindow::on_actionAbout_triggered()
{
	QMessageBox::about(this->centralWidget(), QString("Minigolf | LabEngine v0.0.2"), QString("Made by Kevin Kügler and Jan Schult"));
}

void MainWindow::showWinScreen(){
	if(!won){
		won = true;
		QMessageBox::about(this->centralWidget(),QString("You Won!!!"), QString("Congratulations, you won! To play again, press CTRL+R or select Reinitialize Scene from File Menu"));
	}

}

void MainWindow::on_remEnergySpinBox_valueChanged(double value)
{
	for(Model* model : glWidget->models){
		model->getCollider()->setRemainingEnergy(value);
	}
}

void MainWindow::on_horiFrictionSpinBox_valueChanged(double value)
{
	for(Model* model : glWidget->models){
		model->getCollider()->setHorizontalFriction(value);
	}
}

void MainWindow::on_vertFrictionSpinBox_valueChanged(double value)
{
	for(Model* model : glWidget->models){
		model->getCollider()->setVerticalFriction(value);
	}
}

void MainWindow::on_gravitySpinBox_valueChanged(double value)
{
	glWidget->physicsSimulation.setG(value);
}

void MainWindow::on_simulationPauseSpinBox_valueChanged(int value)
{
	glWidget->physicsSimulation.setPauseTickTime(value);
}

void MainWindow::on_actionRestart_Scene_triggered()
{
	qApp->quit();
	QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::on_actionControls_triggered()
{
	QMessageBox::about(this->centralWidget(),QString("Control Sheet"), QString("Hold the Right Mousebutton and use WASD to move in the scene. \nQ and E are for vertical movement. \n\nUse F1 to toggle Wireframe Mode. \n\nUse F2 and F3 to move the light around."));
}
