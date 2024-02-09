#ifndef TABLEAU_H
#define TABLEAU_H

/// <summary>
/// Définit la classe de base à toute entité que l'on peut ensuite retrouver comme élément d'un tableau d'entités
/// </summary>
class CEntite
{
public:
	/// <summary>
	/// Constructeur par défaut
	/// </summary>
	CEntite();

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Entité source</param>
	CEntite(const CEntite& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	virtual ~CEntite();
	
	/// <summary>
	/// Retourne le nombre de comparaisons pris en charge par toute entité de ce type
	/// </summary>
	/// <returns>Nombre de comparaisons</returns>
	virtual char NombreComparaisons() const;

	/// <summary>
	/// Indique si la modalité de comparaison spécifiée sert comme critère d'unicité de telles entités au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalité de comparaison à tester</param>
	/// <returns>Vrai si cette modalité de comparaison sert comme critère d'unicité, sinon faux</returns>
	virtual bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de créer un duplicata de cette entité
	/// </summary>
	/// <returns>Objet créé dynamiquement par clonage</returns>
	virtual CEntite* Cloner() const;

	/// <summary>
	/// Indique si les données de cette entité sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entité à utiliser optionnellement pour tester la validité de l'entité pour laquelle cette méthode est appelée</param>
	/// <returns>Vrai si cette entité est valide,sinon faux</returns>
	virtual bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Permet de tester la validité de l'entité spécifiée en paramètre
	/// <para>La réécriture de cette méthode n'a d'intérêt que si cette classe sert entre autre d'entité validatrice, et donc à priori, à définir l'entité par défaut d'un tableau</para>
	/// </summary>
	/// <param name="entiteATester">Entité à tester</param>
	/// <returns>Vrai si l'entité à tester est valide selon les règles imposées par l'entité pour laquelle cette méthode est appelée, sinon faux</returns>
	virtual bool TesterValidite(const CEntite& entiteATester) const;

	/// <summary>
	/// Compare cette entité à celle passée en paramètre, selon la modalité de comparaison spécifiée
	/// </summary>
	/// <param name="autreEntite">Autre entité à laquelle on compare celle pour laquelle cette méthode est appelée, et ce, selon la modalité de comparaison spécifiée</param>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser</param>
	/// <returns>-1 si cette entité est "inférieure" à l'autre entité, 1 si cette entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
	virtual int Comparer(const CEntite& autreEntite, char modaliteComparaison) const;
};

/// <summary>
/// Définit un tableau d'entités
/// </summary>
class CTableau : public CEntite
{
public:
	/// <summary>
	/// Modalité de comparaison non utilisable, permettant de signaler que le tableau n'est actuellement pas trié
	/// </summary>
	static const char NonTrie = -1;

public:
	/// <summary>
	/// Constructeur spécifique
	/// </summary>
	/// <param name="entiteParDefaut">Modèle d'entité par défaut (c'est ce qui détermine le "dénominateur commun" à tout élément que l'on veut placer dans ce tableau)</param>
	CTableau(const CEntite& entiteParDefaut);

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Entité source de cette copie</param>
	CTableau(const CTableau& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CTableau();

	/// <summary>
	/// Permet de créer un duplicata de cette entité
	/// </summary>
	/// <returns>Objet créé dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Permet de supprimer toutes les entités du tableau
	/// </summary>
	void Vider();

	/// <summary>
	/// Permet d'ajouter une nouvelle entité en fin de tableau, à partir du modèle spécifié d'entité
	/// </summary>
	/// <param name="entiteAAjouter">Modèle de l'entité à ajouter dans le tableau</param>
	/// <returns>Vrai si l'ajout a pu se faire, sinon faux</returns>
	bool Ajouter(const CEntite& entiteAAjouter);

	/// <summary>
	/// Permet d'insérer une nouvelle entité à la position spécifiée du tableau, à partir du modèle spécifié d'entité
	/// </summary>
	/// <param name="indiceInsertion">Indice d'insertion<para>Compris entre 0 et le nombre d'entités</para></param>
	/// <param name="entiteAAjouter">Modèle de l'entité à ajouter dans le tableau</param>
	/// <returns>Vrai si l'insertion a pu se faire, sinon faux</returns>
	bool Inserer(long indiceInsertion, const CEntite& entiteAAjouter);

	/// <summary>
	/// Permet de supprimer l'entité spécifiée du tableau
	/// </summary>
	/// <param name="indiceElement">Indice de l'élément à supprimer<para>Compris entre 0 et le nombre d'entités - 1</para></param>
	/// <returns>Vrai si la suppression a pu se faire, sinon faux</returns>
	bool Supprimer(long indiceElement);

	/// <summary>
	/// Permet de trier les entités selon la modalité de comparaison spécifiée
	/// </summary>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser lors du tri des entités</param>
	/// <returns>Vrai si le tri est réalisé, sinon faux</returns>
	bool Trier(char modaliteComparaison = (char)0);

	/// <summary>
	/// Permet de rechercher une entité dans le tableau en fonction de la modalité de comparaison spécifiée
	/// </summary>
	/// <param name="entiteARechercher">Modèle de l'entité à rechercher</param>
	/// <param name="modaliteComparaison">Modalité de comparaison à utiliser lors de la recherche de l'entité</param>
	/// <param name="indiceDebut">Indice de début de la recherche<para>Compris entre 0 et le nombre d'entités - 1</para></param>
	/// <returns>Indice de la première occurrence d'entité correspondant à la recherche entamée, sinon -1</returns>
	long Rechercher(const CEntite& entiteARechercher, char modaliteComparaison = (char)0, long indiceDebut = 0) const;

	/// <summary>
	/// Accesseur du nombre d'entités de ce tableau
	/// </summary>
	/// <returns>Nombre d'entités</returns>
	long Nombre() const;

	/// <summary>
	/// Indexeur d'une entité en fonction de son indice dans ce tableau
	/// </summary>
	/// <param name="indiceElement">Indice de l'élément à récupérer</param>
	/// <returns>Référence de l'élément du tableau à l'indice valide, sinon l'entité par défaut</returns>
	const CEntite& Element(long indiceElement) const;

	/// <summary>
	/// Indexeur d'une entité en fonction de son indice dans ce tableau
	/// </summary>
	/// <param name="indiceElement">Indice de l'élément à récupérer</param>
	/// <returns>Référence de l'élément du tableau à l'indice valide, sinon l'entité par défaut</returns>
	template <class T> T& Element(long indiceElement) const
	{
		return (T&)Element(indiceElement);
	}

	/// <summary>
	/// Accesseur indiquant comment le tableau est actuellement trié
	/// </summary>
	/// <returns>Nombre d'entités</returns>
	char TriActuel() const;

	/// <summary>
	/// Indique si le tableau est actuellement trié (selon la modalité spécifiée)
	/// </summary>
	/// <param name="modaliteComparaison">Modalité de comparaison à tester comme modalité de tri actuel</param>
	/// <returns>Vrai si le tableau est actuellement trié selon la modalité de comparaison spécifiée, sinon faux</returns>
	bool EstTrie(char modaliteComparaison = (char)0) const;

private:
	/// <summary>
	/// Fonction de comparaison compatible avec le callback des fonctions qsort_c, bsearch_c et lfind_c
	/// </summary>
	/// <param name="adresseEntite">Adresse d'un emplacement contenant l'adresse d'une entité</param>
	/// <param name="adresseAutreEntite">Adresse d'un autre emplacement contenant l'adresse d'une autre entité</param>
	/// <param name="contexte">Adresse du contexte de callback</param>
	/// <returns>-1 si l'entité est "inférieure" à l'autre entité, 1 si l'entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
	static int Comparer(const void* adresseEntite, const void* adresseAutreEntite, const void* contexte);

private:
	/// <summary>
	/// Membre contenant le nombre actuel d'entités à prendre en considération
	/// </summary>
	long m_Nombre;

	/// <summary>
	/// Membre contenant la taille actuelle du tableau des pointeurs
	/// </summary>
	long m_Taille;

	/// <summary>
	/// Membre contenant l'adresse de début du tableau des pointeurs vers chaque objet d'entité
	/// </summary>
	CEntite** m_Tableau;

	/// <summary>
	/// Membre retenant l'état actuel garanti du tableau d'entités
	/// </summary>
	char m_TriActuel;

	/// <summary>
	/// Membre pointant sur l'entité de référence
	/// </summary>
	CEntite* m_EntiteParDefaut;
};

#endif//TABLEAU_H
