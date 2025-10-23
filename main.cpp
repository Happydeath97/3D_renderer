#include "raylib.h"
#include <math.h>   // for sinf/cosf

// --- Minimal Matrix helpers (self-implemented) ---
static Matrix MatrixIdentityCustom() {
    Matrix m = {0};
    m.m0 = 1.0f; m.m5 = 1.0f; m.m10 = 1.0f; m.m15 = 1.0f;
    return m;
}

static Matrix MatrixMultiplyCustom(Matrix a, Matrix b) {
    Matrix result = {0};
    result.m0  = a.m0*b.m0 + a.m4*b.m1 + a.m8*b.m2 + a.m12*b.m3;
    result.m1  = a.m1*b.m0 + a.m5*b.m1 + a.m9*b.m2 + a.m13*b.m3;
    result.m2  = a.m2*b.m0 + a.m6*b.m1 + a.m10*b.m2 + a.m14*b.m3;
    result.m3  = a.m3*b.m0 + a.m7*b.m1 + a.m11*b.m2 + a.m15*b.m3;

    result.m4  = a.m0*b.m4 + a.m4*b.m5 + a.m8*b.m6 + a.m12*b.m7;
    result.m5  = a.m1*b.m4 + a.m5*b.m5 + a.m9*b.m6 + a.m13*b.m7;
    result.m6  = a.m2*b.m4 + a.m6*b.m5 + a.m10*b.m6 + a.m14*b.m7;
    result.m7  = a.m3*b.m4 + a.m7*b.m5 + a.m11*b.m6 + a.m15*b.m7;

    result.m8  = a.m0*b.m8 + a.m4*b.m9 + a.m8*b.m10 + a.m12*b.m11;
    result.m9  = a.m1*b.m8 + a.m5*b.m9 + a.m9*b.m10 + a.m13*b.m11;
    result.m10 = a.m2*b.m8 + a.m6*b.m9 + a.m10*b.m10 + a.m14*b.m11;
    result.m11 = a.m3*b.m8 + a.m7*b.m9 + a.m11*b.m10 + a.m15*b.m11;

    result.m12 = a.m0*b.m12 + a.m4*b.m13 + a.m8*b.m14 + a.m12*b.m15;
    result.m13 = a.m1*b.m12 + a.m5*b.m13 + a.m9*b.m14 + a.m13*b.m15;
    result.m14 = a.m2*b.m12 + a.m6*b.m13 + a.m10*b.m14 + a.m14*b.m15;
    result.m15 = a.m3*b.m12 + a.m7*b.m13 + a.m11*b.m14 + a.m15*b.m15;
    return result;
}

static Matrix MatrixRotateXCustom(float angle) {
    Matrix m = MatrixIdentityCustom();
    float c = cosf(angle);
    float s = sinf(angle);
    m.m5 = c;  m.m6 = -s;
    m.m9 = s;  m.m10 = c;
    return m;
}

static Matrix MatrixRotateYCustom(float angle) {
    Matrix m = MatrixIdentityCustom();
    float c = cosf(angle);
    float s = sinf(angle);
    m.m0 = c;  m.m2 = s;
    m.m8 = -s; m.m10 = c;
    return m;
}

// --- Main program ---
int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rotate cube with mouse drag (pure raylib + custom math)");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 6.0f, 6.0f, 6.0f };
    camera.target   = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Mesh cube = GenMeshCube(2.0f, 2.0f, 2.0f);
    Model cubeModel = LoadModelFromMesh(cube);
    cubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = RED;

    float rotationX = 0.0f;
    float rotationY = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Mouse drag → change rotation
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 delta = GetMouseDelta();
            rotationX += delta.y * 0.01f; // radians
            rotationY += delta.x * 0.01f;
        }

        // Build transform matrix manually
        Matrix rotX = MatrixRotateXCustom(rotationX);
        Matrix rotY = MatrixRotateYCustom(rotationY);
        cubeModel.transform = MatrixMultiplyCustom(rotX, rotY);

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
            DrawModel(cubeModel, (Vector3){0,0,0}, 1.0f, WHITE);
        EndMode3D();

        DrawText("Drag left mouse button to rotate cube", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadModel(cubeModel);
    CloseWindow();
    return 0;
}
