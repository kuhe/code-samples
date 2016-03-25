#include "test_rule_of_X.h"


void test_rule_of_X() {
    using rule_of_X::Q;

    Q q1;
    Q q2((int)q1);
    Q q3 = q2;
    Q q4 = std::move(q3);
    Q q5;
    q5 = q4;
    Q q6;
    q6 = 5 + (int) q5;

    console_test(q1.state, Q::ctor);
    console_test(q2.state, Q::ctor_param);
    console_test(q3.state, Q::ctor_copy);
    console_test(q4.state, Q::ctor_move);
    console_test(q5.state, Q::assign_copy);
    console_test(q6.state, Q::assign_move);
    console_test(q6.state, Q::assign_move);

    // X is apparently 5 or 6

}