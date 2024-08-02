#include <namespaceTest.h>

namespace NamespaceTest {
  Stepper stepper = Stepper(27, 14, 1, 0);

  void setupNamespaceTest() {
  }

  void rotate(double revs) {
    Serial.println("Stepping " + String(revs));
    stepper.stepRevs(revs);
  }
}