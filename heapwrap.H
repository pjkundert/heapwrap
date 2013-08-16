#ifndef _INCLUDE_HEAPWRAP_H
#define _INCLUDE_HEAPWRAP_H 1

#include <cstring>
#include <algorithm>
#include <functional>

// 
// heap			-- min/max heaps, useful for priority queues and sorting
// 
//     When provided with a pre-allocated heap of data, will heap-ify it into
// the specified min- or max-heap.  If the heap size is greater than the current
// length (or 'dynamic' allocation is indicated, allowing heap re-allocation),
// insertion will be allowed.
// 
// NOTE: with 0-based arrays, children are i*2+1 and i*2+2.
// 
namespace heap {

    // 
    // heap::base	-- generic heap functionality; applies to both min/max heaps
    // 
    template <
	typename T,
	typename P,
	typename S = size_t >
    class base {
    public:
	typedef S		index_type;
	typedef T		value_type;

    protected:
	T		       *_arr;		// The heap array
	S			_end;		// end of the heap w/in elemennts
	S			_len;		// number of elements in use
	S			_siz;		// maximum element capacity (_siz-_len unused )
	P			_cmp;

    public:

	// heap::base()		-- Remembers the provided array, and turns it into a heap
				base(
				    value_type	       *array,
				    index_type		length,
				    index_type		size	= 0 ) // same as length
				    : _arr( array )
				    , _end( 0 )
				    , _len( length )
				    , _siz( size ? size : length )
				    , _cmp( P() )
	{
	    heapify();
	}

	index_type		left(
				    const index_type   &i )
	    const
	{ return i*2+1; }

	index_type		right(
				    const index_type   &i )
	    const
	{ return i*2+2; }

	index_type		parent(
				    const index_type   &i )
	    const
	{ return (i-1)/2; }

	// 
	// heap::base::heapify -- convert an array into a heap (w/ given comparo)
	// 
	//    Working up from the bottom, sift each parent down into its (already heaped) children.
	// Assumes that the heap is not 
	void			heapify()
	{
	    // start with the last parent node in array.  The O'th element's l=1, r=2, the 3'rds
	    // l=7, r=8.  The n'th l=n*2+1, r=n*2+2:  So, 
	    // 
	    //               last valid slot
	    //  0 1 2 3      | _len
	    //  v v v v      v v
	    // | | | | | ...| |
	    // 
	    _end			= _len;
	    if ( _len <= 1 )
		return;
	    index_type		start	= 0;
	    if ( _len > 1 )
		start			= ( _len - 2 ) / 2;
	    sift_down( start );
	    while ( start > 0 )
		sift_down( --start );
	}

	void			sift_down(
				    S			start )
	{
	    index_type		root	= start;
	    index_type		child;
	    while (( child 
		     = left( root ))
		   < _end ) {
		index_type	swap	= root;
		if ( _cmp( _arr[swap], _arr[child] ))
		    swap		= child;
		child			= right( root );
	        if ( child < _end && _cmp( _arr[swap], _arr[child] ))
		    swap		= child;
		if ( swap != root ) {
		    std::swap( _arr[root], _arr[swap] );
		    root		= swap;
		} else
		    break;
	    }
	}

	// 
	// heap::base::sort	-- convert a heap into a sorted array
	// 
	//     The greatest (or inverse of _cmp, if not std::less<T>) element is
	// at the front of the heap denoted by _end.    If we have more than
	// one element remaining
	inline
	void			sort()
	{
	    while ( _end > 1 ) {
		std::swap( _arr[0], _arr[--_end] );
		sift_down( 0 );
	    }
	}
    };

    // heap::max
    template <
	typename T,
	typename P = std::less<T>,
	typename S = size_t >
    class max
	: public base<T,P,S>
    {
    public:
	typedef typename base<T,P,S>::value_type value_type;
	typedef typename base<T,P,S>::index_type index_type;
				max(
				    value_type	       *array,
				    index_type		length,
				    index_type		size	= 0 ) // same as length
				    : base<T,P,S>( array, length, size )
	{
	    ;
	}
    };

    // heap::min
    template <
	typename T,
	typename P = std::greater<T>,
	typename S = size_t >
    class min
	: public base<T,P,S>
    {
    public:
	typedef typename base<T,P,S>::value_type value_type;
	typedef typename base<T,P,S>::index_type index_type;
				min(
				    value_type	       *array,
				    index_type		length,
				    index_type		size	= 0 ) // same as length
				    : base<T,P,S>( array, length, size )
	{
	    ;
	}
    };

}

#endif // _INCLUDE_HEAP_H
