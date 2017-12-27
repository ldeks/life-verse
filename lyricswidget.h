#ifndef LYRICSWIDGET_H
#define LYRICSWIDGET_H

#include <QLabel>
#include <QStandardItemModel>
#include <QStringList>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>

class LyricsWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit LyricsWidget(QWidget *parent = 0);
    ~LyricsWidget();

    bool eventFilter(QObject* watched, QEvent* event);

  public slots:
    void setLyrics(QStringList lyrics, QStringList order);

  signals:
    void simpleKeyPress(int key);

  private:
    QWidget* lyricsWidget;
    QVBoxLayout* lyricsLayout;
    QLabel* lyricsLabel;
    QTableView* lyricsView;
    QStandardItemModel* lyricsModel;
    QStringList lyricsList;
    QStringList orderList;
    int baseRowHeight;
};

#endif // LYRICSWIDGET_H
