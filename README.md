# Plato.Constants

A light framework for constant definition.

## License

[LGPL-3.0-or-later](LICENSE.md)

## One constant

Constants are expressed in SI and CGS unit systems as `Quantity`s,
optionally with some description:

```cpp
struct Constant {
  Quantity si;
  Quantity cgs;
  const char* description;
};
```

A `Quantity` is a light structure made of a `value` (as a `double`) and `unit` (as a `string`).
It can be sliced as its value so that accessing a constant,
e.g. `LightYear` in namespace `Distance`, is straightforward:

```
const double ly = Distance::LightYear::si;
```

Conversions are not implemented; this could be added later through Boost.Units.

## A lot of constants

Constants can be registered, so that they are looked up by name, in a `ConstantRegister`,
which is a global constant singleton filled at compile time.
This provides run time access to constants, and a few short cuts, e.g.:

```cpp
const auto ly = ConstantRegister::at("Distance::LightYear");
const auto lyCsg = ConstantRegister::csg("Distance::LightYear");
```

## A CSV-like definition

A few macros are provided to ease constant declaration and act as an abstraction layer
(for example, this would ease the migration to Boost.Units):

```cpp
DEFINE_PLATO_CONSTANT(group, tag, siValue, siUnit, cgsValue, cgsUnit, desc)
```

generates a conforming `struct` named `tag` in namespace `Plato::group`.

Additionally:

```cpp
REGISTER_PLATO_CONSTANT(group, tag, siValue, siUnit, cgsValue, cgsUnit, desc)
```

registers the constant in the `ConstantRegister` as `group::tag`.

Last but not least, aliases can be defined with:

```cpp
ALIAS_PLATO_CONSTANT(group, tag, alias)
```

## Versioning in API

Function `std::string Constant::version()` is declared in the framework.
It should be defined in the user code, e.g.:

```cpp
std::string Constant::version() {
  return "1.0";
}
```

## Using the constants

To use the constants, include `constant_builder.h`,
and create and include some `constants.h` file contain made of the aforementioned macros.
An example such file is provided for reference.

You can also check the example program, `example.cpp` which is built and run as:

```sh
mkdir build ; cd build
cmake ..
make
./example
```

