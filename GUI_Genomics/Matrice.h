#ifndef MATRICE_H
#define MATRICE_H

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cmath>

#include "MatrixWriter.h"

/*! On part sur l'idee que la classe FastaReader et LinksFile gère les exceptions suivnates :
 * - le nucleotide est non existant (different du enum type {A, T, C, G}
 * - la position n'existe pas dans le genome
 * - la position correspond a un endroit ou la sequence ne peut pas être calculée
 * */


 enum Nucleotide {A, T, C, G};
 /*! Ces nucleotides permettent de referencer les acides amines du code genomique, mais aussi les colonnes du array de tab_matrice */

class Matrice {


/*! Tableau bi-dimensionnel pour représenter la matrice : un vector (donc dont la taille peut etre variable)
 *  													  contenant des array de 4 (le nombre de nucleotides differents)*/
private :
Matrix tab_matrice;
std::vector<std::string> list_seq;
size_t L;

public :

Matrice(std::vector<std::string> sequences,size_t l);
/*! Constructeur
 * initialise list_seq avec les séquences d'intérêt trouver par FastaReader
 * @param [in] sequences std::vector<std::string> qui comprend toutes les séquences que l'ont veut considérer dans la matrice
 * @param [in] l size_t correspondant à la taille de la séquence que l'ont veut analyser
 * */

void initialize();
/*! Initialise la matrice
 * Se fait en trois etapes :
 * [- appelle a la fonction FastaReader et recupération de la liste de sequence d'interet, qu on stockera ici dans une variable intermediare list_seq pour
 *   pouvoir y acceder plus tard ]
 * - Pour chacune de ces séquences de la liste :
 * 			-> lire nucleotide par nucleotide et incrémenter tab_matrice en correspondance [fonction : void lire_seq (std::string seq)]
 * - Calcucler les probabilités [fonction void CalculProba (std::vector<std::array>>)]
 * @throw std::logic_error La liste de séquence à traiter est vide
 */


void decoupage(std::vector<std::string>& listeSeq);
/*! Découpe toutes les séquences trop longues par rapport à la taille du motif
 * 	et ajoute les séquences découpées au vecteur de séquences à analyser
 * 	@param [in] listeSeq vecteur des séquences à analyser
* */

void CalculProbaMatrice ();
 /*! Parcourir tab_matrice, pour chaque ligne (p est le numero de la ligne) appeler [void CaclculProbasPosition (double p, double list_seq.size())]
  * Une fois qu'elle est totalement calculee, si exeption_zero_proba alors rediviser chaque probabilite de chaque nucleotide de chaque ligne par 8
*/

 void lire_seq (std::vector<std::string> seq, double incr = 1);
 /*! parcourt la sequence seq et pour chaque nucleotide, met a jour tab_matrice avec la fonction :  void incrementer (Nuceoltide N)
  * @param [in] incr valeur à incrémenter dans la matrice en fonction de la taille de la séquence (si elle est de la bonne taille, la
  * valeur incrémentée est 1, si elle a un nucléotide de trop, la valeur incrémentée est 0.5, ..., si elle est n nucléotides de trop,
  * la valeur incrémentée est (1/(n+1))
  * */


 void incrementer (Nucleotide N, size_t placeNucleotide, double incr);
 /*! doit incrementer tab_matrice avec le nucleotide N au nucléotide à l'emplacement placeNucleotide de la séquence
  * - creation d une nouvelle ligne (push_back) dans le vector de tab_matrice lorsque c est la premiere sequence lue, sinon parcourt du vector
  * - switch pour choisir quelle colonne incrementer en fonction de la nature de N (utilisation type enumere)
  * @param [in] N Nucleotide position dans le array
  * @param [in] placeNucleotide size_t qui détermine la ligne à laquelle on doit incrémenter
  * @param [in] incr valeur à incrémenter dans la matrice en fonction de la taille de la séquence (si elle est de la bonne taille, la
  * valeur incrémentée est 1, si elle a un nucléotide de trop, la valeur incrémentée est 0.5, ..., si elle est n nucléotides de trop,
  * la valeur incrémentée est (1/(n+1))
  * Ici on incremente physiquement avec +1, on ne calcule les probabilités que a lorsque la matrice est completement remplie*/

void create_file_matrice();
/*! Appelle la fonction create_file de MatrixWriter pour créer un fichier de lequel
 * la matrice sera affichée
 * */
};

#endif
