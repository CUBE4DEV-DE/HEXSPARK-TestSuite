#include "TTestStorage.h"

#include "CoreBase/XDebug.h"

#include <QDir>

#include "CoreStorage/XFile.h"
#include "CoreStorage/XDirectory.h"
#include "CoreStorage/XBackup.h"
#include "CoreStorage/XCompress.h"
#include "CoreStorage/XRepository.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestStart
//----------------------------------------------------------------------------- 
void TTestStorage::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestEnd
//----------------------------------------------------------------------------- 
void TTestStorage::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestStorage::TestInit()
{
	XTest::TestInit();

	QDir(".").mkpath("Test");
	QDir(".").mkpath("Test/Backup");
	XDirectory::copy("./Raw", "./Test/Data");


}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestStorage::TestClear()
{
	XTest::TestClear();
//	XDirectory::removeDirectory("Test");
}



//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestUserWhere
//----------------------------------------------------------------------------- 

void TTestStorage::TestReadWrite()
{
	QString srccontent = "Test";

	XFile::write("./Test/Test.txt", srccontent);
	QString dstcontent=XFile::read("./Test/Test.txt");

	if (srccontent!= dstcontent)
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    03.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestReadWriteBinary
//----------------------------------------------------------------------------- 

void TTestStorage::TestReadWriteBinary()
{
	QByteArray srccontent = "Test";

	XFile::writeBinary("./Test/Test.txt", srccontent);
	QByteArray dstcontent = XFile::readBinary("./Test/Test.txt");

	if (srccontent != dstcontent)
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    03.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestReadCompress
//----------------------------------------------------------------------------- 

void TTestStorage::TestCompress()
{
	QByteArray srccontent = "Test";
	XFile::writeBinary("./Test/Compress.txt", srccontent);

	XFile::compress("./Test/Compress.txt");
	XFile::remove("./Test/Compress.txt");

	XFile::unCompress("./Test/Compress.txt.z");

	QByteArray dstcontent = XFile::readBinary("./Test/Compress.txt");

	if (srccontent != dstcontent)
		failed();

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    03.10.2022
// Context: DefaultNamespace01
// Class:   TTestStorage
// Method:  TestCopy
//----------------------------------------------------------------------------- 

void TTestStorage::TestCopy()
{
	QByteArray srccontent = "Test";
	XFile::writeBinary("./Test/Copy.txt", srccontent);
	XFile::copy("./Test/Copy.txt", "./Test/Copy2.txt");

	QByteArray dstcontent = XFile::readBinary("./Test/Copy2.txt");

	if (srccontent != dstcontent)
		failed();
}



//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    03.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestBackup
//----------------------------------------------------------------------------- 

void TTestStorage::TestBackup()
{
	{
		XBackup backup;
		backup.setPath("./Test/Data", "./Test/Backup", 0);

		{
			backup.timestamp(QDateTime::currentDateTime(),false);
		}

		QThread::sleep(1);

		XFile::write("./Test/Data/Test.txt", "Test");
		XFile::write("./Test/Data/TestA.txt", "Test");

		{
			backup.timestamp(QDateTime::currentDateTime(), false);
		}
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    03.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestBackupRun
//----------------------------------------------------------------------------- 

void TTestStorage::TestBackupRun()
{
		XBackup backup;
		backup.setPath("./Test/Data", "./Test/BackupRun", 0);

		backup.timestamp();
		QThread::sleep(1);
		XFile::write("./Test/Data/TestRun.txt", "TestRun");
		XFile::write("./Test/Data/TestRunA.txt", "TestRun");
		backup.timestamp();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    18.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestRollBack
//----------------------------------------------------------------------------- 

void TTestStorage::TestRollBack()
{
	{
		XBackup backup;
		backup.setPath("./Test/Data", "./Test/BackupRB", 0);

		{
			backup.timestamp(QDateTime::currentDateTime(), false);
		}

		QThread::sleep(1);

		XFile::write("./Test/Data/TestRB.txt", "Test");
		XFile::write("./Test/Data/TestRBA.txt", "Test");

		{
			backup.timestamp(QDateTime::currentDateTime(), false);
		}

		backup.setDataPath("./Test/DataRunRB");
		backup.rollback(QDateTime::currentDateTime());
	}

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    18.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestRollBackRun
//----------------------------------------------------------------------------- 

void TTestStorage::TestRollBackRun()
{
	XBackup backup;
	backup.setPath("./Test/Data", "./Test/BackupRunRB", 0);

	backup.timestamp();
	QThread::sleep(1);
	XFile::write("./Test/Data/TestRBRun.txt", "TestRun");
	XFile::write("./Test/Data/TestRBRunA.txt", "TestRun");
	backup.timestamp();

	backup.setDataPath("./Test/DataRB");
	backup.rollback(QDateTime::currentDateTime());


}

void TTestStorage::TestRepository()
{
	{
		XRepository repository;
		repository.includeFilter("*.js");
		repository.setPath("./Test/Data", "./Test/Repository");

		{
			repository.version("1","1");
		}

		QThread::sleep(1);

		XFile::write("./Test/Data/Test.js", "Test");
		XFile::write("./Test/Data/TestA.js", "Test");

		{
			repository.version("1", "2");
		}
	}

}

void TTestStorage::TestRepositoryRun()
{
	XRepository repository;
	repository.includeFilter("*.js");
	repository.setPath("./Test/Data", "./Test/RepositoryRun");

	repository.version("2", "1",true);
	repository.wait();
	QThread::sleep(1);
	XFile::write("./Test/Data/TestRun.js", "TestRun");
	XFile::write("./Test/Data/TestRunA.js", "TestRun");
	repository.version("2", "2",true);
	repository.wait();
}

void TTestStorage::TestRepositoryRollBack()
{
	{
		XRepository repository;
		repository.includeFilter("*.js");
		repository.setPath("./Test/Data", "./Test/RepositoryRB");

		{
			repository.version("3", "1");
		}

		QThread::sleep(1);

		XFile::write("./Test/Data/TestRB.js", "Test");
		XFile::write("./Test/Data/TestRBA.js", "Test");

		{
			repository.version("3", "2");
		}

		repository.setDataPath("./Test/DataRunRPRB");
		repository.rollback("3", "2");
	}


}

void TTestStorage::TestRepositoryRollBackRun()
{
	XRepository repository;
	repository.includeFilter("*.js");
	repository.setPath("./Test/Data", "./Test/RepositoryRunRB");

	repository.version("4", "1",true);
	repository.wait();
	QThread::sleep(1);
	XFile::write("./Test/Data/TestRBRun.js", "TestRun");
	XFile::write("./Test/Data/TestRBRunA.js", "TestRun");
	repository.version("4", "2", true);
	repository.wait();

	repository.setDataPath("./Test/DataRPRB");
	repository.rollback("4", "2");


}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    19.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestPack
//----------------------------------------------------------------------------- 

void TTestStorage::TestPack()
{
	XCompress::pack("./Test/Data", "./Test/Data.zip", false);
	XCompress::unPack("./Test/DataZIP", "./Test/Data.zip", false);

	if (!XDirectory::equal("./Test/Data", "./Test/DataZIP"))
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    19.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestCrypt
//----------------------------------------------------------------------------- 

void TTestStorage::TestCrypt()
{
	XFile::crypt("./Test/Data.zip", "./Test/Data.zip.y", "65245656562425645DFGFDSfg");
	XFile::unCrypt("./Test/Data.zip.y", "./Test/Data2.zip", "65245656562425645DFGFDSfg");
	XCompress::unPack("./Test/Data2", "./Test/Data2.zip", false);

	if (!XFile::equal("./Test/Data.zip", "./Test/Data2.zip"))
		failed();

	if (!XDirectory::equal("./Test/Data", "./Test/Data2"))
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    19.10.2022
// Context: DefaultNamespace
// Class:   TTestStorage
// Method:  TestAlias
//----------------------------------------------------------------------------- 

void TTestStorage::TestAlias()
{
	XFile::alias("./Test/MasterData.txt", "MasterData.txt");
	XFile::alias("./Test/SubData.txt", "SubData.txt");

	XFile::write("MasterData.txt", "MasterData");
	XFile::copy("MasterData.txt", "SubData.txt");
	
	if (!XFile::equal("./Test/MasterData.txt", "SubData.txt"))
		failed();

}


