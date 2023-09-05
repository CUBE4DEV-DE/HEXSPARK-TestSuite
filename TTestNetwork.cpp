#include "TTestNetwork.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XObjectFactory.h"
#include "CoreBase/XSystem.h"
#include "CoreNetwork/XClient.h"
#include "CoreNetwork/XServer.h"

#include  <QtConcurrent>

#include "CoreNetwork/XSync.h"
#include "CoreStorage/XConfig.h"
#include "CoreStorage/XCrypt.h"
#include "CoreStorage/XDirectory.h"
#include "CoreStorage/XFile.h"
//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  TestStart
//----------------------------------------------------------------------------- 
void TTestNetwork::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  TestEnd
//----------------------------------------------------------------------------- 
void TTestNetwork::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestNetwork::TestInit()
{
	XTest::TestInit();


}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestNetwork::TestClear()
{
	XTest::TestClear();
}


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    23.10.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  waitNetwork
//----------------------------------------------------------------------------- 

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  TestInteger
//----------------------------------------------------------------------------- 

void TTestNetwork::TestServerClient()
{
	QtConcurrent::run([]
		{
			XServer server;
			server.ActionActiv(false);

			server.open(5000);
			server.wait(10);
		});

	QtConcurrent::run([]
		{
			XServer server;
			server.open(5001);
			server.wait(10);
			
		});


	QtConcurrent::run([]
		{
			{
				QByteArray src("SendA");
				QByteArray dst = XClient::call(QHostAddress::LocalHost, 5000, src);
				O_PARAM(src);
				O_PARAM(dst);
			}

			{
				QMap<QString, QVariant> values;

				QByteArray crypt = XCrypt::crypt(qCompress(QByteArray("Hello")),"HALLO");
				values["hash"] = QCryptographicHash::hash(crypt, QCryptographicHash::Algorithm::Md5);

				QMap<QString, QVariant> ret= XClient::action(QHostAddress::LocalHost, 5001,"ping",values, crypt);

				O_PARAM(ret["retcrypt"].toString());

				O_PARAM(ret["stamp"].toString());
				O_PARAM(ret["adress"].toString());
				O_PARAM(ret["port"].toString());
			}

			{
				QMap<QString, QVariant> values;

				QByteArray crypt = XCrypt::crypt(qCompress(QByteArray("Yeah")), "HALLO");
				values["hash"] = QCryptographicHash::hash(crypt, QCryptographicHash::Algorithm::Md5);

				QMap<QString, QVariant> ret = XClient::action(QHostAddress::LocalHost, 5001, "ping", values, crypt);

				O_PARAM(ret["retcrypt"].toString());

				O_PARAM(ret["stamp"].toString());
				O_PARAM(ret["adress"].toString());
				O_PARAM(ret["port"].toString());
			}

			{
				QByteArray src("SendC");
				QByteArray dst = XClient::call(QHostAddress::LocalHost, 5000, src);
				O_PARAM(src);
				O_PARAM(dst);
			}
		});

	{

		QByteArray src("SendB");
		QByteArray dst = XClient::call(QHostAddress::LocalHost, 5000, src);

		O_PARAM(src);
		O_PARAM(dst);

		if (dst != src)
			failed();
	}
	
	int i = 0;
	while (i++ < 10*10)
	{
		QThread::msleep(100);
		QCoreApplication::processEvents();
	}

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    25.10.2022
// Context: DefaultNamespace
// Class:   TTestNetwork
// Method:  TestSync
//----------------------------------------------------------------------------- 

void TTestNetwork::TestSync()
{
	XDirectory::copy("./Raw", "./Test/Client/LocalData");
	XFile::writeBinary("./Test/Client/NetworkSrc.txt", "Test");

	XConfig::setValue("SERVICES","SYNCSERVER", 4000);
	O_PARAM(XConfig::value("SERVICES", "SYNCSERVER").toInt());


	// Syncserver
	QtConcurrent::run([]
		{
			XSync server(XConfig::value("SERVICES","SYNCSERVER").toInt());
			server.setRootPath("./Test/Server");
			server.setAppName("MasterSync");
			server.wait(60);
		});

	// Commands
	XSync client(XConfig::value("SERVICES", "SYNCSERVER").toInt(),QHostAddress::LocalHost);
	client.setRootPath("./Test/Client");

	client.upload("NetworkSrc.txt", "NetworkDst.txt");
	client.upload("NetworkSrc.txt", "NetworkDst2.txt");
	client.remove("NetworkDst2.txt");
	client.download("NetworkDst.txt", "NetworkSrcDownload.txt");
	client.sync("LocalData", "LocalData");
	client.uploadDirectory("LocalData", "LocalDataCopy01");
	client.downloadDirectory("LocalData", "LocalDataCopy02");

	QMap<QString, QVariant> info=XService::serviceInfo(QHostAddress::LocalHost, 4000);
	for(QString key:info.keys())
	{
		QString val = info[key].toString();
		O_PARAM(key + "=" + val);
	}

	QList<QMap<QString, QVariant>> logs= XService::serviceLogs(QHostAddress::LocalHost, 4000);

	for (const QMap<QString, QVariant>& map : logs)
	{
		O_STACK(Log, Map);
		for (QString key : map.keys())
		{
			QString val = map[key].toString();
			O_PARAM(key + "=" + val);
		}
	}

	// Test

	if (!XFile::equal("./Test/Client/NetworkSrc.txt", "./Test/Server/NetworkDst.txt"))
		failed();
	if (!XFile::equal("./Test/Client/NetworkSrc.txt", "./Test/Client/NetworkSrcDownload.txt"))
		failed();
	if (!XDirectory::equal("./Raw", "./Test/Server/LocalData"))
		failed();
	if (!XDirectory::equal("./Raw", "./Test/Client/LocalData"))
		failed();

	if (!XDirectory::equal("./Raw", "./Test/Server/LocalDataCopy01"))
		failed();
	if (!XDirectory::equal("./Raw", "./Test/Client/LocalDataCopy02"))
		failed();

	if (XFile::exists("./Test/Client/NetworkDst2.txt"))
		failed();

}
