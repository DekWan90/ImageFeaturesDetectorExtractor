#pragma once
#ifndef VERSION_H
#define VERSION_H

#ifndef SIZEOF
#define SIZEOF( X ) sizeof( X ) / sizeof( X[0] )
#endif // SIZEOF

// std
#include <iostream>
#include <memory>
#include <typeinfo>

// library
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <gtkmm.h>
#include <omp.h>

// dekwan library
#include <matematik.h>

#define FULL_VERSION "ImageFeaturesDetectorExtractor 0.19.04.30.08"
#define ImageFeaturesDetectorExtractor_VERSION "0.19.04.30.08"
#define ImageFeaturesDetectorExtractor_VERSION_SHORT "0.19.04"
#define ImageFeaturesDetectorExtractor_VERSION_MAJOR 19
#define ImageFeaturesDetectorExtractor_VERSION_MINOR 04
#define ImageFeaturesDetectorExtractor_VERSION_RELEASE 30
#define ImageFeaturesDetectorExtractor_VERSION_BUILD 08

const std::string PROJEK_DIR = "/home/dekwan/.ImageFeaturesDetectorExtractor/";

#endif /* VERSION_H */
