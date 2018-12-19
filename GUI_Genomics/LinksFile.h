#ifndef _LINKS_FILE_
#define _LINKS_FILE_
#include <map>

class LinksFile
{
	public:

	/*! Constructeur
	 * @param [in] Bedfile_name string 2 noms des fichiers BED et fasta fournis pour cette usage
	 * @param [in] length size_t longueur de la séquence dont on veut calculer les probabilités
	 * */
	LinksFile(std::string Bedfile_name, std::string fastafile_name, size_t _length);

	/*! Crée la matrice, cette fonction est appelée dans le main.cpp
	 * @throw std::logic_error Les fonctions à traiter sont vides
	 */
	void creationMatrice();

	size_t getLongueurSequencesATraiter();

	/*! Modifie 2 positions en fonction du signe + ou - dans le BED qui détermine
	 * dans quel sens on lit une séquence*/
	bool modificationPositions(int& a, int& b, bool complementaire);

	/*! Vérifie si une séquence est plus grande que la longueur voulue
	 *  Si on cherche le complémentaire
	 * 	@param [in] a, b int& qui correspondent aux positions à chercher dans le fasta
	 *  @param [in] complementaire bool qui vérifie si on doit chercher le complémentaire de la séquence
	 *  @param [out] bool vérifie si on traite la séquence ou non
	 * */
	bool tooLarge(const std::string& seq);

	private:
	std::string BEDFileName;				///chaîne de caractères contenant le nom du fichier BED contenant les positions à traiter
	std::string fastaFileName;				///chaîne de caractères contenant le nom du fichier fasta contenant le génome
	size_t length;								///longueur de la séquence
	std::multimap<std::string, std::pair<size_t, size_t>> positionsSurChromosome;		///pair pour les positions recherchées avec comme key le chromosome correspondant
	size_t longueurSequencesATraiter;
};

#endif
