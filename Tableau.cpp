#include "BisConsole.h"
#include "Tableau.h"

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// Recherche dichotomique
/// </summary>
const void* bsearch_c(const void* key, const void* base, size_t num, size_t width, int(*compare)(const void*, const void*, const void*), const void* context);

/// <summary>
/// Recherche séquentielle
/// </summary>
const void* lfind_c(const void* key, const void* base, size_t num, size_t width, int(*compare)(const void*, const void*, const void*), const void* context);

/// <summary>
/// Tri "rapide"
/// </summary>
void qsort_c(void* base, size_t num, size_t width, int(*compare)(const void*, const void*, const void*), const void* context);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// Constructeur par défaut
/// </summary>
CEntite::CEntite()
{
}

/// <summary>
/// Constructeur par copie
/// </summary>
/// <param name="source">Entité source</param>
CEntite::CEntite(const CEntite& source)
{
}

/// <summary>
/// Destructeur
/// </summary>
/*virtual*/ CEntite::~CEntite()
{
}

/// <summary>
/// Retourne le nombre de comparaisons pris en charge par toute entité de ce type
/// </summary>
/// <returns>Nombre de comparaisons</returns>
/*virtual*/ char CEntite::NombreComparaisons() const
{
	return 0;
}

/// <summary>
/// Indique si la modalité de comparaison spécifiée sert comme critère d'unicité de telles entités au sein d'un tableau
/// </summary>
/// <param name="modaliteComparaison">Modalité de comparaison à tester</param>
/// <returns>Vrai si cette modalité de comparaison sert comme critère d'unicité, sinon faux</returns>
/*virtual*/ bool CEntite::EstComparaisonPourUnicite(char modaliteComparaison) const
{
	return false;
}

/// <summary>
/// Permet de créer un duplicata de cette entité
/// </summary>
/// <returns>Objet créé dynamiquement par clonage</returns>
/*virtual*/ CEntite* CEntite::Cloner() const
{
	return new CEntite(*this);
}

/// <summary>
/// Indique si les données de cette entité sont valides
/// </summary>
/// <param name="entiteValidatrice">Entité à utiliser optionnellement pour tester la validité de l'entité pour laquelle cette méthode est appelée</param>
/// <returns>Vrai si cette entité est valide,sinon faux</returns>
/*virtual*/ bool CEntite::EstValide(const CEntite* entiteValidatrice) const
{
	return true;
}

/// <summary>
/// Permet de tester la validité de l'entité spécifiée en paramètre
/// <para>La réécriture de cette méthode n'a d'intérêt que si cette classe sert entre autre d'entité validatrice, et donc à priori, à définir l'entité par défaut d'un tableau</para>
/// </summary>
/// <param name="entiteATester">Entité à tester</param>
/// <returns>Vrai si l'entité à tester est valide selon les règles imposées par l'entité pour laquelle cette méthode est appelée, sinon faux</returns>
/*virtual*/ bool CEntite::TesterValidite(const CEntite& entiteATester) const
{
	return entiteATester.EstValide();
}

/// <summary>
/// Compare cette entité à celle passée en paramètre, selon la modalité de comparaison spécifiée
/// </summary>
/// <param name="autreEntite">Autre entité à laquelle on compare celle pour laquelle cette méthode est appelée, et ce, selon la modalité de comparaison spécifiée</param>
/// <param name="modaliteComparaison">Modalité de comparaison à utiliser</param>
/// <returns>-1 si cette entité est "inférieure" à l'autre entité, 1 si cette entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
/*virtual*/ int CEntite::Comparer(const CEntite& autreEntite, char modaliteComparaison) const
{
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// Constructeur spécifique
/// </summary>
/// <param name="entiteParDefaut">Modèle d'entité par défaut (c'est ce qui détermine le "dénominateur commun" à tout élément que l'on veut placer dans ce tableau)</param>
CTableau::CTableau(const CEntite& entiteParDefaut)
	:m_Nombre(0), m_Taille(0), m_Tableau(NULL), m_TriActuel(CTableau::NonTrie), m_EntiteParDefaut(entiteParDefaut.Cloner())
{
}

/// <summary>
/// Constructeur par copie
/// </summary>
/// <param name="source">Entité source de cette copie</param>
CTableau::CTableau(const CTableau& source)
	:m_Nombre(0), m_Taille(0), m_Tableau(NULL), m_TriActuel(CTableau::NonTrie), m_EntiteParDefaut(source.m_EntiteParDefaut->Cloner())
{
	for (long indice = 0; indice < source.m_Nombre; indice++)
	{
		Ajouter(*(source.m_Tableau[indice]));
	}
	m_TriActuel = source.m_TriActuel;
}

/// <summary>
/// Destructeur
/// </summary>
CTableau::~CTableau()
{
	Vider();
	delete m_EntiteParDefaut;
}

/// <summary>
/// Permet de créer un duplicata de cette entité
/// </summary>
/// <returns>Objet créé dynamiquement par clonage</returns>
CEntite* CTableau::Cloner() const
{
	return new CTableau(*this);
}

/// <summary>
/// Permet de supprimer toutes les entités du tableau
/// </summary>
void CTableau::Vider()
{
	if (m_Tableau != NULL)
	{
		for (long indice = 0; indice < m_Nombre; indice++) delete m_Tableau[indice];
		free(m_Tableau);
		m_Tableau = NULL;
	}
	m_Nombre = 0;
	m_Taille = 0;
	m_TriActuel = CTableau::NonTrie;
}

/// <summary>
/// Permet d'ajouter une nouvelle entité en fin de tableau, à partir du modèle spécifié d'entité
/// </summary>
/// <param name="entiteAAjouter">Modèle de l'entité à ajouter dans le tableau</param>
/// <returns>Vrai si l'ajout a pu se faire, sinon faux</returns>
bool CTableau::Ajouter(const CEntite& entiteAAjouter)
{
	return Inserer(m_Nombre, entiteAAjouter);
}

/// <summary>
/// Permet d'insérer une nouvelle entité à la position spécifiée du tableau, à partir du modèle spécifié d'entité
/// </summary>
/// <param name="indiceInsertion">Indice d'insertion<para>Compris entre 0 et le nombre d'entités</para></param>
/// <param name="entiteAAjouter">Modèle de l'entité à ajouter dans le tableau</param>
/// <returns>Vrai si l'insertion a pu se faire, sinon faux</returns>
bool CTableau::Inserer(long indiceInsertion, const CEntite& entiteAAjouter)
{
	// Vérifier la validité des paramètres
	if ((indiceInsertion < 0) || (indiceInsertion > m_Nombre)) return false;
	if (!entiteAAjouter.EstValide(m_EntiteParDefaut)) return false;
	// Vérifier la ou les unicités à tester
	for (char modaliteComparaison = 0, nombreComparaisons = m_EntiteParDefaut->NombreComparaisons(); modaliteComparaison < nombreComparaisons; modaliteComparaison++)
	{
		if (m_EntiteParDefaut->EstComparaisonPourUnicite(modaliteComparaison))
		{
			if (Rechercher(entiteAAjouter, modaliteComparaison) >= 0) return false;
		}
	}
	// Création d'un nouvel objet clone de celui à ajouter
	CEntite* entiteClonee = entiteAAjouter.Cloner();
	if (entiteClonee == NULL) return false;
	if (!entiteClonee->EstValide(m_EntiteParDefaut))
	{
		delete entiteClonee;
		return false;
	}
	// Ajustement si nécessaire de la taille du tableau des pointeurs
	if (m_Nombre == m_Taille)
	{
		long nouvelleTaille = m_Taille + 10;
		void* nouvelleAdresse = (m_Tableau == NULL) ? malloc(nouvelleTaille * sizeof(CEntite*)) : realloc(m_Tableau, nouvelleTaille * sizeof(CEntite*));
		if (nouvelleAdresse == NULL)
		{
			delete entiteClonee;
			return false;
		}
		m_Tableau = (CEntite**)nouvelleAdresse;
		m_Taille = nouvelleTaille;
	}
	// Décalage des pointeurs vers les éléments, d'une position vers la position suivante, et ce, à partir de la position d'insertion
	if (indiceInsertion < m_Nombre)
	{
		memmove(m_Tableau + (indiceInsertion + 1), m_Tableau + indiceInsertion, (m_Nombre - indiceInsertion) * sizeof(CEntite*));
	}
	// Copie de l'adresse du nouvel objet clone de celui à ajouter à la position spécifiée
	m_Tableau[indiceInsertion] = entiteClonee;
	// Incrémentation du nombre d'éléments
	m_Nombre++;
	// Indication de perte possible de l'état actuel de tri
	m_TriActuel = CTableau::NonTrie;
	// Indication de réussite de l'insertion
	return true;
}

/// <summary>
/// Permet de supprimer l'entité spécifiée du tableau
/// </summary>
/// <param name="indiceElement">Indice de l'élément à supprimer<para>Compris entre 0 et le nombre d'entités - 1</para></param>
/// <returns>Vrai si la suppression a pu se faire, sinon faux</returns>
bool CTableau::Supprimer(long indiceElement)
{
	// Vérifier la validité des paramètres
	if ((indiceElement < 0) || (indiceElement >= m_Nombre)) return false;
	// Suppression de l'élément spécifié par son indice
	delete m_Tableau[indiceElement];
	// Décalage des pointeurs vers les éléments, d'une position vers la position précédente, et ce, à partir de la position suivant celle de suppression
	if (indiceElement < (m_Nombre - 1))
	{
		memmove(m_Tableau + indiceElement, m_Tableau + (indiceElement + 1), ((m_Nombre - 1) - indiceElement) * sizeof(CEntite*));
	}
	// Décrémentation du nombre d'éléments
	m_Nombre--;
	if (m_Nombre >= 1)
	{
		// Remise à NULL du pointeur stocké dans la case suivante du dernier élément
		m_Tableau[m_Nombre] = NULL;
		// Optionnellement, on réduit la taille effective du tableau de pointeurs quand on a "trop" de cases non utilisées dans ce tableau
		if (m_Nombre < (m_Taille / 2))
		{
			long nouvelleTaille = m_Nombre;
			void* nouvelleAdresse = realloc(m_Tableau, nouvelleTaille * sizeof(CEntite*));
			if (nouvelleAdresse != NULL)
			{
				m_Tableau = (CEntite**)nouvelleAdresse;
				m_Taille = nouvelleTaille;
			}
		}
	}
	else
	{
		// Comme on vient de supprimer le tout dernier élément, on revient dans l'état initial du tableau
		free(m_Tableau);
		m_Tableau = NULL;
		m_Taille = 0;
		m_TriActuel = CTableau::NonTrie;
	}
	// Indication de réussite de la suppression
	return true;
}

/// <summary>
/// Fonction de comparaison compatible avec le callback des fonctions qsort_c, bsearch_c et lfind_c
/// </summary>
/// <param name="adresseEntite">Adresse d'un emplacement contenant l'adresse d'une entité</param>
/// <param name="adresseAutreEntite">Adresse d'un autre emplacement contenant l'adresse d'une autre entité</param>
/// <param name="contexte">Adresse du contexte de callback</param>
/// <returns>-1 si l'entité est "inférieure" à l'autre entité, 1 si l'entité est "supérieure" à l'autre entité, sinon 0 (en cas d'égalité)</returns>
/*static*/ int CTableau::Comparer(const void* adresseEntite, const void* adresseAutreEntite, const void* contexte)
{
	const CEntite& entite = *(*((const CEntite**)adresseEntite));
	const CEntite& autreEntite = *(*((const CEntite**)adresseAutreEntite));
	char modaliteComparaison = *((const char*)contexte);
	return entite.Comparer(autreEntite, modaliteComparaison);
}

/// <summary>
/// Permet de trier les entités selon la modalité de comparaison spécifiée
/// </summary>
/// <param name="modaliteComparaison">Modalité de comparaison à utiliser lors du tri des entités</param>
/// <returns>Vrai si le tri est réalisé, sinon faux</returns>
bool CTableau::Trier(char modaliteComparaison)
{
	if ((modaliteComparaison < 0) || (modaliteComparaison >= m_EntiteParDefaut->NombreComparaisons())) return false;
	if (modaliteComparaison == m_TriActuel) return true;
	if (m_Nombre >= 2)
	{
		qsort_c(m_Tableau, m_Nombre, sizeof(CEntite*), Comparer, &modaliteComparaison);
	}
	// Indication de réussite du tri
	m_TriActuel = modaliteComparaison;
	return true;
}

/// <summary>
/// Permet de rechercher une entité dans le tableau en fonction de la modalité de comparaison spécifiée
/// </summary>
/// <param name="entiteARechercher">Modèle de l'entité à rechercher</param>
/// <param name="modaliteComparaison">Modalité de comparaison à utiliser lors de la recherche de l'entité</param>
/// <param name="indiceDebut">Indice de début de la recherche<para>Compris entre 0 et le nombre d'entités - 1</para></param>
/// <returns>Indice de la première occurrence d'entité correspondant à la recherche entamée, sinon -1</returns>
long CTableau::Rechercher(const CEntite& entiteARechercher, char modaliteComparaison, long indiceDebut) const
{
	if (!entiteARechercher.EstValide(m_EntiteParDefaut)) return -1;
	if ((modaliteComparaison < 0) || (modaliteComparaison >= m_EntiteParDefaut->NombreComparaisons())) return -1;
	if ((indiceDebut < 0) || (indiceDebut >= m_Nombre)) return -1;
	const CEntite* adresseEntiteARechercher = &entiteARechercher;
	const void* resultat = ((modaliteComparaison == m_TriActuel) ? bsearch_c : lfind_c)(&adresseEntiteARechercher, m_Tableau, m_Nombre, sizeof(CEntite*), Comparer, &modaliteComparaison);
	return (resultat != NULL) ? (long)((CEntite**)resultat - m_Tableau) : -1;
}

/// <summary>
/// Accesseur du nombre d'entités de ce tableau
/// </summary>
/// <returns>Nombre d'entités</returns>
long CTableau::Nombre() const
{
	return m_Nombre;
}

/// <summary>
/// Indexeur d'une entité en fonction de son indice dans ce tableau
/// </summary>
/// <param name="indiceElement">Indice de l'élément à récupérer</param>
/// <returns>Référence de l'élément du tableau à l'indice valide, sinon l'entité par défaut</returns>
const CEntite& CTableau::Element(long indiceElement) const
{
	return *(((indiceElement >= 0) && (indiceElement < m_Nombre)) ? m_Tableau[indiceElement] : m_EntiteParDefaut);
}

/// <summary>
/// Accesseur indiquant comment le tableau est actuellement trié
/// </summary>
/// <returns>Nombre d'entités</returns>
char CTableau::TriActuel() const
{
	return m_TriActuel;
}

/// <summary>
/// Indique si le tableau est actuellement trié (selon la modalité spécifiée)
/// </summary>
/// <param name="modaliteComparaison">Modalité de comparaison à tester comme modalité de tri actuel</param>
/// <returns>Vrai si le tableau est actuellement trié selon la modalité de comparaison spécifiée, sinon faux</returns>
bool CTableau::EstTrie(char modaliteComparaison) const
{
	if ((modaliteComparaison < 0) || (modaliteComparaison >= m_EntiteParDefaut->NombreComparaisons())) return false;
	return (modaliteComparaison == m_TriActuel);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

/****************************************************************************
*bsearch.c - do a binary search
*lfind.c - do a linear search
*qsort.c - quicksort algorithm; qsort() library function for sorting arrays
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines bsearch() - do a binary search an an array
*       defines _lfind() - do a linear search of an array.
*       To implement the qsort() routine for sorting arrays.
*
*******************************************************************************/

/***
*char *bsearch() - do a binary search on an array
*
*Purpose:
*       Does a binary search of a sorted array for a key.
*
*Entry:
*       const char *key    - key to search for
*       const char *base   - base of sorted array to search
*       size_t num   - number of elements in array
*       size_t width - number of bytes per element
*       int (*compare)()   - pointer to function that compares two array
*               elements, returning neg when #1 < #2, pos when #1 > #2, and
*               0 when they are equal. Function is passed pointers to two
*               array elements.
*
*Exit:
*       if key is found:
*               returns pointer to occurrence of key in array
*       if key is not found:
*               returns NULL
*
*Exceptions:
*
*******************************************************************************/

const void* bsearch_c(
	const void* key,
	const void* base,
	size_t num,
	size_t width,
	int (*compare)(const void*, const void*, const void*),
	const void* context
)
{
	char* lo = (char*)base;
	char* hi = (char*)base + (num - 1) * width;
	char* mid;
	size_t half;
	int result;

	while (lo <= hi)
		if (half = num / 2)
		{
			mid = lo + (num & 1 ? half : (half - 1)) * width;
			if (!(result = (*compare)(key, mid, context)))
				return(mid);
			else if (result < 0)
			{
				hi = mid - width;
				num = num & 1 ? half : half - 1;
			}
			else {
				lo = mid + width;
				num = half;
			}
		}
		else if (num)
			return((*compare)(key, lo, context) ? NULL : lo);
		else
			break;

	return(NULL);
}

/***
*char *lfind(key, base, num, width, compare, context) - do a linear search
*
*Purpose:
*       Performs a linear search on the array, looking for the value key
*       in an array of num elements of width bytes in size.  Returns
*       a pointer to the array value if found, NULL if not found.
*
*Entry:
*       char *key - key to search for
*       char *base - base of array to search
*       unsigned *num - number of elements in array
*       int width - number of bytes in each array element
*       int (*compare)() - pointer to function that compares two
*               array values, returning 0 if they are equal and non-0
*               if they are different.  Two pointers to array elements
*               are passed to this function.
*
*Exit:
*       if key found:
*               returns pointer to array element
*       if key not found:
*               returns NULL
*
*Exceptions:
*
*******************************************************************************/

const void* lfind_c(
	const void* key,
	const void* base,
	size_t num,
	size_t width,
	int (*compare)(const void*, const void*, const void*),
	const void* context
)
{
	size_t place = 0;
	while (place < num)
		if (!(*compare)(key, base, context))
			return((void*)base);
		else
		{
			base = (char*)base + width;
			place++;
		}
	return(NULL);
}

/***
*qsort.c - quicksort algorithm; qsort() library function for sorting arrays
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       To implement the qsort() routine for sorting arrays.
*
*******************************************************************************/


/* prototypes for local routines */
static void shortsort_c(char* lo, char* hi, size_t width,
	int (*comp)(const void*, const void*, const void*),
	const void* context);
static void swap_c(char* p, char* q, size_t width);

/* this parameter defines the cutoff between using quick sort and
   insertion sort for arrays; arrays with lengths shorter or equal to the
   below value use insertion sort */

#define QSORT_CUTOFF 8            /* testing shows that this is good value */


   /***
   *qsort(base, num, wid, comp, context) - quicksort function for sorting arrays
   *
   *Purpose:
   *       quicksort the array of elements
   *       side effects:  sorts in place
   *
   *Entry:
   *       char *base = pointer to base of array
   *       unsigned num  = number of elements in the array
   *       unsigned width = width in bytes of each array element
   *       int (*comp)() = pointer to function returning analog of strcmp for
   *               strings, but supplied by user for comparing the array elements.
   *               it accepts 2 pointers to elements and returns neg if 1<2, 0 if
   *               1=2, pos if 1>2.
   *
   *Exit:
   *       returns void
   *
   *Exceptions:
   *
   *******************************************************************************/

   /* sort the array between lo and hi (inclusive) */

void qsort_c(
	void* base,
	size_t num,
	size_t width,
	int (*compare)(const void*, const void*, const void*),
	const void* context
)
{
	char* lo, * hi;              /* ends of sub-array currently sorting */
	char* mid;                  /* points to middle of subarray */
	char* loguy, * higuy;        /* traveling pointers for partition step */
	size_t size;              /* size of the sub-array */
	char* lostk[30], * histk[30];
	int stkptr;                 /* stack for saving sub-array to be processed */

	/* Note: the number of stack entries required is no more than
	   1 + log2(size), so 30 is sufficient for any array */

	if (num < 2 || width == 0)
		return;                 /* nothing to do */

	stkptr = 0;                 /* initialize stack */

	lo = (char*)base;
	hi = (char*)base + width * (num - 1);        /* initialize limits */

	/* this entry point is for pseudo-recursion calling: setting
	   lo and hi and jumping to here is like recursion, but stkptr is
	   prserved, locals aren't, so we preserve stuff on the stack */
recurse:

	size = (hi - lo) / width + 1;        /* number of el's to sort */

	/* below a certain size, it is faster to use a O(n^2) sorting method */
	if (size <= QSORT_CUTOFF) {
		shortsort_c(lo, hi, width, compare, context);
	}
	else {
		/* First we pick a partititioning element.  The efficiency of the
		   algorithm demands that we find one that is approximately the
		   median of the values, but also that we select one fast.  Using
		   the first one produces bad performace if the array is already
		   sorted, so we use the middle one, which would require a very
		   wierdly arranged array for worst case performance.  Testing shows
		   that a median-of-three algorithm does not, in general, increase
		   performance. */

		mid = lo + (size / 2) * width;      /* find middle element */
		swap_c(mid, lo, width);               /* swap it to beginning of array */

		/* We now wish to partition the array into three pieces, one
		   consisiting of elements <= partition element, one of elements
		   equal to the parition element, and one of element >= to it.  This
		   is done below; comments indicate conditions established at every
		   step. */

		loguy = lo;
		higuy = hi + width;

		/* Note that higuy decreases and loguy increases on every iteration,
		   so loop must terminate. */
		for (;;) {
			/* lo <= loguy < hi, lo < higuy <= hi + 1,
			   A[i] <= A[lo] for lo <= i <= loguy,
			   A[i] >= A[lo] for higuy <= i <= hi */

			do {
				loguy += width;
			} while (loguy <= hi && compare(loguy, lo, context) <= 0);

			/* lo < loguy <= hi+1, A[i] <= A[lo] for lo <= i < loguy,
			   either loguy > hi or A[loguy] > A[lo] */

			do {
				higuy -= width;
			} while (higuy > lo && compare(higuy, lo, context) >= 0);

			/* lo-1 <= higuy <= hi, A[i] >= A[lo] for higuy < i <= hi,
			   either higuy <= lo or A[higuy] < A[lo] */

			if (higuy < loguy)
				break;

			/* if loguy > hi or higuy <= lo, then we would have exited, so
			   A[loguy] > A[lo], A[higuy] < A[lo],
			   loguy < hi, highy > lo */

			swap_c(loguy, higuy, width);

			/* A[loguy] < A[lo], A[higuy] > A[lo]; so condition at top
			   of loop is re-established */
		}

		/*     A[i] >= A[lo] for higuy < i <= hi,
			   A[i] <= A[lo] for lo <= i < loguy,
			   higuy < loguy, lo <= higuy <= hi
		   implying:
			   A[i] >= A[lo] for loguy <= i <= hi,
			   A[i] <= A[lo] for lo <= i <= higuy,
			   A[i] = A[lo] for higuy < i < loguy */

		swap_c(lo, higuy, width);     /* put partition element in place */

		/* OK, now we have the following:
			  A[i] >= A[higuy] for loguy <= i <= hi,
			  A[i] <= A[higuy] for lo <= i < higuy
			  A[i] = A[lo] for higuy <= i < loguy    */

			  /* We've finished the partition, now we want to sort the subarrays
				 [lo, higuy-1] and [loguy, hi].
				 We do the smaller one first to minimize stack usage.
				 We only sort arrays of length 2 or more.*/

		if (higuy - 1 - lo >= hi - loguy) {
			if (lo + width < higuy) {
				lostk[stkptr] = lo;
				histk[stkptr] = higuy - width;
				++stkptr;
			}                           /* save big recursion for later */

			if (loguy < hi) {
				lo = loguy;
				goto recurse;           /* do small recursion */
			}
		}
		else {
			if (loguy < hi) {
				lostk[stkptr] = loguy;
				histk[stkptr] = hi;
				++stkptr;               /* save big recursion for later */
			}

			if (lo + width < higuy) {
				hi = higuy - width;
				goto recurse;           /* do small recursion */
			}
		}
	}

	/* We have sorted the array, except for any pending sorts on the stack.
	   Check if there are any, and do them. */

	--stkptr;
	if (stkptr >= 0) {
		lo = lostk[stkptr];
		hi = histk[stkptr];
		goto recurse;           /* pop subarray from stack */
	}
	else
		return;                 /* all subarrays done */
}


/***
*shortsort_c(hi, lo, width, comp) - insertion sort for sorting short arrays
*
*Purpose:
*       sorts the sub-array of elements between lo and hi (inclusive)
*       side effects:  sorts in place
*       assumes that lo < hi
*
*Entry:
*       char *lo = pointer to low element to sort
*       char *hi = pointer to high element to sort
*       unsigned width = width in bytes of each array element
*       int (*comp)() = pointer to function returning analog of strcmp for
*               strings, but supplied by user for comparing the array elements.
*               it accepts 2 pointers to elements and returns neg if 1<2, 0 if
*               1=2, pos if 1>2.
*
*Exit:
*       returns void
*
*Exceptions:
*
*******************************************************************************/

static void shortsort_c(
	char* lo,
	char* hi,
	size_t width,
	int (*comp)(const void*, const void*, const void*),
	const void* context
)
{
	char* p, * max;

	/* Note: in assertions below, i and j are alway inside original bound of
	   array to sort. */

	while (hi > lo) {
		/* A[i] <= A[j] for i <= j, j > hi */
		max = lo;
		for (p = lo + width; p <= hi; p += width) {
			/* A[i] <= A[max] for lo <= i < p */
			if (comp(p, max, context) > 0) {
				max = p;
			}
			/* A[i] <= A[max] for lo <= i <= p */
		}

		/* A[i] <= A[max] for lo <= i <= hi */

		swap_c(max, hi, width);

		/* A[i] <= A[hi] for i <= hi, so A[i] <= A[j] for i <= j, j >= hi */

		hi -= width;

		/* A[i] <= A[j] for i <= j, j > hi, loop top condition established */
	}
	/* A[i] <= A[j] for i <= j, j > lo, which implies A[i] <= A[j] for i < j,
	   so array is sorted */
}


/***
*swap_c(a, b, width) - swap two elements
*
*Purpose:
*       swaps the two array elements of size width
*
*Entry:
*       char *a, *b = pointer to two elements to swap
*       unsigned width = width in bytes of each array element
*
*Exit:
*       returns void
*
*Exceptions:
*
*******************************************************************************/

static void swap_c(
	char* a,
	char* b,
	size_t width
)
{
	char tmp;

	if (a != b)
		/* Do the swap one character at a time to avoid potential alignment
		   problems. */
		while (width--) {
			tmp = *a;
			*a++ = *b;
			*b++ = tmp;
		}
}
