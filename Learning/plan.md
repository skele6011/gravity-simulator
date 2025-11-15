# Gravity Simulator

---

## Phase 1: SDL2 Practice Game (2D Mouse Survival)

**Goal:** Build a small 2D game to practice SDL fundamentals and programming concepts.

### Completed / Learned

- [x] Initialization (Basic)
- [x] Initialization
- [x] Initialization (OOP Integrated)
- [x] Window Creation (Class + destructor)
- [x] Event Manager Class (basic polling)
- [x] Using Event Manager in `main`
- [x] Drawing #1 (Window class with `beginFrame`, `drawRectangle`, `endFrame`)
- [x] Drawing #2 (Using Window to draw rectangles in `main`)

---

### To Learn / Next Steps

- [x] Multibutton Input (`SDL_GetKeyboardState`)
- [x] Mouse Input (`SDL_GetMouseState`, `SDL_SetRelativeMouseMode`)
    - [x] Won't use SetRelativeMouseMode as no use for it (at least now), will use `ShowCursor`.
- [ ] More advanced drawing
- [ ] Continuous Collision Detection (`SDL_HasIntersection`, reversing velocities)
- [ ] Game Objects (Player circle, enemy squares, lightweight classes)
- [ ] Game Loop & Timing (`SDL_GetTicks`, delta time)
- [ ] Levels & Difficulty (progression, retry mechanism)
- [ ] Optional: Sound effects (`SDL_INIT_AUDIO`, SDL_mixer)

---

## Phase 2: OpenGL 3D Gravity Simulator (Future)

**Goal:** Use SDL mainly for window/input while implementing a 3D physics simulator in OpenGL.

### To Learn

- [ ] OpenGL Basics (triangles, colors, buffers)
- [ ] Shaders (vertex and fragment)
- [ ] Matrices & Transformations (model, view, projection)
- [ ] 3D Vectors & Physics (position, velocity, acceleration, gravity formulas)
- [ ] Motion Integration (Euler, optionally RK4)
- [ ] Camera & Controls (moving camera, mouse orientation)
- [ ] SDL Integration (window creation, input, timing; rendering in OpenGL)
