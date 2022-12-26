#pragma once

class NonCopyable {
protected:
        NonCopyable() {}
        virtual ~NonCopyable() {}

private:
        NonCopyable(const NonCopyable&);
        NonCopyable& operator =(const NonCopyable&);
};
