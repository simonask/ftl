#pragma once
#ifndef LIST_HPP_4CWWVYPW
#define LIST_HPP_4CWWVYPW

#include "enumerable.hpp"
#include "utils.hpp"

namespace ftl {
	template <typename T> class List;
	template <typename T> class ListEnumerator;
	
	template <typename T>
	class List : public Enumerable<List<T>, ListEnumerator<T>> {
	private:
		struct Node {
			Node* _next;
			Node* _prev;
			T _x;
			Node(const T& x) : _x(x) {}
		};
	public:
		friend class ListEnumerator<T>;
		typedef ListEnumerator<T> Enumerator;
		
		List();
		List(const List<T>& other);
		~List();
		List<T>& operator=(const List<T>& other);
		
		size_t size() const { return _size; }
		void clear();
		void fill(size_t new_size, const T& element = T());
		
		T& push(const T& element = T());
		void pop();
		// TODO: erase
		
		T& first() { FTL_ASSERT(_head); return _head->_x; }
		const T& first() const { FTL_ASSERT(_head); return _head->_x; }
		T& last() { FTL_ASSERT(_tail); return _tail->_x; }
		const T& last() const { FTL_ASSERT(_tail); return _tail->_x; }
		
		Enumerator get_enumerator() const { return Enumerator(reinterpret_cast<const Node*>(&_before_head)); }
	private:
		union {
			struct {
				Node* _head;
				Node* _tail;
			};
			struct {
				Node* _head;
				Node* _tail;
			} _before_head;
		};

		size_t _size;
	};
	
	template <typename T>
	class ListEnumerator {
	public:
		friend class List<T>;
		typedef T ValueType;
		ListEnumerator(const ListEnumerator<T>& other) : _node(other._node) {}
		bool at_end() const { return _node == NULL; }
		bool move_next() { _node = _node->_next; return _node != NULL; }
		const T& current() const { return _node->_x; }
		const ListEnumerator<T>& get_enumerator() const { return *this; }
	private:
		ListEnumerator(const typename List<T>::Node* node) : _node(node) {}
		const typename List<T>::Node* _node;
	};
	
	template <typename T>
	List<T>::List() {
		_head = NULL;
		_tail = NULL;
		_size = 0;
	}
	
	template <typename T>
	List<T>::List(const List<T>& other) {
		_head = NULL;
		_tail = NULL;
		_size = 0;
		*this = other;
	}
	
	template <typename T>
	List<T>::~List() {
		clear();
	}
	
	template <typename T>
	List<T>& List<T>::operator=(const List<T>& other) {
		other.each([&](const T& x) { push(x); });
	}
	
	template <typename T>
	void List<T>::clear() {
		Node* n = _head;
		while (n) {
			Node* next = n->_next;
			delete n;
			n = next;
		}
		_size = 0;
		_head = NULL;
		_tail = NULL;
	}
	
	template <typename T>
	void List<T>::fill(size_t n, const T& x) {
		for (size_t i = _size; _size < n; ++n) {
			push(x);
		}
	}
	
	template <typename T>
	T& List<T>::push(const T& x) {
		Node* n = new Node(x);
		n->_next = NULL;
		n->_prev = _tail;
		_tail = n;
		if (n->_prev) n->_prev->_next = n;
		if (!_head) _head = n;
		++_size;
		return n->_x;
	}
	
	template <typename T>
	void List<T>::pop() {
		FTL_ASSERT(_size);
		//erase(end()-1);
	}
}

#endif /* end of include guard: LIST_HPP_4CWWVYPW */
