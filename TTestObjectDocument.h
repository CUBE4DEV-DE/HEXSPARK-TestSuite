#pragma once

#include <QObject>

class TTestObjectDocument : public QObject
{
	Q_OBJECT

public:
	TTestObjectDocument(QObject *parent);
	~TTestObjectDocument();
};
