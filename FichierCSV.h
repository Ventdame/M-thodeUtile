#ifndef FICHIER_CSV_H
#define FICHIER_CSV_H

#include "Chaine.h"

/// <summary>
/// D�finit un objet permettant de charger des donn�es � partir d'un fichier texte, type CSV
/// </summary>
class CFichierCSV : public CChaineDecoupee
{
public:
	/// <summary>
	/// Permet de cr�er un duplicata de cette entit�
	/// </summary>
	/// <returns>Objet cr�� dynamiquement par clonage</returns>
	CEntite* Cloner() const = 0;

public:
	/// <summary>
	/// Constructeur par d�faut
	/// </summary>
	CFichierCSV();

	/// <summary>
	/// Destructeur
	/// </summary>
	virtual ~CFichierCSV();

	/// <summary>
	/// Permet de lancer le processus de chargement des donn�es � partir du fichier sp�cifi� par son chemin d'acc�s relatif � l'ex�cutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier</param>
	/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage de chaque ligne lue</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage de chaque ligne lue doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
	/// <returns>Vrai si le chargement a �t� r�alis� jusqu'� la fin du fichier, sinon faux</returns>
	virtual bool Charger(const char* nomFichier, char separateur = '\t', bool suppressionEspacesSuperflus = true);

protected:
	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Chargeur de fichier CSV qui sert de source de cette copie</param>
	CFichierCSV(const CFichierCSV& source);

	/// <summary>
	/// M�thode � r��crire afin de traiter les donn�es de chaque ligne lue
	/// </summary>
	/// <param name="champs">Tableau de champs r�cup�r�s de la ligne lue</param>
	/// <returns>Vrai pour indiquer que l'on veut continuer le chargement des donn�es du fichier, sinon faux pour arr�ter imm�diatement le chargement avec un retour d'erreur</returns>
	virtual bool Traiter(const CChaineDecoupee& champs) = 0;

private:
	/// <summary>
	/// Permet d'ouvrir un fichier � partir d'un emplacement relatif � celui de l'ex�cutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier avec un chemin relatif � calculer � partir de l'emplacement de l'ex�cutable</param>
	/// <param name="modalite">Modalit� d'ouverture</param>
	/// <returns>"Pointeur" de type FILE si le fichier a pu �tre ouvert, sinon NULL</returns>
	static void* fopen_x(const char* nomFichier, const char* modalite);
};

#endif//FICHIER_CSV_H
