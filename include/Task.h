//
// Created by romain on 26/04/18.
//

#ifndef PLAZZA_TASK_H
#define PLAZZA_TASK_H

#include <utility>
#include <vector>
#include <string>

class Task {
public:
    Task(std::string const &regex, std::vector<std::string> &files) :
            _regex(regex),
            _files(files) {}

    std::string const &getRegex() const;
    std::vector<std::string> &getFiles();
private:
    std::string _regex;
    std::vector<std::string> _files;

};


#endif //PLAZZA_TASK_H
