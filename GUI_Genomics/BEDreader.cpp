#include "BEDreader.h"

bedreader::bedreader(std::string NomFichier):
monfichier(NomFichier), nomCherche("")
{}

//------------------------------------------------------------------------------

void bedreader::setName(std::string nomEntre)
{
	nomCherche = nomEntre;
}

//------------------------------------------------------------------------------

void bedreader::setFichier(std::string nomFichier)
{
	monfichier=nomFichier;
}

//------------------------------------------------------------------------------

void bedreader::Read()
{
	std::string line;
	std::ifstream myfile(monfichier);

	if(not(myfile.is_open()))
	{
		std::cerr << "Log 5 : ERROR : Le fichier fasta n a pas pu être lu"  << std::endl;// Log tracking
		throw std::logic_error(std::string ("BEDreader::Read() Votre fichier n'a pas pu être lu."));
	}
	else
	{
		while(!myfile.eof())
		{
			std::getline(myfile,line);
			if(!line.empty()) { fichier_entier.push_back(line); }
		}
	}
	myfile.close();
}

//------------------------------------------------------------------------------

std::vector<std::vector<std::string>>  bedreader::getlignes()
{
	return lignes;
}

//------------------------------------------------------------------------------

void bedreader::FindAndParse()
{
	std::string delimiter = "\t";
	std::size_t pos = 0;
	std::string token;
	std::vector<std::string> fichier_ent(fichier_entier);
	for(size_t i(0);i<fichier_ent.size();++i)
	{
		pos = fichier_ent.at(i).find(delimiter);
		token = fichier_ent.at(i).substr(0, pos);
		if ((token==nomCherche) or nomCherche=="")
		{
			do
			{
				pos = fichier_ent.at(i).find(delimiter);
				token = fichier_ent.at(i).substr(0, pos);
				element.push_back(token);
				fichier_ent.at(i).erase(0, pos + delimiter.length());
			} while ((pos = fichier_ent[i].find(delimiter))!= std::string::npos);
			element.push_back(fichier_ent.at(i));
			lignes.push_back(element);
			element.clear();
			size_t n;
			n = lignes.at(i).size();
			if(lignes.at(i).at(n-1)!="+" or lignes.at(i).at(n-1)!="-")
			{
				lignes.at(i).push_back("+");
			}
		}
	}
	if(lignes.size()==0)
	{
		std::cerr << "Log 6 : ERROR : Nom de sequence dans le fichier bed n est pas trouve dans le fasta"  << std::endl;// Log tracking
		throw std::logic_error(std::string("BEDreader::FindAndParse() Aucune séquence de ce nom n'a été trouvée"));
	}
}

//------------------------------------------------------------------------------
