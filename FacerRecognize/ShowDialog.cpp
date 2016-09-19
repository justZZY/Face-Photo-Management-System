#include "ShowDialog.h"
ShowDialog::ShowDialog(QString picpath)
{
	stdflag = true;
	grayflag = false;
	erodeflag = false;
	blurflag = false;
	cannyflag = false;
	stdpath = picpath;
	/*创建左侧label区域*/
	piclabel = new QLabel();
	/******************/
	initFilterLayout();
	initMainLayout(picpath);
	this->setLayout(mainlayout);
	connect(stdbutton, SIGNAL(clicked()), this, SLOT(toStd()));
	connect(graybutton, SIGNAL(clicked()), this, SLOT(toGray()));
	connect(erodebutton, SIGNAL(clicked()), this, SLOT(toErode()));
	connect(blurbutton, SIGNAL(clicked()), this, SLOT(toBlur()));
	connect(cannybutton, SIGNAL(clicked()), this, SLOT(toCanny()));
	connect(savebutton, SIGNAL(clicked()), this, SLOT(savePic()));
}

void ShowDialog::initFilterLayout()
{
	stdbutton = new QPushButton("Origin");
	graybutton = new QPushButton("GrayandWhite");
	erodebutton = new QPushButton("Erode");
	blurbutton = new QPushButton("Blur");
	cannybutton = new QPushButton("Canny");
	savebutton = new QPushButton("Save");
	filterlayout = new QGridLayout();
	namelayout = new QHBoxLayout();
	filterlabel = new QLabel("Filter");
	filterlabel->setAlignment(Qt::AlignHCenter);
	namelayout->addWidget(filterlabel);
	/*******************/
	filterlayout->addLayout(namelayout, 0, 0);
	filterlayout->addWidget(stdbutton, 1, 0);
	filterlayout->addWidget(graybutton, 2, 0);
	filterlayout->addWidget(erodebutton, 3, 0);
	filterlayout->addWidget(blurbutton, 4, 0);
	filterlayout->addWidget(cannybutton, 5, 0);
	filterlayout->addWidget(savebutton, 6, 0);
}

QImage ShowDialog::cutPic(QString path)
{
	QImage image;
	image.load(path);
	int w, h;
	w = image.width() / 1400;
	h = image.height() / 900;
	if (w > 0 || h > 0)
	{
		if (w == 0)
		{
			image = image.scaled(QSize(image.width() / (2 * h), image.height() / (2 * h)));
		}
		else if (h == 0)
		{
			image = image.scaled(QSize(image.width() / (2 * w), image.height() / (2 * w)));
		}
		else
		{
			image = image.scaled(QSize(image.width() / (2 * w), image.height() / (2 * h)));
		}
	}
	return image;
}

void ShowDialog::setPic(QImage image)
{
	piclabel->setPixmap(QPixmap::fromImage(image));
	piclabel->resize(QSize(image.width(), image.height()));
}

void ShowDialog::initMainLayout(QString picpath)
{
	setPic(cutPic(picpath));
	mainlayout = new QGridLayout();
	mainlayout->setColumnStretch(0, 5);
	mainlayout->setColumnStretch(1, 1);
	mainlayout->addWidget(piclabel, 0, 0);
	mainlayout->addLayout(filterlayout, 0, 1);
}

void ShowDialog::savePic()
{
	QImage image;
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Image"), "/", tr("Images (*.png *.xpm *.jpg *.jpeg)")); //选择路径  
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		if (grayflag)
		{
			image.load("./bawPic/baw.jpg");
			if (!image.save(filename))
				printf("erro");
		}
		else if (erodeflag)
		{
			image.load("./erodePic/erode.jpg");
			if (!image.save(filename))
				printf("erro");
		}
		else if (blurflag)
		{
			image.load("./blurPic/blur.jpg");
			if (!image.save(filename))
				printf("erro");
		}
		else if (cannyflag)
		{
			image.load("./cannyPic/canny.jpg");
			if (!image.save(filename))
				printf("erro");
		}
		else
		{
			image.load(stdpath);
			if (!image.save(filename))
				printf("erro");
		}
	}
}

void ShowDialog::toStd()
{
	setPic(cutPic(stdpath));
	stdflag = true;
	grayflag = false;
	erodeflag = false;
	blurflag = false;
	cannyflag = false;
}

void ShowDialog::toGray()
{
	IplImage *img = cvLoadImage(stdpath.toStdString().c_str());
	IplImage *gray = cvCreateImage(CvSize(img->width, img->height), 8, 1);
	cvCvtColor(img, gray, CV_RGB2GRAY);
	cv::Mat graypic = cv::cvarrToMat(gray);
	cv::imwrite("./bawPic/baw.jpg", graypic);
	setPic(cutPic("./bawPic/baw.jpg"));
	stdflag = false;
	grayflag = true;
	erodeflag = false;
	blurflag = false;
	cannyflag = false;
}

void ShowDialog::toErode()
{
	cv::Mat erodeimage = cv::imread(stdpath.toStdString());
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::Mat dstimage;
	cv::erode(erodeimage, dstimage, element);
	cv::imwrite("./erodePic/erode.jpg", dstimage);
	setPic(cutPic("./erodePic/erode.jpg"));
	stdflag = false;
	grayflag = false;
	erodeflag = true;
	blurflag = false;
	cannyflag = false;
}

void ShowDialog::toBlur()
{
	cv::Mat blurimage = cv::imread(stdpath.toStdString());
	cv::Mat dstimage;
	cv::blur(blurimage, dstimage, cv::Size(12, 12));
	cv::imwrite("./blurPic/blur.jpg", dstimage);
	setPic(cutPic("./blurPic/blur.jpg"));
	stdflag = false;
	grayflag = false;
	erodeflag = false;
	blurflag = true;
	cannyflag = false;
}

void ShowDialog::toCanny()
{
	cv::Mat cannyimage = cv::imread(stdpath.toStdString());
	cv::Mat dstimage, edge, grayimage;
	dstimage.create(cannyimage.size(), cannyimage.type());
	IplImage *img = cvLoadImage(stdpath.toStdString().c_str());
	IplImage *gray = cvCreateImage(CvSize(img->width, img->height), 8, 1);
	cvCvtColor(img, gray, CV_RGB2GRAY);
	grayimage = cv::cvarrToMat(gray);
	cv::blur(grayimage, edge, cv::Size(3, 3));
	cv::Canny(edge, edge, 3, 9, 3);
	cv::imwrite("./cannyPic/canny.jpg", edge);
	setPic(cutPic("./cannyPic/canny.jpg"));
	stdflag = false;
	grayflag = false;
	erodeflag = false;
	blurflag = false;
	cannyflag = true;
}

