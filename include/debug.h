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

    LogEntry(int lvl, std::string msg, time_t tstamp) : level(lvl), message(msg), timestamp(tstamp) {};
};
typedef std::vector<LogEntry> LogList;


extern LogList log_list;

template<typename... Args>
void log(int lvl, const Args&... args) {

    
    // store logentry into a datastructure
    std::ostringstream oss;
    // oss << first;
    ((oss << args), ...);

    if (lvl < 4){ // higher priority log (1 is highest, 4 lowest) are sotred separately to be printed on console later 
        log_list.push_back(LogEntry(lvl, oss.str(), frame.t_current_ms));
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
    {
        std::ostringstream oss;
        // oss << first;
        ((oss << args), ...);
        if (b_BALISE)
            std::cout << oss.str() << std::endl;
        log(4, "Balise : ", oss.str());
        // log_list.push_back(LogEntry(lvl, oss.str()));
    }
}

