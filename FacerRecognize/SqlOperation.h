#ifndef SQLOPERATION_H_
#define SQLOPERATION_H_
#include "HeadFiles.h"
#include <Windows.h>
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <qsql.h>
#include <QtSql>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qsqldriver.h>
#include <qsqlrecord.h>
class SqlOperation
{
public:
	SqlOperation();
	void createTable();
	void insert(int id, char *name, int label);
	void query(char *q);
	void getMap();
	void addMap(std::string name, char *path);
	void getLabel();
	void addLabel(cv::Mat graypic, int label);
	void getMaxId();
	int getMaxLabel();
	QString getName(int predictlabel);
	int getLabeltoCorrect(std::string name);
	int addLabel();
	void sublabel();
	int addId();
	void setImgGrayPath(const char *imgpath, std::string graypath);
	std::vector<cv::Mat> getImagesVector();
	std::vector<int> getLabelVector();
	std::map<std::string, std::list<char *>> getFacemap();
	const char *getImgPath();
	const char *getGrayPath();
	void getDistinctMap();
	void deleteMessage(QString name, QString path);
	void updateLabel(QString newname, QString oldname ,QString path);
	void clearAllData();

private:
	QSqlDatabase db;
	int id;
	int label;
	const char *imgpath;
	const char *graypath;
	std::map<std::string, std::list<char *>> nameMap;
	std::vector<cv::Mat> images;//两个容器images,labels来存放图像数据和对应的标签
	std::vector<int> labels;
};
#endif // !SQLOPERATION_H_

