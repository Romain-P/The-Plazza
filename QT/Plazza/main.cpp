//
// EPITECH PROJECT, 2018
// main
// File description:
// main.cpp
//

#include "plazzagui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlazzaGUI w;
    w.show();

    return a.exec();
}
