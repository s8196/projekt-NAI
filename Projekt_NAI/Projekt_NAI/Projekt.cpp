#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); //obraz z kamery

	int pos0X = -1;
	int pos0Y = -1;

	//tymczasowy obraz z kamery
	Mat obrazKameraChwila;
	cap.read(obrazKameraChwila);

	//stworzenie czarnego obrazu o rozmiarze obrazu kamery
	Mat obrazDoLinia = Mat::zeros(obrazKameraChwila.size(), CV_8UC3);;


	while (true)
	{
		Mat obrazKamera;
		bool b1 = cap.read(obrazKamera); //wczytanie klatki obrazu

		Mat obrazHSV;
		cvtColor(obrazKamera, obrazHSV, COLOR_BGR2HSV); //konwersja z BGR na HSV

		Mat obrazRoznica;
		inRange(obrazHSV, Scalar(170, 150, 60), Scalar(179, 255, 255), obrazRoznica); //pokazanie r�nicy mi�dzy kolorem czerwonym a t�em

		//pomini�cie ma�ych element�w
		erode(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		dilate(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		dilate(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		erode(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));

		//Obliczenie moment�w przedmiotu
		Moments Moments = moments(obrazRoznica);

		double M01 = Moments.m01;
		double M10 = Moments.m10;
		double Obiekt = Moments.m00;

		//je��li obiekt wi�kszy od 1000 pikseli
		if (Obiekt > 10000)
		{
			//wsp�rz�dne �rodka obiektu
			int pos1X = M10 / Obiekt;
			int pos1Y = M01 / Obiekt;

			if (pos0X >= 0 && pos0Y >= 0 && pos1X >= 0 && pos1Y >= 0)
			{
				//rysuje linie mi�dzy punktami
				line(obrazDoLinia, Point(pos1X, pos1Y), Point(pos0X, pos0Y), Scalar(130, 130, 130), 20);
			}

			pos0X = pos1X;
			pos0Y = pos1Y;
		}

		imshow("R�nica mi�dzy kolorem czerwonym a reszta", obrazRoznica);

		obrazKamera = obrazKamera + obrazDoLinia;
		imshow("Kamera", obrazKamera);

		if (waitKey(30) == 27)
		{
			break;
		}
	}

	return 0;
}