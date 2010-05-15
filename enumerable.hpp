#pragma once
#ifndef ENUMERABLE_HPP_6UZ88P0F
#define ENUMERABLE_HPP_6UZ88P0F

namespace ftl {
	template <typename SourceEnumerator, typename Functor> class SelectEnumerator;
	template <typename SourceEnumerator, typename Functor> class RejectEnumerator;
	template <typename SourceEnumerator, typename TargetType, typename Functor> class MapEnumerator;

	template <typename TargetClass, typename Enumerator = TargetClass>
	class Enumerable {
		/*
			XXX: When deriving from Enumerable, it must be the first parent class.
			This is because we want to avoid virtual functions, but Enumerable still needs
			to access get_enumerator() on the derived class, so it does an ugly static_cast(this).
		*/
	public:
		template <typename Functor>
		SelectEnumerator<Enumerator, Functor> select(Functor func) const;
		template <typename Functor>
		RejectEnumerator<Enumerator, Functor> reject(Functor func) const;

		template <typename TargetType, typename Functor>
		MapEnumerator<Enumerator, TargetType, Functor> map(Functor func) const;

		template <typename TargetType, typename Functor>
		TargetType inject(TargetType base, Functor func) const {
			TargetType result = base;
			Enumerator e = get_enumerator();
			while (e.move_next()) { result = func(result, e.current()); }
			return result;
		}

		template <typename Functor>
		Enumerator find(Functor func) const {
			Enumerator e = get_enumerator();
			while (e.move_next()) { if (func(e.current())) break; }
			return e;
		}

		template <typename Functor>
		void each(Functor func) const {
			Enumerator e = get_enumerator();
			while (e.move_next()) func(e.current());
		}

		template <typename Functor>
		void each_index(Functor func) const {
			Enumerator e = get_enumerator();
			size_t n = 0;
			while (e.move_next()) func(e.current(), n++);
		}

		size_t count_all() const {
			Enumerator e = get_enumerator();
			size_t n = 0;
			while (e.move_next()) ++n;
			return n;
		}

		template <typename Functor>
		size_t count(Functor func) const {
			Enumerator e = get_enumerator();
			size_t n = 0;
			while (e.move_next()) if (func(e.current())) ++n;
			return n;
		}

		template <typename Functor>
		bool any(Functor func) const {
			return count(func) > 0;
		}

		template <typename Functor>
		bool all(Functor func) const {
			return count(func) == count_all();
		}

	private:
		Enumerator get_enumerator() const { return static_cast<const TargetClass*>(this)->get_enumerator(); }
	};

	template <typename SourceEnumerator, typename Functor>
	class SelectEnumerator : public Enumerable<SelectEnumerator<SourceEnumerator, Functor>> {
	public:
		typedef typename SourceEnumerator::ValueType ValueType;

		SelectEnumerator(const SourceEnumerator& e, Functor func) : _enumerator(e), _func(func) {}
		SelectEnumerator(const SelectEnumerator& other) : _enumerator(other._enumerator), _func(other._func) {}

		bool move_next() { do { if (!_enumerator.move_next()) return false; } while (!_func(current())); return true; }
		ValueType current() const { return _enumerator.current(); }
		bool at_end() const { return _enumerator.at_end(); }
		const SelectEnumerator<SourceEnumerator,Functor>& get_enumerator() const { return *this; }
	private:
		Functor _func;
		SourceEnumerator _enumerator;
	};

	template <typename SourceEnumerator, typename Functor>
	class RejectEnumerator : public Enumerable<RejectEnumerator<SourceEnumerator, Functor>> {
	public:
		typedef typename SourceEnumerator::ValueType ValueType;

		RejectEnumerator(const SourceEnumerator& e, Functor func) : _enumerator(e), _func(func) {}
		RejectEnumerator(const RejectEnumerator& other) : _enumerator(other._enumerator), _func(other._func) {}

		bool move_next() { do { if (!_enumerator.move_next()) return false; } while (_func(current())); return true; }
		ValueType current() const { return _enumerator.current(); }
		bool at_end() const { return _enumerator.at_end(); }
		const RejectEnumerator<SourceEnumerator,Functor>& get_enumerator() const { return *this; }
	private:
		Functor _func;
		SourceEnumerator _enumerator;
	};

	template <typename SourceEnumerator, typename TargetType, typename Functor>
	class MapEnumerator : public Enumerable<MapEnumerator<SourceEnumerator, TargetType, Functor>> {
	public:
		typedef TargetType ValueType;
		MapEnumerator(const SourceEnumerator& e, Functor func) : _enumerator(e), _func(func) {}
		MapEnumerator(const MapEnumerator& other) : _enumerator(other._enumerator), _func(other._func) {}

		bool move_next() { return _enumerator.move_next(); }
		TargetType current() const { return _func(_enumerator.current()); }
		bool at_end() const { return _enumerator.at_end(); }
		const MapEnumerator<SourceEnumerator,TargetType,Functor>& get_enumerator() const { return *this; }
	private:
		Functor _func;
		SourceEnumerator _enumerator;
	};

	template <typename TargetClass, typename Enumerator>
	template <typename Functor>
	SelectEnumerator<Enumerator, Functor> Enumerable<TargetClass,Enumerator>::select(Functor func) const {
		return SelectEnumerator<Enumerator, Functor>(get_enumerator(), func);
	}

	template <typename TargetClass, typename Enumerator>
	template <typename Functor>
	RejectEnumerator<Enumerator, Functor> Enumerable<TargetClass,Enumerator>::reject(Functor func) const {
		return RejectEnumerator<Enumerator, Functor>(get_enumerator(), func);
	}

	template <typename TargetClass, typename Enumerator>
	template <typename TargetType, typename Functor>
	auto Enumerable<TargetClass,Enumerator>::map(Functor func) const -> MapEnumerator<Enumerator, TargetType, Functor> {
		return MapEnumerator<Enumerator, TargetType, Functor>(get_enumerator(), func);
	}
}

#endif /* end of include guard: ENUMERABLE_HPP_6UZ88P0F */
