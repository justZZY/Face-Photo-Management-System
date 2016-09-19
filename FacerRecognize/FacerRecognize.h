#ifndef FACERRECOGNIZE_H
#define FACERRECOGNIZE_H

#include <QtWidgets/QMainWindow>
#include <opencv2\face\facerec.hpp>
#include <qtreewidget.h>
#include <qlistwidget.h>
#include <qgridlayout.h>
#include <qfiledialog.h>
#include <qtextstream.h>
#include <qlist.h>
#include <qtoolbar.h>
#include <qmenu.h>
#include <qmenubar.h>
#include <qtoolbutton.h>
#include <qtextcodec.h>
#include <qwidget.h>
#include <qinputdialog.h>
#include <qevent.h>
#include <qtimer.h>
#include <iostream>
#include <cstdlib>
#include "ui_facerrecognize.h"
#include "SqlOperation.h"
#include "CV_Face.h"
#include "ShowDialog.h"

class FacerRecognize : public QMainWindow
{
	Q_OBJECT

public:
	FacerRecognize(SqlOperation *sqlop, QWidget *parent = 0);
	~FacerRecognize();
	void createLeft(QTreeWidget *LeftTreeWidget);
	void createRight(QListWidget *RightListWidget);
	void createMain(QGridLayout *MainLayout, QTreeWidget *LeftTreeWidget, QListWidget *RightListWidget);
	void addRightPic(QString picpath, QListWidget *RightListWidget);
	QTreeWidgetItem * addTreeRoot(QTreeWidget *LeftTreeWidget, QString str);
	void addTreeChild(QTreeWidgetItem *parent, QString str);
	void createAction();
	void createMenu();
	void createToolBars();
	void readTreefromMap();
	//virtual void contextMenuEvent(QContextMenuEvent *);
	QString getCurrentName();

protected slots:
	void openFileOperation();
	void setPathsToRight(QTreeWidgetItem *, int);
	void setPathsToDialog(QTreeWidgetItem *, int);
	void setPathToDialog(QListWidgetItem *);
	void changePicLabel();
	void deletePicfromDB();
	void signalManager(QListWidgetItem *);
	void createRightMenu();
	void clearAll();
	void addSample();

private:
	Ui::FacerRecognizeClass ui;
	QGridLayout *MainLayout;
	QTreeWidget *LeftTreeWidget;
	QListWidget *RightListWidget;
	QStringList fileName;
	const int W_ICONSIZE = 100;
	const int H_ICONSIZE = 100;
	QMenu *fileMenu;
	QMenu *rightMenu;
	QAction *openFileAction;
	QAction *exitAction;
	QAction *changeAction;
	QAction *deleteAction;
	QAction *clearAction;
	QAction *addSampleAction;
	QToolBar *fileTool;
	SqlOperation *sqloperation;
	std::map<std::string, std::list<char *>> name_picmap;
	CV_Face *cvface;
	QTimer *clicktimer;
	bool isdouble;
	QListWidgetItem *chooseditem;
};

#endif // FACERRECOGNIZE_H
