#ifndef INT_ITERATOR_H_
#define INT_ITERATOR_H_ 1

#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <any>

namespace ContainersIterators
{
    class IntIterator
    {
    public:

        using  iterator_category = std::input_iterator_tag;
        using  value_type = int;
        using  reference = const int&;
        using  pointer = int*;
        using  difference_type = ptrdiff_t;
        using  self_type = IntIterator;

        IntIterator( int cursor ) : _cursor{ cursor } { ; }

        IntIterator( const self_type &it ) = default;

        bool operator==( const self_type &it ) const noexcept
        {
            return _cursor == it._cursor;
        }

        bool operator!=( const self_type &it ) const noexcept
        {
            return !(*this == it);
        }

        self_type operator++( int )  noexcept
        {
            self_type tmp = *this;
            _cursor += 1;
            return tmp;
        }

        self_type& operator++( )  noexcept
        {
            _cursor += 1;
            return *this;
        }

        reference operator* ( ) const
        {
            return  const_cast<int&>(_cursor);
        }

        reference operator-> ( ) const
        {
            return  const_cast<int&>(_cursor);
        }

        operator int( ) const { return _cursor; }

    private:

        int _cursor;
    };

    class IntRange
    {
    public:

        explicit IntRange( int i1, int i2 ) : _i1{ i1 }, _i2{ i2 } {; }

        IntIterator begin( ) const { return _i1; }

        IntIterator end( ) const
        {
            return _i2;
        }

    private:

        IntIterator _i1, _i2;
    };
}


#endif
