#ifndef cell_h
#define cell_h
#include <vector>

template <class CellType>
class Cell{
    CellType val;
    bool isNull = true;
public:
    bool setValue(CellType val);
    CellType getValue()const;
    std::string toString();
    bool cellIsNull();
};

#endif
