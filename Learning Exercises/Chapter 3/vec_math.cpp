// Compile with:  g++ -std=c++17 vec_math.cpp -o vec_math
#include <iostream>
#include <cmath>
#include <cassert>

struct Vector2 {
    float x, y;
    Vector2(float x = 0.f, float y = 0.f) : x(x), y(y) {}
};

struct Vector3 {
    float x, y, z;
    Vector3(float x = 0.f, float y = 0.f, float z = 0.f) : x(x), y(y), z(z) {}
};

// ── TASK 1: Implement these functions ──────────────────────────────

Vector2 Add(Vector2 a, Vector2 b) {return Vector2(a.x+b.x, a.y+b.y); }
Vector2 Subtract(Vector2 a, Vector2 b) {return Vector2(a.x-b.x, a.y-b.y); }
Vector2 Scale(Vector2 v, float s) {return Vector2(v.x * s, v.y * s); }
float   Length(Vector2 v) {return sqrt(v.x*v.x + v.y*v.y); }
float   LengthSquared(Vector2 v) {return v.x * v.x + v.y * v.y; }
Vector2 Normalize(Vector2 v) {
    float length = Length(v);
    if (length != 0) {
        return Vector2(v.x / length, v.y / length);
    }
    else {
        return v;
    }
    
}

// ── TASK 2: Also implement for Vector3 ────────────────────────────

Vector3 Add3(Vector3 a, Vector3 b) { /* TODO */ return {}; }
Vector3 Scale3(Vector3 v, float s) { /* TODO */ return {}; }
float   Length3(Vector3 v) { /* TODO */ return 0.f; }
Vector3 Normalize3(Vector3 v) { /* TODO */ return {}; }

// ── Helper for float comparison ────────────────────────────────────
bool Near(float a, float b, float eps = 0.001f) {
    return std::fabs(a - b) < eps;
}
bool NearVec(Vector2 a, Vector2 b) {
    return Near(a.x, b.x) && Near(a.y, b.y);
}

int main() {
    // --- Test Suite ---
    // Subtraction: vector FROM ship TO target
    Vector2 ship(5.f, 2.f), target(3.f, 5.f);
    Vector2 toTarget = Subtract(target, ship);
    assert(NearVec(toTarget, Vector2(-2.f, 3.f)));

    // Addition: move player forward
    Vector2 pos(10.f, 10.f), forward(0.f, -1.f);
    Vector2 newPos = Add(pos, Scale(forward, 150.f));
    assert(NearVec(newPos, Vector2(10.f, -140.f)));

    // Length
    assert(Near(Length(Vector2(3.f, 4.f)), 5.f));
    assert(Near(LengthSquared(Vector2(3.f, 4.f)), 25.f));

    // Normalize: result should have length == 1
    Vector2 n = Normalize(Vector2(3.f, 4.f));
    assert(Near(Length(n), 1.f));

    // Safe normalize: zero vector should NOT crash
    Vector2 zero = Normalize(Vector2(0.f, 0.f));
    // Just shouldn't crash or produce NaN

    std::cout << "All Vector2 tests passed!\n";

    // --- BONUS: Distance between two points using vectors ---
    // Compute distance from ship(5,2) to target(3,5)
    // Expected: ~3.606
    float dist = Length(Subtract(target, ship));
    std::cout << "Distance ship→target: " << dist << "\n";

    return 0;
}