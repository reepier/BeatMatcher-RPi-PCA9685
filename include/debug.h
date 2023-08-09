#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "constant.h"
#include "wiringPi.h"

void init_display();
void display();
void display_curse();


void balise(const char*);


class LogEntry{
public:
    int level;
    std::string message;
    LogEntry(int lvl, std::string msg) : level(lvl), message(msg) {};
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

void spit_log();


