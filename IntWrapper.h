#ifndef INTWRAPPER_H_
#define INTWRAPPER_H_ 1

#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <any>

using namespace std;

class IntWrapper
{
 
public:

    IntWrapper( int cursor ) : _cursor{ cursor } { ; }

    IntWrapper( const IntWrapper &it ) = default;

    bool operator==( const IntWrapper &it ) const noexcept
    {
        return _cursor == it._cursor;
    }

    bool operator!=( const IntWrapper &it ) const noexcept
    {
        return !(*this == it);
    }

    IntWrapper operator++( int )  noexcept
    {
        IntWrapper tmp = *this;
        _cursor += 1;
        return tmp;
    }

    IntWrapper& operator++( )  noexcept
    {
        _cursor += 1;
        return *this;
    }

    const int& operator* ( ) const
    {
        return  const_cast<int&>(_cursor);
    }

private:

    int _cursor;
};


class IntWrapperRange
{
public:

    explicit IntWrapperRange( int i1, int i2 ) : _i1{ i1 }, _i2{ i2 } {; }

    IntWrapper begin( ) const
    {
        return _i1;
    }

    IntWrapper end( ) const
    {
        return _i2;
    }

private:

    IntWrapper _i1, _i2;
};


#endif 
