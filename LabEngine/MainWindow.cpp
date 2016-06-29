#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSoundEffect>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// OpenGL Version
	const int OPENGL_MAJOR_VERSION       = 4;
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
	connect(glWidget, SIGNAL(updateWindowTitle(QString)), this, SLOT(setTitle(QString)));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setTitle(const QString& title)
{
	setWindowTitle(mainWindowTitle + title);
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

void MainWindow::on_XspnBox_valueChanged(double arg1)
{
	int row = ui->ModelList->currentRow();
	if(row == -1){
		return;
	}
	auto model = glWidget->models.at(row);
	model->setLocation(arg1, model->getLocation().y(), model->getLocation().z());
}

void MainWindow::on_YspnBox_valueChanged(double arg1)
{
	int row = ui->ModelList->currentRow();
	if(row == -1){
		return;
	}
	auto model = glWidget->models.at(row);
	model->setLocation(model->getLocation().x(),arg1, model->getLocation().z());
}

void MainWindow::on_ZspnBox_valueChanged(double arg1)
{
	int row = ui->ModelList->currentRow();
	if(row == -1){
		return;
	}
	auto model = glWidget->models.at(row);
	model->setLocation(model->getLocation().x(), model->getLocation().y(), arg1);
}

void MainWindow::on_AddModelBtn_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this->centralWidget(),QString("Open OBJ"),QString(),QString("OBJ Files (*.obj)"));
	qDebug() << filename;
	if(!filename.isEmpty()){
		Model* model = new Model(glWidget->cubePath.toStdString(),glWidget->shader, &(glWidget->physicsSimulation)); //filename.toStdString()
		model->setModelColor(QColor(255,255,255));
		if(model->isValid()){
			glWidget->models.append(model);
			QString name = filename.section('/',-1);
			qDebug() << name;
			ui->ModelList->addItem(new QListWidgetItem(name));
		}else{
			QMessageBox::critical(this->centralWidget(),QString("Error parsing OBJ!"),QString("There was an error parsing the selected .obj file!"),QMessageBox::Ok, QMessageBox::NoButton);
		}


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
	float x = ui->VelocityXSpinBox->value();
	float y = ui->VelocityYSpinBox->value();
	float z = ui->VelocityZSpinBox->value();
	Model* model = glWidget->models.at(0);
	bool error = false;
	if(model){
		auto player = static_cast<PhysicsSphere*>(model->getCollider());
		player->setVelocity(x,y,z);
		if(player->getID() != 1){
			error = true;
		}
	}else{
		error = true;
	}
	if(error){
		qWarning() << "WARNING: PLAYER SPHERE NOT FOUND!";
		QMessageBox::critical(this->centralWidget(),QString("Player Sphere not found!"),QString("There is no Player Sphere in the scene, please restart application!"),QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}
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

void MainWindow::setMainWindowTitle(const QString& value)
{
	mainWindowTitle = value;
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
