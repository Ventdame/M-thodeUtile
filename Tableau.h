#ifndef TABLEAU_H
#define TABLEAU_H

/// <summary>
/// D�finit la classe de base � toute entit� que l'on peut ensuite retrouver comme �l�ment d'un tableau d'entit�s
/// </summary>
class CEntite
{
public:
	/// <summary>
	/// Constructeur par d�faut
	/// </summary>
	CEntite();

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Entit� source</param>
	CEntite(const CEntite& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	virtual ~CEntite();
	
	/// <summary>
	/// Retourne le nombre de comparaisons pris en charge par toute entit� de ce type
	/// </summary>
	/// <returns>Nombre de comparaisons</returns>
	virtual char NombreComparaisons() const;

	/// <summary>
	/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
	/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
	virtual bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de cr�er un duplicata de cette entit�
	/// </summary>
	/// <returns>Objet cr�� dynamiquement par clonage</returns>
	virtual CEntite* Cloner() const;

	/// <summary>
	/// Indique si les donn�es de cette entit� sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
	/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
	virtual bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Permet de tester la validit� de l'entit� sp�cifi�e en param�tre
	/// <para>La r��criture de cette m�thode n'a d'int�r�t que si cette classe sert entre autre d'entit� validatrice, et donc � priori, � d�finir l'entit� par d�faut d'un tableau</para>
	/// </summary>
	/// <param name="entiteATester">Entit� � tester</param>
	/// <returns>Vrai si l'entit� � tester est valide selon les r�gles impos�es par l'entit� pour laquelle cette m�thode est appel�e, sinon faux</returns>
	virtual bool TesterValidite(const CEntite& entiteATester) const;

	/// <summary>
	/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
	/// </summary>
	/// <param name="autreEntite">Autre entit� � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
	/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
	virtual int Comparer(const CEntite& autreEntite, char modaliteComparaison) const;
};

/// <summary>
/// D�finit un tableau d'entit�s
/// </summary>
class CTableau : public CEntite
{
public:
	/// <summary>
	/// Modalit� de comparaison non utilisable, permettant de signaler que le tableau n'est actuellement pas tri�
	/// </summary>
	static const char NonTrie = -1;

public:
	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="entiteParDefaut">Mod�le d'entit� par d�faut (c'est ce qui d�termine le "d�nominateur commun" � tout �l�ment que l'on veut placer dans ce tableau)</param>
	CTableau(const CEntite& entiteParDefaut);

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Entit� source de cette copie</param>
	CTableau(const CTableau& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CTableau();

	/// <summary>
	/// Permet de cr�er un duplicata de cette entit�
	/// </summary>
	/// <returns>Objet cr�� dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Permet de supprimer toutes les entit�s du tableau
	/// </summary>
	void Vider();

	/// <summary>
	/// Permet d'ajouter une nouvelle entit� en fin de tableau, � partir du mod�le sp�cifi� d'entit�
	/// </summary>
	/// <param name="entiteAAjouter">Mod�le de l'entit� � ajouter dans le tableau</param>
	/// <returns>Vrai si l'ajout a pu se faire, sinon faux</returns>
	bool Ajouter(const CEntite& entiteAAjouter);

	/// <summary>
	/// Permet d'ins�rer une nouvelle entit� � la position sp�cifi�e du tableau, � partir du mod�le sp�cifi� d'entit�
	/// </summary>
	/// <param name="indiceInsertion">Indice d'insertion<para>Compris entre 0 et le nombre d'entit�s</para></param>
	/// <param name="entiteAAjouter">Mod�le de l'entit� � ajouter dans le tableau</param>
	/// <returns>Vrai si l'insertion a pu se faire, sinon faux</returns>
	bool Inserer(long indiceInsertion, const CEntite& entiteAAjouter);

	/// <summary>
	/// Permet de supprimer l'entit� sp�cifi�e du tableau
	/// </summary>
	/// <param name="indiceElement">Indice de l'�l�ment � supprimer<para>Compris entre 0 et le nombre d'entit�s - 1</para></param>
	/// <returns>Vrai si la suppression a pu se faire, sinon faux</returns>
	bool Supprimer(long indiceElement);

	/// <summary>
	/// Permet de trier les entit�s selon la modalit� de comparaison sp�cifi�e
	/// </summary>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser lors du tri des entit�s</param>
	/// <returns>Vrai si le tri est r�alis�, sinon faux</returns>
	bool Trier(char modaliteComparaison = (char)0);

	/// <summary>
	/// Permet de rechercher une entit� dans le tableau en fonction de la modalit� de comparaison sp�cifi�e
	/// </summary>
	/// <param name="entiteARechercher">Mod�le de l'entit� � rechercher</param>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser lors de la recherche de l'entit�</param>
	/// <param name="indiceDebut">Indice de d�but de la recherche<para>Compris entre 0 et le nombre d'entit�s - 1</para></param>
	/// <returns>Indice de la premi�re occurrence d'entit� correspondant � la recherche entam�e, sinon -1</returns>
	long Rechercher(const CEntite& entiteARechercher, char modaliteComparaison = (char)0, long indiceDebut = 0) const;

	/// <summary>
	/// Accesseur du nombre d'entit�s de ce tableau
	/// </summary>
	/// <returns>Nombre d'entit�s</returns>
	long Nombre() const;

	/// <summary>
	/// Indexeur d'une entit� en fonction de son indice dans ce tableau
	/// </summary>
	/// <param name="indiceElement">Indice de l'�l�ment � r�cup�rer</param>
	/// <returns>R�f�rence de l'�l�ment du tableau � l'indice valide, sinon l'entit� par d�faut</returns>
	const CEntite& Element(long indiceElement) const;

	/// <summary>
	/// Indexeur d'une entit� en fonction de son indice dans ce tableau
	/// </summary>
	/// <param name="indiceElement">Indice de l'�l�ment � r�cup�rer</param>
	/// <returns>R�f�rence de l'�l�ment du tableau � l'indice valide, sinon l'entit� par d�faut</returns>
	template <class T> T& Element(long indiceElement) const
	{
		return (T&)Element(indiceElement);
	}

	/// <summary>
	/// Accesseur indiquant comment le tableau est actuellement tri�
	/// </summary>
	/// <returns>Nombre d'entit�s</returns>
	char TriActuel() const;

	/// <summary>
	/// Indique si le tableau est actuellement tri� (selon la modalit� sp�cifi�e)
	/// </summary>
	/// <param name="modaliteComparaison">Modalit� de comparaison � tester comme modalit� de tri actuel</param>
	/// <returns>Vrai si le tableau est actuellement tri� selon la modalit� de comparaison sp�cifi�e, sinon faux</returns>
	bool EstTrie(char modaliteComparaison = (char)0) const;

private:
	/// <summary>
	/// Fonction de comparaison compatible avec le callback des fonctions qsort_c, bsearch_c et lfind_c
	/// </summary>
	/// <param name="adresseEntite">Adresse d'un emplacement contenant l'adresse d'une entit�</param>
	/// <param name="adresseAutreEntite">Adresse d'un autre emplacement contenant l'adresse d'une autre entit�</param>
	/// <param name="contexte">Adresse du contexte de callback</param>
	/// <returns>-1 si l'entit� est "inf�rieure" � l'autre entit�, 1 si l'entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
	static int Comparer(const void* adresseEntite, const void* adresseAutreEntite, const void* contexte);

private:
	/// <summary>
	/// Membre contenant le nombre actuel d'entit�s � prendre en consid�ration
	/// </summary>
	long m_Nombre;

	/// <summary>
	/// Membre contenant la taille actuelle du tableau des pointeurs
	/// </summary>
	long m_Taille;

	/// <summary>
	/// Membre contenant l'adresse de d�but du tableau des pointeurs vers chaque objet d'entit�
	/// </summary>
	CEntite** m_Tableau;

	/// <summary>
	/// Membre retenant l'�tat actuel garanti du tableau d'entit�s
	/// </summary>
	char m_TriActuel;

	/// <summary>
	/// Membre pointant sur l'entit� de r�f�rence
	/// </summary>
	CEntite* m_EntiteParDefaut;
};

#endif//TABLEAU_H
