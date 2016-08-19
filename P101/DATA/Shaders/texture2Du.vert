// Version du GLSL

#version 150 core


// Entrée Shader

in vec2 in_Vertex;
in vec2 in_TexCoord0;

uniform float profondeur;

// Sortie

out vec2 coordTexture;

// Fonction main

void main()
{
    // Position finale du vertex

    gl_Position = vec4(in_Vertex, profondeur, 1.0);


    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_TexCoord0;
}
