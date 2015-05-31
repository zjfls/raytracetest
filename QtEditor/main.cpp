#include "stdafx.h"
#include "qteditor.h"
#include <QtWidgets/QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
	
	//
	AllocConsole();
	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w+t", stdout);
	//
	QApplication a(argc, argv);
	QtEditor w;
	w.show();
	return a.exec();
}
