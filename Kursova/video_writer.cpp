#include "video_writer.h"

Video_Writer::Video_Writer(cv::VideoCapture * cam, QObject *parent)
    : QThread(parent) {
    cam = cam;
}

void Video_Writer::setFilePath(std::string pathToSave) {
    // path = pathToSave;
    video = cv::VideoWriter(pathToSave, CV_FOURCC('M','J','P','G'),10,
                         cv::Size(cam->get(CV_CAP_PROP_FRAME_WIDTH),
                                  cam->get(CV_CAP_PROP_FRAME_HEIGHT)),true);
}

void Video_Writer::shouldIwrite(bool continue_write) {
    should_writing = continue_write;
}

void Video_Writer::startWriting() {

    start(LowPriority);

    cv::Mat frame;
    while(1) {
        while(should_writing) {  // every time check bool is slow
            for (int i = 0; i < 8; i++) { // for working faster
                *cam >> frame;
                video.write(frame);
            }
        }
        this->msleep(1000);
    }
}

