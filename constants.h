#ifndef _PLATOCONSTANTS_CONSTANTS_H
#define _PLATOCONSTANTS_CONSTANTS_H

#include "constant_builder.h"

namespace Plato {

std::string Constant::version() {
  return "1.0";
}

REGISTER_PLATO_CONSTANT(
    Distance, // Group
    LightYear, // Name
    92276118600000, // SI value
    m, // SI unit
    9227611860000000, // CGS value
    cm, // CGS unit
    The distance that light travels in one year) // Description

REGISTER_PLATO_CONSTANT(Fundamental, Planck, 6.62607015e-34, J.s, 6.62607015e-27, erg.s, The Planck constant)
ALIAS_PLATO_CONSTANT(Fundamental, Planck, h)

REGISTER_PLATO_CONSTANT(Fundamental, ElectronMass, 9.1093837e-31, kg, 9.1093837e-28, g, The mass of the electron)

} // namespace Plato

#endif
