#include "raylib.h"

int main() {
    InitWindow(800, 600, "Raylib Window");
    SetTargetFPS(60);

    Vector3 a = { -1, 0, 0 };
    Vector3 b = {  1, 0, 0 };

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 2.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawLine3D(a, b, RED);
        DrawSphere(a, 0.1f, BLUE);
        DrawSphere(b, 0.1f, GREEN);
        EndMode3D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
