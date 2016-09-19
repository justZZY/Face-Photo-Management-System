#include "FacerRecognize.h"

FacerRecognize::FacerRecognize(SqlOperation *sqlop, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->sqloperation = sqlop;
	/*cvExam = new IOandExam(sqlop);*/
	//cvExam->train();
	clicktimer = new QTimer();
	isdouble = false;
	cvface = new CV_Face(sqlop);
	setWindowTitle("Photo Manager");
	MainLayout = new QGridLayout();
	LeftTreeWidget = new QTreeWidget();
	RightListWidget = new QListWidget();
	createAction();
	createMenu();
	createToolBars();
	createLeft(LeftTreeWidget);
	createRight(RightListWidget);
	createMain(MainLayout, LeftTreeWidget, RightListWidget);
	sqloperation->getMap();
	sqloperation->getLabel();
	readTreefromMap();
	QWidget *w = new QWidget();
	w->setLayout(MainLayout);
	this->setCentralWidget(w);
	this->setWindowIcon(QIcon("./UIpic/title.png"));
	connect(LeftTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(setPathsToDialog(QTreeWidgetItem *, int)));
	connect(LeftTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(setPathsToRight(QTreeWidgetItem *, int)));
	connect(RightListWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(signalManager(QListWidgetItem *)));
	connect(RightListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(setPathToDialog(QListWidgetItem *)));
	connect(clicktimer, SIGNAL(timeout()), this, SLOT(createRightMenu()));
}

FacerRecognize::~FacerRecognize()
{

}

/*
创建左侧Tree，构造树形列表
*/
void FacerRecognize::createLeft(QTreeWidget * LeftTreeWidget)
{
	LeftTreeWidget->setColumnCount(1);
	LeftTreeWidget->setHeaderLabel(tr("Name"));
}

/*
创建右侧List，构造图形列表
*/
void FacerRecognize::createRight(QListWidget *RightListWidget){
	//设置QListWidget中的单元项的图片大小
	RightListWidget->setIconSize(QSize(W_ICONSIZE, H_ICONSIZE));
	RightListWidget->setResizeMode(QListView::Adjust);
	//设置QListWidget的显示模式
	RightListWidget->setViewMode(QListView::IconMode);
	//设置QListWidget中的单元项不可被拖动
	RightListWidget->setMovement(QListView::Static);
	//设置QListWidget中的单元项的间距
	RightListWidget->setSpacing(10);
}

/*
合并主布局
*/
void FacerRecognize::createMain(QGridLayout * MainLayout, QTreeWidget * LeftTreeWidget, QListWidget * RightListWidget)
{
	MainLayout->setColumnStretch(0, 1);
	MainLayout->setColumnStretch(1, 5);
	MainLayout->addWidget(LeftTreeWidget, 0, 0);
	MainLayout->addWidget(RightListWidget, 0, 1);
}

/*
实现右侧列表添加图片功能
picpath:图片路径
RightListWidget:即将插入的List名称
*/
void FacerRecognize::addRightPic(QString picpath,QListWidget *RightListWidget)
{
	QPixmap pixmap(picpath);
	QListWidgetItem *listitem = new QListWidgetItem(QIcon(pixmap.scaled(QSize(W_ICONSIZE, H_ICONSIZE))), picpath);
	listitem->setSizeHint(QSize(W_ICONSIZE, H_ICONSIZE));
	RightListWidget->addItem(listitem);
}

QTreeWidgetItem *FacerRecognize::addTreeRoot(QTreeWidget *LeftTreeWidget, QString str)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(LeftTreeWidget);
	item->setText(0, str);
	LeftTreeWidget->addTopLevelItem(item);
	return item;
}

void FacerRecognize::addTreeChild(QTreeWidgetItem *parent, QString str)
{
	QTreeWidgetItem *item = new QTreeWidgetItem();
	item->setText(0, str);
	parent->addChild(item);
}

void FacerRecognize::openFileOperation()
{
	fileName = QFileDialog::getOpenFileNames(this, "open dir", "/", "Images (*.png *.xpm *.jpg *.jpeg)");
	QList<QString>::iterator it;
	if (!fileName.empty()) 
	{
		for (it = fileName.begin(); it != fileName.end(); it++)
		{
			std::string s = it->toStdString();
			cvface->faceRecognize(s.c_str());
			/*cvExam->predict(s.c_str());*/
		}
	}
	fileName.clear();
}

void FacerRecognize::createAction()
{
	openFileAction = new QAction(QIcon("./UIpic/open.png"), tr("Open"), this);
	openFileAction->setShortcut(tr("Ctrl+O"));
	openFileAction->setStatusTip(tr("Open Files"));
	connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFileOperation()));
	exitAction = new QAction(QIcon("./UIpic/exit.png"), tr("Exit"), this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	clearAction = new QAction(QIcon("./UIpic/clear.png"), tr("Clear"), this);
	clearAction->setStatusTip(tr("Clear Album"));
	connect(clearAction, SIGNAL(triggered()), this, SLOT(clearAll()));
	addSampleAction = new QAction(QIcon("./UIpic/addSample.png"), tr("Add Sample"), this);
	addSampleAction->setShortcut(tr("Ctrl+E"));
	addSampleAction->setStatusTip(tr("Choose a sample picture"));
	connect(addSampleAction, SIGNAL(triggered()), this, SLOT(addSample()));
}

void FacerRecognize::createMenu()
{
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(addSampleAction);
	fileMenu->addAction(openFileAction);
	fileMenu->addSeparator();
	fileMenu->addAction(clearAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void FacerRecognize::createToolBars()
{
	fileTool = addToolBar("File");
	fileTool->setMovable(false);
	fileTool->addAction(addSampleAction);
	fileTool->addAction(openFileAction);
	fileTool->addSeparator();
	fileTool->addAction(clearAction);
}

void FacerRecognize::readTreefromMap()
{
	LeftTreeWidget->clear();
	sqloperation->getDistinctMap();
	int test = LeftTreeWidget->topLevelItemCount();
	name_picmap = sqloperation->getFacemap();
	std::map<std::string, std::list<char *>>::iterator it;
	std::list<char *> piclist;
	std::list<char *>::iterator picit;
	std::string namestr;
	char *picstr;
	for (it = name_picmap.begin(); it != name_picmap.end(); it++)
	{
		namestr = it->first;
		QTreeWidgetItem *item = addTreeRoot(LeftTreeWidget, QString::fromStdString(namestr));
		piclist = it->second;
		for (picit = piclist.begin(); picit != piclist.end(); picit++)
		{
			picstr = *picit;
			addTreeChild(item, picstr);
		}
	}
}

void FacerRecognize::setPathsToRight(QTreeWidgetItem *item, int index)
{
	if (!item)
		return;
	QTreeWidgetItem *hitem = item->parent();
	if (!hitem)
	{
		RightListWidget->clear();
		QTreeWidgetItemIterator it(item);
		++it;
		while(*it)
		{
			if (!(*it)->parent())
				break;
			QString path = (*it)->text(0);
			addRightPic(path, RightListWidget);
			++it;
		}
	}
	else 
	{

	}
}

void FacerRecognize::setPathsToDialog(QTreeWidgetItem *item, int)
{
	if (!item)
		return;
	QTreeWidgetItem *hitem = item->parent();
	if (hitem)
	{
		ShowDialog *showdiago = new ShowDialog(item->text(0));
		showdiago->show();
	}
	else
	{

	}
}

void FacerRecognize::setPathToDialog(QListWidgetItem *item)
{
	isdouble = true;
	clicktimer->stop();
	ShowDialog *showdiago = new ShowDialog(item->text());
	showdiago->show();
}

void FacerRecognize::createRightMenu()
{
	if (chooseditem != NULL && !isdouble)
	{
		rightMenu = new QMenu(this);
		changeAction = new QAction(tr("Change Picture Name"), this);
		deleteAction = new QAction(tr("Delete this Picture"), this);
		connect(changeAction, SIGNAL(triggered()), this, SLOT(changePicLabel()));
		connect(deleteAction, SIGNAL(triggered()), this, SLOT(deletePicfromDB()));
		rightMenu->addAction(changeAction);
		rightMenu->addAction(deleteAction);
		rightMenu->exec(QCursor::pos());
		isdouble = true;
	}
}

void FacerRecognize::changePicLabel()
{
	QString path = chooseditem->text();
	QString oldname = getCurrentName();
	bool ok = false;
	QString newname = QInputDialog::getText(this, tr("Input"), tr("Please input the name which you want to change"), QLineEdit::Normal, tr(""), &ok);
	if (ok && !newname.isEmpty())
	{
		std::string s = path.toStdString();
		char *cs = new char[s.length() + 1];
		strcpy(cs, s.c_str());
		sqloperation->updateLabel(newname, oldname, path);
		sqloperation->getMap();
		sqloperation->getLabel();
		//sqloperation->addMap(newname.toStdString(), cs);
		readTreefromMap();
		RightListWidget->removeItemWidget(chooseditem);
		delete chooseditem;
	}
	
}

void FacerRecognize::deletePicfromDB()
{
	QString path = chooseditem->text();
	QString name = getCurrentName();
	sqloperation->deleteMessage(name, path);
	sqloperation->getMap();
	sqloperation->getLabel();
	readTreefromMap();
	RightListWidget->removeItemWidget(chooseditem);
	delete chooseditem;
}

QString FacerRecognize::getCurrentName()
{
	QString name;
	int cnt = 0;
	int len = RightListWidget->count();
	QList<QListWidgetItem *> itemList;
	for (int i = 0; i < len; i++)
		itemList.push_back(RightListWidget->item(i));
	std::map<std::string, std::list<char *>>::iterator it;
	std::list<char *>::iterator charit;
	for (it = name_picmap.begin(); it != name_picmap.end(); it++)
	{
		cnt = 0;
		for (charit = it->second.begin(); charit != it->second.end(); charit++)
		{
			QString qs(*charit);
			if (itemList[cnt]->text() == qs)
			{
				cnt++;
			}
		}
		if (cnt == len)
		{
			name = QString::fromStdString(it->first);
		}
	}
	return name;
}

void FacerRecognize::clearAll()
{
	sqloperation->clearAllData();
	name_picmap.clear();
	LeftTreeWidget->clear();
	RightListWidget->clear();
}

void FacerRecognize::addSample()
{
	QString filepath = QFileDialog::getOpenFileName(this, "open dir", "/", "Images (*.png *.xpm *.jpg *.jpeg)");
	if (!filepath.isEmpty())
		cvface->addSample(filepath.toStdString().c_str());
}

void FacerRecognize::signalManager(QListWidgetItem *item)
{
	chooseditem = item;
	if (isdouble)
	{
		isdouble = true;
	}
	else
	{
		clicktimer->start(120);
	}
	isdouble = false;
}