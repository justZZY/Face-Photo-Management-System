#ifndef ASKDIALOG_H
#define ASKDIALOG_H
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <string>
#include <cstring>
#include "SqlOperation.h"
class AskDialog : public QDialog
{
	Q_OBJECT
public:
	AskDialog(SqlOperation *sqlop, int id, int newlabel, const char *picpath, cv::Mat m);
public slots:
	void sqlInsert();
private:
	QLabel *imglabel;
	QLineEdit *nameline;
	QPushButton *okbtn;
	QHBoxLayout *toplayout;
	QHBoxLayout *bottomlaytou;
	QVBoxLayout *totallayout;
	char *name;
	char *picpath;
	int newlabel;
	SqlOperation *sqloperation;
	int id;
	cv::Mat m;
};
#endif // !ASKDIALOG_H

