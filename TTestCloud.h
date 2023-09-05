#pragma once

#include "CoreBase/XTest.h"
#include "CoreBase/XObjectManager.h"


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    23.10.2022
// Context: DefaultNamespace
// Class:   TTestCloud
// Method:  TTestCloud
//----------------------------------------------------------------------------- 

class TTestCloud : public XTest
{
	Q_OBJECT
public:
	virtual void TestStart();
	virtual void TestEnd();
	virtual void TestInit();
	virtual void TestClear();
	
public slots:
	void TestLayer();
};


