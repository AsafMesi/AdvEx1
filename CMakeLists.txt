cmake_minimum_required(VERSION 3.20)
project(APP)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(APP anomaly_detection_util.cpp timeseries.cpp
        SimpleAnomalyDetector.cpp minCircle.cpp minCircle.h HybridAnomalyDetector.cpp HybridAnomalyDetector.h
        commands.h CLI.cpp CLI.h MainTrain_Ex5.cpp)
