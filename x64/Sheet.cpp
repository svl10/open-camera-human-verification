#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); // Setting up the camera. If you have multiple cameras, change the number in cap(n)

    cap.set(CAP_PROP_FRAME_WIDTH, 600);
    cap.set(CAP_PROP_FRAME_HEIGHT, 600);

    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml"); // Load the face detection model

    vector<Rect> faces;
    Mat frame;
    double totalTime = 0;
    int numFaces = 0;

    while (true) {
        cap.read(frame);
        if (frame.empty()) break;

        double timeStart = (double)getTickCount();

        // Detect one face with reduced scales
        faceCascade.detectMultiScale(frame, faces, 1.2, 3, 0, Size(30, 30), Size(0, 0));

        if (!faces.empty()) {
            const auto& face = faces[0];
            rectangle(frame, face, Scalar(255, 0, 255), 3);
            putText(frame, "Face detected", Point(face.x, face.y - 10), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 0, 255), 1);

            // Update timer
            double timeEnd = (double)getTickCount();
            double timeElapsed = (timeEnd - timeStart) / getTickFrequency();
            stringstream ss;
            ss << fixed << setprecision(2) << timeElapsed;
            string timeStr = "Time: " + ss.str() + "s";
            putText(frame, timeStr, Point(face.x, face.y + face.height + 15), FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 0, 255), 1);

            totalTime += timeElapsed;
            numFaces++;
        }

        imshow("Face Detection", frame);

        if (waitKey(20) == 'q') break; // Quit if 'q' key is pressed
    }

    if (numFaces > 0) {
        double avgTime = totalTime / numFaces;
        cout << "Average processing time per face: " << fixed << setprecision(2) << avgTime << "s" << endl;
    }

    return 0;
}