// TODO
#ifndef OBJECTS_CAMERA_H_
#define OBJECTS_CAMERA_H_

#include "config.h"
#include "vector.h"
#include "context.h"

namespace objects {

class Camera {
 public:
  // Default constructor places the camera at (0, 0, -5) facing down along the
  // positive z-axis.
  Camera()
      : position_(0.0, 0.0, -5.0), 
        orientation_(Matrix::Identity()) {
    speed_ = 5.0;
    sensitivity_ = 1.0;
    inverted_ = -1.0;
  }

  // Advances the camera depending on which keys are currently pressed.
  void Step(const TimingContext &timing, const InputContext &input) {
    Vector dz = orientation_.Column(2) * speed_ * timing.dt;
    Vector dx = orientation_.Column(0) * speed_ * timing.dt;
    if (input.keyDown['s']) position_ -= dz;
    if (input.keyDown['w']) position_ += dz;
    if (input.keyDown['d']) position_ -= dx;
    if (input.keyDown['a']) position_ += dx;
  }

  // Reorients the camera depending on the mouse movement.
  void MouseMotion(const InputContext &input) {
    float db = input.dx(0) * isize_ * M_PI/2.0 * sensitivity_;
    float da = input.dx(1) * isize_ * M_PI/2.0 * sensitivity_ * inverted_;
    angles_ += Vector(da, db, 0);
    orientation_ = Matrix::Rotation(angles_(0), angles_(1), angles_(2));
  }

  // Needs to be called when the aspect ratio of the camera changes.
  void Reshape(int w, int h) {
    isize_ = 1.0 / std::min(w, h);
  }

  // Returns the position of the camera.
  Vector position() { return position_; }

  // Returns the vector in which the camera is facing.
  Vector at() { return position_ + orientation_.Column(2); }

  // Returns a vector describing the up direction of the camera.
  Vector up() { return orientation_.Column(1); }


 private:
  Vector position_;       // Current camera position
  Vector angles_;         // The euler angles of the camera orientation
  Matrix orientation_;    // The corresponding rotation matrix

  float speed_;           // Speed of the camera movement
  float sensitivity_;     // Its sensitivity to the mouse movement
  float isize_;           // An inverse measurment of the viewport size
  float inverted_;       // -1 if the y axis should be inverted

  DISALLOW_COPY_AND_ASSIGN(Camera);
};

}

#endif // OBJECTS_CAMERA_H_
