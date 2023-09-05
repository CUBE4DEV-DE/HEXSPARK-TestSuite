#pragma once

#include "CoreBase/XTest.h"
#include "CoreBase/XObjectManager.h"


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    23.10.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TTestProcess
//----------------------------------------------------------------------------- 

class TTestProcess : public XTest
{
	Q_OBJECT
public:
	virtual void TestStart();
	virtual void TestEnd();
	virtual void TestInit();
	virtual void TestClear();
	static void waitProcess(qint32 sec = 10);
public slots:
	void TestShell();
	void TestExe();
	void TestPlugin();
	void TestCompile();
};


