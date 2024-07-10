#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Planet.h"
#include "Camera.h"

// Fonction pour initialiser GLEW
void initOpenGL() {
    glewExperimental = GL_TRUE; // Nécessaire pour certains contextes OpenGL
    GLenum err = glewInit();    // Initialisation de GLEW
    if (err != GLEW_OK) {       // Vérification des erreurs d'initialisation
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);     // Sortie du programme en cas d'erreur
    }

    // Activer les fonctionnalités d'éclairage
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Activer la lumière 0
    glEnable(GL_DEPTH_TEST); // Activer le test de profondeur

    // Définir les propriétés de la lumière
    GLfloat light_pos[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // Position de la lumière
    GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Couleur de la lumière
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

    // Définir les propriétés du matériau
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Variables globales pour la caméra
Camera camera(glm::vec3(0.0f, 1.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -20.0f);
float lastX = 400, lastY = 300;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Fonction de rappel pour le mouvement de la souris
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Inverser car les coordonnées y vont de bas en haut

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

int main(int argc, char** argv) {
    // Initialisation de GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Initialisation de GLUT
    glutInit(&argc, argv);

    // Création d'une fenêtre GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Système Solaire", nullptr, nullptr);
    if (!window) { // Vérification de la création de la fenêtre
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // Fermeture de GLFW en cas d'erreur
        return -1;
    }

    // Rendre le contexte OpenGL de la fenêtre courant
    glfwMakeContextCurrent(window);
    initOpenGL(); // Initialisation de GLEW et configuration de l'éclairage

    // Configuration des rappels de la souris
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Masquer le curseur et capturer la souris

    // Centrer la caméra sur le centre du système solaire
    camera.centerOnPoint(glm::vec3(0.0f, 0.0f, 0.0f));

    // Création des planètes
    std::vector<Planet> planets;
    planets.emplace_back(0.1f, 0.5f, 0.1f, glm::vec3(0.0f, 0.5f, 1.0f), "../earth_texture.jpg", "Terre"); // Terre
    planets.emplace_back(0.2f, 0.8f, 0.05f, glm::vec3(1.0f, 0.5f, 0.0f), "../jupiter_texture.jpg", "Jupiter"); // Jupiter
    planets.emplace_back(0.05f, 0.3f, 0.2f, glm::vec3(1.0f, 0.0f, 0.0f), "../mars_texture.jpg", "Mars"); // Mars
    // Ajoutez d'autres planètes selon vos besoins

    // Création du soleil
    Sun sun(0.3f, glm::vec3(1.0f, 1.0f, 0.0f), "../sun_texture.jpg"); // Soleil

    // Boucle principale
    while (!glfwWindowShouldClose(window)) {
        // Calcul du temps écoulé entre les images
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Processus de l'entrée de la caméra
        camera.processKeyboard(window, deltaTime);

        // Effacer l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Définir la matrice de vue
        glm::mat4 view = camera.getViewMatrix();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(view));

        // Dessiner le soleil
        sun.draw();

        // Dessiner les orbites des planètes
        for (const auto& planet : planets) {
            planet.drawOrbit();
        }

        // Mise à jour et dessin des planètes
        for (auto& planet : planets) {
            planet.update(0.01f); // Exemple de deltaTime
            planet.draw();
            planet.drawName(); // Dessiner le nom de la planète
            planet.drawArrow(); // Dessiner la flèche vers la planète
        }

        // Échanger les buffers et traiter les événements
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Destruction de la fenêtre et terminaison de GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
