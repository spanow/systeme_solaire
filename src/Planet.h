#ifndef PLANET_H
#define PLANET_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

// Classe représentant une planète
class Planet {
public:
    // Constructeur
    Planet(float radius, float distance, float orbitSpeed, glm::vec3 color, const std::string& textureFile, const std::string& name);

    // Méthodes pour dessiner et mettre à jour la planète
    void draw() const;
    void drawOrbit() const;
    void update(float deltaTime);
    void drawName() const;
    void drawArrow() const;

private:
    float radius;       // Rayon de la planète
    float distance;     // Distance par rapport au centre (soleil)
    float orbitSpeed;   // Vitesse de rotation autour du soleil
    glm::vec3 color;    // Couleur de la planète
    float angle;        // Angle actuel de la planète sur son orbite
    GLuint textureID;   // ID de la texture
    std::string name;   // Nom de la planète

    // Méthodes internes
    void init();
    void loadTexture(const std::string& textureFile);
};

// Classe représentant le soleil
class Sun {
public:
    // Constructeur
    Sun(float radius, glm::vec3 color, const std::string& textureFile);

    // Méthode pour dessiner le soleil
    void draw() const;

private:
    float radius;       // Rayon du soleil
    glm::vec3 color;    // Couleur du soleil
    GLuint textureID;   // ID de la texture

    // Méthodes internes
    void init();
    void loadTexture(const std::string& textureFile);
};

#endif // PLANET_H
