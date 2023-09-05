#pragma once

#include "CoreBase/XTest.h"
#include "CoreBase/XObjectManager.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TTestLinq
//----------------------------------------------------------------------------- 

class TTestLinq : public XTest
{
	Q_OBJECT
public:
	virtual void TestStart();
	virtual void TestEnd();
	virtual void TestInit();
	virtual void TestClear();
protected: 
	bool createSystem();
public slots:
	void TestInteger();
	void TestStruct();
	void TestAuto();
	void TestUser();
	void TestUserDistinct();
	void TestUserOrderBy();
	void TestUserWhere();
private:
	XObjectManager* m_Manager;
};


