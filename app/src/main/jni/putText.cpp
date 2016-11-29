#include "jni.h"
#include "primalpond_com_sensibleopencv_MainActivity.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

void vRotate180(Mat* img);

JNIEXPORT void JNICALL Java_primalpond_com_sensibleopencv_MainActivity_putText
  (JNIEnv * env, jobject obj, jlong imageAddr) {
    Mat* image = (Mat*) imageAddr;
    Point position = Point(100,100);
    Point newLine = Point(0, 50);
    Scalar color = Scalar(255,255,255);

    cvtColor(*image, *image, CV_BGR2GRAY);
    vRotate180(image);



    putText(*image, "Hello SensibleOpenCV.", position, FONT_HERSHEY_PLAIN, 2, color);
    putText(*image, "Andriod OpenCV Java and C++ harmony", position + newLine, FONT_HERSHEY_PLAIN, 2, color);
    return;
   }

uint32_t reverse(uint32_t x)
{
    uint32_t temp = 0, retVal = 0;

    temp = (x & 0xFF000000);
    retVal |= (temp >> 24);

    temp = (x & 0x00FF0000);
    retVal |= (temp >> 8);

    temp = (x & 0x0000FF00);
    retVal |= (temp << 8);

    temp = (x & 0x000000FF);
    retVal |= (temp << 24);

    return(retVal);

}

void vRotate180(Mat* img){
    uint32_t uiTempPixelFront;
    uint32_t uiTempPixelBack;
    uint32_t uiPixelCount = (img->rows * img->cols) / 8;
    uint32_t * uiPicBegin = (uint32_t *) img->data;
    uint32_t * uiPicEnd = (uint32_t *) (img->dataend-4);

    while(uiPixelCount-- > 0) {
        /* Fetch the pixels */
        uiTempPixelFront = *uiPicBegin;
        uiTempPixelBack = *uiPicEnd;

        /* Reverse 32bit int */
        uiTempPixelFront = reverse(uiTempPixelFront);
        uiTempPixelBack = reverse(uiTempPixelBack);

        /* Write reversed pixels from back to the begin of the pic and vice versa, inc and dec the pointers */
        *uiPicBegin++ = uiTempPixelBack;
        *uiPicEnd-- = uiTempPixelFront;
    }
}

