#include "TTestProcess.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XObjectFactory.h"
#include "CoreBase/XSystem.h"

#include  <QtConcurrent>

#include "CoreProcess/XArgs.h"
#include "CoreProcess/XCompile.h"
#include "CoreProcess/XPlugin.h"
#include "CoreProcess/XProcess.h"
#include "CoreStorage/XCrypt.h"
//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestStart
//----------------------------------------------------------------------------- 
void TTestProcess::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestEnd
//----------------------------------------------------------------------------- 
void TTestProcess::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestProcess::TestInit()
{
	XTest::TestInit();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestProcess::TestClear()
{
	XTest::TestClear();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestShell
//----------------------------------------------------------------------------- 
void TTestProcess::TestShell()
{
	XProcess process;
	for(QString env: process.envs())
		O_PARAM(env);

	process.arg("*.h");
	process.arg("/W");
	process.arg("/B");

	process.cmd("dir");

	for (const QString& o : process.output()) O_PARAM(o);
	for (const QString& e : process.error()) O_PARAM(e);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    29.10.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestExe
//----------------------------------------------------------------------------- 

void TTestProcess::TestExe()
{
	XArgs::ping();
	XArgs::copy("./Raw", "./Test/ArgsCopy/LocalData");
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestPlugin
//----------------------------------------------------------------------------- 

void TTestProcess::TestPlugin()
{
	QString testdll("D:/usr/source/20220700_NITROMVC/Framework/x64/Release/TestPlugin.dll");

	QStringList methods= XPlugin::methods(testdll);
	for(const QString&method:methods)
		O_PARAM(method);
	
	QMap<QString,QVariant> values;
	QByteArray result= XPlugin::call(testdll, "ping", values);
	O_PARAM(result);

	XPlugin::unLoad(testdll);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    30.10.2022
// Context: DefaultNamespace
// Class:   TTestProcess
// Method:  TestCompile
//----------------------------------------------------------------------------- 
void TTestProcess::TestCompile()
{
	XCompile::setBuild("C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/msbuild.exe");

	XCompile compile;
	compile.compile("D:/usr/source/20220700_NITROMVC/Portal/TestPlugin/TestPlugin.vcxproj");

	{
		for (const QString& o : compile.output()) O_PARAM(o);
		for (const QString& e : compile.error()) O_PARAM(e);
	}
}



