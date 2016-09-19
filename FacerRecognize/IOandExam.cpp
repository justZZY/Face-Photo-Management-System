//#include "IOandExam.h"
//
//using namespace std;
//using namespace cv;
//IOandExam::IOandExam(SqlOperation *sqlop)
//{
//	sqloperation = sqlop;
//	//opencv的FaceRecogizer目前有三个类实现了他，特征脸和fisherface方法最少训练图像为两张，而LBP可以单张图像训练
//	//cv::Ptr<cv::FaceRecognizer> model = cv::createEigenFaceRecognizer();
//	//cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
//	model = face::createLBPHFaceRecognizer(1, 8, 8, 8, 100.0);//LBP的这个方法在单个人脸验证方面效果最好
//	num_components = 9;
//	facethreshold = 9.0;
//	nested_cascade_opt = "--nested-cascade";
//	nested_cascade_opt_len = (int)strlen(nested_cascade_opt);
//	nested_cascade = 0;
//	use_nested_cascade = 0;
//	cascade_name = "./data/haarcascade_frontalface_alt.xml";//别人已经训练好的人脸检测xml数据
//	nested_cascade_name = "./data/haarcascade_eye_tree_eyeglasses.xml";
//	image = 0;
//	scale_opt = "--scale="; // 分类器选项指示符号 
//	scale_opt_len = (int)strlen(scale_opt);
//	cascade_opt = "--cascade=";
//	cascade_opt_len = (int)strlen(cascade_opt);
//	cascade = (CvHaarClassifierCascade*)cvLoad(cascade_name, 0, 0, 0); //加载分类器 
//	cvface = new CV_Face(cascade, nested_cascade, model, sqloperation);
//}
//
//void IOandExam::train()
//{
//	model->train(sqloperation->getImagesVector(), sqloperation->getLabelVector());
//}
//
//void IOandExam::predict(const char *s)
//{
//	frame = cvLoadImage(s);
//	cvface->recog_and_draw(frame, s);
//}