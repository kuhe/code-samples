### Learning Reference (GCC C++11)

====

The poor man's Computer Science revue (a.k.a. JavaScript developer tries to learn C++), learning bits, hashes, maps, vectors, pointers, in the context of algorithms.

Also adding learner's implementations of common data structures under the Lehr namespace.


todo:

    harden (hash) sets
    more specialty graphs


### Code Style Notes

I'll try to follow these guidelines:
- namespace Lehr for my implementations
- types as title case, methods/variables with underscores
- constant inputs (?)
- for data structures, use pointers
- for applications, use references
- Limit OO terms in type names (e.g. List instead of IList or ListInterface or AbstractList)
- member order: public, protected, private

````
namespace Lehr {
    class MyCoolClass {
        int my_cool_method(const int& input);
    }
}
````
