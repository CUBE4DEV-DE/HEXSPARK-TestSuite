#include "TTestLinq.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XObjectFactory.h"
#include "CoreBase/XSystem.h"
#include "CoreBase/XLinq.h"

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestStart
//----------------------------------------------------------------------------- 
void TTestLinq::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestEnd
//----------------------------------------------------------------------------- 
void TTestLinq::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestLinq::TestInit()
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
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestLinq::TestClear()
{
	XTest::TestClear();

	delete m_Manager;
	XObjectFactory::clear();

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  createSystem
//----------------------------------------------------------------------------- 
bool TTestLinq::createSystem()
{
	XSystem* system = m_Manager->newSuperObject<XSystem>("SYSTEM");

	if (!system)
	{
		failed("XSystem* failed");
		return false;
	}

	if (system)
	{
		for (int i = 0; i < 12; i++)
		{
			XUser* user = system->user().newObject();
			if (!user)
			{
				failed("XUser* failed");
				return false;
			}
			if (user)
			{
				user->setUserName(QString("Name%1").arg(i+1));
				user->setMail("t@test.de");
			}
		}

		for (int i = 0; i < 12; i++)
		{
			XTranslate* translate = system->translate().newObject();
			if (translate)
			{	
				translate->setName("Test");
				translate->setTextDE("TestDE");
				translate->setTextEN("TestEN");
			}
		}

	}
	return true;
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestInteger
//----------------------------------------------------------------------------- 

void TTestLinq::TestInteger()
{
	int src[] = { 1,2,3,4,5,6,7,8 };
	auto dst = from(src).where([](int a) { return a % 2 == 1; })      // 1,3,5,7
		.select([](int a) { return a * 2; })           // 2,6,10,14
		.where([](int a) { return a > 2 && a < 12; }) // 6,10
		.toStdVector();

	int targetsrc[]={ 6, 10 };
	auto target = from(targetsrc).toStdVector();

	if (dst != target)
		failed();

	// dst type: std::vector<int>
	// dst items: 6,10
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestStruct
//----------------------------------------------------------------------------- 

void TTestLinq::TestStruct()
{
	struct Man {
		std::string name;
		int age;
	};

	Man src[] = {
		{"Kevin",14},
		{"Anton",18},
		{"Agata",17},
		{"Terra",20},
		{"Layer",15},
	};

	auto dst = from(src).where([](const Man& man) { return man.age < 18; })
		.orderBy([](const Man& man) { return man.age; })
		.select([](const Man& man) { return man.name; })
		.toStdVector();

	std::string targetsrc[] = { "Kevin", "Layer", "Agata" };
	auto target = from(targetsrc).toStdVector();

	if (dst != target)
		failed();

	// dst type: std::vector<std::string>
	// dst items: "Kevin", "Layer", "Agata"
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestAuto
//----------------------------------------------------------------------------- 

void TTestLinq::TestAuto()
{
	struct Tax {
		std::string name;
		int amount_1;
		int amount_2;

		bool operator ==(const Tax& tax) const {
			return name == tax.name
				&& amount_1 == tax.amount_1
				&& amount_2 == tax.amount_2;
		}
	};

	std::vector<Tax> taxes = {
		{"tax 1", 1, 1},
		{"tax 2", 1, 1},
		{"tax 1", 2, 2},
		{"tax 3", 3, 3},
		{"tax 1", 4, 4},
	};

	Tax ans[] = {
		{"tax 1", 7, 7},
		{"tax 2", 1, 1},
		{"tax 3", 3, 3},
	};

	auto dst = from(taxes)
		.groupBy([](const Tax& a) {return a.name; })
		.select([](const auto& pair) { // use of auto here needs c++14
		return Tax{
			pair.first,
			pair.second.sum([](const Tax& a) {return a.amount_1; }),
			pair.second.sum([](const Tax& a) {return a.amount_2; })
		};
			}).toStdVector();

	auto target = from(ans);

	for(int i=0;i<3;i++)
	{
		if (ans[i].name != dst[i].name)
			failed();

		if (ans[i].amount_1!=dst[i].amount_1)
			failed();

		if (ans[i].amount_2!=dst[i].amount_2)
			failed();
	}
	
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestUser
//----------------------------------------------------------------------------- 

void TTestLinq::TestUser()
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

	auto dst = system->fromXUser().where([](XUser* user) { return !user->getMail().isEmpty(); });
	O_PARAM(dst.count());
	if (dst.count() != 12)
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestUserDistinct
//----------------------------------------------------------------------------- 

void TTestLinq::TestUserDistinct()
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

	auto dst = system->fromXUser().where([](XUser* user) { return !user->getMail().isEmpty(); }).distinct([](XUser* user) { return user->getUserName(); });

	O_PARAM(dst.count());

	if (dst.count() != 12)
		failed();


}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestUserOrderBy
//----------------------------------------------------------------------------- 

void TTestLinq::TestUserOrderBy()
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

	auto dst = system->fromXUser().where([](XUser* user) { return !user->getMail().isEmpty(); }).orderBy([](XUser* user) { return user->getUserName(); });

	O_PARAM(dst.count());

	if (dst.count() != 12)
		failed();

}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    26.09.2022
// Context: DefaultNamespace
// Class:   TTestLinq
// Method:  TestUserWhere
//----------------------------------------------------------------------------- 

void TTestLinq::TestUserWhere()
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

	auto dst = system->fromXUser().where([](XUser* user) { return user->getUserName().contains("4"); });

	O_PARAM(dst.count());

	if (dst.count() != 1)
		failed();


}





