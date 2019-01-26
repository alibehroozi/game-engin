#include "cell.h"
#include <sstream>


template <class CellType>
bool Cell<CellType>::setValue(CellType val){
    this->val = val;
    return true;
}


template <class CellType>
CellType Cell<CellType>::getValue()const{
    return this->val;
}

template <class CellType>
bool Cell<CellType>::cellIsNull(){
    return this->isNull;
}

template <class CellType>
std::string Cell<CellType>::toString(){
    std::stringstream ss;
    std::string target;
    ss << this->val;
    ss >> target;
    return target;
}
