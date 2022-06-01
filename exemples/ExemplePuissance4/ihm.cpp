#include "ihm.h"
#include "ui_ihm.h"

#include <QAction>
#include <QPainter>

Ihm::Ihm(QWidget *parent) : QWidget(parent), ui(new Ui::Ihm) {
  ui->setupUi(this);
  qDebug() << Q_FUNC_INFO;

  // Raccourcis claviers (mode debug)
  attribuerRaccourcisClavier();

  afficherPlateau();
}

Ihm::~Ihm() {
  delete ui;
  qDebug() << Q_FUNC_INFO;
}

void Ihm::attribuerRaccourcisClavier() {
  QAction *quitter = new QAction(this);
  quitter->setShortcut(QKeySequence(
      QKeySequence(Qt::Key_Up))); // fleche du haut pour quitter l'application
  addAction(quitter);
  connect(quitter, SIGNAL(triggered()), this,
          SLOT(fermerApplication())); // Pour fermer l'application

#ifndef QT_NO_DEBUG_OUTPUT
  QAction *actionEquipeRouge = new QAction(this);
  actionEquipeRouge->setShortcut(QKeySequence(Qt::Key_Right));
  addAction(actionEquipeRouge);
  connect(actionEquipeRouge, SIGNAL(triggered()), this,
          SLOT(simulerEquipeRouge()));
  QAction *actionEquipeJaune = new QAction(this);
  actionEquipeJaune->setShortcut(QKeySequence(Qt::Key_Left));
  addAction(actionEquipeJaune);
  connect(actionEquipeJaune, SIGNAL(triggered()), this,
          SLOT(simulerEquipeJaune()));
  QAction *actionReset = new QAction(this);
  actionReset->setShortcut(QKeySequence(Qt::Key_Down));
  addAction(actionReset);
  connect(actionReset, SIGNAL(triggered()), this, SLOT(afficherPlateau()));
#endif
}

void Ihm::afficherPanier(int ligne, int colonne, QString equipe) {
  QImage pionRouge(":/ressources/r.png");
  QImage pionJaune(":/ressources/j.png");
  QPixmap plateau = ui->labelVisualisationPlateau->pixmap()
                        ->copy(); // on récupère l'image précédente

  QPainter p(&plateau);

  if (equipe == "R")
    p.drawImage(QPoint(42 + (colonne * 60), 321 - (ligne * 60)), pionRouge);
  else if (equipe == "J")
    p.drawImage(QPoint(42 + (colonne * 60), 321 - (ligne * 60)), pionJaune);

  // rangée la plus basse
  // p.drawImage(QPoint(42 + (0 * 60), 321 - (0 * 60)), pionRouge);
  // p.drawImage(QPoint(42 + (1 * 60), 321 - (0 * 60)), pionJaune);
  // p.drawImage(QPoint(42 + (2 * 60), 321 - (0 * 60)), pionRouge);
  // p.drawImage(QPoint(42 + (3 * 60), 321 - (0 * 60)), pionJaune);

  // autre rangées
  // p.drawImage(QPoint(42 + (2 * 60), 321 - (3 * 60)), pionRouge);
  // p.drawImage(QPoint(42 + (2 * 60), 321 - (4 * 60)), pionJaune);

  p.end();

  ui->labelVisualisationPlateau->setPixmap(plateau);
}

void Ihm::afficherMessage(QString message) {
  ui->labelStatut->setStyleSheet(
      "color: rgb(109, 43,107); border-color: rgb(109, 43,107);");
  ui->labelStatut->setText(message);
}

void Ihm::fermerApplication() { this->close(); }

void Ihm::afficherPlateau() {
  ui->labelVisualisationPlateau->setPixmap(QPixmap(":/ressources/plateau.png"));
}

void Ihm::simulerEquipeRouge() {
  afficherPanier(0, 0, "R");
  afficherMessage("0,0 R");
}

void Ihm::simulerEquipeJaune() {
  afficherPanier(1, 0, "J");
  afficherMessage("1,0 J");
}
