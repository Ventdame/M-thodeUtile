#ifndef CHAINE_H
#define CHAINE_H

#include "Tableau.h"

/// <summary>
/// D�finit une cha�ne dynamique de caract�res
/// </summary>
class CChaine : public CEntite
{
public:
	/// <summary>
	/// Modalit� de comparaison d'une cha�ne avec une autre, bas� sur un ordonnancement croissant stricte (cf. strcmp)
	/// </summary>
	static const char ComparaisonStricte = 0;

	/// <summary>
	/// Modalit� de comparaison d'une cha�ne avec une autre, bas� sur un ordonnancement croissant sans distinction de casse (cf. stricmp/strcasecmp)
	/// </summary>
	static const char ComparaisonIC = 1;

	/// <summary>
	/// Modalit� de comparaison d'une cha�ne avec une autre, bas� sur un ordonnancement croissant sans distinction d'accentuation
	/// </summary>
	static const char ComparaisonIA = 2;

	/// <summary>
	/// Modalit� de comparaison d'une cha�ne avec une autre, bas� sur un ordonnancement croissant sans distinction de casse et d'accentuation
	/// </summary>
	static const char ComparaisonICA = 3;

public:
	/// <summary>
	/// Transformation de cha�ne : aucune transformation
	/// </summary>
	static const char AucuneTransformation = 0;

	/// <summary>
	/// Transformation de cha�ne : suppression des espaces superflus de d�but et de fin
	/// </summary>
	static const char SuppressionEspacesSuperflus = 1;

	/// <summary>
	/// Transformation de cha�ne : remplacement des majuscules par des minuscules
	/// </summary>
	static const char EnMinuscule = 2;

	/// <summary>
	/// Transformation de cha�ne : remplacement des minuscules par des majuscules
	/// </summary>
	static const char EnMajuscule = 4;

public:
	/// <summary>
	/// Constante indiquant que l'on accepte (� priori) aucun caract�re
	/// </summary>
	static const char RienAccepter = 0;

	/// <summary>
	/// Constante indiquant que l'on accepte les chiffres d�cimaux
	/// </summary>
	static const char AccepterChiffres = 1;

	/// <summary>
	/// Constante indiquant que l'on accepte les lettres non accentu�es
	/// </summary>
	static const char AccepterLettresNA = 2;

	/// <summary>
	/// Constante indiquant que l'on accepte les lettres accentu�es
	/// </summary>
	static const char AccepterLettresAC = 4;

	/// <summary>
	/// Constante indiquant que l'on accepte toutes les lettres (accentu�es et non accentu�es)
	/// </summary>
	static const char AccepterLettres = AccepterLettresNA | AccepterLettresAC;

	/// <summary>
	/// Constante indiquant que l'on accepte les s�parateurs usuels entre les mots (espace, apostrophe et tiret)
	/// </summary>
	static const char AccepterSeparateursMot = 8;

	/// <summary>
	/// Constante indiquant que l'on accepte tous les caract�res usuels d'un mot (mot simple ou compos�)
	/// </summary>
	static const char AccepterMot = AccepterLettres | AccepterSeparateursMot;

	/// <summary>
	/// Constante indiquant que l'on accepte les caract�res de ponctuation d'une phrase (virgule, point-virgule, deux points, point, point d'exclamation et point d'interrogation)
	/// </summary>
	static const char AccepterPonctuations = 16;

	/// <summary>
	/// Constante indiquant que l'on accepte tous les caract�res usuels d'une phrase
	/// </summary>
	static const char AccepterPhrase = AccepterMot | AccepterPonctuations;

public:
	/// <summary>
	/// Retourne le nombre de comparaisons pris en charge par toute entit� de ce type
	/// </summary>
	/// <returns>Nombre de comparaisons</returns>
	char NombreComparaisons() const;

	/// <summary>
	/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
	/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
	bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de cr�er un duplicata de cette entit�
	/// </summary>
	/// <returns>Objet cr�� dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Indique si les donn�es de cette entit� sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
	/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
	bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
	/// </summary>
	/// <param name="autreEntite">Autre entit� � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
	/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
	int Comparer(const CEntite& autreEntite, char modaliteComparaison) const;

public:
	/// <summary>
	/// Constructeur par d�faut
	/// </summary>
	CChaine();

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Cha�ne source de cette copie</param>
	CChaine(const CChaine& source);

	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
	/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de d�but et de fin de cha�ne doivent �tre supprim�s ou non</param>
	CChaine(const char* chaine, bool suppressionEspacesSuperflus = false);

	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
	/// <param name="transformation">Transformation(s) � appliquer lors de cette initialisation de cha�ne</param>
	CChaine(const char* chaine, char transformation);

	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="caractere">Caract�re devant �tre utilis�s pour remplir cette cha�ne � son initialisation</param>
	/// <param name="repetition">Nombre de fois que ce caract�re doit �tre r�p�t� lors du remplissage de cette cha�ne</param>
	CChaine(char caractere, long repetition);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CChaine();

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
	/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de d�but et de fin de cha�ne doivent �tre supprim�s ou non</param>
	/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
	bool Modifier(const char* chaine, bool suppressionEspacesSuperflus = false);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res devant �tre copi�e dynamiquement dans cet objet</param>
	/// <param name="transformation">Transformation(s) � appliquer</param>
	/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
	bool Modifier(const char* chaine, char transformation);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu
	/// </summary>
	/// <param name="caractere">Caract�re devant �tre utilis�s pour remplir cette cha�ne</param>
	/// <param name="repetition">Nombre de fois que ce caract�re doit �tre r�p�t� lors du remplissage de cette cha�ne</param>
	/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
	bool Remplir(char caractere, long repetition);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par remplacement de son contenu selon un format
	/// </summary>
	/// <param name="format">Cha�ne de format � utiliser pour red�finir le contenu de cette cha�ne</param>
	/// <returns>Vrai si la modification a pu �tre r�alis�e, sinon faux</returns>
	bool ModifierF(const char* format, ...);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res devant �tre concat�n�e dynamiquement dans cet objet</param>
	/// <param name="suppressionEspacesSuperflus">Indique si les espaces superflus de d�but et de fin de cha�ne doivent �tre supprim�s ou non</param>
	/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
	bool Concatener(const char* chaine, bool suppressionEspacesSuperflus = false);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res devant �tre concat�n�e dynamiquement dans cet objet</param>
	/// <param name="transformation">Transformation(s) � appliquer</param>
	/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
	bool Concatener(const char* chaine, char transformation);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel
	/// </summary>
	/// <param name="caractere">Caract�re devant �tre utilis�s pour compl�ter cette cha�ne</param>
	/// <param name="repetition">Nombre de fois que ce caract�re doit �tre r�p�t� lors du remplissage de cette cha�ne</param>
	/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
	bool Concatener(char caractere, long repetition);

	/// <summary>
	/// Permet de modifier cette cha�ne de caract�res par concat�nation � son contenu actuel, d'un contenu additionnel selon un format
	/// </summary>
	/// <param name="format">Cha�ne de format � utiliser pour compl�ter le contenu de cette cha�ne</param>
	/// <returns>Vrai si la concat�nation a pu �tre r�alis�e, sinon faux</returns>
	bool ConcatenerF(const char* format, ...);

	/// <summary>
	/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
	/// </summary>
	/// <param name="autreChaine">Autre cha�ne � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
	/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
	int Comparer(const char* autreChaine, char modaliteComparaison) const;

	/// <summary>
	/// Retourne la longueur actuelle de cette cha�ne
	/// </summary>
	/// <returns>Longueur actuelle de cette cha�ne si elle est d�finie, sinon 0</returns>
	long Longueur() const;

	/// <summary>
	/// Retourne le contenu de cette cha�ne pour consultation
	/// </summary>
	/// <returns>Adresse de d�but du contenu de cette cha�ne si elle est d�finie, sinon l'adresse d'une cha�ne constante vide</returns>
	const char* Contenu() const;

	/// <summary>
	/// Indique si cette cha�ne est d�finie ou non
	/// </summary>
	/// <returns>Vrai si cette cha�ne est d�finie (allocation r�alis�e), sinon faux</returns>
	bool EstDefinie() const;

private:
	/// <summary>
	/// Membre contenant le nombre actuel de caract�res de cette cha�ne
	/// </summary>
	long m_Longueur;

	/// <summary>
	/// Membre contenant l'adresse de d�but de ce tableau de caract�res
	/// </summary>
	char* m_Adresse;

private:
	/// <summary>
	/// Ensemble des lettres accentu�es en majuscule
	/// </summary>
	static const char LettresAccentueesEnMajuscule[];

	/// <summary>
	/// Ensemble des lettres accentu�es en majuscule transform�es par suppression de leur accent
	/// </summary>
	static const char LettresAccentueesEnMajuscule_SansAccent[];

	/// <summary>
	/// Ensemble des lettres accentu�es en majuscule transform�es en minuscule
	/// </summary>
	static const char LettresAccentueesEnMajuscule_EnMinuscule[];

	/// <summary>
	/// Ensemble des lettres accentu�es en minuscule
	/// </summary>
	static const char LettresAccentueesEnMinuscule[];

	/// <summary>
	/// Ensemble des lettres accentu�es en minuscule transform�es par suppression de leur accent
	/// </summary>
	static const char LettresAccentueesEnMinuscule_SansAccent[];

	/// <summary>
	/// Ensemble des lettres accentu�es en minuscule transform�es en majuscule
	/// </summary>
	static const char LettresAccentueesEnMinuscule_EnMajuscule[];

public:
	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est un chiffre d�cimal
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est un chiffre d�cimal, sinon faux</returns>
	static bool EstChiffre(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre, sinon faux</returns>
	static bool EstLettre(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre en majuscule
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre en majuscule, sinon faux</returns>
	static bool EstLettreMajuscule(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre en minuscule
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre en minuscule, sinon faux</returns>
	static bool EstLettreMinuscule(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre non accentu�e
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre, sinon faux</returns>
	static bool EstLettreNonAccentuee(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre accentu�e
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre accentu�e, sinon faux</returns>
	static bool EstLettreAccentuee(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre non accentu�e en majuscule
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre non accentu�e en majuscule, sinon faux</returns>
	static bool EstLettreMajusculeNonAccentuee(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre non accentu�e en minuscule
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre non accentu�e en minuscule, sinon faux</returns>
	static bool EstLettreMinusculeNonAccentuee(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre accentu�e en majuscule
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre non accentu�e en majuscule, sinon faux</returns>
	static bool EstLettreMajusculeAccentuee(char caractere);

	/// <summary>
	/// V�rifie si le caract�re sp�cifi� est une lettre accentu�e en minuscule
	/// </summary>
	/// <param name="caractere">Caract�re � tester</param>
	/// <returns>Vrai si le caract�re test� est une lettre accentu�e en minuscule, sinon faux</returns>
	static bool EstLettreMinusculeAccentuee(char caractere);

	/// <summary>
	/// Retourne le caract�re sp�cifi�e, en respectant la casse, mais d�barass� de tout accent
	/// </summary>
	/// <param name="caractere">Caract�re � "transformer" si n�cessaire</param>
	/// <returns>Caract�re sans accent</returns>
	static char CaractereNonAccentue(char caractere);

	/// <summary>
	/// Retourne le caract�re sp�cifi�e, en respectant son accentuation si n�cessaire, mais �crit en majuscule
	/// </summary>
	/// <param name="caractere">Caract�re � "transformer" si n�cessaire</param>
	/// <returns>Caract�re �crit en majuscule</returns>
	static char CaractereEnMajuscule(char caractere);

	/// <summary>
	/// Retourne le caract�re sp�cifi�e, en respectant son accentuation si n�cessaire, mais �crit en minuscule
	/// </summary>
	/// <param name="caractere">Caract�re � "transformer" si n�cessaire</param>
	/// <returns>Caract�re �crit en minuscule</returns>
	static char CaractereEnMinuscule(char caractere);

	/// <summary>
	/// Teste l'�galit� stricte des deux caract�res sp�cifi�s
	/// </summary>
	/// <param name="caractere1">Caract�re � tester</param>
	/// <param name="caractere2">Autre caract�re � tester</param>
	/// <returns>Vrai si les deux caract�res sont �gaux de mani�re stricte, sinon faux</returns>
	static bool CaracteresSontEgaux(char caractere1, char caractere2);

	/// <summary>
	/// Teste l'�galit� sans distinction de casse des deux caract�res sp�cifi�s
	/// </summary>
	/// <param name="caractere1">Caract�re � tester</param>
	/// <param name="caractere2">Autre caract�re � tester</param>
	/// <returns>Vrai si les deux caract�res sont �gaux sans distinction de casse, sinon faux</returns>
	static bool CaracteresSontEgaux_IC(char caractere1, char caractere2);

	/// <summary>
	/// Teste l'�galit� sans distinction d'accentuation des deux caract�res sp�cifi�s
	/// </summary>
	/// <param name="caractere1">Caract�re � tester</param>
	/// <param name="caractere2">Autre caract�re � tester</param>
	/// <returns>Vrai si les deux caract�res sont �gaux sans distinction d'accentuation, sinon faux</returns>
	static bool CaracteresSontEgaux_IA(char caractere1, char caractere2);

	/// <summary>
	/// Teste l'�galit� sans distinction de casse et d'accentuation des deux caract�res sp�cifi�s
	/// </summary>
	/// <param name="caractere1">Caract�re � tester</param>
	/// <param name="caractere2">Autre caract�re � tester</param>
	/// <returns>Vrai si les deux caract�res sont �gaux sans distinction de casse et d'accentuation, sinon faux</returns>
	static bool CaracteresSontEgaux_ICA(char caractere1, char caractere2);

	/// <summary>
	/// Compare de mani�re stricte les deux caract�res sp�cifi�s
	/// </summary>
	/// <param name="caractere1">Caract�re � comparer</param>
	/// <param name="caractere2">Autre caract�re � comparer</param>
	/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
	static int ComparerCaractere(char caractere1, char caractere2);

	/// <summary>
	/// Compare les deux caract�res sp�cifi�s sans distinction de casse
	/// </summary>
	/// <param name="caractere1">Caract�re � comparer</param>
	/// <param name="caractere2">Autre caract�re � comparer</param>
	/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
	static int ComparerCaractere_IC(char caractere1, char caractere2);

	/// <summary>
	/// Compare les deux caract�res sp�cifi�s sans distinction d'accentuation
	/// </summary>
	/// <param name="caractere1">Caract�re � comparer</param>
	/// <param name="caractere2">Autre caract�re � comparer</param>
	/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
	static int ComparerCaractere_IA(char caractere1, char caractere2);

	/// <summary>
	/// Compare les deux caract�res sp�cifi�s sans distinction de casse et d'accentuation
	/// </summary>
	/// <param name="caractere1">Caract�re � comparer</param>
	/// <param name="caractere2">Autre caract�re � comparer</param>
	/// <returns>-1 si le premier caract�re sp�cifi� est plus petit que l'autre caract�re, 1 si le premier caract�re sp�cifi� est plus grand que l'autre caract�re, sinon 0</returns>
	static int ComparerCaractere_ICA(char caractere1, char caractere2);

	/// <summary>
	/// Retourne la longueur de la cha�ne sp�cifi�e
	/// <para>Version "s�curis�e" de strlen vis � vis du pointeur NULL</para>
	/// </summary>
	/// <param name="chaine">Cha�ne dont on veut d�terminer la longueur</param>
	/// <param name="sansTenirCompteEspacesSuperflus">Indique si on doit ignorer ou pas les espaces superflus de d�but et de fin de cha�ne</param>
	/// <returns>Longueur de la cha�ne si elle existe, sinon 0</returns>
	static long LongueurChaine(const char* chaine, bool sansTenirCompteEspacesSuperflus = false);

	/// <summary>
	/// Compare les deux cha�nes sp�cifi�es
	/// <para>Version "s�curis�e" de strcmp vis � vis des pointeurs NULL, avec possibilit� d'ignorer les diff�rences de casse et/ou d'ignorer les diff�rences d'accentuation</para>
	/// </summary>
	/// <param name="chaine1">Cha�ne "1" � comparer</param>
	/// <param name="chaine2">Cha�ne "2" � comparer</param>
	/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les diff�rences de casse</param>
	/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les diff�rences d'accentuation</param>
	/// <returns>-1 si la cha�ne "1" est plus petite que la cha�ne "2", 1 si la cha�ne "1" est plus grande que la cha�ne "2", sinon 0</returns>
	static int ComparerChaine(const char* chaine1, const char* chaine2, bool ignorerCasse, bool ignorerAccentuation);

	/// <summary>
	/// Permet de v�rifier si la cha�ne sp�cifi�e n'est constitu�e que de caract�res parmi ceux autoris�s
	/// </summary>
	/// <param name="chaine">Cha�ne � tester</param>
	/// <param name="acceptation">Combinaison de constante(s) d'acceptation</param>
	/// <param name="caracteresAcceptables">Cha�ne contenant les caract�res acceptables</param>
	/// <param name="caracteresInterdits">Cha�ne contenant les caract�res sp�cifiquement interdits (sachant que l'interdiction prime sur l'autorisation)</param>
	/// <returns>Vrai si tous les caract�res de la cha�ne respecte les prescriptions sp�cifi�es, sinon faux</returns>
	static bool ChaineRespecte(const char* chaine, char acceptation, const char* caracteresAcceptables = NULL, const char* caracteresInterdits = NULL);

	/// <summary>
	/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur r�elle (ou enti�re)
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � tester</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur r�elle, sinon faux</returns>
	static bool EstReel(const char* chaine);

	/// <summary>
	/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur r�elle (ou enti�re)
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � tester</param>
	/// <param name="separateurDecimal">[RESULTAT] Adresse de l'emplacement o� se trouver le s�parateur d�cimal dans la cha�ne test�e, sinon NULL</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur r�elle, sinon faux</returns>
	static bool EstReel(const char* chaine, const char*& separateurDecimal);

	/// <summary>
	/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur r�elle (ou enti�re)
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � tester</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="separateurDecimal">[RESULTAT] Adresse de l'emplacement o� se trouver le s�parateur d�cimal dans la cha�ne test�e, sinon NULL</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur r�elle, sinon faux</returns>
	static bool EstReel(const char* chaine, const char*& messageErreur, const char*& separateurDecimal);

	/// <summary>
	/// Tente de convertir la cha�ne sp�cifi�e en une valeur r�elle
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � convertir</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0.0</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
	static bool EnReel(const char* chaine, double& valeur);

	/// <summary>
	/// Tente de convertir la cha�ne sp�cifi�e en une valeur r�elle
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � convertir</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0.0</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
	static bool EnReel(const char* chaine, const char*& messageErreur, double& valeur);

	/// <summary>
	/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur enti�re
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � tester</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur enti�re, sinon faux</returns>
	static bool EstEntier(const char* chaine);

	/// <summary>
	/// Permet de v�rifier si la cha�ne sp�cifi�e repr�sente une valeur enti�re
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � tester</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e repr�sente une valeur enti�re, sinon faux</returns>
	static bool EstEntier(const char* chaine, const char*& messageErreur);

	/// <summary>
	/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � convertir</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, long& valeur);

	/// <summary>
	/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � convertir</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, const char*& messageErreur, long& valeur);

	/// <summary>
	/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � convertir</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, __int64& valeur);

	/// <summary>
	/// Tente de convertir la cha�ne sp�cifi�e en une valeur enti�re
	/// </summary>
	/// <param name="chaine">Cha�ne de caract�res � convertir</param>
	/// <param name="messageErreur">[RESULTAT] Adresse vers un message d'erreur, sinon NULL</param>
	/// <param name="valeur">[RESULTAT] Valeur convertie, sinon 0</param>
	/// <returns>Vrai si la cha�ne sp�cifi�e a pu �tre convertie, sinon faux</returns>
	static bool EnEntier(const char* chaine, const char*& messageErreur, __int64& valeur);

private:
	/// <summary>
	/// D�finit un type de donn�es pour les fonctions capables de tester l'�galit� entre deux caract�res
	/// </summary>
	typedef bool(*TesteurEgaliteCaracteres)(char, char);

	/// <summary>
	/// D�finit un type de donn�es pour les fonctions capables de comparer deux caract�res
	/// </summary>
	typedef int(*ComparateurCaracteres)(char, char);

	/// <summary>
	/// Retourne la fonction de test d'�galit� entre deux caract�res en fonction des options sp�cifi�es
	/// </summary>
	/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les diff�rences de casse</param>
	/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les diff�rences d'accentuation</param>
	/// <returns>Fonction de test d'�galit� entre deux caract�res en fonction des options sp�cifi�es</returns>
	static TesteurEgaliteCaracteres ObtenirTesteurEgaliteCaracteres(bool ignorerCasse, bool ignorerAccentuation);

	/// <summary>
	/// Retourne la fonction de comparaison entre deux caract�res en fonction des options sp�cifi�es
	/// </summary>
	/// <param name="ignorerCasse">Indique si la comparaison doit ignorer les diff�rences de casse</param>
	/// <param name="ignorerAccentuation">Indique si la comparaison doit ignorer les diff�rences d'accentuation</param>
	/// <returns>Fonction de comparaison entre deux caract�res en fonction des options sp�cifi�es</returns>
	static ComparateurCaracteres ObtenirComparateurCaracteres(bool ignorerCasse, bool ignorerAccentuation);
};

/// <summary>
/// D�finit le mod�le de CChaine lors de l'instanciation d'un objet CTableau pour y stocker des entit�s de type CChaine
/// </summary>
class CRegleSurChaine : public CChaine
{
public:
	/// <summary>
	/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
	/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
	bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de cr�er un duplicata de cette entit�
	/// </summary>
	/// <returns>Objet cr�� dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Indique si les donn�es de cette entit� sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
	/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
	bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Permet de tester la validit� de l'entit� sp�cifi�e en param�tre
	/// <para>La r��criture de cette m�thode n'a d'int�r�t que si cette classe sert entre autre d'entit� validatrice, et donc � priori, � d�finir l'entit� par d�faut d'un tableau</para>
	/// </summary>
	/// <param name="entiteATester">Entit� � tester</param>
	/// <returns>Vrai si l'entit� � tester est valide selon les r�gles impos�es par l'entit� pour laquelle cette m�thode est appel�e, sinon faux</returns>
	bool TesterValidite(const CEntite& entiteATester) const;

public:
	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="unicite">Indique si toutes les modalit�s de comparaison impliquent l'unicit� ou pas</param>
	/// <param name="longueurMinimale">Longueur minimale que doit avoir toute cha�ne de caract�res</param>
	CRegleSurChaine(bool unicite, long longueurMinimale = 0);

	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="uniciteStricte">Indique si la modalit� de comparaison stricte implique l'unicit� ou pas</param>
	/// <param name="uniciteIC">Indique si la modalit� de comparaison sans distinction de casse implique l'unicit� ou pas</param>
	/// <param name="uniciteIA">Indique si la modalit� de comparaison sans distinction d'accentuation implique l'unicit� ou pas</param>
	/// <param name="uniciteICA">Indique si la modalit� de comparaison sans distinction de casse et d'accentuation implique l'unicit� ou pas</param>
	/// <param name="longueurMinimale">Longueur minimale que doit avoir toute cha�ne de caract�res</param>
	CRegleSurChaine(bool uniciteStricte, bool uniciteIC, bool uniciteIA, bool uniciteICA, long longueurMinimale = 0);

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Cha�ne source de cette copie</param>
	CRegleSurChaine(const CRegleSurChaine& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CRegleSurChaine();

private:
	/// <summary>
	/// Membre retenant pour chaque modalit� de comparaison, si on doit appliquer un test d'unicit� des cha�nes de caract�res
	/// </summary>
	bool m_PourUnicite[CChaine::ComparaisonICA + 1];

	/// <summary>
	/// Membre indiquant la longueur minimale que doit avoir une cha�ne de caract�res
	/// </summary>
	long m_LongueurMinimale;
};

/// <summary>
/// D�finit un ensemble de "champs" r�sultant du d�coupage d'une cha�ne de caract�res en fonction d'un caract�re s�parateur
/// </summary>
class CChaineDecoupee : public CEntite
{
public:
	/// <summary>
	/// Retourne le nombre de comparaisons pris en charge par toute entit� de ce type
	/// </summary>
	/// <returns>Nombre de comparaisons</returns>
	char NombreComparaisons() const;

	/// <summary>
	/// Indique si la modalit� de comparaison sp�cifi�e sert comme crit�re d'unicit� de telles entit�s au sein d'un tableau
	/// </summary>
	/// <param name="modaliteComparaison">Modalit� de comparaison � tester</param>
	/// <returns>Vrai si cette modalit� de comparaison sert comme crit�re d'unicit�, sinon faux</returns>
	bool EstComparaisonPourUnicite(char modaliteComparaison) const;

	/// <summary>
	/// Permet de cr�er un duplicata de cette entit�
	/// </summary>
	/// <returns>Objet cr�� dynamiquement par clonage</returns>
	CEntite* Cloner() const;

	/// <summary>
	/// Indique si les donn�es de cette entit� sont valides
	/// </summary>
	/// <param name="entiteValidatrice">Entit� � utiliser optionnellement pour tester la validit� de l'entit� pour laquelle cette m�thode est appel�e</param>
	/// <returns>Vrai si cette entit� est valide,sinon faux</returns>
	bool EstValide(const CEntite* entiteValidatrice = NULL) const;

	/// <summary>
	/// Compare cette entit� � celle pass�e en param�tre, selon la modalit� de comparaison sp�cifi�e
	/// </summary>
	/// <param name="autreEntite">Autre entit� � laquelle on compare celle pour laquelle cette m�thode est appel�e, et ce, selon la modalit� de comparaison sp�cifi�e</param>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
	/// <returns>-1 si cette entit� est "inf�rieure" � l'autre entit�, 1 si cette entit� est "sup�rieure" � l'autre entit�, sinon 0 (en cas d'�galit�)</returns>
	int Comparer(const CEntite& autreEntite, char modaliteComparaison) const;

public:
	/// <summary>
	/// Constructeur sp�cifique
	/// </summary>
	/// <param name="chaine">Cha�ne que l'on va "d�couper" en fonction du caract�re s�parateur sp�cifi�</param>
	/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
	CChaineDecoupee(const char* chaine, char separateur = '\t', bool suppressionEspacesSuperflus = true);

	/// <summary>
	/// Constructeur par copie
	/// </summary>
	/// <param name="source">Cha�ne d�coup�e qui sert de source de cette copie</param>
	CChaineDecoupee(const CChaineDecoupee& source);

	/// <summary>
	/// Destructeur
	/// </summary>
	~CChaineDecoupee();

	/// <summary>
	/// Retourne le nombre de champs
	/// </summary>
	/// <returns>Nombre de champs de cette cha�ne d�coup�e</returns>
	long Nombre() const;

	/// <summary>
	/// Retourne le champ sp�cifi� par son indice
	/// </summary>
	/// <param name="indice">Indice du champ � r�cup�rer</param>
	/// <returns>Adresse de d�but de la cha�ne de caract�res correspondant au champ sp�cifi� par son indice si possible, sinon l'adresse d'une cha�ne vide constante</returns>
	const char* Element(long indice) const;

	/// <summary>
	/// Indique si le champ sp�cifi� par son indice est �gal � la cha�ne sp�cifi�e
	/// </summary>
	/// <param name="indice">Indice du champ � tester</param>
	/// <param name="indice">Correspondance recherch�e lors du test du champ concern�</param>
	/// <param name="modaliteComparaison">Modalit� de comparaison � utiliser</param>
	/// <returns>Vrai si le champ sp�cifi� est �gal � la cha�ne de caract�res sp�cifi�es, sinon faux</returns>
	bool EstEgal(long indice, const char* chaine, char modaliteComparaison = CChaine::ComparaisonStricte) const;

	/// <summary>
	/// Permet de v�rifier si le champ sp�cifi� par son indice n'est constitu�e que de caract�res parmi ceux autoris�s
	/// </summary>
	/// <param name="indice">Indice du champ � tester</param>
	/// <param name="acceptation">Combinaison de constante(s) d'acceptation</param>
	/// <param name="caracteresAcceptables">Cha�ne contenant les caract�res acceptables</param>
	/// <param name="caracteresInterdits">Cha�ne contenant les caract�res sp�cifiquement interdits (sachant que l'interdiction prime sur l'autorisation)</param>
	/// <returns>Vrai si tous les caract�res du champ sp�cifi� respecte les prescriptions sp�cifi�es, sinon faux</returns>
	bool Respecte(long indice, char acceptation, const char* caracteresAcceptables, const char* caracteresInterdits) const;

	/// <summary>
	/// Indique si le champ sp�cifi� repr�sente un nombre entier
	/// </summary>
	/// <param name="indice">Indice du champ � tester</param>
	/// <returns>Vrai si le champ sp�cifi� repr�sente une valeur enti�re, sinon faux</returns>
	bool EstEntier(long indice) const;

	/// <summary>
	/// Indique si le champ sp�cifi� repr�sente un nombre r�el
	/// </summary>
	/// <param name="indice">Indice du champ � tester</param>
	/// <returns>Vrai si le champ sp�cifi� repr�sente une valeur r�elle, sinon faux</returns>
	bool EstReel(long indice) const;

	/// <summary>
	/// Tente de convertir le champ sp�cifi� en un nombre entier [type char]
	/// </summary>
	/// <param name="indice">Indice du champ � convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
	/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
	bool EnEntier(long indice, char& valeur) const;

	/// <summary>
	/// Tente de convertir le champ sp�cifi� en un nombre entier [type short]
	/// </summary>
	/// <param name="indice">Indice du champ � convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
	/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
	bool EnEntier(long indice, short& valeur) const;

	/// <summary>
	/// Tente de convertir le champ sp�cifi� en un nombre entier [type long]
	/// </summary>
	/// <param name="indice">Indice du champ � convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
	/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
	bool EnEntier(long indice, long& valeur) const;

	/// <summary>
	/// Tente de convertir le champ sp�cifi� en un nombre entier [type __int64]
	/// </summary>
	/// <param name="indice">Indice du champ � convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0</param>
	/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur enti�re, sinon faux</returns>
	bool EnEntier(long indice, __int64& valeur) const;

	/// <summary>
	/// Tente de convertir le champ sp�cifi� en un nombre r�el [type double]
	/// </summary>
	/// <param name="indice">Indice du champ � convertir si possible</param>
	/// <param name="valeur">[RESULTAT] Valeur r�sultant de cette conversion r�ussie, sinon 0.0</param>
	/// <returns>Vrai si le champ sp�cifi� a pu �tre converti en une valeur r�elle, sinon faux</returns>
	bool EnReel(long indice, double& valeur) const;

protected:
	/// <summary>
	/// M�thode d�finissant la cha�ne � d�couper
	/// </summary>
	/// <param name="chaine">Cha�ne � d�couper</param>
	/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
	/// <returns>Vrai si le d�coupage a pu se faire, sinon faux</returns>
	bool CopierChaine(const char* chaine);

	/// <summary>
	/// M�thode r�alisant le d�coupage de la cha�ne actuelle en fonction du caract�re s�parateur sp�cifi�
	/// </summary>
	/// <param name="chaine">Cha�ne � d�couper</param>
	/// <param name="separateur">Caract�re s�parateur utilis� pour le d�coupage</param>
	/// <param name="suppressionEspacesSuperflus">Indique si chaque champ r�sultant du d�coupage doit faire l'objet d'une suppression de ces espaces superflus de d�but et de fin de cha�ne</param>
	/// <returns>Vrai si le d�coupage a pu se faire, sinon faux</returns>
	bool Decouper(char separateur = '\t', bool suppressionEspacesSuperflus = true);

protected:
	/// <summary>
	/// Membre retenant le nombre de caract�res constitutifs du "buffer" de cette cha�ne d�coup�e
	/// </summary>
	long m_LongueurChaine;

	/// <summary>
	/// Membre retenant le nombre de caract�res maximum (marqueur de fin de cha�ne non compris) que l'on peut stocker dans le "buffer" de cette cha�ne d�coup�e
	/// </summary>
	long m_TailleChaine;

	/// <summary>
	/// Membre contenant l'adresse de d�but du "buffer" de cette cha�ne d�coup�e
	/// </summary>
	char* m_Chaine;

private:
	/// <summary>
	/// Membre retenant le nombre de champs obtenus suite au d�coupage
	/// </summary>
	long m_NombreChamps;

	/// <summary>
	/// Membre retenant le nombre de cases qui sont actuellement disponibles dans le tableau des adresses des champs
	/// </summary>
	long m_TailleChamps;

	/// <summary>
	/// Membre stockant l'adresse de d�but de chaque champ r�sultant du d�coupage
	/// </summary>
	char** m_Champs;
};

#endif//CHAINE_H
