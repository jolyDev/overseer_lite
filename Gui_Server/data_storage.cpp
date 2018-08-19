#include "data_storage.h"
cv::Mat QImage2Mat(QImage const& src);

Data_Storage::Data_Storage() {

}

QPixmap pixmapFrom(const QJsonValue &val) {
  auto const encoded = val.toString().toLatin1();
  QPixmap p;
  p.loadFromData(QByteArray::fromBase64(encoded), "PNG");
  return p;
}

QString Data_Storage::addDir(QString dir) {
    QDir().mkdir(dir);
    std::cout << dir.toStdString() << std::endl;
    curDir.mkpath(dir);
    return (QDir().mkdir(dir)) ? "dir added" : "can't add dir";
}

bool Data_Storage::send_photo_dir_content(QString data) {

    std::string ArtomVsePorishae = data.toStdString();
    std::string path = "";
    int i = 0;
    for (; ArtomVsePorishae.at(i) != '/'; i++) {
        path = path + ArtomVsePorishae.at(i);
    }
    QDir newDir(QString::fromStdString(path));
    std::cout << path << std::endl;

    std::string path2 = "";

    i++;
    for (; ArtomVsePorishae.at(i) != '/'; i++) {
        path2 = path2 + ArtomVsePorishae.at(i);
    }

    std::string name = "";
    i++;
    for (; ArtomVsePorishae.at(i) != '/'; i++) {
        name = name + ArtomVsePorishae.at(i);
    }


    newDir = QDir(QString::fromStdString(path + "/" + path2 + "/"));
    std::cout << path2  << std::endl;

    QString messStr = data.mid(i + 1, data.length());

    QPixmap m;

    m.loadFromData(QByteArray::fromBase64(messStr.toLatin1()));

    QFile file(QString::fromStdString(path + "/" + path2 + "/" + name));

    m.save(&file, "jpg");

    return true;
}


bool Data_Storage::send_video_dir_content(QString data) {

    std::string ArtomVsePorishae = data.toStdString();
    std::string path = "";
    int i = 0;
    for (; ArtomVsePorishae.at(i) != '/'; i++) {
        path = path + ArtomVsePorishae.at(i);
    }
    std::cout << path << std::endl;

    std::string path2 = "";
    i++;
    for (; ArtomVsePorishae.at(i) != '/'; i++) {
        path2 = path2 + ArtomVsePorishae.at(i);
    }

    std::string name = "";
    i++;
    for (; ArtomVsePorishae.at(i) != '/'; i++) {
        name = name + ArtomVsePorishae.at(i);
    }

    QString messStr = data.mid(i + 1, data.length());

    QPixmap m;
    m.loadFromData(QByteArray::fromBase64(messStr.toLatin1()));

    cv::Mat frame = QImage2Mat(m.toImage());
    if (name.compare(video_name) != 0) {
        video = cv::VideoWriter(path + "/" + path2 + "/" + name,
                                CV_FOURCC('M', 'J', 'P', 'G'),
                                5,
                                frame.size(), true);
        video_name = name;
    }
    cv::cvtColor(frame, frame,CV_BGR2RGB);
    video.write(frame);
    std::cout << path + "/" + path2 + "/" + name  << std::endl;

    return true;
}

cv::Mat QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC4,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}
