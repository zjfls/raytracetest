#include "stdafx.h"
#include "qteditor.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "EditorApplication.h"
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
	a.exec();


	EditorApplication::GetInstance()->OnClose();
}
