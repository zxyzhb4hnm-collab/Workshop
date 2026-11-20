#include <sil/sil.hpp>
#include "random.hpp"
#include <vector>

//vert
void exo_vert(){
    sil::Image image{"images/logo.png"};

    for (glm::vec3& color : image.pixels()){
        color.r = 0.f;
        color.b = 0.f;
    }

    image.save("output/vert.png");
}

//swap
void exo_swap(){
    sil::Image image{"images/logo.png"};
    for (glm::vec3& color : image.pixels()){
        std::swap(color.r, color.b);
    }

    image.save("output/swap.png");
}

//noir et blanc
void exo_noir_et_blanc(){
    sil::Image image{"images/logo.png"};

    for (glm::vec3& color : image.pixels()){
        float gris = 0.2126f * color.r
                   + 0.7152f * color.g
                   + 0.0722f * color.b;
        color.r = gris;
        color.g = gris;
        color.b = gris;
    }

    image.save("output/n&b.png");
}

//negatif
void exo_negatif(){
    sil::Image image{"images/logo.png"};

    for (glm::vec3& color : image.pixels()){
        color.r = 1-color.r;
        color.g = 1-color.g;
        color.b = 1-color.b;
    }

    image.save("output/negatif.png");
}

//degrade
void exo_degrade(){
    sil::Image image{300, 200};
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float valeur = (float)x / (image.width() - 1);
            image.pixel(x, y).r = valeur;
            image.pixel(x, y).g = valeur;
            image.pixel(x, y).b = valeur;
        }
    }
    image.save("output/gradende.png");
}

//miroir
void exo_miroir(){
    sil::Image image{"images/logo.png"};
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width() / 2; x++)
        {
            std::swap(image.pixel(x, y), image.pixel(image.width() - 1 - x, y));
        }
    }
    image.save("output/miroir.png");
}

//image bruitee
void exo_image_bruitee(){
    sil::Image image{"images/logo.png"};
    for (glm::vec3& color : image.pixels()){
        if (true_with_probability(0.3f)){
            color.r = random_float(0.f, 1.f);
            color.g = random_float(0.f, 1.f);
            color.b = random_float(0.f, 1.f);
        }
    }

    image.save("output/bruitee.png");
}

//rotation 90
void exo_rotation_90(){
    sil::Image image{"images/logo.png"};
    sil::Image nouvelle{image.height(), image.width()};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            nouvelle.pixel(image.height() - 1 - y, x) = image.pixel(x, y);

        }
    }
    nouvelle.save("output/rotation.png");
}

//rgb split
void exo_rgb_split(){
    sil::Image image{"images/logo.png"};
    sil::Image nouvelle{image.width(), image.height()};
    int decalage{30};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            if (x - decalage >= 0){
                nouvelle.pixel(x, y).r = image.pixel(x - decalage, y).r;
            }
            nouvelle.pixel(x, y).g = image.pixel(x, y).g;
            if (x + decalage < image.width()){
                nouvelle.pixel(x, y).b = image.pixel(x + decalage, y).b;
            }
        }
    }
    nouvelle.save("output/rgb_split.png");
}

//luminosite (eclaircir)
void exo_luminosite_eclaircir(){
    sil::Image image{"images/photo.jpg"};

    for (glm::vec3& color : image.pixels()){
        color.r = std::pow(color.r, 0.6f);
        color.g = std::pow(color.g, 0.6f);
        color.b = std::pow(color.b, 0.6f);
    }

    image.save("output/eclaircie.png");
}

//luminosite (assombrir)
void exo_luminosite_assombrir(){
    sil::Image image{"images/photo.jpg"};

    for (glm::vec3& color : image.pixels()){
        color.r = std::pow(color.r, 1.6f);
        color.g = std::pow(color.g, 1.6f);
        color.b = std::pow(color.b, 1.6f);
    }

    image.save("output/assombrie.png");
}

// disque
void exo_disque(){
    sil::Image image{500, 500};
    float centre_x{250.f};
    float centre_y{250.f};
    float rayon{100.f};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float distance = std::sqrt((x - centre_x) * (x - centre_x) + (y - centre_y) * (y - centre_y));
            if (distance <= rayon){
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
    image.save("output/disque.png");
}

//cercle
void exo_cercle(){
    sil::Image image{500, 500};
    float centre_x{250.f};
    float centre_y{250.f};
    float rayon{100.f};
    float thickness{10.f};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float distance = std::sqrt((x - centre_x) * (x - centre_x) + (y - centre_y) * (y - centre_y));
            if (distance >= rayon - thickness / 2 && distance <= rayon + thickness / 2){
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
    image.save("output/cercle.png");
}

//animation
void exo_animation(){
    float rayon{50.f};
    for (int i{0}; i < 60; i++)
    {
        sil::Image image{200, 200};
        float centre_x = rayon + i * (200 - 2 * rayon) / 59;
        float centre_y{100.f};
        for (int y{0}; y < image.height(); y++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                float distance = std::sqrt((x - centre_x) * (x - centre_x) + (y - centre_y) * (y - centre_y));
                if (distance <= rayon){
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
        std::string numero = std::to_string(i);
        if (i < 10) numero = "0" + numero;
        image.save("output/animation/frame_" + numero + ".png");
    }
}

//rosace
void exo_rosace(){
    sil::Image image{500, 500};
    float centre_x{250.f};
    float centre_y{250.f};
    float rayon{100.f};
    float thickness{5.f};
    float pi{3.14159265f};

    //celui du milieu (i = 0) + 6 autres tous les 60 degres
    for (int i{0}; i < 7; i++)
    {
        float cx = centre_x;
        float cy = centre_y;
        if (i > 0){
            float angle = i * 2 * pi / 6;
            cx = centre_x + rayon * std::cos(angle);
            cy = centre_y + rayon * std::sin(angle);
        }
        for (int y{0}; y < image.height(); y++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                float distance = std::sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy));
                if (distance >= rayon - thickness / 2 && distance <= rayon + thickness / 2){
                    image.pixel(x, y).r = 1.f;
                    image.pixel(x, y).g = 1.f;
                    image.pixel(x, y).b = 1.f;
                }
            }
        }
    }
    image.save("output/rosace.png");
}

//mosaique
void exo_mosaique(){
    sil::Image image{"images/logo.png"};
    sil::Image nouvelle{image.width() * 5, image.height() * 5};
    for (int y{0}; y < nouvelle.height(); y++)
    {
        for (int x{0}; x < nouvelle.width(); x++)
        {
            nouvelle.pixel(x, y) = image.pixel(x % image.width(), y % image.height());
        }
    } 
    nouvelle.save("output/mosaique.png");
}

//mosaique miroir
void exo_mosaique_miroir(){
    sil::Image image{"images/logo.png"};
    sil::Image nouvelle{image.width() * 5, image.height() * 5};
    for (int y{0}; y < nouvelle.height(); y++)
    {
        for (int x{0}; x < nouvelle.width(); x++)
        {
            int x_logo = x % image.width();
            int y_logo = y % image.height();
            if ((x / image.width()) % 2 == 1){
                x_logo = image.width() - 1 - x_logo;
            }
            if ((y / image.height()) % 2 == 1){
                y_logo = image.height() - 1 - y_logo;
            }
            nouvelle.pixel(x, y) = image.pixel(x_logo, y_logo);
        }
    }
    nouvelle.save("output/mosaique_miroir.png");
}

//glitch
void exo_glitch(){
    sil::Image image{"images/logo.png"};
    for (int i{0}; i < 100; i++)
    {
        int largeur = random_int(5, 40);
        int hauteur = random_int(2, 8);
        int x1 = random_int(0, image.width() - largeur);
        int y1 = random_int(0, image.height() - hauteur);
        int x2 = random_int(0, image.width() - largeur);
        int y2 = random_int(0, image.height() - hauteur);
        for (int y{0}; y < hauteur; y++)
        {
            for (int x{0}; x < largeur; x++)
            {
                std::swap(image.pixel(x1 + x, y1 + y), image.pixel(x2 + x, y2 + y));
            }
        }
    }
    image.save("output/glitch.png");
}

//degrade couleur
void exo_degrade_couleur(){
    sil::Image image{300, 200};
    glm::vec3 couleur_gauche{1.f, 0.f, 1.f};
    glm::vec3 couleur_droite{0.f, 1.f, 1.f}; 

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float t = (float)(x) / (image.width() - 1);
            image.pixel(x, y) = glm::mix(couleur_gauche, couleur_droite, t);
        }
    }
    image.save("output/gradende_couleur.png");
}

//conversions pour le Lab (Oklab)
float srgb_vers_lineaire(float c){
    if (c <= 0.04045f) return c / 12.92f;
    return std::pow((c + 0.055f) / 1.055f, 2.4f);
}

float lineaire_vers_srgb(float c){
    if (c < 0.f) c = 0.f;
    if (c > 1.f) c = 1.f;
    if (c <= 0.0031308f) return c * 12.92f;
    return 1.055f * std::pow(c, 1.f / 2.4f) - 0.055f;
}

glm::vec3 srgb_vers_oklab(glm::vec3 couleur){
    float r = srgb_vers_lineaire(couleur.r);
    float g = srgb_vers_lineaire(couleur.g);
    float b = srgb_vers_lineaire(couleur.b);

    float l = std::cbrt(0.4122214708f * r + 0.5363325363f * g + 0.0514459929f * b);
    float m = std::cbrt(0.2119034982f * r + 0.6806995451f * g + 0.1073969566f * b);
    float s = std::cbrt(0.0883024619f * r + 0.2817188376f * g + 0.6299787005f * b);

    glm::vec3 lab;
    lab.x = 0.2104542553f * l + 0.7936177850f * m - 0.0040720468f * s;
    lab.y = 1.9779984951f * l - 2.4285922050f * m + 0.4505937099f * s;
    lab.z = 0.0259040371f * l + 0.7827717662f * m - 0.8086757660f * s;
    return lab;
}

glm::vec3 oklab_vers_srgb(glm::vec3 lab){
    float l = lab.x + 0.3963377774f * lab.y + 0.2158037573f * lab.z;
    float m = lab.x - 0.1055613458f * lab.y - 0.0638541728f * lab.z;
    float s = lab.x - 0.0894841775f * lab.y - 1.2914855480f * lab.z;
    l = l * l * l;
    m = m * m * m;
    s = s * s * s;

    glm::vec3 couleur;
    couleur.r = lineaire_vers_srgb( 4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s);
    couleur.g = lineaire_vers_srgb(-1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s);
    couleur.b = lineaire_vers_srgb(-0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s);
    return couleur;
}

//degrade rouge vert (sRGB)
void exo_degrade_rouge_vert(){
    sil::Image image{300, 200};
    glm::vec3 couleur_gauche{1.f, 0.f, 0.f};
    glm::vec3 couleur_droite{0.f, 1.f, 0.f};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float t = (float)(x) / (image.width() - 1);
            image.pixel(x, y) = glm::mix(couleur_gauche, couleur_droite, t);
        }
    }
    image.save("output/degrade_rouge_vert.png");
}

//degrade lab
void exo_degrade_lab(){
    sil::Image image{300, 200};
    glm::vec3 couleur_gauche = srgb_vers_oklab({1.f, 0.f, 0.f});
    glm::vec3 couleur_droite = srgb_vers_oklab({0.f, 1.f, 0.f});

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float t = (float)(x) / (image.width() - 1);
            glm::vec3 lab = glm::mix(couleur_gauche, couleur_droite, t);
            image.pixel(x, y) = oklab_vers_srgb(lab);
        }
    }
    image.save("output/degrade_lab.png");
}

//tramage
void exo_tramage(){
    sil::Image image{"images/photo.jpg"};
    float bayer[4][4] = {
        { 0.f,  8.f,  2.f, 10.f},
        {12.f,  4.f, 14.f,  6.f},
        { 3.f, 11.f,  1.f,  9.f},
        {15.f,  7.f, 13.f,  5.f}
    };

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            glm::vec3 color = image.pixel(x, y);
            float gris = 0.2126f * color.r
                       + 0.7152f * color.g
                       + 0.0722f * color.b;
            float seuil = (bayer[y % 4][x % 4] + 0.5f) / 16.f;
            float valeur = 0.f;
            if (gris > seuil){
                valeur = 1.f;
            }
            image.pixel(x, y).r = valeur;
            image.pixel(x, y).g = valeur;
            image.pixel(x, y).b = valeur;
        }
    }
    image.save("output/tramage.png");
}

//convolution
sil::Image convolution(sil::Image image, std::vector<std::vector<float>> kernel){
    sil::Image nouvelle{image.width(), image.height()};
    int rayon_y = kernel.size() / 2;
    int rayon_x = kernel[0].size() / 2;

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            glm::vec3 somme{0.f, 0.f, 0.f};
            for (int j{-rayon_y}; j <= rayon_y; j++)
            {
                for (int i{-rayon_x}; i <= rayon_x; i++)
                {
                    int x_voisin = x + i;
                    int y_voisin = y + j;
                    //si on sort de l'image  on prend le pixel du bord
                    if (x_voisin < 0) x_voisin = 0;
                    if (x_voisin > image.width() - 1) x_voisin = image.width() - 1;
                    if (y_voisin < 0) y_voisin = 0;
                    if (y_voisin > image.height() - 1) y_voisin = image.height() - 1;

                    somme += image.pixel(x_voisin, y_voisin) * kernel[j + rayon_y][i + rayon_x];
                }
            }
            nouvelle.pixel(x, y) = somme;
        }
    }
    return nouvelle;
}

//box blur
void exo_box_blur(){
    sil::Image image{"images/logo.png"};
    int rayon{5};
    int taille = 2 * rayon + 1;
    float poids = 1.f / (taille * taille);
    std::vector<std::vector<float>> kernel(taille, std::vector<float>(taille, poids));

    convolution(image, kernel).save("output/box_blur.png");
}



//box blur separe (horizontal puis vertical)
sil::Image flou_separe(sil::Image image, int rayon){
    int taille = 2 * rayon + 1;
    float poids = 1.f / taille;

    //1 ligne de taille cases
    std::vector<std::vector<float>> kernel_horizontal(1, std::vector<float>(taille, poids));
    //taille lignes de 1 case
    std::vector<std::vector<float>> kernel_vertical(taille, std::vector<float>(1, poids));

    sil::Image horizontal = convolution(image, kernel_horizontal);
    return convolution(horizontal, kernel_vertical);
}

//filtres separables
void exo_filtres_separables(){
    sil::Image image{"images/logo.png"};
    int rayon{50};
    int taille = 2 * rayon + 1;
    float poids = 1.f / (taille * taille);
    std::vector<std::vector<float>> kernel(taille, std::vector<float>(taille, poids));

    convolution(image, kernel).save("output/box_blur_naif.png");
    flou_separe(image, rayon).save("output/box_blur_separe.png");
}

//difference de gaussiennes
void exo_difference_gaussiennes(){
    sil::Image image{"images/photo.jpg"};

    for (glm::vec3& color : image.pixels()){
        float gris = 0.2126f * color.r
                   + 0.7152f * color.g
                   + 0.0722f * color.b;
        color.r = gris;
        color.g = gris;
        color.b = gris;
    }

    sil::Image flou_petit = flou_separe(image, 1);
    sil::Image flou_grand = flou_separe(image, 3);
    float tau{0.98f};
    float seuil{0.005f};

    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            float difference = flou_petit.pixel(x, y).r - tau * flou_grand.pixel(x, y).r;
            float valeur = 0.f;
            if (difference > seuil){
                valeur = 1.f;
            }
            image.pixel(x, y).r = valeur;
            image.pixel(x, y).g = valeur;
            image.pixel(x, y).b = valeur;
        }
    }
    image.save("output/difference_gaussiennes.png");
}

int main(){

    set_random_seed(0);

    exo_vert();
    exo_swap();
    exo_noir_et_blanc();
    exo_negatif();
    exo_degrade();
    exo_miroir();
    exo_image_bruitee();
    exo_rotation_90();
    exo_rgb_split();
    exo_luminosite_eclaircir();
    exo_luminosite_assombrir();
    exo_disque();
    exo_cercle();
    exo_animation();
    exo_rosace();
    exo_mosaique();
    exo_mosaique_miroir();
    exo_glitch();
    exo_degrade_couleur();
    exo_degrade_rouge_vert();
    exo_degrade_lab();
    exo_tramage();
    exo_box_blur();
    exo_nettete_contours();
    exo_filtres_separables();
    exo_difference_gaussiennes();
}
