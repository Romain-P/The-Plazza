/*
** EPITECH PROJECT, 2018
** plazzagui
** File description:
** plazzagui.h
*/

#ifndef PLAZZAGUI_H
#define PLAZZAGUI_H

#include <QMainWindow>

namespace Ui {
class PlazzaGUI;
}

class PlazzaGUI : public QMainWindow
{
	Q_OBJECT

public:
	explicit PlazzaGUI(QWidget *parent = 0);
	~PlazzaGUI();

private:
	Ui::PlazzaGUI *ui;
	QString currentFile;

	void on_actionSave_triggered();
	void on_actionSave_as_triggered();
	void on_actionExit_triggered();
};

#endif // PLAZZAGUI_H
