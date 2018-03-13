#ifndef AUNIT_FSTRING_H
#define AUNIT_FSTRING_H

namespace aunit {

/**
 * A union of (const char*) and (const __FlashStringHelper*) with a
 * discriminator. This allows us to treat these 2 strings like a single object.
 * The major reason this class is needed is because the F() cannot be used
 * outside a function, it can only be used inside a function, so we are forced
 * to use normal c-strings instead of F() strings when manually creating Test or
 * TestOnce instances.
 */
class FCString {
  public:
    static const uint8_t kCStringType = 0;
    static const uint8_t kFStringType = 1;

    explicit FCString(const char* s):
        mStringType(kCStringType) {
      mString.cstring = s;
    }

    explicit FCString(const __FlashStringHelper* s):
        mStringType(kFStringType) {
      mString.fstring = s;
    }

    uint8_t getType() const { return mStringType; }

    const char* getCString() const { return mString.cstring; }

    const __FlashStringHelper* getFString() const { return mString.fstring; }
  
  private:
    union {
      const char* cstring;
      const __FlashStringHelper* fstring;
    } mString;

    const uint8_t mStringType;
};

}

#endif
