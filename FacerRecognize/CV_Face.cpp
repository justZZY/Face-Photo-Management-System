#include "CV_Face.h"
#include "Global.h"
using namespace std;
using namespace cv;

CV_Face::CV_Face(SqlOperation *sql)
{
	sqloperation = sql;
	scale = 1.0;
	tryflip = false;
	model = cv::face::createLBPHFaceRecognizer();
	//model = cv::face::createEigenFaceRecognizer();
	//model = cv::face::createFisherFaceRecognizer();
	storage = cvCreateMemStorage(0);
	cascade = 0;
	//nestedCascade = 0;
	Init();
}

void CV_Face::Init()
{
	cascade = (CvHaarClassifierCascade *)cvLoad(cascade_name, 0, 0, 0);
	//nestedCascade = (CvHaarClassifierCascade *)cvLoad(nested_cascade_name, 0, 0, 0);
	if (!cascade)
	{
		cerr << "ERROR: Could not load classifier cascade or nestedCascade" << endl;
		return;
	}
}

void CV_Face::faceRecognize(const char *path)
{
	sqloperation->getMaxId();
	int maxlabel = sqloperation->getMaxLabel();
	IplImage *img = cvLoadImage(path);
	static CvScalar colors[] =
	{
		{ 0,0,255 },
		{ 0,128,255 },
		{ 0,255,255 },
		{ 0,255,0 },
		{ 255,128,0 },
		{ 255,255,0 },
		{ 255,0,0 },
		{ 255,0,255 }
	};
	IplImage *gray, *small_img;
	vector<cv::Rect> faces, faces2;
	gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
	small_img = cvCreateImage(cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);
	cvCvtColor(img, gray, CV_BGR2GRAY); // ��ɫRGBͼ��תΪ�Ҷ�ͼ�� 
	cvResize(gray, small_img, CV_INTER_LINEAR);
	cvEqualizeHist(small_img, small_img); // ֱ��ͼ���⻯ 
	cvClearMemStorage(storage);
	if (cascade)
	{
		CvSeq* faces = cvHaarDetectObjects(small_img, cascade, storage,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			| CV_HAAR_DO_CANNY_PRUNING
			//|CV_HAAR_SCALE_IMAGE
			,
			cvSize(30, 30));
		for (int i = 0; i < (faces ? faces->total : 0); i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(faces, i); // ��faces���ݴ�CvSeqתΪCvRect 
			CvMat small_img_roi;
			CvSeq* nested_objects;
			cvGetSubRect(small_img, &small_img_roi, *r);
			//��ȡ��⵽������������Ϊʶ���ͼ��
			IplImage *result;
			CvRect roi;
			roi = *r;
			result = cvCreateImage(cvSize(r->width, r->height), img->depth, img->nChannels);
			cvSetImageROI(img, roi);
			// ������ͼ��
			cvCopy(img, result);
			cvResetImageROI(img); IplImage *resizeRes;
			CvSize dst_cvsize;
			dst_cvsize.width = (int)(100);
			dst_cvsize.height = (int)(100);
			resizeRes = cvCreateImage(dst_cvsize, result->depth, result->nChannels);
			//��⵽��������ܲ���100x100��С��������Ҫ��ֵ����ͳһ��С��ͼ��Ĵ�С�����Լ�ָ����
			cvResize(result, resizeRes, CV_INTER_NN);
			IplImage* img1 = cvCreateImage(cvGetSize(resizeRes), IPL_DEPTH_8U, 1);//����Ŀ��ͼ��	
			cvCvtColor(resizeRes, img1, CV_BGR2GRAY);//cvCvtColor(src,des,CV_BGR2GRAY)
			//Ϊ�������label
			int predictedLabel = -5;
			//��ǻҶ�ͼ��id
			int id = sqloperation->addId();
			Mat test = cvarrToMat(img1);
			std::string graypaths = "./grayface/";
			std::stringstream ss;
			ss << graypaths << id << ".jpg";
			ss >> graypaths;
			//����Ҷ�ͼ
			imwrite(graypaths, test);
			sqloperation->setImgGrayPath(path, graypaths);
			//����������������б�
			double predicted_confidence = 0.0;
			if (id > 3)
			{
				model->train(sqloperation->getImagesVector(), sqloperation->getLabelVector());
				model->predict(test, predictedLabel, predicted_confidence);
				if (predictedLabel <= 0)
				{
					AskDialog *askDiago = new AskDialog(sqloperation, id, sqloperation->addLabel(), path, test);
					askDiago->show();
				}
				else
				{
					QString qs = sqloperation->getName(predictedLabel);
					std::string s = qs.toStdString();
					char *names = new char[s.length() + 1];
					char *paths = new char[strlen(path) + 1];
					strcpy(names, s.c_str());
					strcpy(paths, path);
					sqloperation->addMap(s, paths);
					sqloperation->addLabel(test, predictedLabel);
					sqloperation->insert(id, names, predictedLabel);
					mainWindow->readTreefromMap();
				}
			}
			else
			{
				AskDialog *askdialog = new AskDialog(sqloperation, id, sqloperation->addLabel(), path, test);
				askdialog->show();
			}
			//if (!nestedCascade)
			//	continue;

			//nested_objects = cvHaarDetectObjects(&small_img_roi, nestedCascade, storage,
			//	1.1, 2, 0
			//	//|CV_HAAR_FIND_BIGGEST_OBJECT
			//	//|CV_HAAR_DO_ROUGH_SEARCH
			//	//|CV_HAAR_DO_CANNY_PRUNING
			//	//|CV_HAAR_SCALE_IMAGE
			//	,
			//	cvSize(0, 0));
		}
	}
	cvReleaseImage(&img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
}

void CV_Face::addSample(const char *path)
{
	sqloperation->getMaxId();
	int maxlabel = sqloperation->getMaxLabel();
	IplImage *img = cvLoadImage(path);
	static CvScalar colors[] =
	{
		{ 0,0,255 },
		{ 0,128,255 },
		{ 0,255,255 },
		{ 0,255,0 },
		{ 255,128,0 },
		{ 255,255,0 },
		{ 255,0,0 },
		{ 255,0,255 }
	};
	IplImage *gray, *small_img;
	vector<cv::Rect> faces, faces2;
	gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
	small_img = cvCreateImage(cvSize(cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);
	cvCvtColor(img, gray, CV_BGR2GRAY); // ��ɫRGBͼ��תΪ�Ҷ�ͼ�� 
	cvResize(gray, small_img, CV_INTER_LINEAR);
	cvEqualizeHist(small_img, small_img); // ֱ��ͼ���⻯ 
	cvClearMemStorage(storage);
	if (cascade)
	{
		CvSeq* faces = cvHaarDetectObjects(small_img, cascade, storage,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			| CV_HAAR_DO_CANNY_PRUNING
			//|CV_HAAR_SCALE_IMAGE
			,
			cvSize(30, 30));
		for (int i = 0; i < (faces ? faces->total : 0); i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(faces, i); // ��faces���ݴ�CvSeqתΪCvRect 
			CvMat small_img_roi;
			CvSeq* nested_objects;
			cvGetSubRect(small_img, &small_img_roi, *r);
			//��ȡ��⵽������������Ϊʶ���ͼ��
			IplImage *result;
			CvRect roi;
			roi = *r;
			result = cvCreateImage(cvSize(r->width, r->height), img->depth, img->nChannels);
			cvSetImageROI(img, roi);
			// ������ͼ��
			cvCopy(img, result);
			cvResetImageROI(img); IplImage *resizeRes;
			CvSize dst_cvsize;
			dst_cvsize.width = (int)(100);
			dst_cvsize.height = (int)(100);
			resizeRes = cvCreateImage(dst_cvsize, result->depth, result->nChannels);
			//��⵽��������ܲ���100x100��С��������Ҫ��ֵ����ͳһ��С��ͼ��Ĵ�С�����Լ�ָ����
			cvResize(result, resizeRes, CV_INTER_NN);
			IplImage* img1 = cvCreateImage(cvGetSize(resizeRes), IPL_DEPTH_8U, 1);//����Ŀ��ͼ��	
			cvCvtColor(resizeRes, img1, CV_BGR2GRAY);//cvCvtColor(src,des,CV_BGR2GRAY)
			//��ǻҶ�ͼ��id
			int id = sqloperation->addId();
			Mat test = cvarrToMat(img1);
			std::string graypaths = "./grayface/";
			std::stringstream ss;
			ss << graypaths << id << ".jpg";
			ss >> graypaths;
			//����Ҷ�ͼ
			imwrite(graypaths, test);
			sqloperation->setImgGrayPath(path, graypaths);
			AskDialog *askdialog = new AskDialog(sqloperation, id, sqloperation->addLabel(), path, test);
			askdialog->setModal(true);
			askdialog->show();
		}
	}
	cvReleaseImage(&img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
}
