#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    std::ostringstream oss;
    // oss << first;
    ((oss << args), ...);
    log_list.push_back(LogEntry(lvl, oss.str()));
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

