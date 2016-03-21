#ifndef CPPREF_TEST_COMMON_H
#define CPPREF_TEST_COMMON_H

#include "../Utilities/_std_symbols.h"

template <typename T, typename V>
void console_test(T a, V b) {
    if (a == b) {
        cout << ".";
    } else {
        cout << "\n" << a << " != " << b << endl;
    }
}
template void console_test<string, string>(string a, string b);
template void console_test<int, int>(int a, int b);
template void console_test<bool, bool>(bool a, bool b);
template void console_test<double, double>(double a, double b);

#endif //CPPREF_TEST_COMMON_H
