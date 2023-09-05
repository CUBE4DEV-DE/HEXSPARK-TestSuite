#pragma once

#include "CoreBase/XTest.h"
#include "CoreBase/XObjectManager.h"


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TTestEntity
//----------------------------------------------------------------------------- 

class TTestEntity: public XTest
{
	Q_OBJECT
public:
	virtual void TestStart();
	virtual void TestEnd();
	virtual void TestInit();
	virtual void TestClear();
protected:
	bool createSystem();
	void compareSystem(const QString& filenamea, const QString& filenameb,bool reverse=false);
public slots:
	void TestSystem();
	void TestUser();
	void TestTranslate();
	void TestLinq();
	void TestBenchSet();
	void TestBenchSetSame();
	void TestBenchGet();
private:
	XObjectManager* m_Manager;
};
