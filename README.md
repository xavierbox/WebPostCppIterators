
## A very simple demo of C++ custom iterators posted online 

This repo is in support to an online post on C++ iterators. 
The project includes a circular container, which is not available in the STL, and a STL-compliant iterator for it. 
The STL algorithms would work seamlessly with our container. the following code is an exmaple on the use of the 
container:

```
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
```
Adding 9 elements to a container of capacity = 5
[ 0 ]
[ 0 1 ]
[ 0 1 2 ]
[ 0 1 2 3 ]
[ 0 1 2 3 4 ]
[ 1 2 3 4 5 ]
[ 2 3 4 5 6 ]
[ 3 4 5 6 7 ]
[ 4 5 6 7 8 ]
Remove the last three
[ 4 5 ]
Append three more !
[ 4 5 100 200 300 ]
Add four and remove one several times
[ -2 -1 0 101 ]
[ -1 0 1 102 ]
[ 0 1 2 103 ]
[ 1 2 3 104 ]


And the iterator:

```
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
```
