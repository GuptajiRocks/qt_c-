#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setWindowTitle("Qt Widgets Demo");
	resize(400, 300);
	button = new QPushButton("Show Dialog", this);
	button->setGeometry(120, 120, 160, 40);
		connect(button, &QPushButton::clicked, this, [](){
				QMessageBox::information(nullptr,"Hello","This is a simple Qt dialog box!");
 		});
}


