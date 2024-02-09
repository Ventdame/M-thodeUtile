#ifndef DOCUMENT_HTML_H
#define DOCUMENT_HTML_H

#include "Chaine.h"
#include "Tableau.h"

/// <summary>
/// D�finit un objet permettant de cr�er un document HTML
/// </summary>
class CDocumentHtml
{
public:
	/// <summary>
	/// Constructeur par d�faut
	/// </summary>
	CDocumentHtml();

	/// <summary>
	/// Destructeur
	/// </summary>
	virtual ~CDocumentHtml();

	/// <summary>
	/// Permet de lancer le processus de cr�ation d'un document HTML dont le nom de fichier est sp�cifi� par son chemin d'acc�s relatif � l'ex�cutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier</param>
	/// <param name="titre">Titre du document</param>
	/// <returns>Vrai si la cr�ation a �t� r�alis�e jusqu'� la fin, sinon faux</returns>
	virtual bool Creer(const char* nomFichier, const char* titre);

	/// <summary>
	/// Permet d'ouvrir ce document HTML
	/// </summary>
	/// <returns>Vrai si l'ouverture a pu se faire, sinon faux</returns>
	bool Ouvrir();

protected:
	/// <summary>
	/// M�thode � r��crire afin de g�n�rer le corps de page
	/// </summary>
	/// <returns>Vrai pour indiquer que l'on veut finaliser "normalement" la cr�ation du document HTML, sinon faux pour arr�ter imm�diatement cette cr�ation avec un retour d'erreur</returns>
	virtual bool GenererCorps() = 0;

	/// <summary>
	/// M�thode pouvant �tre r��crite afin de compl�ter la partie de code CSS du document HTML
	/// </summary>
	/// <returns>Vrai pour indiquer que l'on veut finaliser "normalement" la cr�ation du document HTML, sinon faux pour arr�ter imm�diatement cette cr�ation avec un retour d'erreur</returns>
	virtual bool CompleterCss();

protected:
	/// <summary>
	/// Permet d'ajouter une d�finition CSS comme code CSS additionnel
	/// </summary>
	/// <param name="selecteur">Code CSS d�crivant un ou plusieurs s�lecteurs (s�par�s les uns des autres par une virgule)</param>
	/// <param name="proprietes">Code CSS r�alisant les modifications de propri�t�s (s�par�es les unes des autres par un point-virgule)</param>
	/// <returns>Vrai si cet ajout a r�ussi, sinon faux</returns>
	bool AjouterCss(const char* selecteur, const char* proprietes);

	/// <summary>
	/// Permet de cr�er un �l�ment du DOM avec une balise ouvrante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Cha�ne d'attributs de cette balise ouvrante</param>
	/// <returns>Vrai si l'ouverture a fonctionn�, sinon faux</returns>
	bool OuvrirBalise(const char* nomBalise, const char* attributs = 0);

	/// <summary>
	/// Permet de fermer l'�l�ment du DOM actuellement "ouvert", et ce, avec sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise, sinon NULL</param>
	/// <param name="toutFermerJusqueBaliseSpecifiee">Indique que l'on veut fermer toutes les balises actuellement ouvertes jusqu'� atteindre et fermer celle sp�cifi�e</param>
	/// <returns>Vrai si la fermeture a pu se faire, sinon faux</returns>
	bool FermerBalise(const char* nomBalise = 0, bool toutFermerJusqueBaliseSpecifiee = false);

	/// <summary>
	/// Permet de cr�er un �l�ment du DOM avec une balise autonome
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Cha�ne d'attributs de cette balise autonome</param>
	/// <returns>Vrai si l'�criture a fonctionn�, sinon faux</returns>
	bool BaliseAutonome(const char* nomBalise, const char* attributs = 0);

	/// <summary>
	/// Permet de cr�er un �l�ment du DOM avec une balise ouvrante, ensuite un contenu, et enfin, sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="contenu">Contenu � placer entre la balise ouvrante et la balise fermante</param>
	/// <returns>Vrai si l'�criture a fonctionn�, sinon faux</returns>
	bool OuvrirEtFermerBalise(const char* nomBalise, const char* contenu);

	/// <summary>
	/// Permet de cr�er un �l�ment du DOM avec une balise ouvrante, ensuite un contenu, et enfin, sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Cha�ne d'attributs de cette balise ouvrante</param>
	/// <param name="contenu">Contenu � placer entre la balise ouvrante et la balise fermante</param>
	/// <returns>Vrai si l'�criture a fonctionn�, sinon faux</returns>
	bool OuvrirEtFermerBalise(const char* nomBalise, const char* attributs, const char* contenu);

	/// <summary>
	/// Permet de cr�er un �l�ment du DOM avec une balise ouvrante, ensuite un contenu param�tr�, et enfin, sa balise fermante
	/// </summary>
	/// <param name="nomBalise">Nom de la balise</param>
	/// <param name="attributs">Cha�ne d'attributs de cette balise ouvrante</param>
	/// <param name="format">Format du contenu � placer entre la balise ouvrante et la balise fermante</param>
	/// <returns>Vrai si l'�criture a fonctionn�, sinon faux</returns>
	bool OuvrirEtFermerBaliseF(const char* nomBalise, const char* attributs, const char* format, ...);

private:
	/// <summary>
	/// Permet d'ouvrir un fichier � partir d'un emplacement relatif � celui de l'ex�cutable
	/// </summary>
	/// <param name="nomFichier">Nom du fichier avec un chemin relatif � calculer � partir de l'emplacement de l'ex�cutable</param>
	/// <param name="modalite">Modalit� d'ouverture</param>
	/// <returns>"Pointeur" de type FILE si le fichier a pu �tre ouvert, sinon NULL</returns>
	static void* fopen_x(const char* nomFichier, const char* modalite);

private:
	/// <summary>
	/// Nom relatif du fichier associ� � ce document
	/// </summary>
	CChaine m_NomFichier;

	/// <summary>
	/// Membre stockant le pointeur de type FILE repr�sentant le fichier �ventuellement ouvert
	/// </summary>
	void* m_Fichier;

	/// <summary>
	/// Indique si l'ajout de code CSS est actuellement autoris�
	/// </summary>
	bool m_AjoutCssPossible;

	/// <summary>
	/// Indique si l'ajout de balises HTML est actuellement autoris�
	/// </summary>
	bool m_EcritureBalisePossible;

	/// <summary>
	/// Indique si la cr�ation a r�ussi
	/// </summary>
	bool m_CreationReussie;

	/// <summary>
	/// Pile des balises actuellement ouvertes
	/// </summary>
	CTableau m_BalisesOuvertes;
};

#endif//DOCUMENT_HTML_H
