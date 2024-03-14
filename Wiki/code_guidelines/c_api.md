# C API

**TL;DR**: use modern C++ features and the STL instead of the old C API.

## Heap Allocation

> Manually allocating memory on the heap is not in itself a bad practice but since the STL provides
> so many helpful wrappers for this functionality that can speed up production, reduce bugs and even lead to performance increases,
> due to clever allocation strategies, it should only be used when all other options have been exhausted.

Direct memory allocation should be avoided if possible
```c++
malloc(), free() // Never!
new, delete      // Only in special cases.
```
and replaced with std containers like
```c++
std::vector, std::string
```
or smart pointers:
```c++
std::unique_ptr, std::shared_ptr, std::weak_ptr
```


## Stack Allocation

> C-Style arrays do not provide a size function and do not have a copy constructor.
> This can lead to numerous bugs and in general issues with the C++ type system.

C-Style arrays like
```c++
char my_str[12];
```
should be replaced with the C++ equivalent:
```c++
std::array<char,12> my_str{}
```


## Strings

> Null terminated strings, stored in a raw pointer combine two of the most unsafe C constructs into one ticking time bomb.
> From buffer overflows, segmentation faults to memory leaks, this construct can lead to more issues than it's simplicity is worth.
> Don't use it unless your really, really have to.

Storing strings as null terminated char pointers like this
```c++
const char* str = get_str();
```
is forbidden and should always be replaced with the appropriate std container:
```c++
std::string // for dynamic strings
std::string_view // for constant string references
std::filesystem::path // for paths and filenames
```


## Casts

> C-style casts give no hint as to the intent behind the conversion. This not only makes understanding the code more difficult
> but also provides the compiler with less information for warnings and errors.

C-Style casts like
```c++
const auto integer = (int)1.0f;
const auto& child = *(const child_class_t*)&super_class;
```
should be replaced with the respective casting operator:
```c++
const auto integer = static_cast<int>(1.0f);
const auto& child = reinterpret_cast<const child_class_t&>(super_class);
```

> Note: `const_cast` was omitted in this description as it's use and that of it's C style equivalent is usually forbidden. 


## C Functions

> Functions provided by the C API cannot use the C++ template system. This often results in the user having to provide the necessary information manually. That process is highly error-prone and representative of a common theme in the C API:
> most functions are not written with safe defaults in mind, meaning a small moment of inattention can lead to major bugs. 

All functions provided by the cstdlib that can be replaced with an STL counterpart have to be replaced.
Prominent examples of this are:
```c++
memcpy -> std::copy
memset -> std::fill
printf -> std::cout // or in our case the logger api
sin, log -> std::sin, std::log
```


## Pointers

> Besides adding a lot of visual noise to the code, pointers are inherently dangerous
> as they can point to invalid memory, while references cannot. 
> Since references however, cannot be reassigned, pointers may be needed in certain cases.

Where possible the use of raw pointers like in this example
```c++
template<typename T>
void swap(T* a, T* b) {
	T tmp = std::move(*a);
	*a = std::move(*b);
	*b = std::move(tmp);
}
```
should be replaced with references:
```c++
template<typename T>
void swap(T& a, T& b) {
	T tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);
}
```


## Logical operators

> Even though programmers are used to reading  `!`, `&&` and `||` like `not`, `and` and `or`,
> writing these operators out can make it a lot easier to comprehend complex logical statements.

For logical expressions replace
```c++
!, &&, ||
```
with the C++ provided written out operator names:
```c++
not, and, or
```

## Macros

> C provides an API which leverages the precompiler to copy and paste code based on user defined "Macros".
> These macros are limited to basic text editing and can quickly lead to unwanted results.
> In C++ this system can mostly be replaced with [templates](https://en.cppreference.com/w/cpp/language/templates) . Templates are part of the type system itself and give the compiler more context
> to understand and warn about issues.

Only resort to macros if templates and other modern compile time constructs do not work. 
(This essentially means never)
```c++
// C
#define max(a, b) ((a) > (b) ? (a) : (b))

// C++
template<class T>
const T& min(const T& a, const T& b) {
    return (b < a) ? b : a;
}
```
