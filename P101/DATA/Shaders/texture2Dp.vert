// Version du GLSL

#version 150 core


// Entrée Shader

in vec2 in_Vertex;
in vec2 in_TexCoord0;

uniform vec3 position;

// Sortie

out vec2 coordTexture;

// Fonction main

void main()
{
    // Position finale du vertex

    gl_Position = vec4(vec3(in_Vertex, 0) + position, 1.0);


    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_TexCoord0;
}
