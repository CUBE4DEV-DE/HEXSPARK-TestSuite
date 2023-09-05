#include <QGuiApplication>
#include <QtCore/QCoreApplication>

#include "TTestCloud.h"
#include "TTestObject.h"
#include "TTestEntity.h"
#include "TTestLinq.h"
#include "TTestNetwork.h"
#include "TTestProcess.h"
#include "TTestStorage.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XTest.h"
#include "CoreProcess/XArgs.h"
#include "CoreProcess/XProcess.h"
#include "CoreStorage/XDirectory.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   main
// Method:  main
// Params:  int argc
// Params:  char* argv[]
//----------------------------------------------------------------------------- 

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    if (XArgs::command(a.arguments()))
        return 0;
    
    XDebug::setDebug();
    XDebug::initLog();
    XDebug::resetLog();
    XDebug::setDebugCache(4096);

    //// CoreBase
    //{
    //    TTestObject testobject;
    //    testobject.run();
    //}
    //// CoreBase Entity
    //{
    //    TTestEntity testobject;
    //    testobject.run();
    //}
    //// Linq
    //{
    //    TTestLinq testobject;
    //    testobject.run();
    //}
    //// Storage
    //{
    //    TTestStorage testobject;
    //    testobject.run();
    //}
    // Network
    //{
     //   TTestNetwork testobject;
     //   testobject.run();
    //}
    // Process
    //{
    //    TTestProcess testobject;
    //    testobject.run();
    //}

    // Cloud
    {
        TTestCloud testobject;
        testobject.run();
    }


    XTest::globalResult();
	XDebug::flushLog();

    return 0;
}
