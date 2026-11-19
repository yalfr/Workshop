#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <complex>

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
    int rayon = 50;
    float pi = 3.14159265f;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow(x - centre_xc, 2) + pow(y - centre_yc, 2) < pow(rayon + 2, 2)) && (pow(x - centre_xc, 2) + pow(y - centre_yc, 2) > pow(rayon - 2, 2)))
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
            for (float angle = 0; angle < 2 * pi; angle += 2 * pi / 6)
            {
                float centre_x = centre_xc + rayon * std::cos(angle);
                float centre_y = centre_yc + rayon * std::sin(angle);

                if ((pow(x - centre_x, 2) + pow(y - centre_y, 2) < pow(rayon + 2, 2)) && (pow(x - centre_x, 2) + pow(y - centre_y, 2) > pow(rayon - 2, 2)))
                {
                    image.pixel(x, y) = glm::vec3{1, 1, 1};
                }
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
            for (int a{0}; a < 5; a++)
            {
                for (int b{0}; b < 5; b++)
                {
                    // on definit les calculs nécéssaires pour inverser une image
                    int x_inv;
                    int y_inv;

                    // si a est paire on a pas besoin d'inverse sinon si
                    if (a % 2 == 0)
                    {
                        x_inv = x;
                    }
                    else
                    {
                        x_inv = image.width() - 1 - x;
                    }

                    // si b est paire on a pas besoin d'inverser sinon si
                    if (b % 2 == 0)
                    {
                        y_inv = y;
                    }
                    else
                    {
                        y_inv = image.height() - 1 - y;
                    }

                    copie.pixel(x + a * image.width(), y + b * image.height()) = image.pixel(x_inv, y_inv);
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
    float somme = color.x + color.y + color.z;
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
        for (int y{0}; y < image.height(); y++)
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

sil::Image k_means(sil::Image &image)
{
    // genere aléatoirement des pixels de départ pour faire des groupes autour
    int nb_couleurs = 10;
    std::vector<glm::vec3> table_pixels;
    for (int a{0}; a < nb_couleurs; a++)
    {
        int Y = random_int(0, image.height() - 1);
        int X = random_int(0, image.width() - 1);

        table_pixels.push_back(image.pixel(X, Y));
    }
    // tableau de 10 tableaux/groupes pour mettre des pixels dans chaque groupe après pour mettre les vecteurs
    std::vector<std::vector<glm::vec3>> groupes(nb_couleurs);
    for (int a{0}; a < 5; a++)
    {
        for (int i{0}; i < nb_couleurs; i++)
        {
            groupes[i].clear();
        }
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
                int indice = 0;
                for (int i{1}; i < nb_couleurs; i++)
                {
                    if (table_distance[i] < table_distance[indice])
                    {
                        indice = i;
                    }
                }
                groupes[indice].push_back(image.pixel(x, y));
            }
        }

        // on a notre première division on doit déplacer le pixel de référence au centre du groupe
        // calcul de la moyenne
        for (int i{0}; i < nb_couleurs; i++)
        {
            table_pixels[i] = calcul_distance(groupes[i]);
        }
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
            // même boucle que avant pour éviter de faire des if, else à rallonge
            int indice = 0;
            for (int i{1}; i < nb_couleurs; i++)
            {
                if (distance_fin[i] < distance_fin[indice])
                {
                    indice = i;
                }
            }

            image.pixel(x, y) = table_pixels[indice];
        }
    }
    return image;
}

int kmeans_compatibilite_calcul(sil::Image &image)
{
    sil::Image n_image1 = k_means(image);

    int nb_couleurs = 10;

    std::vector<std::vector<glm::vec3>> groupes(nb_couleurs);

    std::vector<glm::vec3> couleurs_autre;

    glm::vec3 new_depart{n_image1.pixel(0, 0)};
    for (int i{0}; i < nb_couleurs; i++)
    {
        couleurs_autre.push_back(new_depart);

        bool prochaine_couleur = false;

        glm::vec3 new_depart2{0};
        for (int x{0}; x < n_image1.width(); x++)
        {
            for (int y{0}; y < n_image1.height(); y++)
            {
                if (glm::vec3{n_image1.pixel(x, y)} == new_depart)
                {
                    groupes[i].push_back(n_image1.pixel(x, y));
                }
                else if (!prochaine_couleur)
                {
                    bool prise = false;
                    for (std::size_t k{0}; k < couleurs_autre.size(); k++)
                    {
                        if (n_image1.pixel(x, y) == couleurs_autre[k])
                        {
                            prise = true;
                            break;
                        }
                    }
                    if (!prise)
                    {
                        new_depart2 = n_image1.pixel(x, y);
                        prochaine_couleur = true;
                    }
                }
            }
        }

        if (!prochaine_couleur)
        {
            break;
        }
        new_depart = new_depart2;
    }
    int nb_couleur{0};
    std::vector<float> table_couleurs;
    for (int a{0}; a < nb_couleurs; a++)
    {
        if (!groupes[a].empty()) // Sécurité si l'image a moins de 10 couleurs
        {
            int nombre_reccurence{0};

            for (std::size_t i{0}; i < groupes[a].size(); i++)
            {

                nombre_reccurence++;
            }
            float somme = somme_couleur(groupes[a][0]);
            nb_couleur = nombre_reccurence * somme;
            table_couleurs.push_back(nb_couleur);
        }
    }
    int somme_finale{0};
    for (std::size_t i{0}; i < table_couleurs.size(); i++)
    {

        somme_finale += table_couleurs[i];
    }
    return somme_finale;
}
int kmeans_compatibilite(int a, int b)
{
    int difference{0};

    if (a < b)
    {
        difference = b - a;
    }
    else
    {
        difference = a - b;
    }
    return difference;
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void vortex(sil::Image &image)
{
    sil::Image copie{image.width(), image.height()};
    float pi = 3.14159265f;
    glm::vec2 centre_of_rotation = {368, 244};
    float angle = 4 * pi;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 position{x, y};

            float distance = glm::distance(position, centre_of_rotation);
            // plus on s'éloigne moins ça bouge, donc fonction exp inversé par rapport à la distance par rapport au centre
            float coulee = angle * std::exp(-distance / 488);

            glm::vec2 position_d = rotated(position, centre_of_rotation, -coulee);
            int V = position_d.x;
            int W = position_d.y;

            // il ne faut pas que ça dépasse de l'image

            if (V >= 0 && V < image.width() && W >= 0 && W < image.height())
            {

                copie.pixel(x, y) = image.pixel(V, W);
            }
        }
    }
    image = copie;
}

void convultion(sil::Image &image)
{
    sil::Image copie{image.width(), image.height()};
    std::vector<glm::vec3> tableau_cube;
    for (int x{0}; x < image.width(); x++)
    {
        tableau_cube.clear();
        for (int y{0}; y < image.height(); y++)
        {
            if ((x + 1) < image.width() && (x - 1) > 0)
            {
                if ((y + 1) < image.height() && (y - 1) > 0)
                {
                    tableau_cube.push_back(image.pixel(x, y));
                    tableau_cube.push_back(image.pixel(x - 1, y - 1));
                    tableau_cube.push_back(image.pixel(x, y - 1));
                    tableau_cube.push_back(image.pixel(x + 1, y - 1));
                    tableau_cube.push_back(image.pixel(x + 1, y));
                    tableau_cube.push_back(image.pixel(x + 1, y + 1));
                    tableau_cube.push_back(image.pixel(x, y + 1));
                    tableau_cube.push_back(image.pixel(x - 1, y + 1));
                    tableau_cube.push_back(image.pixel(x - 1, y));
                }
            }
            glm::vec3 moyenne = calcul_distance(tableau_cube);
            copie.pixel(x, y) = moyenne;
        }
    }
    image = copie;
}

void convolution(sil::Image &image)
{
    sil::Image copie{image.width(), image.height()};
    float flou = 9.f;
    for (int x{1}; x < image.width() - 1; x++)
    {
        for (int y{1}; y < image.height() - 1; y++)
        {
            copie.pixel(x - 1, y - 1) = image.pixel(x, y) / flou + image.pixel(x + 1, y + 1) / flou +
                                        image.pixel(x + 1, y) / flou + image.pixel(x + 1, y - 1) / flou + image.pixel(x, y + 1) / flou +
                                        image.pixel(x, y - 1) / flou + image.pixel(x - 1, y - 1) / flou + image.pixel(x - 1, y) / flou +
                                        image.pixel(x - 1, y + 1) / flou;
        }
    }
    image = copie;
}

sil::Image fractale(sil::Image &image)
{
    std::vector<glm::vec3> repetition_pixel;

    for (int x{1}; x < image.width() - 1; x++)
    {
        for (int y{1}; y < image.height() - 1; y++)
        {
            std::complex<float> z{0, 0};
            std::complex<float> c{x / 200.f - 2, y / 200.f - 1.2};
            int repetition{0};
            for (int a{0}; a < 50; a++)
            {
                if (std::abs(z) < 2)
                {
                    z = z * z + c;
                    repetition++;
                }
                else
                {

                    if (repetition > 50)
                    {
                        image.pixel(x, y) = glm::vec3{0, 0, 0};
                    }
                    else if (repetition > 30 && repetition < 40)
                    {
                        image.pixel(x, y) = glm::vec3{0, 0, 0};
                    }
                    else if (repetition > 20 && repetition < 30)
                    {
                        image.pixel(x, y) = glm::vec3{0, 0, 0};
                    }
                    else if (repetition > 10 && repetition < 20)
                    {
                        image.pixel(x, y) = glm::vec3{0, 0, 0};
                    }
                    else if (repetition < 10)
                    {
                        image.pixel(x, y) = glm::vec3{0, 0, 0};
                    }
                    break;
                }
            }
            if (std::abs(z) < 2)
            {
                image.pixel(x, y) = glm::vec3{1, 1, 1};
            }
        }
    }
    return image;
}

sil::Image fractale_ds_image(sil::Image &image, sil::Image &image2)
{
    sil::Image new_image = fractale(image);

    for (int x{0}; x < new_image.width(); x++)
    {
        for (int y{0}; y < new_image.height(); y++)
        {
            if (new_image.pixel(x, y) == glm::vec3{1, 1, 1})
            {
                new_image.pixel(x, y) = image2.pixel(x, y);
            }
        }
    }
    return new_image;
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
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
    //     rosace(image);                                   // Utilise la fonction pour modifier l'image
    //     image.save("output/rosace.png");
    // }
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
    // {
    //     sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //     k_means(image);                                    // Utilise la fonction pour modifier l'image
    //     image.save("output/kmeans.png");                   // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //     vortex(image);                                     // Utilise la fonction pour modifier l'image
    //     image.save("output/vortex.png");                   // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //     convultion(image);                                 // Utilise la fonction pour modifier l'image
    //     image.save("output/convultion.png");               // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
    //     convolution(image);                                // Utilise la fonction pour modifier l'image
    //     image.save("output/convolution.png");              // Sauvegarde l'image
    // }

    // {
    //     sil::Image image{736, 488};
    //     sil::Image image2{"images/Gumball and Darwin.jpg"};
    //     fractale_ds_image(image, image2);
    //     image.save("output/fractale_ds.png");
    // }
    {
        sil::Image image{20, 20};
        sil::Image image2{20, 20};
        std::cout << kmeans_compatibilite(kmeans_compatibilite_calcul(image), kmeans_compatibilite_calcul(image2)) << std::endl;
        ;
    }
}
