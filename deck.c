



typedef enum {
    coeur,
    carreau,
    trefle,
    pique
} couleur;

typedef struct {
    int valeur;      // 1 = as, 11 = valet, 12 = dame, 13 = roi
    couleur couleur;
    int face_visible; // 0 = cachée, 1 = visible
} carte;

typedef struct {
    carte cartes[52];
    int nb_cartes;
} deck;
