
#pragma once

#include "CoreBase/XTest.h"
#include "CoreBase/XObjectManager.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    03.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TTestStorage
//----------------------------------------------------------------------------- 

class TTestStorage : public XTest
{
	Q_OBJECT
public:
	virtual void TestStart();
	virtual void TestEnd();
	virtual void TestInit();
	virtual void TestClear();
public slots:
	void TestReadWrite();
	void TestReadWriteBinary();
	void TestCompress();
	void TestCopy();
	void TestBackup();
	void TestBackupRun();
	void TestRollBack();
	void TestRollBackRun();
	void TestRepository();
	void TestRepositoryRun();
	void TestRepositoryRollBack();
	void TestRepositoryRollBackRun();
	void TestPack();
	void TestCrypt();
	void TestAlias();
};


