#pragma once
#include <qdialog.h>
#include <qstring.h>
#include <qgridlayout.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qimage.h>
#include "HeadFiles.h"
class ShowDialog :public QDialog 
{
	Q_OBJECT
public:
	ShowDialog(QString picpath);

public slots:
	void savePic();
	void toStd();
	void toGray();
	void toErode();
	void toBlur();
	void toCanny();

protected:
	void initFilterLayout();
	void initMainLayout(QString picpath);
	QImage cutPic(QString path);
	void setPic(QImage image);

private:
	QGridLayout *mainlayout;
	QGridLayout *filterlayout;
	QHBoxLayout *namelayout;
	QLabel *piclabel;
	QLabel *filterlabel;
	QString stdpath;
	QPushButton *stdbutton;
	QPushButton *graybutton;
	QPushButton *erodebutton;
	QPushButton *blurbutton;
	QPushButton *cannybutton;
	QPushButton *savebutton;
	bool stdflag;
	bool grayflag;
	bool erodeflag;
	bool blurflag;
	bool cannyflag;
};


