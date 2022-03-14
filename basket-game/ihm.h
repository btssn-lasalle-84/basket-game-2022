#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHM
 * @author
 * @version 1.0
 *
 */

#include <QtWidgets>

/**
 * @def TEST_IHM
 * @brief Pour le mode test (raccourcis clavier)
 */
#define TEST_IHM

/**
 * @def PLEIN_ECRAN
 * @brief Pour le mode kiosque de la télévision
 */
#define PLEIN_ECRAN

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHM;
}
QT_END_NAMESPACE

/**
 * @class IHM
 * @brief Déclaration de la classe IHM
 * @details Cette classe s'occupe de l'affichage sur l'écran de télévision
 */
class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    IHM(QWidget* parent = nullptr);
    ~IHM();

  private:
    Ui::IHM* ui; //!< la fenêtre graphique associée à cette classe

    /**
     * @enum Fenetre
     * @brief Définit les différents fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        Principale = 0,
        Finale,
        NbFenetres
    };

#ifdef TEST_IHM
    void fixerRaccourcisClavier();
#endif

  public slots:
    void afficherFenetre(IHM::Fenetre fenetre);
    void afficherFenetrePrecedente();
    void afficherFenetreSuivante();
    void quitter();
};

#endif // IHM_H
