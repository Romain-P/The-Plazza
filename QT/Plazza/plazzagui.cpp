//
// EPITECH PROJECT, 2018
// plazzagui
// File description:
// plazzagui.cpp
//

#include "plazzagui.h"
#include "ui_plazzagui.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

PlazzaGUI::PlazzaGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlazzaGUI)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

PlazzaGUI::~PlazzaGUI()
{
    delete ui;
}

void PlazzaGUI::on_actionSave_triggered() {
	QString fileName;
	if (currentFile.isEmpty()) {
		fileName = QFileDialog::getSaveFileName(this, "Save");
		currentFile = fileName;
	} else {
		fileName = currentFile;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
		return;
	}
	setWindowTitle(fileName);
	QTextStream out(&file);
	QString text = ui->textEdit->toPlainText();
	out << text;
	file.close();
}

void PlazzaGUI::on_actionSave_as_triggered() {
	QString fileName = QFileDialog::getSaveFileName(this, "Save as");
	QFile file(fileName);

	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
		return;
	}
	currentFile = fileName;
	setWindowTitle(fileName);
	QTextStream out(&file);
	QString text = ui->textEdit->toPlainText();
	out << text;
	file.close();
}

void PlazzaGUI::on_actionExit_triggered() {
	QCoreApplication::quit();
}
