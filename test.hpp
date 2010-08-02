#pragma once
#ifndef TEST_HPP_TVLGV63D
#define TEST_HPP_TVLGV63D

#include "print.hpp"
#include "stringref.hpp"
#include "type_conversion.hpp"

namespace ftl {
	class Test {
	public:
		enum TestStatus {
			STATUS_OK,
			STATUS_PENDING,
			STATUS_FAILED
		};
		
		template <typename Functor>
		static void test_suite(StringRef name, Functor func);
		
		template <typename Functor>
		static void test_case(StringRef name, Functor func);
		
		class Failed {
		public:
			Failed(StringRef reason) : _reason(reason) {}
			StringRef reason() const { return _reason; }
		private:
			String _reason;
		};
		
		class Pending {
			
		};
	};
	
	#define TEST_SUITE(NAME, BLOCK) Test::test_suite(NAME, []() BLOCK)
	#define TEST_CASE(NAME, BLOCK) Test::test_case(NAME, []() BLOCK)
	
	#define TEST_FAIL(DESCRIPTION) throw Test::Failed(DESCRIPTION);
	#define TEST(EXPR) { if (!(EXPR)) TEST_FAIL(#EXPR); }
	
	template <typename Functor>
	void Test::test_suite(StringRef name, Functor func) {
		print("SUITE: {0}\n", name);
		func();
	}
	
	template <typename Functor>
	void Test::test_case(StringRef name, Functor func) {
		int pad = 70 - name.length();
		TestStatus status = STATUS_OK;
		String failure_reason;
		
		try {
			func();
		}
		catch (const Failed& f) {
			status = STATUS_FAILED;
			failure_reason = f.reason();
		}
		catch (const Pending& p) {
			status = STATUS_PENDING;
		}
		#ifndef FTL_NO_EXCEPTIONS
		catch (const AssertException& a) {
			status = STATUS_FAILED;
			failure_reason = format("Assertion failed: {0}", a.what());
		}
		#endif
		catch (...) {
			status = STATUS_FAILED;
			failure_reason = "Unknown exception.";
		}
		
		StringRef status_text;
		switch (status) {
			case STATUS_OK: status_text = "OK"; break;
			case STATUS_FAILED: status_text = "FAILED"; break;
			case STATUS_PENDING: status_text = "PENDING"; break;
		}
		
		print("{0}{1}{2}\n", name, String(" ") * pad, status_text);
		if (status == STATUS_FAILED) print("Reason: {0}\n", failure_reason);
	}
}

#endif /* end of include guard: TEST_HPP_TVLGV63D */
