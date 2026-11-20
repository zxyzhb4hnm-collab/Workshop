#include <sil/sil.hpp>
#include "random.hpp"

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
}
