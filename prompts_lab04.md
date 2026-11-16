# AI assistance notes — Lab4

Lab4 extends CyberDefense from Lab3 to demonstrate the C++ Standard Library.

The implementation uses `std::deque` for the game path, towers, and enemies, and `std::array` for the fixed-size render grid. It uses `std::string` and the stream operators from Lab3 for text input and output. STL algorithms demonstrate searching (`std::find`, `std::any_of`), sorting (`std::stable_sort`), comparison (`std::equal`, `std::lexicographical_compare`), copying (`std::copy_if`), and filling (`std::fill`). Enemy selection uses a container iterator, and the engine holds a renderer reference rather than allocating a renderer dynamically.

The work was built with CMake and checked with the existing test target.
