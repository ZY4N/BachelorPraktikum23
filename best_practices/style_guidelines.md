## General

- Identifiers are written in snake_case.
- The only exception are template parameter, those are written in PascalCase.
-  Use `#pragma once` Instead of explicit include guards.
- Only use `<>` in includes for the standard library and `""` for everything else.
- `using namespace` should only be used with small namespaces that you have full control over.

## clang-format

- Most of everything else is done by `clang-format`
- The provided `.clang-format` needs to be applied to every C++ file before pushing
- Since clang format is currently not working flawlessly in all cases it might to be disabled in special cases
	- `// clang-format off` and `// clang-format on`
	- The following rules only apply until they are fixed in the `.clang-format` file
- This includes wrongly over indented function blocks
```c++
const auto last = std::unique(  
                  m_bound_arguments.rbegin(),  
                  m_bound_arguments.rend(),  
                  [](const bound_argument& a, const bound_argument& b) { return a.flag_index == b.flag_index; }  
).base();
```

```c++
// clang-format off  
const auto last = std::unique(  
    m_bound_arguments.rbegin(),  
    m_bound_arguments.rend(),  
    [](const bound_argument& a, const bound_argument& b) { return a.flag_index == b.flag_index; }  
).base();  
// clang-format on
````

- Complex logical statements

```c++
return (short_name != no_short_flag and argument.length() == short_flag_prefix.length() + sizeof(short_name) and  
       argument.substr(0, short_flag_prefix.length()) == short_flag_prefix and  
       argument[short_flag_prefix.length()] == short_name) or  
    (argument.length() == long_flag_prefix.length() + long_name.length() and  
     argument.substr(0, long_flag_prefix.length()) == long_flag_prefix and  
     argument.substr(long_flag_prefix.length()) == long_name);
```

```c++
// clang-format off  
return (  
    short_name != no_short_flag and argument.length() == short_flag_prefix.length() + sizeof(short_name) and  
    argument.substr(0, short_flag_prefix.length()) == short_flag_prefix and  
    argument[short_flag_prefix.length()] == short_name  
) or (  
    argument.length() == long_flag_prefix.length() + long_name.length() and  
    argument.substr(0, long_flag_prefix.length()) == long_flag_prefix and  
    argument.substr(long_flag_prefix.length()) == long_name  
);  
// clang-format on
```

- Or other more complex constructs
```c++
const auto found_match = std::apply(  
    [&](const Flags&... flag_config) {  
       return (  
          (++flag_index,  
           is_bool_flag = std::is_same_v<typename Flags::type, bool>,  
           matches_flag<Flags>(flag_config.short_name, flag_config.long_name, argument)) or  
          ...  
       );  
    },  
    m_flags  
);
```

```c++
// clang-format off  
const auto found_match = std::apply(  
    [&](const Flags&... flag_config) {  
       return (  
          (  
             ++flag_index,  
              is_bool_flag = std::is_same_v<typename Flags::type, bool>,  
              matches_flag<Flags>(  
                flag_config.short_name,  
                flag_config.long_name,  
                argument  
             )  
          ) or ...  
       );  
    },  
    m_flags  
);  
// clang-format on
```

- The final decision over these cases are down to code reviews and not the individual programmer

