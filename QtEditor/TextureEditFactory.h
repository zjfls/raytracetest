#pragma once
#include "qtpropertybrowser.h"
#include <QMap>
#include "qtpropertybrowser.h"
#include "QtTexturePropertyManager.h"

class TextureEdit;

class TextureEditFactory : public QtAbstractEditorFactory < QtTexturePropertyManager >
{
	Q_OBJECT
public:
	TextureEditFactory(QObject *parent = 0)
		: QtAbstractEditorFactory<QtTexturePropertyManager>(parent)
	{ }
	virtual ~TextureEditFactory();
protected:
	virtual void connectPropertyManager(QtTexturePropertyManager *manager);
	virtual QWidget *createEditor(QtTexturePropertyManager *manager, QtProperty *property,
		QWidget *parent);
	virtual void disconnectPropertyManager(QtTexturePropertyManager *manager);
	private slots:
	void slotPropertyChanged(QtProperty *property, const QString &value);
	void slotFilterChanged(QtProperty *property, const QString &filter);
	void slotSetValue(const QString &value);
	void slotEditorDestroyed(QObject *object);
private:
	QMap<QtProperty *, QList<TextureEdit *> > theCreatedEditors;
	QMap<TextureEdit *, QtProperty *> theEditorToProperty;
};

