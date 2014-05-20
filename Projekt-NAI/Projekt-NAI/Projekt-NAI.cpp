#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); //obraz z kamery

	while (true)
	{
		Mat obrazKamera;
		bool b1 = cap.read(obrazKamera); //wczytanie klatki obrazu

		Mat obrazHSV;
		cvtColor(obrazKamera, obrazHSV, COLOR_BGR2HSV); //konwersja z BGR na HSV

		Mat obrazRoznica;
		inRange(obrazHSV, Scalar(170, 150, 60), Scalar(179, 255, 255), obrazRoznica); //pokazanie ró¿nicy miêdzy kolorem czerwonym a t³em

		//pominiêcie ma³ych elementów
		erode(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		dilate(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		dilate(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		erode(obrazRoznica, obrazRoznica, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));

		imshow("Ró¿nica miêdzy kolorem czerwonym a reszta", obrazRoznica);

		obrazKamera = obrazKamera;
		imshow("Kamera", obrazKamera);

		if (waitKey(30) == 27)
		{
			break;
		}
	}

	return 0;
}