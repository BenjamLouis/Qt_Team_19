#include "BEDreader.h"
#include "LinksFile.h"
#include "fastareader.h"
#include "FastaWriter.h"
#include "Matrice.h"
#include "command_line.h"
#include "MatrixWriter.h"
#include <string>
#include <algorithm>
#include <stdexcept>

LinksFile::LinksFile(std::string Bedfile_name, std::string fastafile_name, size_t _length):
BEDFileName(Bedfile_name), fastaFileName(fastafile_name), length(_length)
{}

void LinksFile::creationMatrice() //cette fonction sera appelée dans le main
{
	bedreader BEDentier(BEDFileName);
	BEDentier.Read();
	BEDentier.FindAndParse();

	std::vector<std::vector<std::string>> lignesBED(BEDentier.getlignes());

	for(size_t i(0); i < lignesBED.size(); ++i)
	{
		int a(std::stoi(lignesBED.at(i).at(1))), b(std::stoi(lignesBED.at(i).at(2)));

		bool complementaire;

		if(lignesBED[i].size() < 4)
		{
			complementaire = false;
		} else {
			complementaire = lignesBED.at(i).at(lignesBED.at(i).size()-1)=="-";
		}
		
		if(modificationPositions(a, b, complementaire))
		{
			positionsSurChromosome.insert(std::make_pair(lignesBED.at(i).at(0),std::make_pair(a,b)));
		}
	}
	Fastareader fasta(fastaFileName);
	std::vector<std::string> sequencesATraiter(fasta.seqInterest(positionsSurChromosome));
	FastaWriter writefasta(fasta.mapToWriter()); //we write a fasta file with all the sequences from the bed.
	writefasta.create_file();

	if(sequencesATraiter.size() != 0)
	{
		Matrice matrice(sequencesATraiter, length);
		matrice.initialize();
		//écriture de la matrice dans un fichier créé pour
		matrice.create_file_matrice();
	} else {
		std::cerr << "Log 12 : ERROR : Les sequences issues du bed et retrouvees dans le fasta sont vides" << std::endl; // Log tracking					                     
		throw(std::logic_error(std::string("LinksFile::creationMatrice() les sequences a traiter sont vides")));
	}
}

//----------------------------------------------------------------------

bool LinksFile::modificationPositions(int &a, int &b, bool complementaire)
{
	if(a >= 0 && b >= 0)
	{
		if(fabs(b-a) >= length)
		{
			if((!complementaire && a > b) or (complementaire && a < b)) // If the boundaries are inverted
			{
					std::swap(a, b);
					return true;
			}
		} else {
			//throw std::logic_error("sequence trop courte");																		_____________A VERIFIER AVEC CHARLOTTE_______________(Cela doit être un cerr et pas un throw -Neil)
			return false;
		}
	} else {
		//throw std::logic_error("position négative sur ligne ");																	_____________A VERIFIER AVEC CHARLOTTE_______________(Cela doit aussi être un cerr et non un throw -Neil)
		return false;
	}
	return true;
}

//----------------------------------------------------------------------

bool LinksFile::tooLarge(const std::string& seq)
{
	return seq.size() > length;
}

//----------------------------------------------------------------------

size_t LinksFile::getLongueurSequencesATraiter()
{
	return longueurSequencesATraiter;
}

//----------------------------------------------------------------------
