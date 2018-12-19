#include "Matrice.h"
#include <cmath>

Matrice::Matrice(std::vector<std::string> sequences,size_t l)
:list_seq(sequences), L(l)
{}

//------------------------------------------------------------------------------

void Matrice::initialize()
{
	if (list_seq.size() != 0) {
		double nucl_en_trop;
	
		while(tab_matrice.size() < L) {
			std::array<double,4> push({0.0, 0.0, 0.0, 0.0});
			tab_matrice.push_back(push);
		}

		for(size_t i(0); i<list_seq.size(); ++i){
			std::vector<std::string> liste_a_incrementer({list_seq[i]});
			nucl_en_trop = (list_seq[i].size() - L);
			
			if(nucl_en_trop > 0) decoupage(liste_a_incrementer);
			
			lire_seq(liste_a_incrementer, 1./(nucl_en_trop+1));
		}
		
		CalculProbaMatrice();
		
	} else {
		std::cerr << "Log 1 : FATAL : Liste de sequence vide dans le BED" << std::endl; // Log tracking
		throw(std::logic_error(std::string("Matrice::initialize : liste de sequence vide")));

	}
}

//------------------------------------------------------------------------------

void Matrice::decoupage(std::vector<std::string>& listeSeq)
{
	std::string seqADecouper(listeSeq[0]);
	size_t nombreDecalages(listeSeq[0].size() - L);
	for(size_t j(0); j <= nombreDecalages; ++j)
	{
		if(!seqADecouper.empty()) {
			if(j == 0)
			{
				listeSeq[0] = seqADecouper.substr(j, L);
			} else {
				listeSeq.push_back(seqADecouper.substr(j, L));
			}
		}
	}
}

//------------------------------------------------------------------------------

void Matrice::CalculProbaMatrice()
{
	for(size_t i(0); i<tab_matrice.size(); ++i){
		for (size_t j(0); j<4; ++j){
			tab_matrice[i][j] += 0.25;
			tab_matrice[i][j] /= (list_seq.size() + 1);
		}
	}
}

//------------------------------------------------------------------------------

void Matrice::lire_seq (std::vector<std::string> seq, double incr)
{
	for(size_t i(0); i<seq.size() ; ++i)
	{
		for(size_t j(0); j < seq[i].size(); ++j)
		{
			char Nucl;
			Nucl = seq[i][j];

			switch (Nucl) {
				case ('A') : case ('a') :// We interpret the char into a Nucleotide type
					incrementer(A,j, incr);
					break;
				case ('T') : case ('t') :
					incrementer(T,j, incr);
					break;
				case ('G') : case ('g') :
					incrementer(G,j, incr);
					break;
				case ('C') : case ('c') :
					incrementer(C,j, incr);
					break;
				default :
				std::cerr << "Log 2 : INFO : Nucléotide inconnu dans la sequence lue du fasta" << std::endl; // Log tracking
			}
		}
	}
}

//------------------------------------------------------------------------------

void Matrice::incrementer (Nucleotide N, size_t placeNucleotide, double incr)
{
  switch(N)
  {
    case A : tab_matrice[placeNucleotide][0] += incr;
    break;
    case T : tab_matrice[placeNucleotide][1] += incr;
    break;
    case G : tab_matrice[placeNucleotide][2] += incr;
    break;
    case C : tab_matrice[placeNucleotide][3] += incr;
    break;
    default : std::cerr << "Log 3 : INFO : Nucléotide inconnu dans la sequence lue du fasta" << std::endl; // Log tracking
  }
}

//------------------------------------------------------------------------------

void Matrice::create_file_matrice()
{
	MatrixWriter mat(tab_matrice);
	mat.create_file();
}

//------------------------------------------------------------------------------	
