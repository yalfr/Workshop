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

sil::Image split(sil::Image &image, int decalage)
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

                if (x + decalage < copie.width())
                {
                    copie.pixel(x + decalage, y).r = image.pixel(x, y).r;
                }

                if (x - decalage >= 0)
                {
                    copie.pixel(x - decalage, y).b = image.pixel(x, y).b;
                }
            }
        }
    }
    image = copie;
    return image;
}

sil::Image split_h(sil::Image &image, int decalage)
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

                if (y + decalage < copie.width())
                {
                    copie.pixel(x, y + decalage).r = image.pixel(x, y).r;
                }

                if (y - decalage >= 0)
                {
                    copie.pixel(x, y - decalage).b = image.pixel(x, y).b;
                }
            }
        }
    }
    image = copie;
    return image;
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

sil::Image glitch(sil::Image &image)
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
                if ((X + a) < image.width() && (Y + b) < image.height() && (Xp + a) < image.width() && (Yp + a) < image.height())
                {
                    image.pixel(X + a, Y + b) = image.pixel(Xp + a, Yp + b);
                }
            }
        }
    }
    return image;
}

float somme_couleur(glm::vec3 color)
{

    float somme = (color.x) + (color.y) + (color.z);
    return (somme);
}

float somme_couleur_kmeans(glm::vec3 color)
{
    // pour que les couleurs soient comprises entre 0 et 7 donc pour que dans le calcul final un bleu pur et un vert pur ne donnent pas le même résultat
    float somme = (color.x * 1.0f) + (color.y * 2.0f) + (color.z * 4.0f);
    return (somme);
}

void tri_w(sil::Image &image)
{
    for (int y{0}; y < image.height(); y++)
    {
        std::vector<int> tableau_couleur;
        for (int x{0}; x < image.width() - 1; x++)
        {
            if (x + 1 < image.width())
            {

                for (int i{x}; i >= 0 && somme_couleur(image.pixel(i, y)) > somme_couleur(image.pixel(i + 1, y)); i--)
                {
                    std::swap(image.pixel(i, y), image.pixel(i + 1, y));
                }
            }
        }
    }
}

sil::Image tri(sil::Image &image)
{
    tri_w(image);
    for (int x{0}; x < image.width(); x++)
    {
        std::vector<int> tableau_couleur;
        for (int y{0}; y < image.height(); y++)
        {
            if (y + 1 < image.height())
            {

                for (int i{y}; i >= 0 && somme_couleur(image.pixel(x, i)) > somme_couleur(image.pixel(x, i + 1)); i--)
                {
                    std::swap(image.pixel(x, i), image.pixel(x, i + 1));
                }
            }
        }
    }
    return image;
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

sil::Image k_means(sil::Image image)
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
// on met tout en float pour ne pas perdre de données
float kmeans_compatibilite_calcul(sil::Image &image)
{
    //on applique k-means
    sil::Image n_image1 = k_means(image);

    int nb_couleurs = 10;
//pour éviter de faire 10 groupes d'un coup 
    std::vector<std::vector<glm::vec3>> groupes(nb_couleurs);

    std::vector<glm::vec3> couleurs_autre;
//parcourir l'image pixel par pixel, on part du premier et si le suivant est différent du premier on le met comme prochaine couleur de depart pour recommencer la boucle et analyser un nouveau groupe
    glm::vec3 new_depart{n_image1.pixel(0, 0)};
    for (int i{0}; i < nb_couleurs; i++)
    {
        //comme ça on réanalyse pas cette couleur de départ
        couleurs_autre.push_back(new_depart);

        bool prochaine_couleur = false;

        glm::vec3 new_depart2{0};
        for (int x{0}; x < n_image1.width(); x++)
        {
            for (int y{0}; y < n_image1.height(); y++)
            {
                //si c'est égal a la couleur du groupe
                if (glm::vec3{n_image1.pixel(x, y)} == new_depart)
                {
                    groupes[i].push_back(n_image1.pixel(x, y));
                }
                //sinon si c'est différent de prochaine couleur
                else if (!prochaine_couleur)
                {
                    bool prise = false;
                    //on parcours toutes les couleurs qu'on a déjà faites
                    for (std::size_t k{0}; k < couleurs_autre.size(); k++)
                    {
                        if (n_image1.pixel(x, y) == couleurs_autre[k])
                        {
                            prise = true;
                            break;
                        }
                    }
                    //si c'est faux on le met en prochaine couleur de départ
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
    std::vector<float> table_couleurs;
    for (int a{0}; a < nb_couleurs; a++)
    {
        if (!groupes[a].empty()) // si moins de 10 couleurs
        {

            float nombre_reccurence = static_cast<float>(groupes[a].size());//on converti car tout est en float
            float somme = somme_couleur_kmeans(groupes[a][0]);//somme pixel par  pixel dans chaque groupe
            table_couleurs.push_back(nombre_reccurence * somme);
        }
    }

    float somme_finale{0};
    for (std::size_t i{0}; i < table_couleurs.size(); i++)
    {

        somme_finale += table_couleurs[i];
    }
    // on divise par le nombre de pixels comme ça deux images de taille différentes donnent un pourcentage représentatif
    float total_pixels = static_cast<float>(n_image1.width() * n_image1.height());
    return somme_finale / total_pixels;
}

float kmeans_compatibilite(float a, float b)
{
    const float valeur_max = 7.0f; //score maximum possible
    float difference = std::abs(a - b);//pour eviter d'avoir une valeur négative 

    // on inverse pour avoir un pourcentage de ressemblance et pas l'inverse, on le met en pourcentage
    //différence/valeur max donne l'écart entre les images
    float compatibilite = (1.0f - (difference / valeur_max)) * 100.0f;
    return compatibilite;
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void vortex(sil::Image &image, float angle)
{
    sil::Image copie{image.width(), image.height()};
    float pi = 3.14159265f;
    glm::vec2 centre_of_rotation = {368, 244};
    angle = angle * pi;
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

sil::Image vortex_inv(sil::Image &image, float angle)
{
    sil::Image copie{image.width(), image.height()};
    float pi = 3.14159265f;
    glm::vec2 centre_of_rotation = {368, 244};
    angle = angle * pi;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            glm::vec2 position{x, y};

            float distance = glm::distance(position, centre_of_rotation);
            // plus on s'éloigne moins ça bouge, donc fonction exp inversé par rapport à la distance par rapport au centre
            float coulee = angle * std::exp(distance / 488);

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
    return image;
}

sil::Image convultion(sil::Image &image, int taille)
{
    sil::Image copie{image.width(), image.height()};
    std::vector<glm::vec3> tableau_cube;
    for (int x{0}; x < image.width(); x++)
    {
        tableau_cube.clear();
        for (int y{0}; y < image.height() / taille; y++)
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
            copie.pixel(x, y) = moyenne * 3.f;
        }
    }
    for (int a{0}; a < taille; a++)
    {
        if (taille != 1 && taille != 0)
        {

            for (int x{0}; x < image.width(); x++)
            {
                tableau_cube.clear();
                for (int y{a * image.height() / taille}; y < image.height(); y++)
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
                    copie.pixel(x, y) = moyenne * 3.f;
                }
            }
        }
    }
    image = copie;
    return image;
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

void convolution_nette(sil::Image &image)
{
    sil::Image copie{image.width(), image.height()};
    for (int x{1}; x < image.width() - 1; x++)
    {
        for (int y{1}; y < image.height() - 1; y++)
        {
            copie.pixel(x - 1, y - 1) = image.pixel(x, y) * 5.f + image.pixel(x + 1, y + 1) * 0.f +
                                        image.pixel(x + 1, y) * -1.f + image.pixel(x + 1, y - 1) * 0.f + image.pixel(x, y + 1) * -1.f +
                                        image.pixel(x, y - 1) * -1.f + image.pixel(x - 1, y - 1) * 0.f + image.pixel(x - 1, y) * -1.f +
                                        image.pixel(x - 1, y + 1) * 0.f;
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

void degrade2(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {

        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = glm::vec3{0 + (x * 0.0025), 1 - (x * 0.0025), 0};
        }
    }
}

int main()
{
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        keep_green_only(image);                            // Utilise la fonction pour modifier l'image
        image.save("output/keep_green_only.png");          // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        channels_swap(image);                              // Utilise la fonction pour modifier l'image
        image.save("output/channels_swap.png");            // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        black_white(image);                                // Utilise la fonction pour modifier l'image
        image.save("output/black_white.png");              // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        negatif(image);                                    // Utilise la fonction pour modifier l'image
        image.save("output/negatif.png");                  // Sauvegarde l'image
    }
    {
        sil::Image image{400 /*width*/, 200 /*height*/}; // Lis l'image
        degrade(image);                                  // Utilise la fonction pour modifier l'image
        image.save("output/degrade.png");                // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        miroir(image);                                     // Utilise la fonction pour modifier l'image
        image.save("output/miroir.png");                   // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        bruit(image);                                      // Utilise la fonction pour modifier l'image
        image.save("output/bruit.png");                    // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        rotation(image);                                   // Utilise la fonction pour modifier l'image
        image.save("output/rotation.png");                 // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        splitfaux(image);                                  // Utilise la fonction pour modifier l'image
        image.save("output/splitfaux.png");                // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        split(image, 30);                                  // Utilise la fonction pour modifier l'image
        image.save("output/split.png");                    // Sauvegarde l'image
    }
    {
        sil::Image image{500, 500}; // Lis l'image
        sil::Image image2 = fractale(image);
        image2 = split_h(image2, 100);
        image2 = convultion(image2, 1);
        image2 = split(image2, 100);
        image2 = tri(image2);

        image2.save("output/split2.png");
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        eclair(image);                                     // Utilise la fonction pour modifier l'image
        image.save("output/eclair.png");                   // Sauvegarde l'image
    }
    {
        sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
        rond(image);                                     // Utilise la fonction pour modifier l'image
        image.save("output/rond.png");                   // Sauvegarde l'image
    }
    {
        sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
        rondp(image);                                    // Utilise la fonction pour modifier l'image
        image.save("output/rondp.png");                  // Sauvegarde l'image
    }
    {
        sil::Image image{500, 500};
        int r{0};
        int i{0};
        int centre_x = 0;
        int centre_y = 250;
        int rayon = 25;
        for (r = 0; r < 19; r++)
        {
            centre_x = centre_x + 25;
            gif(image, centre_x, centre_y, rayon);
            std::string nomfichier = std::to_string(r);
            image.save("output/gif/" + nomfichier + ".png");
        }
    }
    {
        sil::Image image{500 /*width*/, 500 /*height*/}; // Lis l'image
        rosace(image);                                   // Utilise la fonction pour modifier l'image
        image.save("output/rosace.png");
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        mosa(image);                                       // Utilise la fonction pour modifier l'image
        image.save("output/mosa.png");                     // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        mosam(image);                                      // Utilise la fonction pour modifier l'image
        image.save("output/mosam.png");                    // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        glitch(image);                                     // Utilise la fonction pour modifier l'image
        image.save("output/glitch.png");                   // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        tri(image);                                        // Utilise la fonction pour modifier l'image
        image.save("output/tri.png");                      // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        image = k_means(image);                                    // Utilise la fonction pour modifier l'image
        image.save("output/kmeans.png");                   // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        vortex(image, 4);                                  // Utilise la fonction pour modifier l'image
        image.save("output/vortex.png");                   // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        vortex_inv(image, 4);                              // Utilise la fonction pour modifier l'image
        image.save("output/vortex_inverse.png");           // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"};
        image = convultion(image, 1);        // Utilise la fonction pour modifier l'image
        image.save("output/convultion.png"); // Sauvegarde l'image
    }
    {
        sil::Image image1{500 /*width*/, 500 /*height*/};
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        image1 = fractale(image1);
        image1 = split_h(image1, 150);
        image1 = convultion(image1, 3);
        image1 = vortex_inv(image1, 4);  
        image1 = convultion(image1, 3);               // Utilise la fonction pour modifier l'image
        image1.save("output/convultion2.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        convolution(image);                                // Utilise la fonction pour modifier l'image
        image.save("output/convolution.png");              // Sauvegarde l'image
    }

    {
        sil::Image image{"images/logo.png"};
        sil::Image image2{"images/Gumball and Darwin.jpg"};
        std::cout << kmeans_compatibilite(kmeans_compatibilite_calcul(image), kmeans_compatibilite_calcul(image2)) << std::endl;
        ;
    }
    {
        sil::Image image{400 /*width*/, 200 /*height*/}; // Lis l'image
        degrade2(image);                                 // Utilise la fonction pour modifier l'image
        image.save("output/degrade2.png");               // Sauvegarde l'image
    }

    {
        sil::Image image{"images/Gumball and Darwin.jpg"}; // Lis l'image
        convolution_nette(image);                          // Utilise la fonction pour modifier l'image
        image.save("output/convolutionnette.png");         // Sauvegarde l'image
    }
}
