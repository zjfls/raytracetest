#pragma once

#include <QLineEdit>
class TextureEdit : public QWidget
{
	Q_OBJECT
public:
	TextureEdit(QWidget *parent = 0);
	void setFilePath(const QString &filePath) { if (theLineEdit->text() != filePath) theLineEdit->setText(filePath); }
	QString filePath() const { return theLineEdit->text(); }
	void setFilter(const QString &filter) { theFilter = filter; }
	QString filter() const { return theFilter; }
signals:
	void filePathChanged(const QString &filePath);
protected:
	void focusInEvent(QFocusEvent *e);
	void focusOutEvent(QFocusEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	private slots:
	void buttonClicked();
private:
	QLineEdit *theLineEdit;
	QString theFilter;
};

