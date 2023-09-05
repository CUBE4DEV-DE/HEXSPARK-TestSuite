#include "TTestObject.h"

#include "CoreBase/XDebug.h"
#include "CoreBase/XObjectFactory.h"


//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestStart
//----------------------------------------------------------------------------- 

void TTestObject::TestStart()
{
	XTest::TestStart();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestEnd
//----------------------------------------------------------------------------- 

void TTestObject::TestEnd()
{
	XTest::TestEnd();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestInit
//----------------------------------------------------------------------------- 
void TTestObject::TestInit()
{
	XTest::TestInit();

	m_Manager = new XObjectManager();
	XObjectFactory::registerClassObject<XObject>();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestClear
//----------------------------------------------------------------------------- 
void TTestObject::TestClear()
{
	XTest::TestClear();

	delete m_Manager;
	XObjectFactory::clear();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestClassName
//----------------------------------------------------------------------------- 

void TTestObject::TestClassName()
{
	XObject obj;
	O_PARAM(obj.className());

	if (obj.className() != "XObject")
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestConstructor
//----------------------------------------------------------------------------- 

void TTestObject::TestConstructor()
{
	XObject*obj=m_Manager->newObject("XObject");
	if (obj == Q_NULLPTR)
		failed();

	if (obj)
		m_Manager->deleteObject(obj);
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestConstructorUnknown
//----------------------------------------------------------------------------- 

void TTestObject::TestConstructorUnknown()
{
	XObject* obj = m_Manager->newObject("XXXXXX");
	if (obj != Q_NULLPTR)
		failed();
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestDestructor
//----------------------------------------------------------------------------- 

void TTestObject::TestDestructor()
{
	XObject* obj = m_Manager->newObject("XObject");
	if (obj == Q_NULLPTR)
		failed();

	if (obj)
	{
		if (!m_Manager->deleteObject(obj))
			failed();
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestIndex
//----------------------------------------------------------------------------- 

void TTestObject::TestIndex()
{
	XObject* obj = m_Manager->newObject("XObject");
	if (obj == Q_NULLPTR)
		failed();

	if (obj)
	{
		O_PARAM(obj->strIndex());

		if (obj->strIndex().isEmpty())
			failed();

		if (!m_Manager->deleteObject(obj))
			failed();
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestPropertyString
//----------------------------------------------------------------------------- 
void TTestObject::TestPropertyString()
{
	XObject* obj = m_Manager->newObject("XObject");
	if (obj == Q_NULLPTR)
		failed();

	if (obj)
	{
		O_PARAM(obj->getString("Test"));
		obj->setString("Test","Test1");
		O_PARAM(obj->getString("Test"));

		if (obj->getString("Test") != "Test1")
			failed();

		if (!m_Manager->deleteObject(obj))
			failed();
	}
}

//-----------------------------------------------------------------------------
// Author:  Tobias Post
// Company: CUBE4DEV GmbH
// Date:    07.04.2022
// Context: DefaultNamespace
// Class:   TTestObject
// Method:  TestPropertyDateTime
//----------------------------------------------------------------------------- 
void TTestObject::TestPropertyDateTime()
{
	QDateTime datetime = QDateTime::currentDateTime();
	datetime = QDateTime::fromString(datetime.toString(Qt::ISODate), Qt::ISODate);

	XObject* obj = m_Manager->newObject("XObject");
	if (obj == Q_NULLPTR)
		failed();

	if (obj)
	{
		O_PARAM(obj->getDateTime("Test").toString(Qt::ISODate));
		O_PARAM(datetime.toString(Qt::ISODate));

		obj->setDateTime("Test", datetime);

		O_PARAM(obj->getDateTime("Test").toString(Qt::ISODate));

		if (obj->getDateTime("Test") != datetime)
			failed();

		if (!m_Manager->deleteObject(obj))
			failed();
	}
}
