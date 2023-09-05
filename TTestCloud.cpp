#include "TTestCloud.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XObjectFactory.h"
#include "CoreBase/XSystem.h"

#include  <QtConcurrent>

#include "CoreCloud/XCloud.h"
#include "CoreCloud/XCluster.h"
#include "CoreCloud/XContainer.h"
#include "CoreCloud/XApp.h"
#include "CoreStorage/XDirectory.h"
#include "CoreStorage/XFile.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestCloud
// Method:  TestStart
//----------------------------------------------------------------------------- 
void TTestCloud::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestCloud
// Method:  TestEnd
//----------------------------------------------------------------------------- 
void TTestCloud::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestCloud
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestCloud::TestInit()
{
	XTest::TestInit();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestCloud
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestCloud::TestClear()
{
	XTest::TestClear();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    02.11.2022
// Context: DefaultNamespace
// Class:   TTestCloud
// Method:  TestLayer
//----------------------------------------------------------------------------- 

void TTestCloud::TestLayer()
{

	XCloud cloud;
	cloud.setPath("D:\\CLOUD");
	cloud.setName("CUBE4DEV");
	cloud.Install();
	cloud.InstallQt(cloud.qtPath());

	XCluster& cluster=cloud.child<XCluster>("ClusterTest");
	cluster.Install();
	
	for (int i = 1; i < 4; i++)
	{
		XContainer& container=cluster.child<XContainer>(QString("Container%1").arg(i));
		container.Install();

		for (int j = 1; j < 4; j++)
		{
			XApp& app = container.child<XApp>(QString("App%1").arg(j));
			app.Install();
		}
	}

	cloud.CopyApplicationSource("D:\\usr\\source\\20220700_NITROMVC\\Portal\\TestSuite", "Test\\TestSuite");
	cloud.CopyApplicationSource("D:\\usr\\source\\20220700_NITROMVC\\Portal\\TestPlugin", "Test\\TestPlugin");


	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreStorage", "Core\\CoreStorage");
	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreNetwork", "Core\\CoreNetwork");
	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreProcess", "Core\\CoreProcess");

	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreBase", "Core\\CoreBase");

	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreCloud", "CoreCloud\\CoreCloud");

	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreMVC", "CoreWeb\\CoreMVC");
	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreUX", "CoreWeb\\CoreUX");

	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\Core2D", "Core2D\\Core2D");

	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\Core3D", "Core3D\\Core3D");
	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\Core3DUX", "Core3D\\Core3DUX");

	cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\CoreTools3D", "Core3D\\CoreTools3D");


	//cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\Core2D", "Core\\Core2D");
	//cloud.CopyLibrarySource("D:\\usr\\source\\20220700_NITROMVC\\Core\\Core3D", "Core\\Core3D");
	
}

