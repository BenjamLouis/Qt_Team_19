#ifndef BEDREADER_H
#define BEDREADER_H
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

/*!
  This is a class allowing to read a BED file and to access to each one of the elements it contains.
 */

class bedreader
{
	private :
	std::string monfichier;
	std::string nomCherche;
	std::vector<std::vector<std::string>> lignes;
	std::vector<std::string> element;
	std::vector<std::string> fichier_entier;



	public :

	/*! Constructor
		@param[in] name string : of the file given by the user */
	bedreader(std::string);

	/*! Reads the file and stocks the lines in avector<string> 
	 * @throw std::logic_error the file cannot be opened
	 */
	void Read();

	/*! Stocks the elements corresponding to the sequence name given by the user in a vector<vector<string>> 
	 * @throw std::logic_error No sequences in the bedfile have been found*/
	void FindAndParse();

	/*! Sets the name of the sequence the user is looking for.
		@param[in] nomEntre string name of the sequence the user is looking for */
	void setName(std::string nomEntre);

	/*! Sets the name of the file the user is providing.
		@param[in] nomFichier string name of file the user is providing (and its full path) */
	void setFichier(std::string nomFichier);

	/*! Get lignes.
		@param[out] lignes vector<vector<string>> cointaining each line corresponding to the sequence we want parsed into a vector<string> */
	std::vector<std::vector<std::string>> getlignes();

};

#endif
