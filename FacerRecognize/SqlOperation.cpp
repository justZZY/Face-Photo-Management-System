#include <SqlOperation.h>
SqlOperation::SqlOperation()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setHostName("FaceDB");
	db.setDatabaseName("Face.db");
	db.setUserName("Saber");
	db.setPassword("123456");
	createTable();
}
void SqlOperation::createTable()
{
	db.open();
	QSqlQuery query;
	query.exec("create table face (id int, picpath varchar(50), name varchar(20), label int, graypic varchar(50))");
	db.close();
}

void SqlOperation::insert(int id, char *name, int label)
{
	db.open();
	QSqlQuery query;
	query.prepare("insert into face values(?, ?, ?, ?, ?)");
	query.bindValue(0, id);
	query.bindValue(1,imgpath);
	query.bindValue(2, name);
	query.bindValue(3, label);
	query.bindValue(4, graypath);
	query.exec();
	db.close();
}
/*查询代码还需细分*/
void SqlOperation::query(char *q)
{
	db.open();
	QSqlQuery query;
	query.exec(q);
	db.close();
}
/*
创建用于显示的map集合
*/
void SqlOperation::getMap()
{
	db.open();
	nameMap.clear();
	QSqlQuery query;
	query.exec("select distinct name from face");
	while (query.next())
	{
		QString n = query.value(0).toString();
		std::string temp;
		temp = n.toStdString();
		char *name = new char[temp.length() + 1];
		strcpy(name, temp.c_str());
		std::list<char *> templist;
		nameMap.insert(std::map<std::string, std::list<char *>>::value_type(temp, templist));
		QSqlQuery querypath;
		querypath.prepare("select picpath from face where name = ?");
		querypath.bindValue(0, n);
		querypath.exec();
		while (querypath.next())
		{
			QString p = querypath.value(0).toString();
			std::string t;
			t = p.toStdString();
			char *path = new char[t.length() + 1];
			strcpy(path, t.c_str());
			addMap(temp, path);
		}
	}
	db.close();
}
/*
将人名与图片地址插值到Map里构造树
*/
void SqlOperation::addMap(std::string name, char *path)
{
	std::map<std::string, std::list<char *>>::iterator it;
	it = nameMap.find(name);
	if (it != nameMap.end())
	{
		it->second.push_back(path);
	}
	else
	{
		std::list<char *> templist;
		templist.push_back(path);
		nameMap.insert(std::map<std::string, std::list<char *>>::value_type(name, templist));
	}
}
/*
从数据库中查询保存的灰度图与标签
为images和labels两个容器赋值
*/
void SqlOperation::getLabel()
{
	db.open();
	images.clear();
	labels.clear();
	QSqlQuery query;
	query.exec("select graypic, label from face");
	while (query.next())
	{
		QString s = query.value(0).toString();
		int label = query.value(1).toInt();
		std::string temp;
		temp = s.toStdString();
		char *gray = new char[temp.length() + 1];
		strcpy(gray, temp.c_str());
		/*if (graypic.data) {
			IplImage t(graypic);
			cvShowImage("test", &t);
			cvWaitKey();
		}*/
		images.push_back(cv::imread(gray, CV_LOAD_IMAGE_GRAYSCALE));
		labels.push_back(label);
	}
	db.close();
}
/*
为images和label增加新的灰度图和标记信息
*/
void SqlOperation::addLabel(cv::Mat graypic, int label)
{
	images.push_back(graypic);
	labels.push_back(label);
}
/*
查询数据库得到目前最大的标签值
*/
int SqlOperation::getMaxLabel()
{
	db.open();
	QSqlQuery query;
	query.exec("select max(label) from face");
	label = 0;
	while (query.next())
	{
		label = query.value(0).toInt();
	}
	db.close();
	return label;
}
 
int SqlOperation::addLabel()
{
	label++;
	return label;
}

void SqlOperation::sublabel()
{
	label--;
}
/*
查询数据库得到目前最大的id值
*/
void SqlOperation::getMaxId()
{
	db.open();
	QSqlQuery query;
	query.exec("select max(id) from face group by id");
	id = 0;
	while (query.next())
	{
		id = query.value(0).toInt();
	}
	db.close();
}
int SqlOperation::addId()
{
	++id;
	return id;
}

std::vector<cv::Mat> SqlOperation::getImagesVector()
{
	return images;
}

std::vector<int> SqlOperation::getLabelVector()
{
	return labels;
}

std::map<std::string, std::list<char *>> SqlOperation::getFacemap()
{
	return nameMap;
}
/*
查询数据库得到标签所属的人名
*/
QString SqlOperation::getName(int predictlabel)
{
	db.open();
	QString s;
	QSqlQuery query;
	query.prepare("select name from face where label = ?");
	query.bindValue(0, predictlabel);
	query.exec();
	while (query.next())
	{
		s = query.value(0).toString();
	}
	db.close();
	return s;
}

void SqlOperation::setImgGrayPath(const char *imgpath, std::string graypath)
{
	char *imgs = new char[strlen(imgpath) + 1];
	strcpy(imgs, imgpath);
	const char *temp = graypath.c_str();
	char *grays = new char[strlen(temp) + 1];
	strcpy(grays, temp);
	this->imgpath = imgs;
	this->graypath = grays;
}

const char* SqlOperation::getImgPath()
{
	return imgpath;
}

const char *SqlOperation::getGrayPath()
{
	return graypath;
}

int SqlOperation::getLabeltoCorrect(std::string name)
{
	db.open();
	QSqlQuery query;
	query.prepare("select label from face where name = ?");
	query.bindValue(0, QString::fromStdString(name));
	query.exec();
	int label = -1;
	while (query.next())
	{
		label = query.value(0).toInt();
	}
	db.close();
	return label;
}

void SqlOperation::getDistinctMap()
{
	std::map<std::string, std::list<char *>>::iterator mapit;
	std::list<char *>::iterator pathlistit;
	std::set<std::string> pathset;
	std::set<std::string>::iterator pathsetit;
	for (mapit = nameMap.begin(); mapit != nameMap.end(); mapit++)
	{
		for (pathlistit = mapit->second.begin(); pathlistit != mapit->second.end(); pathlistit++)
		{
			std::string s = *pathlistit;
			pathset.insert(s);
		}
		mapit->second.clear();
		for (pathsetit = pathset.begin(); pathsetit != pathset.end(); pathsetit++)
		{
			char *path = new char[pathsetit->length() + 1];
			strcpy(path, pathsetit->c_str());
			mapit->second.push_back(path);
		}
		pathset.clear();
	}
}

void SqlOperation::deleteMessage(QString name, QString path)
{
	db.open();
	QSqlQuery query;
	query.prepare("delete from face where name = ? and picpath = ?");
	query.bindValue(0, name);
	query.bindValue(1, path);
	query.exec();
	db.close();
}

void SqlOperation::updateLabel(QString newname, QString oldname,QString path)
{
	int label = getLabeltoCorrect(newname.toStdString());
	int tempmax = getMaxLabel();
	db.open();
	QSqlQuery query;
	if (label == -1)
	{
		label = tempmax;
		query.prepare("update face set label = ?, name = ? where name = ? and picpath = ?");
		query.bindValue(0, ++label);
		query.bindValue(1, newname);
		query.bindValue(2, oldname);
		query.bindValue(3, path);
		query.exec();
	}
	else
	{
		query.prepare("update face set label = ?, name = ? where name = ? and picpath = ?");
		query.bindValue(0, label);
		query.bindValue(1, newname);
		query.bindValue(2, oldname);
		query.bindValue(3, path);
		query.exec();
	}
	db.close();
}

void SqlOperation::clearAllData()
{
	db.open();
	QSqlQuery query("delete from face");
	query.exec();
	db.close();
	nameMap.clear();
	images.clear();
	labels.clear();
}