#ifndef IHM_H
#define IHM_H

#include <QTimer>
#include <QtWidgets>

namespace Ui {
class Ihm;
}

class Ihm : public QWidget {
  Q_OBJECT

public:
  explicit Ihm(QWidget *parent = nullptr);
  ~Ihm();

private:
  Ui::Ihm *ui;

  void attribuerRaccourcisClavier();
  void afficherMessage(QString message);

public slots:
  void fermerApplication();
  /************************/
  void afficherPanier(int ligne, int colonne, QString equipe);
  void afficherPlateau();
  /************************/
  void simulerEquipeRouge();
  void simulerEquipeJaune();
};

#endif // IHM_H
