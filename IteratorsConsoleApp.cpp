// IteratorsConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "IntWrapper.h"
#include "IntIterator.h"
#include "CircularContainer.h"

template<typename T>
void int_wrapper_example( )
{
    cout << "Example using " << typeid(T).name( ) << endl;

    T i1( 0 ), i2( 10 );

    cout << "values: ";
    for(; i1 != i2; ++i1)
        cout << *i1 << " ";
    cout << endl;

}

template<typename T>
void int_range_example( )
{
    cout << "Example of range using " << typeid(T).name( ) << endl;

    cout << "values: ";
    for(auto value : T( 0, 10 ))
        cout << value << " ";
    cout << endl;

    //compile-time error  
    //T range( 0, 10 );
    //vector<int> integers;
    //copy( range.begin( ), range.end( ), back_inserter( integers ) );
    //'iterator_category': is not a member of any direct of'std::iterator_traits<_Iter>'	  
}


template<typename T>
void range_algorithms_example( )
{
    cout << "Example using stl algorithms and the class " << typeid(T).name( ) << endl;

    //no compile-time error  
    T range( 0, 10 );
    vector<int> integers;
    copy( range.begin( ), range.end( ), back_inserter( integers ) );

    //vector created from a range using copy
    copy( integers.begin( ), integers.end( ), ostream_iterator<int>( cout, " " ) );
    cout << endl;

    //copying a range to cout;
    copy( range.begin( ), range.end( ), ostream_iterator<int>( cout, " " ) );
    cout << endl;

    //range-based for
    for(auto n : T( 0, 10 ))
        cout << n << " ";
    cout << endl;

    //advance, next 
    T range2( 0, 10 );
    auto it1 = range2.begin( );
    cout << "*i1 = " << *it1 << " next = " << *(next( it1 )) << endl;

    cout << "*i1 = " << *it1;
    advance( it1, 4 );
    cout << " advance(4) = " << *(it1) << endl;
    cout << endl;
}

void circular_container( )
{
    Containers::CircularContainer<int, 5> container;

    cout << "Adding 9 elements to a container of capacity = 5 " << endl;
    for(auto n : ContainersIterators::IntRange( 0, 9 ))
    {
        container.push_back( n );
        cout << container << endl;
    }

    cout << "Remove the last three" << endl;
    container.pop( 3 );
    cout << container << endl;

    cout << "Append three more !" << endl;
    container.push( { 100,200,300 } );
    cout << container << endl;

    cout << "Add four and remove one several times" << endl;
    container.clear( );
    for(auto n : ContainersIterators::IntRange( 0, 4 ))
    {
        container.push( { n - 2, n - 1, n, n + 101, n + 2000 } );
        container.pop( 1 );
        cout << container << endl;
    }
}

void circular_container_iterator( )
{
    Containers::CircularContainer<int, 5> container;
    container.push( { 1,2,3,4,5,6,7,8,9,10 } );

    vector<int> numbers;
    copy( container.cbegin( ), container.cend( ), back_inserter( numbers ) );

    fill( container.begin( ), container.end( ), 0 );

    auto it = next( container.begin( ) );

    auto highest_price_it = max_element( container.cbegin( ), container.cend( ) );

    for_each( begin( container ), end( container ), []( auto &v ) { v *= 2; } );

    for(auto value : container)
        cout << value << " ";
    cout << endl;
}

int main( )
{
    int option = 6;

    switch(option)
    {

    case 1:
    {
        int_wrapper_example<IntWrapper>( );
        break;
    }

    case 2:
    {
        int_range_example<IntWrapperRange>( );
        break;
    }

    case 3:
    {
        int_wrapper_example<ContainersIterators::IntIterator>( );
        break;
    }

    case 4:
    {
        range_algorithms_example<ContainersIterators::IntRange>( );
        break;
    }

    case 5:
    {
        circular_container( );
        break;
    }

    case 6:
    {
        circular_container_iterator();
        break;
    }


    default:
        break;
    }


    std::cout << "Hello World!\n";
}
