#pragma once
#ifndef APPENDBUFFER_HPP_X9077YRG
#define APPENDBUFFER_HPP_X9077YRG

#include "maxarray.hpp"
#include "list.hpp"
#include "enumerable.hpp"

namespace ftl {
	template <typename T, size_t PageSize> class AppendBuffer;
	template <typename T, size_t PageSize> class AppendBufferEnumerator;
	
	template <typename T, size_t PageSize = 1024>
	class AppendBuffer : Enumerable<AppendBuffer<T, PageSize>, AppendBufferEnumerator<T, PageSize>> {
	public:
		typedef AppendBufferEnumerator<T,PageSize> Enumerator;
		typedef MaxArray<T, PageSize> Page;
		AppendBuffer() {}
		AppendBuffer(const AppendBuffer& other) : _pages(other._pages) {}
		
		T& push() { return current_page().push(); }
		T& push(const T& x) { return current_page().push(x); }
		AppendBuffer<T,PageSize>& operator<<(const T& x) { push(x); return *this; }
		void clear() { _pages.clear(); }
		size_t size() const;
		

		friend class AppendBufferEnumerator<T,PageSize>;
		Enumerator get_enumerator() const { return Enumerator(_pages); }
	protected:
		Page& current_page();
		List<Page> _pages;
	};
	
	template <typename T, size_t PS>
	inline size_t AppendBuffer<T,PS>::size() const {
		return _pages.size() ? ((_pages.size()-1) * PS + _pages.last().size()) : 0;
	}
	
	template <typename T, size_t PS>
	inline typename AppendBuffer<T,PS>::Page& AppendBuffer<T,PS>::current_page() {
		if (!_pages.size()) {
			_pages.push();
		}
		return _pages.last();
	}
	
	template <typename T, size_t PS>
	class AppendBufferEnumerator {
	public:
		typedef typename AppendBuffer<T,PS>::Page Page;
		AppendBufferEnumerator(const AppendBufferEnumerator<T,PS>& other) : _list_e(other._list_e), _page_e(other._page_e), _page_e_init(other._page_e_init) {}
		bool at_end() const;
		bool move_next();
		const T& current() const { return _page_e.current(); }
		const AppendBufferEnumerator<T,PS>& get_enumerator() const { return *this; }
	private:
		friend class AppendBuffer<T,PS>;
		AppendBufferEnumerator(const List<Page>& page_list);
		typename List<Page>::Enumerator _list_e;
		typename Page::Enumerator _page_e;
		bool _page_e_init;
		bool move_next_page();
	};
	
	template <typename T, size_t PS>
	inline AppendBufferEnumerator<T,PS>::AppendBufferEnumerator(const List<Page>& page_list) : _page_e_init(false) {
		_list_e = page_list.get_enumerator();
	}
	
	template <typename T, size_t PS>
	inline bool AppendBufferEnumerator<T,PS>::at_end() const {
		return _list_e.at_end();
	}
	
	template <typename T, size_t PS>
	inline bool AppendBufferEnumerator<T,PS>::move_next() {
		if (!_list_e.at_end()) {
			if (!_page_e_init) {
				_page_e_init = true;
				return move_next_page();
			}
			
			if (_page_e.move_next())
				return true;
			else
				return move_next_page();
		}
		return false;
	}
	
	template <typename T, size_t PS>
	inline bool AppendBufferEnumerator<T,PS>::move_next_page() {
		if (_list_e.move_next()) {
			_page_e = _list_e.current().get_enumerator();
			return _page_e.move_next();
		}
		return false;
	}
}

#endif /* end of include guard: APPENDBUFFER_HPP_X9077YRG */
