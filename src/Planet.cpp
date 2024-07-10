#include "Planet.h"
#include <GL/glut.h> // Bibliothèque GLUT pour dessiner des sphères et du texte
#include <SOIL/SOIL.h> // Bibliothèque SOIL pour charger les textures
#include <iostream>

// Constructeur de la classe Planet
Planet::Planet(float radius, float distance, float orbitSpeed, glm::vec3 color, const std::string& textureFile, const std::string& name)
    : radius(radius), distance(distance), orbitSpeed(orbitSpeed), color(color), angle(0.0f), name(name) {
    init();
    loadTexture(textureFile);
}

// Initialisation (peut être utilisé pour charger des textures plus tard)
void Planet::init() {
    // Initialisation ici si nécessaire
}

// Méthode pour charger une texture
void Planet::loadTexture(const std::string& textureFile) {
    textureID = SOIL_load_OGL_texture(
        textureFile.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << textureFile << std::endl;
    } else {
        std::cout << "Successfully loaded texture: " << textureFile << std::endl;
    }
}

// Méthode pour dessiner la planète
void Planet::draw() const {
    glPushMatrix(); // Sauvegarde de la matrice actuelle

    // Mise à jour de la position de la planète
    glTranslatef(distance * cos(angle), 0.0f, distance * sin(angle));

    // Activer la texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Définir les paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Définir la couleur de la planète (utilisé pour le mélange avec la texture)
    glColor3f(color.r, color.g, color.b);

    // Dessiner la planète comme une sphère texturée
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, radius, 50, 50);
    gluDeleteQuadric(quad);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix(); // Restaure la matrice sauvegardée
}

// Méthode pour dessiner l'orbite de la planète
void Planet::drawOrbit() const {
    glPushMatrix(); // Sauvegarde de la matrice actuelle

    glColor3f(1.0f, 1.0f, 1.0f); // Couleur de l'orbite (blanche)
    glBegin(GL_LINE_LOOP);       // Début du dessin de la ligne en boucle

    // Dessiner un cercle
    for (int i = 0; i < 100; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(100); // Angle actuel
        float x = distance * cos(theta); // Coordonnée x
        float z = distance * sin(theta); // Coordonnée z
        glVertex3f(x, 0.0f, z); // Spécifier le sommet
    }

    glEnd(); // Fin du dessin de la ligne en boucle

    glPopMatrix(); // Restaure la matrice sauvegardée
}

// Méthode pour mettre à jour la position de la planète
void Planet::update(float deltaTime) {
    angle += orbitSpeed * deltaTime; // Mise à jour de l'angle en fonction de la vitesse de rotation
}

// Méthode pour dessiner le nom de la planète
void Planet::drawName() const {
    glPushMatrix(); // Sauvegarde de la matrice actuelle

    // Mise à jour de la position du texte
    glTranslatef(distance * cos(angle), radius + 0.1f, distance * sin(angle));

    // Définir la couleur du texte (blanc)
    glColor3f(1.0f, 1.0f, 1.0f);

    // Afficher le nom de la planète
    glRasterPos3f(0.0f, 0.0f, 0.0f);
    for (char c : name) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix(); // Restaure la matrice sauvegardée
}

// Méthode pour dessiner une flèche vers la planète
void Planet::drawArrow() const {
    glPushMatrix(); // Sauvegarde de la matrice actuelle

    // Définir la couleur de la flèche (rouge)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Dessiner la flèche
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(distance * cos(angle), 0.0f, distance * sin(angle));
    glEnd();

    // Dessiner la pointe de la flèche
    glTranslatef(distance * cos(angle), 0.0f, distance * sin(angle));
    glutSolidCone(0.05, 0.2, 10, 2);

    glPopMatrix(); // Restaure la matrice sauvegardée
}

// Constructeur de la classe Sun
Sun::Sun(float radius, glm::vec3 color, const std::string& textureFile)
    : radius(radius), color(color) {
    init();
    loadTexture(textureFile);
}

// Initialisation (peut être utilisé pour charger des textures plus tard)
void Sun::init() {
    // Initialisation ici si nécessaire
}

// Méthode pour charger une texture
void Sun::loadTexture(const std::string& textureFile) {
    textureID = SOIL_load_OGL_texture(
        textureFile.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << textureFile << std::endl;
    } else {
        std::cout << "Successfully loaded texture: " << textureFile << std::endl;
    }
}

// Méthode pour dessiner le soleil
void Sun::draw() const {
    glPushMatrix(); // Sauvegarde de la matrice actuelle

    // Activer la texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Définir les paramètres de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Définir la couleur du soleil (utilisé pour le mélange avec la texture)
    glColor3f(color.r, color.g, color.b);

    // Dessiner le soleil comme une sphère texturée
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluSphere(quad, radius, 50, 50);
    gluDeleteQuadric(quad);

    glDisable(GL_TEXTURE_2D);

    glPopMatrix(); // Restaure la matrice sauvegardée
}
