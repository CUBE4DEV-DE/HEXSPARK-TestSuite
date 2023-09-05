#include "TTestEntity.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XObjectFactory.h"
#include "CoreBase/XSystem.h"
#include "CoreBase/XLinq.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestStart
//----------------------------------------------------------------------------- 
void TTestEntity::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestEnd
//----------------------------------------------------------------------------- 
void TTestEntity::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestEntity::TestInit()
{
	XTest::TestInit();

	m_Manager = new XObjectManager();
	XObjectFactory::registerClassObject<XSystem>();
	XObjectFactory::registerClassObject<XUser>();
	XObjectFactory::registerClassObject<XTranslate>();

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestEntity::TestClear()
{
	XTest::TestClear();

	delete m_Manager;
	XObjectFactory::clear();

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  createSystem
// Params:  
//----------------------------------------------------------------------------- 
bool TTestEntity::createSystem()
{
	XSystem* system = m_Manager->newSuperObject<XSystem>("SYSTEM");

	if (!system)
	{
		failed("XSystem* failed");
		return false;
	}

	if (system)
	{
		XUser* user = system->user().newObject();

		if (!user)
		{
			failed("XUser* failed");
			return false;
		}

		if (user)
		{
			user->setMail("t@test.de");
		}
		system->user().newObject();
		system->user().newObject();
		system->user().newObject();

		XTranslate* translate = system->translate().newObject();
		if (translate)
		{
			translate->setName("Test");
			translate->setTextDE("TestDE");
			translate->setTextEN("TestEN");
		}

		system->translate().newObject();
		system->translate().newObject();
		system->translate().newObject();

	}
	return true;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  compareSystem
//----------------------------------------------------------------------------- 

void TTestEntity::compareSystem(const QString&filenamea, const QString& filenameb, bool reverse)
{
	{
		m_Manager->open("", filenamea);
		m_Manager->open("", filenameb);

		QString filea=read(filenamea);
		QString fileb=read(filenameb);

		if (reverse)
		{
			if (filea == fileb)
			{
				failed("failed == write read " + filenamea + "<>" + filenameb);
			}
		}
		else
		{
			if (filea != fileb)
			{
				failed("failed != write read " + filenamea + "<>" + filenameb);
			}
		}
	}

	remove(filenamea);
	remove(filenameb);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestSystem
//----------------------------------------------------------------------------- 
void TTestEntity::TestSystem()
{
    if (!createSystem())
        return;

    {
        m_Manager->save("", "database.json");
        if (!exist("database.json"))
        {
            failed("failed database.json");
        }
    }

	{
		m_Manager->save("", "databasecmp.json");
		if (!exist("databasecmp.json"))
		{
			failed("failed databasecmp.json");
		}
	}

    compareSystem("database.json", "databasecmp.json");
}



//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestUser
//----------------------------------------------------------------------------- 
void TTestEntity::TestUser()
{
	if (!createSystem())
		return;

	m_Manager->save("", "database.json");

	XSystem* system = m_Manager->superObject<XSystem>("SYSTEM");

	if (!system)
	{
		failed("XSystem* failed");
		return;
	}

	if (system)
	{
		for (XUser* u : system->user().objects())
		{
			u->setSecondName("Name");
		}
	}

	{
		m_Manager->save("", "databaseuser.json");
		if (!exist("databaseuser.json"))
		{
			failed("failed databaseuser.json");
		}
	}

	compareSystem("database.json", "databaseuser.json",true);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestTranslate
//----------------------------------------------------------------------------- 
void TTestEntity::TestTranslate()
{
	if (!createSystem())
		return;

	m_Manager->save("", "database.json");

	XSystem* system = m_Manager->superObject<XSystem>("SYSTEM");
	if (!system)
	{
		failed("XSystem* failed");
		return;
	}

	if (system)
	{
		for (XTranslate* tr : system->translate().objects())
		{
			tr->setTextFR("TextFR");
		}
	}

	{
		m_Manager->save("", "databasetranslate.json");
		if (!exist("databasetranslate.json"))
		{
			failed("failed databasetranslate.json");
		}
	}

	compareSystem("database.json", "databasetranslate.json", true);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    08.04.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestLinq
//----------------------------------------------------------------------------- 

void TTestEntity::TestLinq()
{
	if (!createSystem())
		return;

	XSystem* system = m_Manager->superObject<XSystem>("SYSTEM");
	if (!system)
	{
		failed("XSystem* failed");
		return;
	}

	O_PARAM(system->user().objects().count());

	//QList<QPointer<XUser> > dst = system->whereUser([](XUser* user) { return !user->getMail().isEmpty(); });
	
	//QList<QPointer<XUser> > dst = 
	//	from(system->user().objects())
	//		.where([](XUser*user) { return !user->getMail().isEmpty(); })
	//		.toList();

	//O_PARAM(dst.count());

	//if (dst.count()!=1)
	//{
	//	failed("failed Count==1");
	//}

	//

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestBenchSet
//----------------------------------------------------------------------------- 

void TTestEntity::TestBenchSet()
{
	if (!createSystem())
		return;

	XSystem* system = m_Manager->superObject<XSystem>("SYSTEM");
	if (!system)
	{
		failed("XSystem* failed");
		return;
	}

	for (int i = 0; i < 10000; i++)
	{
		int j = 0;
		for (XUser* u : system->user().objects())
		{
			u->setFirstName(QString("Name%1").arg(i+j));
			u->setSecondName(QString("Name%1").arg(i+j));

			j++;
		}
	}

}

void TTestEntity::TestBenchSetSame()
{
	if (!createSystem())
		return;

	XSystem* system = m_Manager->superObject<XSystem>("SYSTEM");
	if (!system)
	{
		failed("XSystem* failed");
		return;
	}

	for (int i = 0; i < 10000; i++)
	{
		int j = 0;
		for (XUser* u : system->user().objects())
		{
			u->setFirstName(QString("Name"));
			u->setSecondName(QString("Name"));

			j++;
		}
	}

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestEntity
// Method:  TestBenchGet
//----------------------------------------------------------------------------- 

void TTestEntity::TestBenchGet()
{
	if (!createSystem())
		return;

	XSystem* system = m_Manager->superObject<XSystem>("SYSTEM");
	if (!system)
	{
		failed("XSystem* failed");
		return;
	}

	for (int i = 0; i < 100000; i++)
	{
		int j = 0;
		for (XUser* u : system->user().objects())
		{
			QString firstname=u->getFirstName();
			QString secondname = u->getSecondName();

			j++;
		}
	}

}
