#ifndef DOCUMENT_HTML_H
#define DOCUMENT_HTML_H

#include "Chaine.h"
#include "Tableau.h"

/// <summary>
/// Définit un objet permettant de créer un document HTML
/// </summary>
class CDocumentHtml
{
public:
	/// <summary>
	/// Constructeur par défaut
	/// </summary>
	CDocumentHtml();

	/// <summary>
	/// Destructeur
	/// </summary>
	virtual ~CDocumentHtml();

	/// <summary>
	/// Permet de lancer le processus de création d'un document HTML dont le nom de fichier est spécifié par son chemin d'accès relatif à l'exécutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier</param>
	/// <param name="titre">Titre du document</param>
	/// <returns>Vrai si la création a été réalisée jusqu'à la fin, sinon faux</returns>
	virtual bool Creer(const char* nomFichier, const char* titre);

	/// <summary>
	/// Permet d'ouvrir ce document HTML
	/// </summary>
	/// <returns>Vrai si l'ouverture a pu se faire, sinon faux</returns>
	bool Ouvrir();

protected:
	/// <summary>
	/// Méthode à réécrire afin de générer le corps de page
	/// </summary>
	/// <returns>Vrai pour indiquer que l'on veut finaliser "normalement" la création du document HTML, sinon faux pour arrêter immédiatement cette création avec un retour d'erreur</returns>
	virtual bool GenererCorps() = 0;

	/// <summary>
	/// Méthode pouvant être réécrite afin de compléter la partie de code CSS du document HTML
	/// </summary>
	/// <returns>Vrai pour indiquer que l'on veut finaliser "normalement" la création du document HTML, sinon faux pour arrêter immédiatement cette création avec un retour d'erreur</returns>
	virtual bool CompleterCss();

protected:
	/// <summary>
	/// Permet d'ajouter une définition CSS comme code CSS additionnel
	/// </summary>
	/// <param name="selecteur">Code CSS décrivant un ou plusieurs sélecteurs (séparés les uns des autres par une virgule)</param>
	/// <param name="proprietes">Code CSS réalisant les modifications de propriétés (séparées les unes des autres par un point-virgule)</param>
	/// <returns>Vrai si cet ajout a réussi, sinon faux</returns>
	bool AjouterCss(const char* selecteur, const char* proprietes);

	/// <summary>
	/// Permet de créer un élément du DOM avec une balise ouvrante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Chaîne d'attributs de cette balise ouvrante</param>
	/// <returns>Vrai si l'ouverture a fonctionné, sinon faux</returns>
	bool OuvrirBalise(const char* nomBalise, const char* attributs = 0);

	/// <summary>
	/// Permet de fermer l'élément du DOM actuellement "ouvert", et ce, avec sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise, sinon NULL</param>
	/// <param name="toutFermerJusqueBaliseSpecifiee">Indique que l'on veut fermer toutes les balises actuellement ouvertes jusqu'à atteindre et fermer celle spécifiée</param>
	/// <returns>Vrai si la fermeture a pu se faire, sinon faux</returns>
	bool FermerBalise(const char* nomBalise = 0, bool toutFermerJusqueBaliseSpecifiee = false);

	/// <summary>
	/// Permet de créer un élément du DOM avec une balise autonome
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Chaîne d'attributs de cette balise autonome</param>
	/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
	bool BaliseAutonome(const char* nomBalise, const char* attributs = 0);

	/// <summary>
	/// Permet de créer un élément du DOM avec une balise ouvrante, ensuite un contenu, et enfin, sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="contenu">Contenu à placer entre la balise ouvrante et la balise fermante</param>
	/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
	bool OuvrirEtFermerBalise(const char* nomBalise, const char* contenu);

	/// <summary>
	/// Permet de créer un élément du DOM avec une balise ouvrante, ensuite un contenu, et enfin, sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Chaîne d'attributs de cette balise ouvrante</param>
	/// <param name="contenu">Contenu à placer entre la balise ouvrante et la balise fermante</param>
	/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
	bool OuvrirEtFermerBalise(const char* nomBalise, const char* attributs, const char* contenu);

	/// <summary>
	/// Permet de créer un élément du DOM avec une balise ouvrante, ensuite un contenu paramétré, et enfin, sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Chaîne d'attributs de cette balise ouvrante</param>
	/// <param name="format">Format du contenu à placer entre la balise ouvrante et la balise fermante</param>
	/// <returns>Vrai si l'écriture a fonctionné, sinon faux</returns>
	bool OuvrirEtFermerBaliseF(const char* nomBalise, const char* attributs, const char* format, ...);

private:
	/// <summary>
	/// Permet d'ouvrir un fichier à partir d'un emplacement relatif à celui de l'exécutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier avec un chemin relatif à calculer à partir de l'emplacement de l'exécutable</param>
	/// <param name="modalite">Modalité d'ouverture</param>
	/// <returns>"Pointeur" de type FILE si le fichier a pu être ouvert, sinon NULL</returns>
	static void* fopen_x(const char* nomFichier, const char* modalite);

private:
	/// <summary>
	/// Nom relatif du fichier associé à ce document
	/// </summary>
	CChaine m_NomFichier;

	/// <summary>
	/// Membre stockant le pointeur de type FILE représentant le fichier éventuellement ouvert
	/// </summary>
	void* m_Fichier;

	/// <summary>
	/// Indique si l'ajout de code CSS est actuellement autorisé
	/// </summary>
	bool m_AjoutCssPossible;

	/// <summary>
	/// Indique si l'ajout de balises HTML est actuellement autorisé
	/// </summary>
	bool m_EcritureBalisePossible;

	/// <summary>
	/// Indique si la création a réussi
	/// </summary>
	bool m_CreationReussie;

	/// <summary>
	/// Pile des balises actuellement ouvertes
	/// </summary>
	CTableau m_BalisesOuvertes;
};

#endif//DOCUMENT_HTML_H
