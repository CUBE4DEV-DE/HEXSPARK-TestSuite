#pragma once

#include "CoreBase/XTest.h"
#include "CoreBase/XObjectManager.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TTestObject
//----------------------------------------------------------------------------- 

class TTestObject : public XTest
{
	Q_OBJECT

public:
	virtual void TestStart();
	virtual void TestEnd();
	virtual void TestInit();
	virtual void TestClear();

public slots:
	void TestClassName();
	void TestConstructor();
	void TestConstructorUnknown();
	void TestDestructor();
	void TestIndex();
	void TestPropertyString();
	void TestPropertyDateTime();
private:
	XObjectManager* m_Manager;
};
