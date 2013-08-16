
#include <heapwrap>

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>

#define arraysiz( a ) ((sizeof (a)) / (sizeof *(a)))

typedef bool (*predicate_t)();

struct test_t {
    predicate_t			test;
    const char 		       *desc;
};

bool assume( bool truth, const char *claim )
{
    if ( ! truth )
	std::cout << "FAILED: " << claim << std::endl;
    return truth;
}

bool run( test_t *test, size_t count, const char *name )
{
    size_t failed = 0;
    for ( test_t *t = test; t < test + count; ++t ) {
	if ( (t->test)() )
	    continue;
	std::cout <<  "FAILED: " << t->desc << std::endl;
	++failed;
    }
    std::cout << std::setw( 3 ) << count - failed
	      << '/'
	      << std::left << std::setw( 3 ) << count
	      << std::fixed << std::setprecision( 2 ) << ( count - failed ) * 100.0 / count
	      << '%'
	      << std::resetiosflags( std::ios::floatfield )
	      << std::endl;
    return !failed;
}

bool
test_heapify()
{
    bool			success = true;
    int				h[] = { 1, 2, 3, 10, 5, 0, 4, 5, 6, 9, 8, 7, -1 };
    int				h1[arraysiz(h)];
    int				h2[arraysiz(h)];


    // Make a test heap using make_heap.  Our heap::max should be in the same order
    std::copy( h, h+arraysiz(h), h1 );
    std::vector<int>		hv( h1, h1 + arraysiz( h1 ));
    std::copy( hv.begin(), hv.end(), std::ostream_iterator<int>( std::cout, ", " )); std::cout << std::endl;
    std::make_heap( hv.begin(), hv.end() );

    {
	heap::max<int>		hmax( h1, arraysiz( h1 ));
	std::copy( h1, h1+arraysiz(h1), std::ostream_iterator<int>( std::cout, ", " )); std::cout << std::endl;
	success &= assume( std::equal( h1, h1+arraysiz( h1 ), hv.begin() ), 
			   "our heap is the same as std::make_heap" );
	
	hmax.sort();
	std::sort( hv.begin(), hv.end() );
	std::copy( hv.begin(), hv.end(), std::ostream_iterator<int>( std::cout, ", " )); std::cout << std::endl;
	success &= assume( std::equal( h1, h1+arraysiz( h1 ), hv.begin() ), 
			   "our heap::max sorts ascending" );
    }
    std::copy( h, h+arraysiz(h), h2 );
    {
	heap::min<int>		hmin( h2, arraysiz( h2 ));
	std::copy( h2, h2+arraysiz(h2), std::ostream_iterator<int>( std::cout, ", " )); std::cout << std::endl;

	hmin.sort();
	std::sort( hv.begin(), hv.end() );
	std::copy( hv.begin(), hv.end(), std::ostream_iterator<int>( std::cout, ", " )); std::cout << std::endl;
	success &= assume( std::equal( h2, h2+arraysiz( h2 ), hv.rbegin() ), 
			   "our heap::min sorts descending (in reverse)" );
    }

    return success; 
}

int
main( int argc, const char **argv )
{
    test_t			test[] = {
	{ test_heapify, 	"heap::*.heapification" },
    };
    run( test, arraysiz( test ), "heap tests" );
}
