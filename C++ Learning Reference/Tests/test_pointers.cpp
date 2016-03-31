#include "test_pointers.h"

int test_pointers() {

    struct Widget {
        int id;
        Widget(int i): id(i) {}
    };

    using Lehr::UniquePointer;

    UniquePointer<Widget> u_ptr;
    UniquePointer<Widget> u_ptr2;
    UniquePointer<Widget> u_ptr3;

    Widget* volunteer;
    Widget* volunteer2;
    Widget* volunteer3;
    {
        Widget stack_widget(10);
        volunteer = &stack_widget;
        {
            volunteer2 = new Widget(2);
            u_ptr3 = volunteer2;
            u_ptr2 = u_ptr3;
            u_ptr = u_ptr2;
            console_test(u_ptr2 == nullptr);
            console_test(u_ptr3 == nullptr);
            console_test(u_ptr->id, 2);
        }
        {
            volunteer3 = new Widget(3);
            u_ptr = nullptr;
            u_ptr = volunteer;
            u_ptr = volunteer3;
            u_ptr2 = volunteer;
            console_test(u_ptr2->id, 10);
            console_test(u_ptr->id, 3);
        }
        u_ptr2 = new Widget(-10);
    }

    console_test(u_ptr->id, 3);
    console_test(u_ptr2->id, -10);
    console_test(u_ptr3 == nullptr);

    cout << endl;
    return 0;
};
