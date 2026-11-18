#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void keep_green_only(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {

            image.pixel(x, y).b = 0.f;
            image.pixel(x, y).r = 0.f;
        }
    }
}

void channels_swap(sil::Image &image) // Prend l'image par référence pour pouvoir la modifier
{
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            std::swap(image.pixel(x, y).g, image.pixel(x, y).r);
        }
    }
}

float max_component(glm::vec3 color)
{
    if (color.x > color.y)
    {
        if (color.x > color.z)
        {
            return (color.x);
        }
        else
        {
            return (color.z);
        }
    }
    else if (color.y > color.z)
    {
        return (color.y);
    }
    else
    {
        return (color.z);
    }
}

void black_white(sil::Image &image)
{
    glm::vec3 white{1, 1, 1};
    glm::vec3 black{0, 0, 0};
    glm::vec3 green{0, 1, 0};
    glm::vec3 red{1, 0, 0};
    glm::vec3 blue{0, 0, 1};

    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            // std::swap(image.pixel(x, y).b, image.pixel(x, y) = white);
            if (image.pixel(x, y) != black)
            {
                float plus_grand = max_component(image.pixel(x, y));
                image.pixel(x, y) = glm::vec3{plus_grand, plus_grand, plus_grand};
            }
        }
    }
}

void negatif(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            float a = 1 - image.pixel(x, y).x;
            float b = 1 - image.pixel(x, y).y;
            float c = 1 - image.pixel(x, y).z;
            image.pixel(x, y) = glm::vec3{a, b, c};
        }
    }
}

void degrade(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3{1 - (x * 0.0025), 1 - (x * 0.0025), 1 - (x * 0.0025)};
        }
    }
}

void miroir(sil::Image &image)
{
    sil::Image copie{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            copie.pixel(x, y) = image.pixel(image.width() - 1 - x, y);
        }
    }
    image = copie;
}

void bruit(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int X = random_int(0, 4);
            if (X == 0)
            {
                float a = random_float(0, 1);
                float b = random_float(0, 1);
                float c = random_float(0, 1);
                image.pixel(x, y) = glm::vec3{a, b, c};
            }
        }
    }
}

void rotation(sil::Image &image)
{
    sil::Image copie{image.height(), image.width()};
    for (int x{0}; x < copie.width(); x++)
    {
        for (int y{0}; y < copie.height(); y++)
        {
            copie.pixel(x, y) = image.pixel(y, image.height() - 1 - x);
        }
    }
    image = copie;
}

void splitfaux(sil::Image &image)
{
    glm::vec3 black{0, 0, 0};
    sil::Image copie{image.width() + 40, image.height()};
    for (int x{20}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (image.pixel(x, y) != black)
            {
                copie.pixel(x + 20, y) = image.pixel(x, y);
                copie.pixel(x - 20, y) = image.pixel(x, y);
                copie.pixel(x, y) = image.pixel(x, y);
                copie.pixel(x + 20, y).b = 0.f;
                copie.pixel(x + 20, y).g = 0.f;
                copie.pixel(x - 20, y).g = 0.f;
                copie.pixel(x - 5, y).r = 0.f;
                copie.pixel(x, y).b = 0.f;
                copie.pixel(x, y).r = 0.f;
            }
        }
    }
    image = copie;
}

void split(sil::Image &image)
{
    glm::vec3 black{0, 0, 0};
    sil::Image copie{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (image.pixel(x, y) != black)
            {
                copie.pixel(x, y).g = image.pixel(x, y).g;

                if (x + 20 < copie.width())
                {
                    copie.pixel(x + 20, y).r = image.pixel(x, y).r;
                }

                if (x - 20 >= 0)
                {
                    copie.pixel(x - 20, y).b = image.pixel(x, y).b;
                }
            }
        }
    }
    image = copie;
}

float aug(glm::vec3 color)
{
    float a = color.x;
    float A = std::pow(a, 2);
    return (A);
}

float aug2(glm::vec3 color)
{
    float b = color.y;
    float B = std::pow(b, 2);
    return (B);
}

float aug3(glm::vec3 color)
{
    float c = color.z;
    float C = std::pow(c, 2);
    return (C);
}

void eclair(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3{aug(image.pixel(x, y)), aug2(image.pixel(x, y)), aug3(image.pixel(x, y))};
        }
    }
}

void rond2(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (y == 250)
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
                if (y + x < image.height())
                {
                    image.pixel(x, y + x) = glm::vec3{1, 1, 1};
                }
                if (y + x < image.height())
                {
                    image.pixel(x, y - x) = glm::vec3{1, 1, 1};
                }
                if (x > 250)
                {
                }
            }
        }
    }
}

void rond(sil::Image &image)
{
    int centre_x = 250;
    int centre_y = 250;
    int rayon = 250;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow(x - centre_x, 2) + pow(y - centre_y, 2) < pow(rayon, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
}

void rondp(sil::Image &image)
{
    int centre_x = 250;
    int centre_y = 250;
    int rayon = 250;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow(x - centre_x, 2) + pow(y - centre_y, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x, 2) + pow(y - centre_y, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
}

void gif(sil::Image &image, int centre_x, int centre_y, int rayon)
{
    sil::Image copie{image.width(), image.height()};
    for (int x{0}; x < copie.width(); x++)
    {
        for (int y{0}; y < copie.height(); y++)
        {
            if ((pow(x - centre_x, 2) + pow(y - centre_y, 2) < pow(rayon, 2)))
            {
                copie.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
    image = copie;
}

void rosace(sil::Image &image)
{
    int centre_xc = 250;
    int centre_yc = 250;

    int centre_x = 200;
    int centre_x1 = 150;
    int centre_x2 = 200;
    int centre_x3 = 300;
    int centre_x4 = 350;
    int centre_x5 = 300;
    int centre_y = 335;
    int centre_y1 = 250;
    int centre_y2 = 165;
    int centre_y3 = 165;
    int centre_y4 = 250;
    int centre_y5 = 335;
    int rayon = 100;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow(x - centre_x, 2) + pow(y - centre_y, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x, 2) + pow(y - centre_y, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            if ((pow(x - centre_x1, 2) + pow(y - centre_y1, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x1, 2) + pow(y - centre_y1, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            if ((pow(x - centre_x2, 2) + pow(y - centre_y2, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x2, 2) + pow(y - centre_y2, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            if ((pow(x - centre_x3, 2) + pow(y - centre_y3, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x3, 2) + pow(y - centre_y3, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            if ((pow(x - centre_x4, 2) + pow(y - centre_y4, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x4, 2) + pow(y - centre_y4, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            if ((pow(x - centre_x5, 2) + pow(y - centre_y5, 2) < pow(rayon + 5, 2)) && (pow(x - centre_x5, 2) + pow(y - centre_y5, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            if ((pow(x - centre_xc, 2) + pow(y - centre_yc, 2) < pow(rayon + 5, 2)) && (pow(x - centre_xc, 2) + pow(y - centre_yc, 2) > pow(rayon - 5, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
}

void mosa(sil::Image &image)
{
    sil::Image copie{image.width() * 5, image.height() * 5};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int a{0}; a < 5; a++)
            {
                for (int b{0}; b < 5; b++)
                {
                    copie.pixel(x + a * image.width(), y + b * image.height()) = image.pixel(x, y);
                }
            }
        }
    }
    image = copie;
}

void mosam(sil::Image &image)
{
    sil::Image copie{image.width() * 5, image.height() * 5};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int a{0}; a < 5; a += 2)
            {
                for (int b{0}; b < 5; b += 2)
                {
                    copie.pixel(x + a * image.width(), y + b * image.height()) = image.pixel(x, y);
                }
            }
        }
    }
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int a{1}; a < 5; a += 2)
            {
                for (int b{0}; b < 5; b += 2)
                {
                    copie.pixel(x + a * image.width(), y + b * image.height()) = image.pixel(image.width() - 1 - x, y);
                }
            }
        }
    }
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int a{1}; a < 5; a += 2)
            {
                for (int b{1}; b < 5; b += 2)
                {
                    copie.pixel(x + a * image.width(), y + b * image.height()) = image.pixel(image.width() - 1 - x, image.height() - 1 - y);
                    ;
                }
            }
        }
    }
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            for (int a{0}; a < 5; a += 2)
            {
                for (int b{1}; b < 5; b += 2)
                {
                    copie.pixel(x + a * image.width(), y + b * image.height()) = image.pixel(x, image.height() - 1 - y);
                }
            }
        }
    }
    image = copie;
}

void glitch(sil::Image &image)
{
    for (int a{0}; a < 100; a++)
    {
        int H = random_int(1, 50);
        int W = random_int(1, 50);

        int X = random_int(1, 736 - W);
        int Y = random_int(1, 488 - H);
        int Xp = random_int(1, 736 - W);
        int Yp = random_int(1, 488 - H);

        for (int a{0}; a < W; a++)
        {
            for (int b{0}; b < H; b++)
            {
                image.pixel(X + a, Y + b) = image.pixel(Xp + a, Yp + b);
            }
        }
    }
}

float somme_couleur(glm::vec3 color)
{
    int somme = color.x + color.y + color.z;
    return (somme);
}

void tri_w(sil::Image &image)
{
    for (int y{0}; y < image.height(); y++)
    {
        std::vector<int> tableau_couleur;
        for (int x{0}; x < image.width() - 1; x++)
        {

            for (int i{x}; i >= 0 && somme_couleur(image.pixel(i, y)) > somme_couleur(image.pixel(i + 1, y)); i--)
            {
                std::swap(image.pixel(i, y), image.pixel(i + 1, y));
            }
        }
    }
}

void tri(sil::Image &image)
{
    tri_w(image);
    for (int x{0}; x < image.width(); x++)
    {
        std::vector<int> tableau_couleur;
        for (int y{0}; y < image.height() - 1; y++)
        {

            for (int i{y}; i >= 0 && somme_couleur(image.pixel(x, i)) > somme_couleur(image.pixel(x, i + 1)); i--)
            {
                std::swap(image.pixel(x, i), image.pixel(x, i + 1));
            }
        }
    }
}

glm::vec3 calcul_distance(std::vector<glm::vec3> table)
{
    if (table.empty())
    {
        return glm::vec3{0.f};
    }
    else
    {
        glm::vec3 somme{0};
        for (std::size_t i{0}; i < table.size(); i++)
        {
            somme += table[i];
        }
        float table_size{static_cast<float>(table.size())};
        glm::vec3 moyenne = somme / table_size;
        return moyenne;
    }
}

void k_means(sil::Image &image)
{
    // genere aléatoirement des pixels de départ pour faire des groupes autour
    std::vector<glm::vec3> table_pixels;
    for (int a{0}; a < 10; a++)
    {
        int Y = random_int(0, image.height() - 1);
        int X = random_int(0, image.width() - 1);

        table_pixels.push_back(image.pixel(X, Y));
    }
    // tableaux pour mettre les vecteurs
    std::vector<glm::vec3> groupe1;
    std::vector<glm::vec3> groupe2;
    std::vector<glm::vec3> groupe3;
    std::vector<glm::vec3> groupe4;
    std::vector<glm::vec3> groupe5;
    std::vector<glm::vec3> groupe6;
    std::vector<glm::vec3> groupe7;
    std::vector<glm::vec3> groupe8;
    std::vector<glm::vec3> groupe9;
    std::vector<glm::vec3> groupe10;
    for (int a{0}; a < 15; a++)
    {
        groupe1.clear();
        groupe2.clear();
        groupe3.clear();
        groupe4.clear();
        groupe5.clear();
        groupe6.clear();
        groupe7.clear();
        groupe8.clear();
        groupe9.clear();
        groupe10.clear();
        // on fait tous les groupes pixel par pixel
        for (int x{0}; x < image.width(); x++)
        {

            for (int y{0}; y < image.height(); y++)
            {
                // on calcul la distance du pixel par rappot au 3 pixels de référence
                std::vector<float> table_distance;
                for (std::size_t i{0}; i < table_pixels.size(); i++)
                {
                    glm::vec3 color1{table_pixels[i]};

                    glm::vec3 colora{image.pixel(x, y)};

                    table_distance.push_back(glm::distance(color1, colora));
                }
                // on compart les distance par rapport aux 3 pixels de référence pour les mettre dans les groupes correspondants
                if (table_distance[0] <= table_distance[1] && table_distance[0] <= table_distance[2] && table_distance[0] <= table_distance[3]&& table_distance[0] <= table_distance[4]&& table_distance[0] <= table_distance[5]&& table_distance[0] <= table_distance[6]&& table_distance[0] <= table_distance[7]&& table_distance[0] <= table_distance[8]&& table_distance[0] <= table_distance[9])
                {
                    groupe1.push_back(image.pixel(x, y));
                }
                else if (table_distance[1] <= table_distance[0] && table_distance[1] <= table_distance[2] && table_distance[1] <= table_distance[3]&& table_distance[1] <= table_distance[4]&& table_distance[1] <= table_distance[5]&& table_distance[1] <= table_distance[6]&& table_distance[1] <= table_distance[7]&& table_distance[1] <= table_distance[8]&& table_distance[1] <= table_distance[9])
                {
                    groupe2.push_back(image.pixel(x, y));
                }
                else if (table_distance[2] <= table_distance[1] && table_distance[2] <= table_distance[0] && table_distance[2] <= table_distance[3]&& table_distance[2] <= table_distance[4]&& table_distance[2] <= table_distance[5]&& table_distance[2] <= table_distance[6]&& table_distance[2] <= table_distance[7]&& table_distance[2] <= table_distance[8]&& table_distance[2] <= table_distance[9])
                {
                    groupe3.push_back(image.pixel(x, y));
                }
                else if (table_distance[3] <= table_distance[0] && table_distance[3] <= table_distance[1] && table_distance[3] <= table_distance[2]&& table_distance[3] <= table_distance[4]&& table_distance[3] <= table_distance[5]&& table_distance[3] <= table_distance[6]&& table_distance[3] <= table_distance[7]&& table_distance[3] <= table_distance[8]&& table_distance[3] <= table_distance[9])
                {
                    groupe4.push_back(image.pixel(x, y));
                }
                else if (table_distance[4] <= table_distance[0] && table_distance[4] <= table_distance[1] && table_distance[4] <= table_distance[2]&& table_distance[4] <= table_distance[3]&& table_distance[4] <= table_distance[5]&& table_distance[4] <= table_distance[6]&& table_distance[4] <= table_distance[7]&& table_distance[4] <= table_distance[8]&& table_distance[4] <= table_distance[9])
                {
                    groupe5.push_back(image.pixel(x, y));
                }
                else if (table_distance[5] <= table_distance[0] && table_distance[5] <= table_distance[1] && table_distance[5] <= table_distance[2]&& table_distance[5] <= table_distance[4]&& table_distance[5] <= table_distance[3]&& table_distance[5] <= table_distance[6]&& table_distance[5] <= table_distance[7]&& table_distance[5] <= table_distance[8]&& table_distance[5] <= table_distance[9])
                {
                    groupe6.push_back(image.pixel(x, y));
                }
                else if (table_distance[6] <= table_distance[0] && table_distance[6] <= table_distance[1] && table_distance[6] <= table_distance[2]&& table_distance[6] <= table_distance[4]&& table_distance[6] <= table_distance[5]&& table_distance[6] <= table_distance[3]&& table_distance[6] <= table_distance[7]&& table_distance[6] <= table_distance[8]&& table_distance[6] <= table_distance[9])
                {
                    groupe7.push_back(image.pixel(x, y));
                }
                else if (table_distance[7] <= table_distance[0] && table_distance[7] <= table_distance[1] && table_distance[7] <= table_distance[2]&& table_distance[7] <= table_distance[4]&& table_distance[7] <= table_distance[5]&& table_distance[7] <= table_distance[6]&& table_distance[7] <= table_distance[3]&& table_distance[7] <= table_distance[8]&& table_distance[7] <= table_distance[9])
                {
                    groupe8.push_back(image.pixel(x, y));
                }
                else if (table_distance[8] <= table_distance[0] && table_distance[8] <= table_distance[1] && table_distance[8] <= table_distance[2]&& table_distance[3] <= table_distance[4]&& table_distance[3] <= table_distance[5]&& table_distance[8] <= table_distance[6]&& table_distance[8] <= table_distance[7]&& table_distance[8] <= table_distance[3]&& table_distance[8] <= table_distance[9])
                {
                    groupe9.push_back(image.pixel(x, y));
                }
                else
                {
                    groupe10.push_back(image.pixel(x, y));
                }
            }
        }

        // on a notre première division on doit déplacer le pixel de référence au centre du groupe
        glm::vec3 moyenne_1 = calcul_distance(groupe1);
        glm::vec3 moyenne_2 = calcul_distance(groupe2);
        glm::vec3 moyenne_3 = calcul_distance(groupe3);
        glm::vec3 moyenne_4 = calcul_distance(groupe4);
        glm::vec3 moyenne_5 = calcul_distance(groupe5);
        glm::vec3 moyenne_6 = calcul_distance(groupe6);
        glm::vec3 moyenne_7 = calcul_distance(groupe7);
        glm::vec3 moyenne_8 = calcul_distance(groupe8);
        glm::vec3 moyenne_9 = calcul_distance(groupe9);
        glm::vec3 moyenne_10 = calcul_distance(groupe10);

        table_pixels[0] = moyenne_1;
        table_pixels[1] = moyenne_2;
        table_pixels[2] = moyenne_3;
        table_pixels[3] = moyenne_4;
        table_pixels[4] = moyenne_5;
        table_pixels[5] = moyenne_6;
        table_pixels[6] = moyenne_7;
        table_pixels[7] = moyenne_8;
        table_pixels[8] = moyenne_9;
        table_pixels[9] = moyenne_10;
    }
    // on a finit les groupes, on passe maintenant par tous les pixels pour que les groupes soient tous de la même couleur
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            std::vector<float> distance_fin;
            for (std::size_t i{0}; i < table_pixels.size(); i++)
            {
                glm::vec3 color1{table_pixels[i]};

                glm::vec3 colora{image.pixel(x, y)};

                distance_fin.push_back(glm::distance(color1, colora));
            }
                if (distance_fin[0] <= distance_fin[1] && distance_fin[0] <= distance_fin[2] && distance_fin[0] <= distance_fin[3]&& distance_fin[0] <= distance_fin[4]&& distance_fin[0] <= distance_fin[5]&& distance_fin[0] <= distance_fin[6]&& distance_fin[0] <= distance_fin[7]&& distance_fin[0] <= distance_fin[8]&& distance_fin[0] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[0];
                }
                else if (distance_fin[1] <= distance_fin[0] && distance_fin[1] <= distance_fin[2] && distance_fin[1] <= distance_fin[3]&& distance_fin[1] <= distance_fin[4]&& distance_fin[1] <= distance_fin[5]&& distance_fin[1] <= distance_fin[6]&& distance_fin[1] <= distance_fin[7]&& distance_fin[1] <= distance_fin[8]&& distance_fin[1] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[1];
                }
                else if (distance_fin[2] <= distance_fin[1] && distance_fin[2] <= distance_fin[0] && distance_fin[2] <= distance_fin[3]&& distance_fin[2] <= distance_fin[4]&& distance_fin[2] <= distance_fin[5]&& distance_fin[2] <= distance_fin[6]&& distance_fin[2] <= distance_fin[7]&& distance_fin[2] <= distance_fin[8]&& distance_fin[2] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[2];
                }
                else if (distance_fin[3] <= distance_fin[0] && distance_fin[3] <= distance_fin[1] && distance_fin[3] <= distance_fin[2]&& distance_fin[3] <= distance_fin[4]&& distance_fin[3] <= distance_fin[5]&& distance_fin[3] <= distance_fin[6]&& distance_fin[3] <= distance_fin[7]&& distance_fin[3] <= distance_fin[8]&& distance_fin[3] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[3];
                }
                else if (distance_fin[4] <= distance_fin[0] && distance_fin[4] <= distance_fin[1] && distance_fin[4] <= distance_fin[2]&& distance_fin[4] <= distance_fin[3]&& distance_fin[4] <= distance_fin[5]&& distance_fin[4] <= distance_fin[6]&& distance_fin[4] <= distance_fin[7]&& distance_fin[4] <= distance_fin[8]&& distance_fin[4] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[4];
                }
                else if (distance_fin[5] <= distance_fin[0] && distance_fin[5] <= distance_fin[1] && distance_fin[5] <= distance_fin[2]&& distance_fin[5] <= distance_fin[4]&& distance_fin[5] <= distance_fin[3]&& distance_fin[5] <= distance_fin[6]&& distance_fin[5] <= distance_fin[7]&& distance_fin[5] <= distance_fin[8]&& distance_fin[5] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[5];
                }
                else if (distance_fin[6] <= distance_fin[0] && distance_fin[6] <= distance_fin[1] && distance_fin[6] <= distance_fin[2]&& distance_fin[6] <= distance_fin[4]&& distance_fin[6] <= distance_fin[5]&& distance_fin[6] <= distance_fin[3]&& distance_fin[6] <= distance_fin[7]&& distance_fin[6] <= distance_fin[8]&& distance_fin[6] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[6];
                }
                else if (distance_fin[7] <= distance_fin[0] && distance_fin[7] <= distance_fin[1] && distance_fin[7] <= distance_fin[2]&& distance_fin[7] <= distance_fin[4]&& distance_fin[7] <= distance_fin[5]&& distance_fin[7] <= distance_fin[6]&& distance_fin[7] <= distance_fin[3]&& distance_fin[7] <= distance_fin[8]&& distance_fin[7] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[7];
                }
                else if (distance_fin[8] <= distance_fin[0] && distance_fin[8] <= distance_fin[1] && distance_fin[8] <= distance_fin[2]&& distance_fin[3] <= distance_fin[4]&& distance_fin[3] <= distance_fin[5]&& distance_fin[8] <= distance_fin[6]&& distance_fin[8] <= distance_fin[7]&& distance_fin[8] <= distance_fin[3]&& distance_fin[8] <= distance_fin[9])
                {
                    image.pixel(x, y) = table_pixels[8];
                }
                else
                {
                    image.pixel(x, y) = table_pixels[9];
                }
            }
        }
    }

int main()
{
    // 736, 488
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      keep_green_only(image);                            // Utilise la fonction pour modifier l'image
    //      image.save("output/keep_green_only.png");          // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      channels_swap(image);                              // Utilise la fonction pour modifier l'image
    //      image.save("output/channels_swap.png");            // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      black_white(image);                                // Utilise la fonction pour modifier l'image
    //      image.save("output/black_white.png");              // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      negatif(image);                                    // Utilise la fonction pour modifier l'image
    //      image.save("output/negatif.png");                  // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{400 /*width*/, 200 /*height*/}; // Lis l'image
    //      degrade(image);                                  // Utilise la fonction pour modifier l'image
    //      image.save("output/degrade.png");                // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      miroir(image);                                     // Utilise la fonction pour modifier l'image
    //      image.save("output/miroir.png");                   // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      bruit(image);                                      // Utilise la fonction pour modifier l'image
    //      image.save("output/bruit.png");                    // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      rotation(image);                                   // Utilise la fonction pour modifier l'image
    //      image.save("output/rotation.png");                 // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      splitfaux(image);                                  // Utilise la fonction pour modifier l'image
    //      image.save("output/splitfaux.png");                // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      split(image);                                      // Utilise la fonction pour modifier l'image
    //      image.save("output/split.png");                    // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      eclair(image);                                     // Utilise la fonction pour modifier l'image
    //      image.save("output/eclair.png");                   // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
    //      rond(image);                                     // Utilise la fonction pour modifier l'image
    //      image.save("output/rond.png");                   // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
    //      rondp(image);                                    // Utilise la fonction pour modifier l'image
    //      image.save("output/rondp.png");                  // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{500, 500};
    //      int r{0};
    //      int i{0};
    //      int centre_x = 0;
    //      int centre_y = 250;
    //      int rayon = 25;
    //      for (r = 0; r < 19; r++)
    //      {
    //          centre_x = centre_x + 25;
    //          gif(image, centre_x, centre_y, rayon);
    //          // std::string nomfichier = std::vector{"1", "2", "3", "4" , "19"}[r];
    //          std::string nomfichier = std::to_string(r);
    //          image.save("output/gif/" + nomfichier + ".png");
    //      }
    //  }
    //  {
    //      sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
    //      rosace(image);                                   // Utilise la fonction pour modifier l'image
    //      image.save("output/rosace.png");
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      mosa(image);                                       // Utilise la fonction pour modifier l'image
    //      image.save("output/mosa.png");                     // Sauvegarde l'image
    //  }
    //  {
    //      sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //      mosam(image);                                      // Utilise la fonction pour modifier l'image
    //      image.save("output/mosam.png");                    // Sauvegarde l'image
    //  }
    // {
    //     sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //     glitch(image);                                     // Utilise la fonction pour modifier l'image
    //     image.save("output/glitch.png");                   // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //     tri(image);                                        // Utilise la fonction pour modifier l'image
    //     image.save("output/tri.png");                      // Sauvegarde l'image
    // }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        k_means(image);                                    // Utilise la fonction pour modifier l'image
        image.save("output/kmeans.png");                   // Sauvegarde l'image
    }
}
