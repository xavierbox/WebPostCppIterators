#ifndef CIRCULARCONTAINER_H_
#define CIRCULARCONTAINER_H_ 1

#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>

using namespace std;

namespace Containers
{

    template<typename T, int CAPACITY>
    class CircularContainer
    {
        friend ostream& operator<<( ostream &out, const CircularContainer& buffer )
        {
            out << "[ ";
            for(int n = 0; n < buffer.size( ); n++)
            {
                out << buffer.at( n ) << " ";
            }
            out << "]";

            return out;
        }

    public:

        using  value_type = T;
        using  reference = T & ;
        using  pointer = T * ;
        using  value_type = typename T;
        using  reference = typename T&;

        CircularContainer( ) : _head( 0 ), _tail( 0 ), _size( 0 ), _current( 0 ), _capacity( CAPACITY ) { }

        CircularContainer( const  CircularContainer &c )
            :_head( c._head ), _tail( c._tail ), _size( c._size ), _current( c._current ), _capacity( c._capacity )
        {
            std::copy( std::begin( c._c ), std::end( c._c ), std::begin( _c ) );
        }

        CircularContainer( CircularContainer &&c ) noexcept
            :_head( c._head ), _tail( c._tail ), _size( c._size ), _current( c._current ), _capacity( c._capacity )
        {
            _c = std::move( c._c );
            c.reset( );
        }

        ~CircularContainer( ) = default;

        CircularContainer& operator = ( const  CircularContainer &c ) noexcept
        {
            std::copy( std::begin( c._c ), std::end( c._c ), std::begin( _c ) );
            std::tie( _head, _tail, _current, _size, _capacity ) = c.props( );
            return *this;
        }

        CircularContainer& operator = ( const  CircularContainer &&c ) noexcept
        {
            if(this == &c) return *this;
            _c = std::move( c._c );
            std::tie( _head, _tail, _current, _size, _capacity ) = c.props( );
            c.reset( );
            return *this;
        }


        CircularContainer( std::initializer_list<T> l ) : _head( 0 ), _tail( 0 ), _size( 0 ), _current( 0 ), _capacity( CAPACITY )
        {
            for(auto item : l) push_back( item );
        }

        CircularContainer* operator->( ) { return this; }

        int capacity( ) const { return _capacity; }

        void push( const vector<T> &values )
        { 
          for(auto value: values) push_back(value);
        }

        void push_back( T val ) noexcept
        {
            _c[_current] = val;
            _current = move_right( _current );
            _tail = move_left( _current );

            if(_size >= _capacity)
            {
                _head = move_right( _head );
            }

            _size = std::min<int>( _size + 1, _capacity );
        }

        void reset( ) noexcept { clear( ); }

        void clear( ) noexcept
        {
            _head = 0;
            _tail = 0;
            _size = 0;
            _current = 0;
        }

        void emplace_back( T val )
        {
            if(full( ))
            {
                throw overflow_error( "Container is full" );
            }

            push_back( val );
        };

        void pop( int n ) noexcept
        {
            if(n >= _size)
            {
                clear( );
            }
            else
            {
                for(int k = 0; k < n; k++)
                    pop( );
            }
        }

        void pop( ) noexcept
        {
            //size = 0 or 1 
            if((empty( )) || (_head == _tail))
            {
                clear( );
                return;
            }

            _current = _tail;
            _tail = move_left( _tail );
            _size = std::max<int>( 0, _size - 1 );
        }

        std::size_t size( ) const noexcept { return _size; };

        bool empty( ) const noexcept { return size( ) <= 0; };

        bool full( ) const noexcept { return size( ) >= capacity( ); };


        template<typename Container>
        class CircularIterator
        {
        public:

            using  iterator_category = std::forward_iterator_tag;
            using  value_type = typename Container::value_type;
            using  reference = typename Container::reference;
            using  pointer = typename Container::pointer;
            using  difference_type = ptrdiff_t;
            using  self_type = CircularIterator;

            CircularIterator( )
            {
                _container = nullptr;
                _cursor = -1;
            }

            CircularIterator( const Container &container, int cursor )
            {
                _container = &container;
                _cursor = cursor;
            };

            CircularIterator( const Container *container, int cursor )
            {
                _container = container;
                _cursor = cursor;
            };

            CircularIterator( const CircularIterator &it ) = default;

            bool operator==( const CircularIterator &it ) const noexcept
            {
                return _cursor == it._cursor;
            }

            bool operator!=( const CircularIterator &it ) const noexcept
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
                return  (_container->at( real_index( ) ));
            }

            reference operator* ( )
            {
                return  _container->operator[]( _cursor );
            }

            reference operator-> ( ) const
            {
                return  _container->operator[]( _cursor );
            }

        private:

            const Container *_container;
            int _cursor;
        };

        typedef CircularIterator< CircularContainer<T, CAPACITY> > circular_iterator;
        typedef CircularIterator< const CircularContainer<T, CAPACITY> > const_circular_iterator;

        circular_iterator begin( )
        {
            return circular_iterator( *this, 0 );
        }

        circular_iterator end( )
        {
            return circular_iterator( *this, _size );
        }

        const_circular_iterator cbegin( )
        {
            return const_circular_iterator( *this, 0 );
        }

        const_circular_iterator cend( )
        {
            return const_circular_iterator( *this, _size );
        }
        reference operator [] ( int n ) const
        {
            return get( n );
        }

        reference operator [] ( int n )
        {
            return get( n );
        }

        inline const value_type at( int n ) const
        {
            auto v = real_index( n );
            return _c.at( v );
        }

    private:


        int _head, _tail, _current;
        size_t _size, _capacity;
        array<T, CAPACITY> _c;

        tuple<int, int, int, size_t, size_t> props( )   const { return make_tuple( _head, _tail, _current, _size, _capacity ); }

        inline int move_right( int pos ) const
        {
            return pos + 1 >= _capacity ? 0 : pos + 1;
        }

        inline int move_left( int pos ) const
        {
            return pos - 1 < 0 ? _capacity - 1 : pos - 1;
        }

        int real_index( int n ) const
        {
            int fold = (_head + n) / _capacity;

            int ret = _head + n - fold * _capacity;

            return  _head + n - fold * _capacity;
        }

        reference get( int n ) const
        {
            return  const_cast<int&>(_c[real_index( n )]);
        }

        reference get( int n )
        {
            return _c[real_index( n )];
        }

    };

}

#endif 


