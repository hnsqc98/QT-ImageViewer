#ifndef DLGLOG_H
#define DLGLOG_H

#include <QDialog>

namespace Ui {
class DlgLog;
}

class DlgLog : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLog(QWidget *parent = nullptr);
    ~DlgLog();

public slots:
    void accept();

signals:
    void confirmed(double);

private:
    Ui::DlgLog *ui;
};

#endif // DLGLOG_H
