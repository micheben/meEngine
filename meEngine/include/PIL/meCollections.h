#pragma once

#include <vector>
#include <list>
#include <tuple>

namespace meEngine
{
	template <typename _Ty, typename _Alloc = allocator<_Ty> >
	using meVector = std::vector<_Ty, _Alloc>;

	template <typename _Ty, typename _Alloc = allocator<_Ty> >
	using meDoubleLinkedList = std::list<_Ty, _Alloc>;

}