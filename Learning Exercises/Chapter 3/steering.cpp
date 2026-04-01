// Compile with:  g++ -std=c++17 steering.cpp -o steering
#include <iostream>
#include <cmath>
#include <cassert>
#include "vec_math.cpp"

const float PI = 3.14159265f;

struct Vector2 {
    float x, y;
    Vector2(float x = 0, float y = 0) : x(x), y(y) {}
};

float   Length(Vector2 v) { return std::sqrtf(v.x * v.x + v.y * v.y); }
Vector2 Normalize(Vector2 v) {
    float l = Length(v);
    if (l < 0.001f) return Vector2(0, 0);
    return Vector2(v.x / l, v.y / l);
}
Vector2 Subtract(Vector2 a, Vector2 b) { return Vector2(a.x - b.x, a.y - b.y); }

// ── TASK 1: Given rotation angle in radians, return forward vector ──
//   Uses the unit circle: (cos(angle), -sin(angle))
//   We negate y because SDL has +y pointing DOWN
Vector2 AngleToForward(float radians) {
    /* TODO */
    return Vector2{ cos(radians), -sin(radians) };
}

// ── TASK 2: Given a direction vector, return the angle in radians ──
//   Use atan2. Remember to negate y for SDL coordinate system.
//   Tangent function takes in an angle and returns the ratio between opposite and adjacent sides of a triangle
float ForwardToAngle(Vector2 forward) {
    /* TODO */
    return atan2(-forward.y, forward.x);
}

// ── TASK 3: Point ship toward asteroid ─────────────────────────────
//   Given ship position and asteroid position,
//   return the rotation angle the ship should face.
float FaceToward(Vector2 shipPos, Vector2 asteroidPos) {
    /* TODO: subtract, normalize, convert to angle */
    Vector2 shipToAsetroid = Subtract(asteroidPos, shipPos);
    Vector2 normalized = Normalize(shipToAsetroid);
    return ForwardToAngle(normalized);
}

bool Near(float a, float b, float eps = 0.01f) { return std::fabs(a - b) < eps; }

int main() {
    // TASK 1 tests: angle → forward vector
    Vector2 fwd0 = AngleToForward(0.f);
    assert(Near(fwd0.x, 1.f) && Near(fwd0.y, 0.f));  // facing right

    Vector2 fwdUp = AngleToForward(-PI / 2.f);
    assert(Near(fwdUp.x, 0.f) && Near(fwdUp.y, 1.f)); // facing up in SDL

    std::cout << "Task 1 passed: angle → forward\n";

    // TASK 2 tests: forward vector → angle
    float ang = ForwardToAngle(Vector2(1.f, 0.f));
    assert(Near(ang, 0.f));  // pointing right = angle 0

    std::cout << "Task 2 passed: forward → angle\n";

    // TASK 3 test: ship at (5,2), asteroid at (3,5)
    float shipAngle = FaceToward(Vector2(5.f, 2.f), Vector2(3.f, 5.f));
    // Expected: roughly -2.159 radians (pointing left+down in SDL coords)
    std::cout << "FaceToward angle: " << shipAngle << " rad\n";
    // Verify the resulting forward vector actually points toward the asteroid
    Vector2 resultFwd = AngleToForward(shipAngle);
    Vector2 expected = Normalize(Subtract(Vector2(3.f, 5.f), Vector2(5.f, 2.f)));
    assert(Near(resultFwd.x, expected.x, 0.02f) && Near(resultFwd.y, expected.y, 0.02f));

    std::cout << "All steering tests passed!\n";
    return 0;
}