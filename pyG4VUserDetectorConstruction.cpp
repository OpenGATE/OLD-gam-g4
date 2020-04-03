
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

namespace py = pybind11;

// https://pybind11.readthedocs.io/en/stable/advanced/classes.html
// Needed helper class because of the pure virtual method
class PyG4VUserDetectorConstruction : public G4VUserDetectorConstruction {
public:
  /* Inherit the constructors */
  using G4VUserDetectorConstruction::G4VUserDetectorConstruction;

  /* Trampoline (need one for each virtual function) */
  G4VPhysicalVolume * Construct() override {
    std::cout << "I am in PyG4VUserDetectorConstruction::Construct" << std::endl;
    PYBIND11_OVERLOAD_PURE(G4VPhysicalVolume*, /* Return type */
                           G4VUserDetectorConstruction, /* Parent class */
                           Construct, /* Name of function in C++ (must match Python name) */
                           /* No argument here  */
                           );
  }
};


// main python wrapper
void init_G4VUserDetectorConstruction(py::module & m) {
  
  py::class_<G4VUserDetectorConstruction, PyG4VUserDetectorConstruction>(m, "G4VUserDetectorConstruction")

    .def(py::init_alias())
    .def("Construct", &G4VUserDetectorConstruction::Construct)//, py::return_value_policy::reference)

    /*
      .def("__del__",
      [](G4VUserDetectorConstruction * ) {
      std::cout << "py G4VUserDetectorConstruction destructor" << std::endl;
      })
    */
    ;
}
