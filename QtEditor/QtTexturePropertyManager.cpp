#include "stdafx.h"
#include "QtTexturePropertyManager.h"
#include "qtpropertybrowserutils_p.h"
#include "FilePath.h"
#include <string>
QtTexturePropertyManager::QtTexturePropertyManager(QObject* pParent)
	: QtAbstractPropertyManager(pParent)
{
}


QtTexturePropertyManager::~QtTexturePropertyManager()
{
}

std::string QtTexturePropertyManager::value(const QtProperty *property) const
{
	return m_values.value(property, std::string(""));
}

QString QtTexturePropertyManager::valueText(const QtProperty *property) const
{
	return value(property).c_str();
}

QIcon QtTexturePropertyManager::valueIcon(const QtProperty *property) const
{
	const PropertyValueMap::const_iterator it = m_values.constFind(property);
	if (it == m_values.constEnd())
		return QIcon();

	//
	QImage img2(tr("./data/texture/990011_N.jpg"));
	QImage img3 = img2.scaled(16,16);

	int height = img3.height();
	int width = img3.width();
	return QPixmap::fromImage(img3);
}

void QtTexturePropertyManager::initializeProperty(QtProperty *property)
{
	m_values[property] = "";
}

void QtTexturePropertyManager::uninitializeProperty(QtProperty *property)
{

}

void QtTexturePropertyManager::setValue(QtProperty *property, std::string &val)
{
	const PropertyValueMap::iterator it = m_values.find(property);
	if (it == m_values.end())
		return;

	if (it.value() == val)
		return;

	it.value() = val;

	emit propertyChanged(property);
	emit valueChanged(property, val);
}

QString QtTexturePropertyManager::filter(const QtProperty *property) const
{
	if (!m_values.contains(property))
		return QString();
	return (std::string("") + "." + getFileSuffix(m_values[property])).c_str();
}
