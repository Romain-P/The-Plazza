//
// Created by romain on 26/04/18.
//

#include "Task.h"

std::string const &Task::getRegex() const {
    return _regex;
}

std::vector<std::string> &Task::getFiles() {
    return _files;
}
