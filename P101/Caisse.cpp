#include "stdafx.h"
#include "Caisse.h"


// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur et Destructeur

Caisse::Caisse(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture) : Cube(taille, vertexShader, fragmentShader),
                                                                                                                            m_texture(texture)
{
    // Chargement de la texture

    m_texture.charger();


    // Coordonnées de texture temporaires

    float coordTextureTmp[] = {0, 0,   1, 0,   1, 1,     // Face 1
                               0, 0,   0, 1,   1, 1,     // Face 1

                               0, 0,   1, 0,   1, 1,     // Face 2
                               0, 0,   0, 1,   1, 1,     // Face 2

                               0, 0,   1, 0,   1, 1,     // Face 3
                               0, 0,   0, 1,   1, 1,     // Face 3

                               0, 0,   1, 0,   1, 1,     // Face 4
                               0, 0,   0, 1,   1, 1,     // Face 4

                               0, 0,   1, 0,   1, 1,     // Face 5
                               0, 0,   0, 1,   1, 1,     // Face 5

                               0, 0,   1, 0,   1, 1,     // Face 6
                               0, 0,   0, 1,   1, 1};    // Face 6


    // Copie des valeurs dans le tableau final

    for(int i (0); i < 72; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}


Caisse::~Caisse()
{

}


// Méthodes

void Caisse::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader

    glUseProgram(m_shader.getProgramID());


        // Envoi des vertices

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);


        // Envoi des coordonnées de texture

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
        glEnableVertexAttribArray(2);


        // Envoi des matrices

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Verrouillage de la texture

        glBindTexture(GL_TEXTURE_2D, m_texture.getID());


        // Rendu

        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Déverrouillage de la texture

        glBindTexture(GL_TEXTURE_2D, 0);


        // Désactivation des tableaux

        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);
}
