#-------------------------------------------------
#
# Project created by QtCreator 2019-04-15T22:22:32
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = garage
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    camera.cpp \
    v4l2.c \
    picture.cpp \
    scanner.cpp \
    rfid.cpp \
    zibgee.cpp \
    setting.cpp \
    frmnum.cpp \
    cost.cpp

HEADERS  += mainwidget.h \
    camera.h \
    v4l2.h \
    picture.h \
    garage.hpp \
    scanner.h \
    rfid.h \
    zibgee.h \
    setting.h \
    frmnum.h \
    cost.h

FORMS    += mainwidget.ui \
    camera.ui \
    picture.ui \
    scanner.ui \
    setting.ui \
    frmnum.ui \
    cost.ui

RESOURCES += \
    pictures.qrc

INCLUDEPATH += /home/teoan/opencv-3.2.0_arm/include \
/home/teoan/opencv-3.2.0_arm/include/opencv \
/home/teoan/opencv-3.2.0_arm/include/opencv2 \
/home/teoan/EasyPR/include \
/home/teoan/EasyPR/include/easypr





LIBS += /home/teoan/opencv-3.2.0_arm/lib/libopencv_calib3d.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_core.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_features2d.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_flann.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_highgui.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_imgcodecs.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_imgproc.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_ml.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_objdetect.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_photo.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_shape.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_stitching.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_superres.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_videoio.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_video.so \
/home/teoan/opencv-3.2.0_arm/lib/libopencv_videostab.so \
/home/teoan/EasyPR_arm/libeasypr.so \
/home/teoan/EasyPR_arm/libthirdparty.so




QMAKE_CXXFLAGS+=-std=c++11

#INCLUDEPATH += /usr/local/include \
#/usr/local/include/opencv \
#/usr/local/include/opencv2 \
#/usr/local/include/opencv2/imgproc \
#/home/teoan/EasyPR/include \
#/home/teoan/EasyPR/include/easypr



#LIBS += /usr/local/lib/libopencv_imgproc.so.3.2 \
#/usr/local/lib/libopencv_calib3d.so.3.2 \
#/usr/local/lib/libopencv_core.so.3.2 \
#/usr/local/lib/libopencv_features2d.so.3.2 \
#/usr/local/lib/libopencv_flann.so.3.2 \
#/usr/local/lib/libopencv_highgui.so.3.2 \
#/usr/local/lib/libopencv_imgcodecs.so.3.2 \
#/usr/local/lib/libopencv_ml.so.3.2 \
#/usr/local/lib/libopencv_objdetect.so.3.2 \
#/usr/local/lib/libopencv_photo.so.3.2 \
#/usr/local/lib/libopencv_shape.so.3.2 \
#/usr/local/lib/libopencv_stitching.so.3.2 \
#/usr/local/lib/libopencv_superres.so.3.2 \
#/usr/local/lib/libopencv_videoio.so.3.2 \
#/usr/local/lib/libopencv_video.so.3.2 \
#/usr/local/lib/libopencv_videostab.so.3.2 \
#/usr/local/lib/libeasypr.so \
#/usr/local/lib/libthirdparty.so






