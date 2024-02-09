#include "BisConsole.h"
#include "Chaine.h"
#include "Interface.h"

/// <summary>
/// Permet � l'utilisateur d'encoder une valeur enti�re
/// <para>L'encodage ne se termine que sur une r�ussite de conversion de ce qui a �t� encod� en une valeur enti�re, de type long
/// </summary>
/// <returns>Valeur num�rique encod�e</returns>
long EncoderEntier()
{
	char chaineEncodee[254 + 1];
	while (true)
	{
		printf("> ");
		gets(chaineEncodee);
		const char* messageErreur;
		long valeur;
		if (CChaine::EnEntier(chaineEncodee, messageErreur, valeur)) return valeur;
		AfficherMessageErreur(messageErreur);
	}
}

/// <summary>
/// Permet � l'utilisateur d'encoder une valeur r�elle
/// <para>L'encodage ne se termine que sur une r�ussite de conversion de ce qui a �t� encod� en une valeur r�elle, de type double
/// </summary>
/// <returns>Valeur num�rique encod�e</returns>
double EncoderReel()
{
	char chaineEncodee[254 + 1];
	while (true)
	{
		printf("> ");
		gets(chaineEncodee);
		const char* messageErreur;
		double valeur;
		if (CChaine::EnReel(chaineEncodee, messageErreur, valeur)) return valeur;
		AfficherMessageErreur(messageErreur);
	}
}

/// <summary>
/// Permet d'afficher un message d'erreur, en rouge, dans la console
/// <para>La valeur retourn�e correspond par d�faut � false, sinon on peut la changer avec le second param�tre qui est optionnel</para>
/// </summary>
/// <param name="messageErreur">Message d�crivant l'erreur</param>
/// <param name="valeurARetourner">Valeur bool�enne que la fonction doit retourner</param>
/// <returns>Valeur bool�enne � retourner</returns>
bool AfficherMessageErreur(const char* messageErreur, bool valeurARetourner)
{
#ifdef BIS_CONSOLE_HEADER
	ColorCode couleur = console_get_textcolor();
	console_set_textcolor(ColorCode::Red);
#endif
	printf("%s\n", messageErreur);
#ifdef BIS_CONSOLE_HEADER
	console_set_textcolor(couleur);
#endif
	return valeurARetourner;
}

/// <summary>
/// Permet d'attendre que l'utilisateur appuie sur une touche
/// </summary>
/// <param name="caractereAttendu">Caract�re (ou code de caract�re) que l'utilisateur doit encoder par la frappe d'une touche</param>
/// <param name="finMessage">Fin du message pr�cisant qu'on attend que l'utilisateur appuie sur [telle touche] pour [faire quelque chose]</param>
void AttendreTouche(char caractereAttendu, const char* finMessage)
{
	char nomTouche[6 + 1];
	switch (caractereAttendu)
	{
	case TOUCHE_ESPACE:
		strcpy(nomTouche, "ESPACE");
		break;
	case TOUCHE_RETURN:
		strcpy(nomTouche, "RETURN");
		break;
	case TOUCHE_ESC:
		strcpy(nomTouche, "ESC");
		break;
	case TOUCHE_TAB:
		strcpy(nomTouche, "TAB");
		break;
	default:
		*nomTouche = caractereAttendu;
		nomTouche[1] = 0;
		break;
	}
	if (finMessage != NULL)
	{
		printf("\nVeuillez appuyer sur la touche %s pour %s", nomTouche, finMessage);
	}
	else
	{
		printf("\nVeuillez appuyer sur la touche %s", nomTouche);
	}
	while (getch() != caractereAttendu);
	printf("\n");
}

/// <summary>
/// Permet � l'utilisateur de r�pondre par oui ou par non � une question
/// </summary>
/// <param name="question">Texte de la question</param>
/// <returns>Vrai si l'utilisateur r�pond oui, sinon faux (pour non)</returns>
bool RepondreOuiNon(const char* question)
{
	if (question == NULL) return false;
	printf("%s (O/N)", question);
	while (true)
	{
		switch (getch())
		{
		case 'O':
		case 'o':
			printf(" Oui\n");
			return true;
		case 'N':
		case 'n':
			printf(" Non\n");
			return false;
		}
	}
}

/// <summary>
/// Permet d'attendre que l'utilisateur appuie sur une touche afin de fournir un caract�re parmi ceux autoris�s
/// </summary>
/// <param name="caracteresAutorises">Cha�ne de caract�res contenant le ou les caract�res autoris�s</param>
char AttendreCaractere(const char* caracteresAutorises)
{
	if ((caracteresAutorises == NULL) || (*caracteresAutorises == 0)) return false;
	while (true)
	{
		char caractereEncode = getch();
		if (strchr(caracteresAutorises, caractereEncode) != NULL) return caractereEncode;
	}
}
