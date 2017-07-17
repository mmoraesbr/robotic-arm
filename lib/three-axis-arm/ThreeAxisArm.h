#ifndef ThreeAxisArm_H
#define ThreeAxisArm_H

class ThreeAxisArm
{
public:

  ThreeAxisArm();
  ~ThreeAxisArm();
  void start(byte xPin, byte yPin, byte zPin, byte cPin);

};

#endif
