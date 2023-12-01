#version 450

void main() {
    gl_Position = vec4(triangle[gl_VertexID], 0.0, 1.0);
}