### Learning Reference (GCC C++11)

====

The poor man's Computer Science revue, learning bits, hashes, maps, vectors, pointers, in the context of basic algorithms and data structures.

Also adding learner's implementations of common data structures under the Lehr namespace.


todo:

    harden (hash) sets
    add a TreeSet implementation
    more specialty graphs
    add standard iterator compatibility? (is that even possible?)
    see 23.2 Container Requirements, refactor to meet requirements


### Code Style Notes

I'll try, unsuccessfully, to follow these guidelines:
- namespace Lehr for my implementations
- types as title case, methods/variables with underscores
- constant input references? (yeah, right...)
- restrict pointer usage outside of data structure implementations
- Limit OO terms in type names (e.g. List instead of IList or ListInterface or AbstractList)
- member order: public, protected, private

````
namespace Lehr {
    class MyCoolClass {
    public:
        int my_cool_method(const int& input);
    protected:
        bool blah;
    }
}
````
