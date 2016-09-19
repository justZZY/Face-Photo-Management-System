#include "AskDialog.h"
#include "Global.h"
AskDialog::AskDialog(SqlOperation *sqlop, int id, int newlabel, const char *picpath, cv::Mat m)
{
	this->newlabel = newlabel;
	this->id = id;
	this->picpath = new char[strlen(picpath) + 1];
	strcpy(this->picpath, picpath);
	this->sqloperation = sqlop;
	this->m = m;
	imglabel = new QLabel();
	nameline = new QLineEdit();
	okbtn = new QPushButton("ok");
	toplayout = new QHBoxLayout();
	bottomlaytou = new QHBoxLayout();
	totallayout = new QVBoxLayout();
	/*QString qs;
	qs.append(graypath);*/
	imglabel->setPixmap(QPixmap(sqloperation->getGrayPath()));
	nameline->setPlaceholderText(tr("Input the name which belongs to the face"));
	toplayout->addWidget(imglabel);
	toplayout->addWidget(nameline);
	bottomlaytou->addWidget(okbtn);
	totallayout->addLayout(toplayout);
	totallayout->addLayout(bottomlaytou);
	this->setLayout(totallayout);
	this->setWindowTitle(tr("Input"));
	connect(okbtn, SIGNAL(clicked()), this, SLOT(sqlInsert()));
}


void AskDialog::sqlInsert()
{
	QString qs = nameline->text();
	std::string s = qs.toStdString();
	const char *cs = s.c_str();
	name = new char[strlen(cs) + 1];
	strcpy(name, cs);
	int templabel = sqloperation->getLabeltoCorrect(s);
	if (templabel > 0)
	{
		sqloperation->sublabel();
		newlabel = templabel;
	}
	sqloperation->addMap(s, picpath);
	sqloperation->addLabel(m, newlabel);
	sqloperation->insert(id, name, newlabel);
	mainWindow->readTreefromMap();
	this->close();
}