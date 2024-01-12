#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Définition de la structure de la particule
typedef struct {
    double x, y; // Position
    double vx, vy; // Vitesse
    double fx, fy; // Force
} Particule;

// Prototypes de fonctions
void initialiserParticules(Particule *particules, int n);
void calculerForces(Particule *particules, int n);
void mettreAJourParticules(Particule *particules, int n, double dt);
void afficherParticules(const Particule *particules, int n);

int main() {
    const int nombreDeParticules = 1000;
    const double dt = 0.01; // Pas de temps
    Particule *particules = (Particule *)malloc(nombreDeParticules * sizeof(Particule));

    initialiserParticules(particules, nombreDeParticules);

    for (int step = 0; step < 1000; ++step) {
        calculerForces(particules, nombreDeParticules);
        mettreAJourParticules(particules, nombreDeParticules, dt);
        afficherParticules(particules, nombreDeParticules);
    }

    free(particules);
    return 0;
}

void initialiserParticules(Particule *particules, int n) {
    for (int i = 0; i < n; ++i) {
        particules[i].x = (double)rand() / RAND_MAX;
        particules[i].y = (double)rand() / RAND_MAX;
        particules[i].vx = 0;
        particules[i].vy = 0;
        particules[i].fx = 0;
        particules[i].fy = 0;
    }
}

void calculerForces(Particule *particules, int n) {
    for (int i = 0; i < n; ++i) {
        particules[i].fx = 0;
        particules[i].fy = 0;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double dx = particules[j].x - particules[i].x;
                double dy = particules[j].y - particules[i].y;
                double distance = sqrt(dx * dx + dy * dy);
                double force = 1 / (distance * distance); // Force simplifiée
                particules[i].fx += dx / distance * force;
                particules[i].fy += dy / distance * force;
            }
        }
    }
}

void mettreAJourParticules(Particule *particules, int n, double dt) {
    for (int i = 0; i < n; ++i) {
        // Mise à jour de la vitesse
        particules[i].vx += particules[i].fx * dt;
        particules[i].vy += particules[i].fy * dt;

        // Mise à jour de
        // la position
        particules[i].x += particules[i].vx * dt;
        particules[i].y += particules[i].vy * dt;
    }
}

void afficherParticules(const Particule *particules, int n) {
    for (int i = 0; i < n; ++i) {
        printf("Particule %d: Position=(%f, %f), Vitesse=(%f, %f)\n",
               i, particules[i].x, particules[i].y, particules[i].vx, particules[i].vy);
    }
}
