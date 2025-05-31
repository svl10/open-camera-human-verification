#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>

using namespace std;
using namespace cv;


int main()
{
    string ans;
    cout << "Are you a human?(Y/N): ";
    cin >> ans;
    if (ans != "Y") {
        system("Color 0C");
        cout << "Not a human" << endl;
        return -1;
    }

    string ans2;
    cout << "For security measures we would need to verify if you're actually a human." << endl
        << "With that said we would be using your camera to see if you're actually" << endl
        << "a human by detecting your face, rest assured we won't be collecting any" << endl
        << "data before, during, and after the process" << endl;
    cout << "Would you grant us access to your camera (Y/N): ";
    cin >> ans2;
    if (ans2 != "Y") {
        system("Color 0C");
        cout << "You cannot proceed, please try again" << endl;
        return -1;
    }

    VideoCapture cap(0); //Setting up the camera,if you have multiple camera change the number in cap(n)

    /// Changing camera size/pixels para dili lag
    cap.set(CAP_PROP_FRAME_WIDTH, 600);
    cap.set(CAP_PROP_FRAME_HEIGHT, 600);


    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml"); //Importing the file para ma detect ang face

    vector<Rect> faces;

    //Storing images
    Mat frame;

    float timer = 15.00;
    float ftimer = 5.00;


    while (true) {
        if (ftimer < 0) {
            system("Color 0A");
            cout << " " << endl;
            cout << " " << endl;
            cout << "     Human Verification Complete: You are a Human     " << endl;
            cout << " " << endl;
            cout << " " << endl;
            break;
        }

        else if (timer < 0) {
            system("Color 0C");
            cout << " " << endl;
            cout << " " << endl;
            cout << "      Human verification failed, please try again      " << endl;
            cout << " " << endl;
            cout << " " << endl;
            break;
        }

        cap.read(frame);
        if (frame.empty()) break;

        Point text_pos(50, 50);
        float text_size = 0.8;
        string text = "Scanning complete in ";
        text = text + to_string(int(ftimer)) + " seconds";
        Scalar font_Color(0, 255, 255);
        int font_weight = 1;



        faceCascade.detectMultiScale(frame, faces, 1.2, 10, 0, Size(70, 70)); // Detect faces

        for (const auto& face : faces) {

            rectangle(frame, face, Scalar(0, 0, 255), 3);
            putText(frame, text, Point(face.x, face.y), FONT_HERSHEY_COMPLEX, text_size, font_Color, font_weight);
            ftimer = ftimer - 0.05;
        }

        imshow("Human Verification", frame);
        if (waitKey(1) == 'q') break; // Quit if 'q' key is pressed
        Sleep(1);
        timer = timer - 0.05;

    }

    return 0;
}