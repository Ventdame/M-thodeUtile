#ifndef INTERFACE_H
#define INTERFACE_H

#define TOUCHE_ESPACE 32
#define TOUCHE_RETURN 13
#define TOUCHE_ESC 27
#define TOUCHE_TAB 9

/// <summary>
/// Permet � l'utilisateur d'encoder une valeur enti�re
/// <para>L'encodage ne se termine que sur une r�ussite de conversion de ce qui a �t� encod� en une valeur enti�re, de type long
/// </summary>
/// <returns>Valeur num�rique encod�e</returns>
long EncoderEntier();

/// <summary>
/// Permet � l'utilisateur d'encoder une valeur r�elle
/// <para>L'encodage ne se termine que sur une r�ussite de conversion de ce qui a �t� encod� en une valeur r�elle, de type double
/// </summary>
/// <returns>Valeur num�rique encod�e</returns>
double EncoderReel();

/// <summary>
/// Permet d'afficher un message d'erreur, en rouge, dans la console
/// <para>La valeur retourn�e correspond par d�faut � false, sinon on peut la changer avec le second param�tre qui est optionnel</para>
/// </summary>
/// <param name="messageErreur">Message d�crivant l'erreur</param>
/// <param name="valeurARetourner">Valeur bool�enne que la fonction doit retourner</param>
/// <returns>Valeur bool�enne � retourner</returns>
bool AfficherMessageErreur(const char* messageErreur, bool valeurARetourner = false);

/// <summary>
/// Permet d'attendre que l'utilisateur appuie sur une touche
/// </summary>
/// <param name="caractereAttendu">Caract�re (ou code de caract�re) que l'utilisateur doit encoder par la frappe d'une touche</param>
/// <param name="finMessage">Fin du message pr�cisant qu'on attend que l'utilisateur appuie sur [telle touche] pour [faire quelque chose]</param>
void AttendreTouche(char caractereAttendu, const char* finMessage);

/// <summary>
/// Permet � l'utilisateur de r�pondre par oui ou par non � une question
/// </summary>
/// <param name="question">Texte de la question</param>
/// <returns>Vrai si l'utilisateur r�pond oui, sinon faux (pour non)</returns>
bool RepondreOuiNon(const char* question);

/// <summary>
/// Permet d'attendre que l'utilisateur appuie sur une touche afin de fournir un caract�re parmi ceux autoris�s
/// </summary>
/// <param name="caracteresAutorises">Cha�ne de caract�res contenant le ou les caract�res autoris�s</param>
char AttendreCaractere(const char* caracteresAutorises);

#endif//INTERFACE_H
