#pragma once
#include "qtpropertybrowser.h"
#include <QMap>
#include <string>
class QtTexturePropertyManager :
	public QtAbstractPropertyManager
{
	Q_OBJECT
public:
	QtTexturePropertyManager(QObject *parent = 0);
	virtual ~QtTexturePropertyManager();
	//
	std::string value(const QtProperty *property) const;
	QString filter(const QtProperty *property) const;

	public Q_SLOTS:
	void setValue(QtProperty *property, std::string &val);
Q_SIGNALS:
	void valueChanged(QtProperty *property, std::string &val);
protected:
	QString valueText(const QtProperty *property) const;
	QIcon valueIcon(const QtProperty *property) const;
	virtual void initializeProperty(QtProperty *property);
	virtual void uninitializeProperty(QtProperty *property);
private:
	typedef QMap<const QtProperty *, std::string> PropertyValueMap;
	PropertyValueMap m_values;
};

