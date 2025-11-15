#pragma This was a failed attempt at making a drawing of a filled triangle
// void Window::drawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color) {
//     // Sort vertices by y-coordinate (y1 <= y2 <= y3)
//     // y1 = top, y2 = mid, y3 = bottom
//     if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }
//     if (y2 > y3) { std::swap(x2, x3); std::swap(y2, y3); }
//     if (y1 > y2) { std::swap(x1, x2); std::swap(y1, y2); }

//     // Lambda function to draw every pixel from startX till endX at Y
//     auto drawLineH = [&](int sx, int ex, int y) {
//         for (int x = sx; x <= ex; x++) {
//           drawPoint(x, y, color);  
//         } 
//     };

//     // If slope != 0, set to the slope (x2-x1 / y2 - y1), else, slope is set to 0.
//     float dx1 = (y2 - y1) ? float(x2 - x1) / float(y2 - y1) : 0; // Middle -> Top
//     float dx2 = (y3 - y1) ? float(x3 - x1) / float(y3 - y1) : 0; // Bottom -> Top
//     float dx3 = (y3 - y2) ? float(x3 - x2) / float(y3 - y2) : 0; // Bottom -> Middle

//     // Tippy top. Same x as it's litrally one pixel.
//     float sx = x1;
//     float ex = x1;

//     // We keep filling from the top till we get to the middle
//     for (int y = y1; y <= y2; y++) {
//         drawLineH(int(sx), int(ex), y);
//         sx += dx1; // Set the start to be increased using the left edge
//         ex += dx2; // Set the end to be increased using the right edge
//     }

//     // Repeat the process above but from middle to bottom vertices
//     sx = x2;
//     for (int y = y2; y <= y3; y++) {
//         drawLineH(int(sx), int(ex), y);
//         sx += dx3;
//         ex += dx2;
//     }
// }