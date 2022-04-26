#ifndef _PLATOCONSTANTS_CONSTANT_BUILDER_H
#define _PLATOCONSTANTS_CONSTANT_BUILDER_H

#include <map>
#include <string>

namespace Plato {

/**
 * @brief A value and unit.
 */
struct Quantity {

  /**
   * @brief The value.
   */
  double value;

  /**
   * @brief The unit.
   */
  const char* unit;

  /**
   * @brief Slice the quantity as its value.
   */
  operator double() const {
    return value;
  }
};

/**
 * @brief The record of a constant for the register.
 */
struct Constant {

  /**
   * @brief The SI quantity.
   */
  Quantity si;

  /**
   * @brief The CGS quantity.
   */
  Quantity cgs;

  /**
   * @brief The constant description.
   */
  const char* description = nullptr;

  /**
   * @brief The library version.
   */
  static std::string version();
};

/**
 * @brief Named-constant register.
 */
class ConstantRegister {
  template <typename T>
  friend class Register;

public:
  /**
   * @brief Get the record of a registered constant.
   */
  static const Constant& at(std::string tag) {
    return get()[tag];
  }

  /**
   * @brief Get the SI value of a registered constant.
   */
  static const Quantity& si(std::string tag) {
    return at(tag).si;
  }

  /**
   * @brief Get the CGS value of a registered constant.
   */
  static const Quantity& cgs(std::string tag) {
    return at(tag).cgs;
  }

  /**
   * @brief Get the description of a registered constant.
   */
  static const char* description(std::string tag) {
    return at(tag).description;
  }

  /**
   * @brief Constructor-based registration functor.
   * @details
   * Constants are registered through the constructor:
   * \code
   * static Constant::Register<MyConstant> mine;
   * \endcode
   */
  template <typename T>
  struct Register {
    /**
     * @brief Register a constant.
     */
    Register(std::string tag) {
      ConstantRegister::get().insert(tag, {T::si, T::cgs, T::description});
    }
  };

private:
  /**
   * @brief Get the singleton.
   */
  static ConstantRegister& get() {
    static ConstantRegister instance {};
    return instance;
  }

  /**
   * @brief Get the value with given name.
   */
  const Constant& operator[](std::string tag) const {
    try {
      return m_values.at(tag);
    } catch (const std::out_of_range& e) {
      auto message = std::string("No constant named: ") + tag + ".\n";
      message += "List of known constants: [";
      auto it = m_values.begin();
      message += it->first;
      for (++it; it != m_values.end(); ++it) {
        message += std::string(", ") + it->first;
      }
      message += "]";
      throw std::runtime_error(message);
    }
  }

  /**
   * @brief Insert a new constant.
   */
  void insert(std::string tag, const Constant& record) {
    m_values[tag] = record;
  }

  /**
   * @brief The registered constants.
   */
  std::map<std::string, Constant> m_values;
};

/**
 * @brief Define a constant.
 * @param group The group the constant belongs to, modeled as a namespace
 * @param tag The tag of the constant, modeled as struct
 * @param siValue The SI value
 * @param siUnit The SI unit
 * @param cgsValue The CGS value
 * @param cgsUnit The CGS unit
 * @param desc The description
 */
#define DEFINE_PLATO_CONSTANT(group, tag, siValue, siUnit, cgsValue, cgsUnit, desc) \
  namespace group { \
  struct tag { \
    static constexpr Quantity si = {siValue, #siUnit}; \
    static constexpr Quantity cgs = {cgsValue, #cgsUnit}; \
    static constexpr const char* description = #desc; \
  }; \
  }

/**
 * @brief Define and register a constant.
 */
#define REGISTER_PLATO_CONSTANT(group, tag, siValue, siUnit, cgsValue, cgsUnit, desc) \
  DEFINE_PLATO_CONSTANT(group, tag, siValue, siUnit, cgsValue, cgsUnit, desc) \
  static ConstantRegister::Register<group::tag> group##_##tag(#group "::" #tag);

/**
 * @brief Create an alias for a constant.
 */
#define ALIAS_PLATO_CONSTANT(group, tag, alias) \
  namespace group { \
  using alias = tag; \
  }

} // namespace Plato

#endif
