#ifndef AUNIT_ASSERTION_H
#define AUNIT_ASSERTION_H

#include "Printer.h"
#include "Verbosity.h"
#include "TestRunner.h"

// Various assertXxx() macros, implemented using the assertOp() macro.

#define assertEqual(arg1,arg2) assertOp(arg1,aunit::compareEqual,"==",arg2)

#define assertNotEqual(arg1,arg2) \
    assertOp(arg1,aunit::compareNotEqual,"!=",arg2)

#define assertLess(arg1,arg2) assertOp(arg1,aunit::compareLess,"<",arg2)

#define assertMore(arg1,arg2) assertOp(arg1,aunit::compareMore,">",arg2)

#define assertLessOrEqual(arg1,arg2) \
    assertOp(arg1,aunit::compareLessOrEqual,"<=",arg2)

#define assertMoreOrEqual(arg1,arg2) \
    assertOp(arg1,aunit::compareMoreOrEqual,">=",arg2)

#define assertTrue(arg) assertEqual(arg,true)

#define assertFalse(arg) assertEqual(arg,false)

#define assertOp(arg1,op,opName,arg2) do {\
  if (!aunit::assertion(__FILE__,__LINE__,(arg1),opName,op,(arg2)))\
    return;\
} while (false)

namespace aunit {

// This can be a template function because it is accessed only through the
// various assertXxx() methods. Those assertXxx() methods are explicitly
// overloaded for the various types that we want to support.
//
// Prints something like the following:
// Assertion failed: (5) == (6), file Test.ino line 820.
// Assertion passed: (6) == (6), file Test.ino line 820.
template <typename A, typename B>
void printAssertionMessage(bool ok, const char* file, uint16_t line,
    const A& lhs, const char *opName, const B& rhs) {

  bool isOutput =
      (ok && TestRunner::isVerbosity(Verbosity::kAssertionPassed)) ||
      (!ok && TestRunner::isVerbosity(Verbosity::kAssertionFailed));
  if (!isOutput) return;

  // Don't use F() strings here because flash memory strings are not deduped by
  // the compiler, so each template instantiation of this method causes a
  // duplication of all the strings below. See
  // https://github.com/mmurdoch/arduinounit/issues/70
  // for more info.
  Printer::getPrinter()->print("Assertion ");
  Printer::getPrinter()->print(ok ? "passed" : "failed");
  Printer::getPrinter()->print(": (");
  Printer::getPrinter()->print(lhs);
  Printer::getPrinter()->print(") ");
  Printer::getPrinter()->print(opName);
  Printer::getPrinter()->print(" (");
  Printer::getPrinter()->print(rhs);
  Printer::getPrinter()->print("), file ");
  Printer::getPrinter()->print(file);
  Printer::getPrinter()->print(", line ");
  Printer::getPrinter()->print(line);
  Printer::getPrinter()->println('.');
}

// For the same reason as the compareXxx() methods, we use explicit overloaded
// functions, instead of using template specialization. And just as before, I
// was unable to use a template function for primitive integer types, because it
// interfered with the resolution of assertion(char*, char*). The wrong function
// would be called.

bool assertion(const char* file, uint16_t line, bool lhs,
    const char* opName, bool (*op)(bool lhs, bool rhs),
    bool rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, char lhs,
    const char* opName, bool (*op)(char lhs, char rhs),
    char rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, int lhs,
    const char* opName, bool (*op)(int lhs, int rhs),
    int rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, unsigned int lhs,
    const char* opName, bool (*op)(unsigned int lhs, unsigned int rhs),
    unsigned int rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, long lhs,
    const char* opName, bool (*op)(long lhs, long rhs),
    long rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, unsigned long lhs,
    const char* opName, bool (*op)(unsigned long lhs, unsigned long rhs),
    unsigned long rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, double lhs,
    const char* opName, bool (*op)(double lhs, double rhs),
    double rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const char* lhs,
    const char* opName, bool (*op)(const char* lhs, const char* rhs),
    const char* rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const char* lhs,
    const char *opName, bool (*op)(const char* lhs, const String& rhs),
    const String& rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const char* lhs,
    const char *opName,
    bool (*op)(const char* lhs, const __FlashStringHelper* rhs),
    const __FlashStringHelper* rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const String& lhs,
    const char *opName, bool (*op)(const String& lhs, const char* rhs),
    const char* rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const String& lhs,
    const char *opName, bool (*op)(const String& lhs, const String& rhs),
    const String& rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const String& lhs,
    const char *opName,
    bool (*op)(const String& lhs, const __FlashStringHelper* rhs),
    const __FlashStringHelper* rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const __FlashStringHelper* lhs,
    const char *opName,
    bool (*op)(const __FlashStringHelper* lhs, const char* rhs),
    const char* rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const __FlashStringHelper* lhs,
    const char *opName,
    bool (*op)(const __FlashStringHelper* lhs, const String& rhs),
    const String& rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

bool assertion(const char* file, uint16_t line, const __FlashStringHelper* lhs,
    const char *opName,
    bool (*op)(const __FlashStringHelper* lhs, const __FlashStringHelper* rhs),
    const __FlashStringHelper* rhs) {
  bool ok = op(lhs, rhs);
  printAssertionMessage(ok, file, line, lhs, opName, rhs);
  TestRunner::setPassOrFail(ok);
  return ok;
}

}
#endif
