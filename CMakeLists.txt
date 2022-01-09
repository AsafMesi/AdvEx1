cmake_minimum_required(VERSION 3.20)
project(APP)

set(CMAKE_CXX_STANDARD 11)

add_executable(APP anomaly_detection_util.cpp timeseries.cpp SimpleAnomalyDetector.cpp minCircle.cpp minCircle.h HybridAnomalyDetector.cpp HybridAnomalyDetector.h "Ex5 files/MainTrain_Ex5.cpp" commands.h CLI.cpp CLI.h Server.cpp Server.h MainTrain_Ex6.cpp)
