#ifndef APPLICATIONSHORTLIST_H
#define APPLICATIONSHORTLIST_H

#include <QWidget>
#include <memory>
#include "applicationlist/applicationlist.h"
#include "applicationlist/iapplicationlistservice.h"

namespace Ui {
class ApplicationShortList;
}

class ApplicationShortList : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationShortList(QWidget *parent = nullptr);
    ~ApplicationShortList();

    void setApplicationLists(QList<sun::persistence::ApplicationList>);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::ApplicationShortList *ui;
    QStringList listNames;

    void updateText();

    std::unique_ptr<sun::core::IApplicationListService> applicationListService;
};

#endif // APPLICATIONSHORTLIST_H
