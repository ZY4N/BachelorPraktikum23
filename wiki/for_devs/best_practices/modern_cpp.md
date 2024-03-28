## auto

> C++ provides the keyword `auto` which allows for a type to be automatically deduced by the compiler.
> This allows programmers to omit complex type declarations in their code which reduces noise and
> therefore makes the code (usually) better readable.

Use `auto` when storing a returned value or referencing one.  
```c++
const auto it = values.begin();
for (const auto& value : values);
```
`auto` should also be used in variable declarations to make them more consistent with previous the case.

```c++
const auto my_arr = std::array{ 1, 2, 3 };
const auto my_str = std::string_view{ values.begin(), values.end() };
const auto my_str = "text"sv;
const auto my_char = '\n';
const auto my_int = 1;
const auto my_size = std::size_t{};
const auto my_float = 1.0f;
const auto my_double = 1.0;
const auto my_class = my_quite_exquisitely_sophisticated_class(values);
```
Just to prove the point, here the same code without `auto`:
```c++
const std::array<int, 3> my_arr{ 1, 2, 3 };
const std::string_view my_str{ values.begin(), values.end() };
const std::string_view my_str = "text";
const char my_char = '\n';
const int my_int = 1;
const std::size_t my_size = 0;
const float my_float = 1.0f;
const double my_double = 1.0;
const my_quite_exquisitely_sophisticated_class my_class(values);
```


## Range-based for loops

> C++ has range-based for loops that provide a simple interface for looping over ranges.
> For it to work, a range must simply provide a `begin()` and `end()` function that return iterators to the first element
> and one past the last element in the range. 
> This makes code better readable, faster to write and can prevent bugs with integer overflows and out of bounds accesses. 

Where possible don't write
```c++
for (std::size_t i{}; i != values.size(); ++i) {
	std::cout << values[i] << std::endl;
}
```
instead use:
```c++
for (const auto& value : values) {
	std::cout << value << std::endl;
}
```

This also holds true for iterating in reverse
```c++
// Since C++20
for (const auto& value : values | std::views::reverse) {
	std::cout << value << std::endl;
}
// In our case use tcb::span and reverse_iterators:
const auto reverse_values_view = tcb::span{ values.rbegin(), values.rend() };
for (const auto& value : reverse_values_view) {
	std::cout << value << std::endl;
}
```


## STL algorithms

> The C++ **S**tandard **T**emplate **L**ibrary provides implementations for most of your algorithm needs!
> Before writing the same code for the 100th time check if the standard library provides an implementation.
> This not only speeds up writing your code but can also prevent a *metric* ton of bugs and frustration.

When possible use an implementation provided by the STL over a writing the algorithm yourself.

Here is a small list of commonly use algorithms
- [std::sort](https://en.cppreference.com/w/cpp/algorithm/sort), [std::stable_sort](https://en.cppreference.com/w/cpp/algorithm/stable_sort) Sorts given range with complexity of O(N·log(N)) or O(N·log(N)²).
- [std::find](https://en.cppreference.com/w/cpp/algorithm/find) Performs linear search on given range for given value.
- [std::lower_bound](https://en.cppreference.com/w/cpp/algorithm/lower_bound), [std::upper_bound](https://en.cppreference.com/w/cpp/algorithm/upper_bound) Performs binary search on given range.
- [std::copy](https://en.cppreference.com/w/cpp/algorithm/copy), [std::copy_backward](https://en.cppreference.com/w/cpp/algorithm/copy_backward) Copies elements from one range to another.
- [std::move](https://en.cppreference.com/w/cpp/algorithm/move), [std::move_backward](https://en.cppreference.com/w/cpp/algorithm/move_backward) Moves elements from one range to another.
- [std::accumulate](https://en.cppreference.com/w/cpp/algorithm/accumulate) Computes sum of elements in a given range.
- [std::transform](https://en.cppreference.com/w/cpp/algorithm/transform) Applies functor to given range and stores result in output range.
- [std::fill](https://en.cppreference.com/w/cpp/algorithm/fill) Fills range with given value.
- [std::min_element](https://en.cppreference.com/w/cpp/algorithm/min_element), [std::max](https://en.cppreference.com/w/cpp/algorithm/max_element), [std::min_max](https://en.cppreference.com/w/cpp/algorithm/minmax_element) Finds min and/or max element of given elements.
- [std::reverse](https://en.cppreference.com/w/cpp/algorithm/reverse) Reverses given range.
- [std::swap](https://en.cppreference.com/w/cpp/algorithm/swap) Swaps contents of given elements.

> Note: **RTFM!** There is tons of [documentation](https://en.cppreference.com/) . Read it, before using the implementations.


## Lambda Functions

> C++ provides a syntax for creating unnamed function called "lambdas".
> These functions can store references to and values itself.
> In most cases lambas are inlined and will therefore not have a runtime overhead.

In most cases a lambda should be used over a named function when dealing with the STL API:
```c++
const auto last = std::unique(  
    m_bound_arguments.rbegin(),  
    m_bound_arguments.rend(),  
    [](const bound_argument& a, const bound_argument& b) {
	    return a.flag_index == b.flag_index;
	}  
);
```
But Lambdas can and should also be used to avoid code duplication in cases where handing all parameters over to an external function is not practical or the application is too specific to the use case:
```c++
const auto make_2D = [&begin_timestamp](
	const types::timed_velocity_t& timed_velocity
) -> Eigen::Vector2d {
	return {
		std::chrono::duration<double>(timed_velocity.timestamp - begin_timestamp).count(),
		timed_velocity.velocity
	};
};
const auto p0 = make_2D(velocity_it[outer_left]);
const auto p1 = make_2D(velocity_it[inner_left]);
const auto p2 = make_2D(velocity_it[inner_right]);
const auto p3 = make_2D(velocity_it[outer_right]);
```

```c++
const auto push_mesh = [&]() {
	// ...
};
while (std::getline(in, line)) {
	// ...
	if (/**/) {
		push_mesh();
	}
	// ...
}
push_mesh(); // Handle left over elements.
```


## const, constexpr

> Even though variables are mutable by default, in a surprising amount of cases an immutable variable would suffice.
> Marking variables `const` when possible will not only prevent you from overwriting values that you did not or should not want to modify,
> but also provides valuable information to the compiler for warnings and optimizations.
> Going one step further, the `constexpr` keywords marks variables and branches that can be evaluated at compile time.
> This allows one to shift calculations from runtime to compile time which can significantly improve the runtime.

Whenever possible mark a variable or reference `const`
```c++
const auto num_bytes = values.size() * sizeof(decltype(values)::value_type); // Only calculated once and after that unchanged. 
for (const auto& value : values) { // const since values are only read.
	std::cout << value << std::endl;
}
void print_value(const auto& value); // For printing the value does not need to modify.
const auto my_lambda = []() { std::cout << "hi\n"; }; // The lambdas are by default immutable.
const auto prev_size = values.size(); // Value is only used to 'remember' size.
```

Whenever possible mark variables and branches  `constexpr`
```c++
static constexpr auto two_pi = 2.0 * M_PI;

static constexpr auto first_bit = (1ull << (sizeof(std::size_t) * 8 - 1);

const auto print_value = [](const auto& value) {
	using type = std::remove_cvref_t<decltype(value)>;
	if constexpr (std::is_floating_v<type>) {
		std::cout << std::scientific << value;
	} else if (std::is_integral_v<type>) {
		std::cout << std::hex << value;
	} else {
		std::cout << value;
	}
	std::cout << std::endl;
}

```

## Move semantics

> By default assignments in C++ copy one object to another. Since in many cases you might just want to move
> values from one container to another, without creating an extra copy, move semantics are needed.

> Note: this topic is too complex to explain here, but very important, so read up on it!

Here a small checklist of things you should know about this topic:
- [ ] What are lvalues, rvalues and xvalues?
- [ ] What does `std::move` and `std::forward<T>` do?
- [ ] What is a move constructor and how can I implement one?
- [ ] What is a move assignment and how can I implement it?
- [ ] How can move semantics of containers like `std::vector` or `std::unique_ptr` help when implementing my own class?
- [ ] practice, practice, practice
