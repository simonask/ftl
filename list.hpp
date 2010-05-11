#pragma once
#ifndef LIST_HPP_4CWWVYPW
#define LIST_HPP_4CWWVYPW

#include "enumerable.hpp"
#include "utils.hpp"

namespace ftl {
	template <typename T> class List<T>;
	template <typename T> class List<T>::Enumerator;
	
	template <typename T>
	class List : public Enumerable<List<T>, List<T>::Enumerator> {
	private:
		struct Node {
			Node* _next;
			Node* _prev;
			T _x;
		};
	public:
		friend class List<T>::Enumerator;
		
		List();
		List(const List<T>& other);
		~List();
		
		size_t size() const { return _size; }
		void clear();
		void fill(size_t new_size, const T& element = T());
		
		T& push(const T& element);
		T& push();
		void pop();
		// TODO: erase
		
		T& first();
		const T& first() const;
		T& last();
		const T& last() const;
		
		class Enumerator {
		public:
			friend class List<T>;
			typedef T ValueType;
			Enumerator(const Enumerator& other) : _node(other._node) {}
			bool at_end() const { return _node == NULL; }
			bool move_next() { _node = _node->next; return _node != NULL; }
			const T& current() const { return _node->_x; }
			const Enumerator& get_enumerator() const { return *this; }
		private:
			Enumerator(Node* node) : _node(node) {}
			const Node* _node;
		};
		
		Enumerator get_enumerator() const { return Enumerator(reinterpret_cast<Node*>(&_before_head)); }
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
}

#endif /* end of include guard: LIST_HPP_4CWWVYPW */
