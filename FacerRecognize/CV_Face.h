#ifndef CV_Face_H
#define CV_Face_H
#include "HeadFiles.h"
#include "SqlOperation.h"
#include "AskDialog.h"
class CV_Face 
{
public:
	CV_Face(SqlOperation *sqlop);
	void Init();
	void faceRecognize(const char *s);
	void addSample(const char *);
private:
	CvHaarClassifierCascade *cascade;
	//CvHaarClassifierCascade *nestedCascade;
	const char *cascade_name = "./data/haarcascade_frontalface_alt.xml";//别人已经训练好的人脸检测xml数据
	//const char* nested_cascade_name = "./data/haarcascade_eye_tree_eyeglasses.xml";
	CvMemStorage *storage;
	double scale;
	bool tryflip;
	cv::Ptr<cv::face::FaceRecognizer> model;
	SqlOperation *sqloperation;
};
#endif


