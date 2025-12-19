#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
	Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = nullptr);

	private:
		QPushButton *button;
};

#endif

