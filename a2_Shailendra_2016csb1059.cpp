/*
	Name : Shailendra Kumar Gupta
	Entry No.: 2016csb1059

	compile details:
			g++ a2_Shailendra_2016csb1059.cpp -o output `pkg-config --cflags --libs opencv`

	execution details:
			./output

	after execution you will get screen like below:

	1. Part 1
	2. Part 2:

	enter your choice and proceed further.

	1st part was only to understand the main idea of cross disolving so i have hust cross dissolved the images entered with given transformation matrix.

	2nd part was done as instructed.

	name of the input tie point filename should be SameImageName.EXT.txt
	eg. if image name is image.jpg then file name should be image.jpg.txt
*/

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <bitset>

using namespace std;
using namespace cv;

float area_tri(vector<Point2f> pt1)
{
	return 0.5*abs((pt1[0].x*(pt1[1].y - pt1[2].y) + pt1[1].x*(pt1[2].y - pt1[0].y) + pt1[2].x*(pt1[0].y - pt1[1].y)));
}

float area_tri(vector<Point2f> pt1, int i, int j)
{
	float area = 0.5*abs((i*(pt1[1].y - pt1[2].y) + pt1[1].x*(pt1[2].y - j) + pt1[2].x*(j - pt1[1].y)));
	area += 0.5*abs((pt1[0].x*(j - pt1[2].y) + i*(pt1[2].y - pt1[0].y) + pt1[2].x*(pt1[0].y - j)));
	area += 0.5*abs((pt1[0].x*(pt1[1].y - j) + pt1[1].x*(j - pt1[0].y) + i*(pt1[0].y - pt1[1].y)));
	return area;
}

vector<Point2f> reading_points(string file_name)
{
	ifstream fp;
	fp.open(file_name.c_str());
	vector<Point2f> read_points;
	int x,y;
	int i=0;
	while(fp>>x>>y)
	{
		//cout<<"i:"<<i<<endl;
		i++;
		read_points.push_back(Point2f(x,y));
	}
	return read_points;
}

vector<Point2f> intermediate_image_points(string filename1, string filename2, float tp)
{

	vector<Point2f> read_points;
	//for (float i = 1; i <= 10; ++i)
	{
		/* code */
		float t;
	//t = i/10;
		t = tp;
	ifstream fp1,fp2;
	fp1.open(filename1.c_str());
	fp2.open(filename2.c_str());

	Mat image1 = Mat::zeros(1500,1600,CV_32F);
	Scalar r(255,0,0);

	
	int x1,y1,x2,y2,x,y;
	while(fp1>>x1>>y1 && fp2>>x2>>y2)
	{
		
		x = (float)t*x1 + (1-t)*(float)x2;
		y = (float)t*y1 + (1-t)*(float)y2;		
		read_points.push_back(Point2f(x,y));
	}
	/*for (int k = 0; k < read_points.size(); ++k)
	{
		draw_point(image1,read_points[k],r);
	}*/
	//imshow("im",image1);
	//waitKey(100);
}
	return read_points;
}

vector<Vec6f> delaunay(Subdiv2D& subdivm, Size size)
{
	
	vector<Vec6f> triangleListm, tri_list;
    subdivm.getTriangleList(triangleListm);

    Size sizem = size;
    Rect rectm(0,0, sizem.width, sizem.height);

    int x,y,z;
        
    x=0;
    y=1;
    z=2;
    vector<Point> ptm(3);
	vector<Point2f> tm;

    for(int i = 0; i < triangleListm.size(); i++)
    {
    	Vec6f t;
        t = triangleListm[i];
        ptm[0] = Point(cvRound(t[0]), cvRound(t[1]));
        ptm[1] = Point(cvRound(t[2]), cvRound(t[3]));
        ptm[2] = Point(cvRound(t[4]), cvRound(t[5]));

        if ( rectm.contains(ptm[0]) && rectm.contains(ptm[1]) && rectm.contains(ptm[2]))
        {
            /*tm.push_back( ptm[x] );
		    tm.push_back( ptm[y] );
		    tm.push_back( ptm[z] );*/
		    tri_list.push_back(triangleListm[i]);
        }
    }
    return tri_list;
}

float max_number(float num1, float num2, float num3)
{
	float m = max(num1,num2);
	return max(m,num3);
}

float min_number(float num1, float num2, float num3)
{
	float m = min(num1,num2);
	return min(m,num3);
}

int binary(int number) {
	 int a;
    int remainder;
 
    if(number <= 1) {
        cout << number;
        a = a*10 + number;
        return number;
    }
 
 
    remainder = number%2;
    binary(number >> 1);
    a = a*10 + remainder;
    cout << a<<endl;
    return a;
}

void morphTriangle(Mat &img1, Mat &img2, Mat &img, vector<Point2f> t1[], vector<Point2f> t2[], vector<Point2f> t[], float alpha, int size_tm)
{
	
	Mat m1[size_tm] = Mat(2,3,CV_64F);//  = getAffineTransform(t,t1);
	Mat m2[size_tm] = Mat(2,3,CV_64F);// = getAffineTransform(t,t2);
	//float t = 0.5;

	//Mat temp = Mat::zeros(img.rows,img.cols,img.type());;
//Mat imge = Mat::zeros(img.rows,img.cols,CV_8U);
	int p,q,r,s;
	float area[size_tm] = {0};
	for (int i = 0; i < size_tm; ++i)
	{
		//if(negative_check(t[i]) && negative_check(t1[i]) && negative_check(t2[i]) ){
        m1[i] = getAffineTransform(t[i],t1[i]);
        m2[i] = getAffineTransform(t[i],t2[i]);
        area[i] = area_tri(t[i]);          
    }

    for(int loop=0;loop<size_tm;loop++){

    int xmin = min_number(t[loop][0].x,t[loop][1].x,t[loop][2].x);
    int xmax = max_number(t[loop][0].x,t[loop][1].x,t[loop][2].x);
    int ymin = min_number(t[loop][0].y,t[loop][1].y,t[loop][2].y);
    int ymax = max_number(t[loop][0].y,t[loop][1].y,t[loop][2].y);

	for (float i = xmin; i < xmax; ++i)
	{
		for (float j = ymin; j < ymax; ++j)
		{

			//cout<<i<<" "<<j<<"\n\n\n\n\n\n"<<endl;
			//for(int k=0;k<size_tm;k++)
			{
				if(area[loop] != 0){
				float a = area_tri(t[loop],i,j);
				
				//cout<<"k:"<<k<<" "<<abs(a-area[k])<<endl;
				if(abs(a - area[loop]) < 0.0001)
				{
					p = m1[loop].at<double>(0,0)*i + m1[loop].at<double>(0,1)*j + m1[loop].at<double>(0,2);
					q = m1[loop].at<double>(1,0)*i + m1[loop].at<double>(1,1)*j + m1[loop].at<double>(1,2);

					r = m2[loop].at<double>(0,0)*i + m2[loop].at<double>(0,1)*j + m2[loop].at<double>(0,2);
					s = m2[loop].at<double>(1,0)*i + m2[loop].at<double>(1,1)*j + m2[loop].at<double>(1,2);		

					if(q<img1.rows && s<img2.rows && p<img1.cols && r<img2.cols && p>=0 && q>=0 && r>=0 && s>=0)
					{
						img.at<uchar>(j,i) = (int)(img1.at<uchar>(q,p)*(alpha) + img2.at<uchar>(s,r)*(1-alpha));
					}
				}}
				
			}
			//cout<<"pixel value:" <<(float)img1.at<uchar>(p,q)<<endl;}
		}
	}
}



static int var = 1;
int x = binary(var);
ostringstream strg;
strg << var;
string sp = "./folder/" + strg.str() + ".jpg";
//string str =  ".jpg";
cout<<strg<<endl;
imshow("image",img);
imwrite(sp,img);
var++;
    	waitKey(100);
	//img = temp;
	
	//return temp;
}

void morphing(vector<Vec6f> tri_list, Mat &img1, Mat &img2, Mat &img, vector<Point2f> t1, vector<Point2f> t2, vector<Point2f> t, float alpha)
{
	
	vector<Point> ptm(3);
	vector<Point2f> tri_list1[tri_list.size()], tri_list2[tri_list.size()] ,tri_listm[tri_list.size()];
	for(int i = 0; i < tri_list.size(); i++)
    {
    	Vec6f tp;
        tp = tri_list[i];
        ptm[0] = Point(cvRound(tp[0]), cvRound(tp[1]));
        ptm[1] = Point(cvRound(tp[2]), cvRound(tp[3]));
        ptm[2] = Point(cvRound(tp[4]), cvRound(tp[5]));

        int index1,index2,index3;

        for(int k=0;k<t.size();k++){
        if(ptm[0].x == t[k].x && ptm[0].y == t[k].y){
        	index1 = k;
        }
        }
        for(int k=0;k<t.size();k++){
        if(ptm[1].x == t[k].x && ptm[1].y == t[k].y){
        	index2 = k;
        }}
        for(int k=0;k<t.size();k++){
        if(ptm[2].x == t[k].x && ptm[2].y == t[k].y){
        	index3 = k;
        }}

        tri_list1[i].push_back( t1[index1] );
	    tri_list1[i].push_back( t1[index2] );
	    tri_list1[i].push_back( t1[index3] );
		//if(pt1[x].x >=0 && pt1[x].y >=0 && pt1[y].x >=0 && pt1[y].y >=0 && pt1[z].x >=0 && pt1[z].y >=0){
        tri_list2[i].push_back( t2[index1] );
        tri_list2[i].push_back( t2[index2] );
        tri_list2[i].push_back( t2[index3] );
        //if ( rectm.contains(ptm[0]) && rectm.contains(ptm[1]) && rectm.contains(ptm[2])){
        tri_listm[i].push_back( ptm[0] );
        tri_listm[i].push_back( ptm[1] );
        tri_listm[i].push_back( ptm[2] );
    }
    
    //Mat im ;
   // for(float i=0;i<100;i++)
    	//img = Mat::zeros(img1.rows,img1.cols,img1.type());

    //for(float i=0;i<100;i++)
    	morphTriangle(img1, img2, img, tri_list1, tri_list2, tri_listm, alpha, tri_list.size());

   
    	
    	
}

int main(int argc, char const *argv[])
{

	int ch;
	cout<<"\n1. Part 1\n2. Part 2: \n\nEnter choice";
	cin>>ch;
	string name1,name2;
	if(ch == 1)
	{
		cout<<"Enter 1st image : ";
		cin>>name1;
		cout<<"Enter 2nd image : ";
		cin>>name2;

	Mat image1 = imread(name1,0);//tie_point_sample_image.png
	Mat image2 = imread(name2,0);
	


	Mat transform = Mat::zeros(3,3,CV_32F);

	cout<<"Enter 3X3 Matrix: \n";
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			cin>>transform.at<float>(i,j);


	int x,y,p,q;
	float alpha = 0.5;

	cout<<transform<<endl;

cout<<"Enter number of intermediate images: ";
	int no_of_images;
	cin>>no_of_images;

for(float k=0;k<=no_of_images;k++)
{
	Mat imagem = Mat::zeros(image1.rows,image1.cols,image1.type());
	alpha = k/no_of_images;
	for(int i=0;i<image1.rows;i++)
	{
		for(int j=0;j<image1.cols;j++)
		{
			x = transform.at<float>(0,0)*(i - image1.rows/2) + transform.at<float>(0,1)*(j - image2.cols/2) + transform.at<float>(0,2) + image2.rows/2;
			y = transform.at<float>(1,0)*(i - image1.rows/2) + transform.at<float>(1,1)*(j - image2.cols/2) + transform.at<float>(1,2) + image2.cols/2;

			p = (float)x*alpha + (float)i*(1 - alpha);
			q = (float)y*alpha + (float)j*(1 - alpha);


			if(p<=imagem.rows && x<image1.rows && q<imagem.cols && y<image1.cols && p>=0 && q>=0 && x>=0 && y>=0)
				imagem.at<uchar>(p,q) =  (image1.at<uchar>(i,j))*(1 - alpha) + image2.at<uchar>(x,y)*(alpha);

		}
	}

	imshow("imagem",imagem);
	waitKey(100);
}
	}
	else if(ch == 2)
	{

		cout<<"Enter 1st image : ";
		cin>>name1;
		cout<<"Enter 2nd image : ";
		cin>>name2;


	Mat image1 = imread(name1,0);
	Mat image2 = imread(name2,0);
	

	vector<Point2f> image1_points, image2_points, morphed_image_points;

	image1_points = reading_points(name1 + ".txt");
	image2_points = reading_points(name2 + ".txt");

	cout<<"Enter number of intermediate images: ";
	int no_of_images;
	cin>>no_of_images;
	for(int i=1;i<no_of_images;i++)
	{
		Mat imagem = Mat::zeros(image1.rows,image1.cols,image2.type());
		morphed_image_points = intermediate_image_points(name1 + ".txt",name2 + ".txt",(float)i/no_of_images);

		Scalar delaunay_color(255,255,255), points_color(0, 0, 255);
		Size sizem = imagem.size();

		Rect rectm(0, 0, sizem.width, sizem.height);
	    Subdiv2D subdivm(rectm);

	    for( vector<Point2f>::iterator it = morphed_image_points.begin(); it != morphed_image_points.end(); it++)
	    {
	        subdivm.insert(*it);
	    }

	    vector<Vec6f> tri_list = delaunay(subdivm,sizem);
	   
	    morphing(tri_list,image1,image2, imagem, image1_points,image2_points,morphed_image_points,(float)i/no_of_images);

	}

}
else
{
	cout<<"wrong choice entered ... terminating...\n\n";
}

return 0;
}