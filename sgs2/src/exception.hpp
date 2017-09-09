#ifndef __EXCEPTION_H
#define __EXCEPTION_H

namespace own_excpetion
{
class file_not_exist
{
public:
    file_not_exist() {};
    ~file_not_exist() {};
    const char* what() const { return "Unable to find file!"; }
};
}

#endif
