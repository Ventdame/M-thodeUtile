#ifndef FICHIER_CSV_H
#define FICHIER_CSV_H

#include "Chaine.h"

/// <summary>
/// Définit un objet permettant de charger des données à partir d'un fichier texte, type CSV
/// </summary>
class CFichierCSV : public CChaineDecoupee
{
public:
	/// <summary>
	/// Permet de créer un duplicata de cette entité
	/// </summary>
	/// <returns>Objet créé dynamiquement par clonage</returns>
	CEntite* Cloner() const = 0;

public:
	/// <summary>
	/// Constructeur par défaut
	/// </summary>
	CFichierCSV();

	/// <summary>
	/// Destructeur
	/// </summary>
	virtual ~CFichierCSV();

	/// <summary>
	/// Permet de lancer le processus de chargement des données à partir du fichier spécifié par son chemin d'accès relatif à l'exécutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier</param>
	/// <param name="separateur">Caractère séparateur utilisé pour le découpage de chaque ligne lue</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ résultant du découpage de chaque ligne lue doit faire l'objet d'une suppression de ces espaces superflus de début et de fin de chaîne</param>
	/// <returns>Vrai si le chargement a été réalisé jusqu'à la fin du fichier, sinon faux</returns>
	virtual bool Charger(const char* nomFichier, char separateur = '\t', bool suppressionEspacesSuperflus = true);

protected:
	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Chargeur de fichier CSV qui sert de source de cette copie</param>
	CFichierCSV(const CFichierCSV& source);

	/// <summary>
	/// Méthode à réécrire afin de traiter les données de chaque ligne lue
	/// </summary>
	/// <param name="champs">Tableau de champs récupérés de la ligne lue</param>
	/// <returns>Vrai pour indiquer que l'on veut continuer le chargement des données du fichier, sinon faux pour arrêter immédiatement le chargement avec un retour d'erreur</returns>
	virtual bool Traiter(const CChaineDecoupee& champs) = 0;

private:
	/// <summary>
	/// Permet d'ouvrir un fichier à partir d'un emplacement relatif à celui de l'exécutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier avec un chemin relatif à calculer à partir de l'emplacement de l'exécutable</param>
	/// <param name="modalite">Modalité d'ouverture</param>
	/// <returns>"Pointeur" de type FILE si le fichier a pu être ouvert, sinon NULL</returns>
	static void* fopen_x(const char* nomFichier, const char* modalite);
};

#endif//FICHIER_CSV_H
