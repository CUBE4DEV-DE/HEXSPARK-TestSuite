#pragma once

#include <QObject>

class TTestObjectList : public QObject
{
	Q_OBJECT

public:
	TTestObjectList(QObject *parent);
	~TTestObjectList();
};
