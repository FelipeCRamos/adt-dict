/**
 * @file driver_dictionary.cpp
 * @brief File for DAL and DSAL classes tests .
 */

#include <iostream>   // cout, endl
#include <cassert>    // assert()
#include <algorithm>  // shuffle
#include <random>     // random_device, mt19937
#include <iterator>   // std::begin(), std::end()

#include "dal.hpp"
#include "dsal.hpp"

/**
 * @brief      Class for my key comparator.
 */
class MyKeyComparator
{
    public:
        bool operator ()( const int & lhs, const int & rhs ) const
        {
            return lhs < rhs ;
        }
};

int main ( void )
{
    {
        // Testing default constructor.
        auto cmp = [](const int& l, const int& r) { return l < r; };
        DAL<int, std::string, decltype(cmp) > dic;
        // assert( dic.capacity() == 50 );

        DAL<int, std::string, MyKeyComparator> dic2(100);
        // assert( dic2.capacity() == 100 );
    }

    {
        // Testing insert.
        DAL<int, std::string, MyKeyComparator> dict(3);
        auto cmp = [](const int& l, const int& r) { return l < r; };
        DAL<int, std::string, decltype(cmp) > dict2(3);

        // testing the regular insert
        assert( dict.insert( 1, "AAA" ) );
        assert( dict.insert( 2, "BBB" ) );

        // dicting the insert failure for duplicate keys.
        assert( false == dict.insert( 2, "BBB" ) );

        // dicting the insert for overflow check.
        assert( dict.insert( 3, "CCC" ) );
        // assert( dict.insert( 4, "DDD" ) == false );
    }

    {
        // Testing search.
        DAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };

        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

        // retrieve itens
        for ( const auto & e : table )
        {
            assert( dict.search( e.key, result ) );
            assert( result == e.data );
        }

        // serching for non-existing key.
        assert( dict.search( 6, result ) == false);

        // seaching in an empty dictionary.
        DAL<int, std::string> dict2;
        assert ( dict2.search( 1, result) == false );
    }

    {
        // Testing remove.
        DAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };


        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

        // Trying to remove a non-existing element.
        assert( false == dict.remove( 6 , result ) );

        // remove itens
        for ( const auto & e : table )
        {
            assert( dict.remove( e.key, result ) );
            assert( result == e.data );
        }

        // assert( dict.empty() );

        // seaching in an empty dictionary.
        DAL<int, std::string> dict2;
        assert ( false == dict2.remove( 1, result) );
    }
    
    {
        // Testing min/max.
        DAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };

        // Shuffle table
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle( std::begin( table ), std::end( table ), g);

        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

		// std::cout << "Dict.min()=" << dict.min() << std::endl;
		// std::cout << "Dict.max()=" << dict.max() << std::endl;
        assert( dict.min() == 1 );
        assert( dict.max() == 5 );

        // Trying to get min/max of a empty dictionary.
        DAL<int, std::string> dict2;
        auto worked( false );
        try {
            result = dict2.min();
        }
        catch ( std::out_of_range & e )
        {
            worked = true;
        }
        assert ( worked );
        worked =  false;
        try {
            result = dict2.max();
        }
        catch ( std::out_of_range & e )
        {
            worked = true;
        }
        assert ( worked );
    }

    {
        // Testing successor/predecessor
        DAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };

        // Shuffle table
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle( std::begin( table ), std::end( table ), g);

        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

        auto key ( dict.min() );
        int next_key(0);
        int i(1);
        while( dict.successor( key, next_key ) )
        {
            assert( key == i++ );
            // go to the next key.
            key = next_key;
        }
        assert( key == i );

        key = dict.max();
        next_key = 0;
        i = 5;
        while( dict.predecessor( key, next_key ) )
        {
            assert( key == i-- );
            // go to the next key.
            key = next_key;
        }
        assert( key == i );
    }


    {
        // Testing default constructor.
        DSAL<int, std::string, MyKeyComparator> dic;
        // assert( dic.capacity() == 50 );

        DSAL<int, std::string, MyKeyComparator> dic2(100);
        // assert( dic2.capacity() == 100 );
    }

    {
        // Testing insert.
        DSAL<int, std::string> dict(3);

        // testing the regular insert
        assert( dict.insert( 1, "AAA" ) );
        assert( dict.insert( 2, "BBB" ) );

        // dicting the insert failure for duplicate keys.
		// std::cout << dict << std::endl;
        assert( false == dict.insert( 2, "BBB" ) );

        // dicting the insert for overflow check.
        // assert( dict.insert( 3, "CCC" ) );
        // assert( dict.insert( 4, "DDD" ) == false );
    }

    {
        // Testing search.
        DSAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };


        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

        // retrieve itens
        for ( const auto & e : table )
        {
            assert( dict.search( e.key, result ) );
            assert( result == e.data );
        }

        // serching for non-existing key.
        assert( dict.search( 6, result ) == false);

        // seaching in an empty dictionary.
        DSAL<int, std::string> dict2;
        assert ( dict2.search( 1, result) == false );
    }

    {
        // Testing remove.
        DSAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };


        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

        // Trying to remove a non-existing element.
        assert( false == dict.remove( 6 , result ) );

        // remove itens
        for ( const auto & e : table )
        {
            assert( dict.remove( e.key, result ) );
            assert( result == e.data );
        }

        // assert( dict.empty() );

        // seaching in an empty dictionary.
        DSAL<int, std::string> dict2;
        assert ( false == dict2.remove( 1, result) );
    }
    
    {
        // Testing min/max.
        DSAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };

        // Shuffle table
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle( std::begin( table ), std::end( table ), g);

        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

		// std::cout << dict << std::endl;

        assert( dict.min() == 1 );
        assert( dict.max() == 5 );

        // Trying to get min/max of a empty dictionary.
        DSAL<int, std::string> dict2;
        auto worked( false );
        try {
            result = dict2.min();
        }
        catch ( std::out_of_range & e )
        {
            worked = true;
        }
        assert ( worked );
        worked =  false;
        try {
            result = dict2.max();
        }
        catch ( std::out_of_range & e )
        {
            worked = true;
        }
        assert ( worked );
    }

    {
        // Testing successor/predecessor
        DSAL<int, std::string> dict;
        std::string result;

        // The Data
        struct Entry
        {
            int key;
            std::string data;
        };

        Entry table[] =
        {
            { 1, "AAA" },
            { 2, "BBB" },
            { 3, "CCC" },
            { 4, "DDD" },
            { 5, "EEE" }
        };

        // Shuffle table
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle( std::begin( table ), std::end( table ), g);

        // insert all itens first.
        for ( const auto & e : table )
        {
            assert( dict.insert( e.key, e.data ) );
        }

        auto key { dict.min() };
        int next_key{0};
        int i{1};
        while( dict.successor( key, next_key ) )
        {
            assert( key == i++ );
            // go to the next key.
            key = next_key;
        }
        assert( key == i );

        key = dict.max();
        next_key = 0;
        i = 5;
        while( dict.predecessor( key, next_key ) )
        {
            assert( key == i-- );
            // go to the next key.
            key = next_key;
        }
        assert( key == i );
    }

    std::cout << ">>> Passed the unit tests successfully!\n";
    return EXIT_SUCCESS;
}
