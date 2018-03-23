/*
        tree in g++
        find_by_order(x) returns k-th iterator (0-indexed)
        order_of_key(x) returns the index whose value >= x
*/
using namespace __gnu_pbds;
template<typename T>
using myset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
