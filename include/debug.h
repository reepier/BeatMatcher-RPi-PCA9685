#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

#include "sysfcn.h"
#include "config.h"
#include "wiringPi.h"
 
void init_display();
void display();
void display_curse();


class LogEntry{
public:
    int level;
    std::string message;
    time_t timestamp;

    LogEntry(int lvl, std::string msg) : level(lvl), message(msg), timestamp(frame.t_current_ms) {};
};
typedef std::vector<LogEntry> LogList;


extern LogList log_list;

template<typename... Args>
void log(int lvl, const Args&... args) {

    
    // store logentry into a datastructure
    std::ostringstream oss;
    // oss << first;
    ((oss << args), ...);

    if (lvl < 4){
        log_list.push_back(LogEntry(lvl, oss.str()));
    }


    // log into a file
    const std::string filename = "beatmatcher.log";
    const std::size_t thresholdSizeInBytes = 1000000;               //Bytes     1Mo
    std::ofstream logFile(filename, std::ios::app);
    logFile << "[" << frame.t_current_ms/1000.0 << "] " << std::string(lvl, ' ') << oss.str() << std::endl;

    //delete log if its size exceeds a threshold
    struct stat fileInfo;
    if (stat(filename.c_str(), &fileInfo) != 0) {
        // Error accessing file information
        std::cerr << "Error accessing file: " << filename << std::endl;
        return;
    }

    // Check if the file size exceeds the threshold
    if (fileInfo.st_size > static_cast<off_t>(thresholdSizeInBytes)) {
        // File size exceeds the threshold, delete the file
        if (std::remove(filename.c_str()) != 0) {
            log(3, "Error deleting file: ", filename);
        } else {
            // log(3, "File deleted: ", filename );
        }
    } else {

    }



}

template<typename... Args>
void balise(const Args&... args) {
    if (b_BALISE){
        std::ostringstream oss;
        // oss << first;
        ((oss << args), ...);
        std::cout << oss.str() << std::endl;
        // log_list.push_back(LogEntry(lvl, oss.str()));
    }
}

