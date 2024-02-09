#ifndef INTERFACE_H
#define INTERFACE_H

#define TOUCHE_ESPACE 32
#define TOUCHE_RETURN 13
#define TOUCHE_ESC 27
#define TOUCHE_TAB 9

/// <summary>
/// Permet à l'utilisateur d'encoder une valeur entière
/// <para>L'encodage ne se termine que sur une réussite de conversion de ce qui a été encodé en une valeur entière, de type long
/// </summary>
/// <returns>Valeur numérique encodée</returns>
long EncoderEntier();

/// <summary>
/// Permet à l'utilisateur d'encoder une valeur réelle
/// <para>L'encodage ne se termine que sur une réussite de conversion de ce qui a été encodé en une valeur réelle, de type double
/// </summary>
/// <returns>Valeur numérique encodée</returns>
double EncoderReel();

/// <summary>
/// Permet d'afficher un message d'erreur, en rouge, dans la console
/// <para>La valeur retournée correspond par défaut à false, sinon on peut la changer avec le second paramètre qui est optionnel</para>
/// </summary>
/// <param name="messageErreur">Message décrivant l'erreur</param>
/// <param name="valeurARetourner">Valeur booléenne que la fonction doit retourner</param>
/// <returns>Valeur booléenne à retourner</returns>
bool AfficherMessageErreur(const char* messageErreur, bool valeurARetourner = false);

/// <summary>
/// Permet d'attendre que l'utilisateur appuie sur une touche
/// </summary>
/// <param name="caractereAttendu">Caractère (ou code de caractère) que l'utilisateur doit encoder par la frappe d'une touche</param>
/// <param name="finMessage">Fin du message précisant qu'on attend que l'utilisateur appuie sur [telle touche] pour [faire quelque chose]</param>
void AttendreTouche(char caractereAttendu, const char* finMessage);

/// <summary>
/// Permet à l'utilisateur de répondre par oui ou par non à une question
/// </summary>
/// <param name="question">Texte de la question</param>
/// <returns>Vrai si l'utilisateur répond oui, sinon faux (pour non)</returns>
bool RepondreOuiNon(const char* question);

/// <summary>
/// Permet d'attendre que l'utilisateur appuie sur une touche afin de fournir un caractère parmi ceux autorisés
/// </summary>
/// <param name="caracteresAutorises">Chaîne de caractères contenant le ou les caractères autorisés</param>
char AttendreCaractere(const char* caracteresAutorises);

#endif//INTERFACE_H
