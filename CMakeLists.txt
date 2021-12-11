cmake_minimum_required(VERSION 3.20)
project(AdvEx1)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvEx1 MainTrain.cpp anomaly_detection_util.cpp timeseries.cpp SimpleAnomalyDetector.cpp MainTrain.cpp minCircle.cpp minCircle.h)
