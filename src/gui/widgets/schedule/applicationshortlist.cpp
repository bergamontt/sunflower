#include "applicationshortlist.h"
#include "applicationlist.h"
#include "ui_applicationshortlist.h"
#include <qnamespace.h>

using namespace sun::persistence;

ApplicationShortList::ApplicationShortList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationShortList)
{
    ui->setupUi(this);
}

ApplicationShortList::~ApplicationShortList()
{
    delete ui;
}

void ApplicationShortList::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateText();
}

void ApplicationShortList::setApplicationLists(QList<ApplicationList> appicationLists)
{
    listNames.clear();
    for(const ApplicationList& applicationList : appicationLists)
    {
        if(applicationList.name.has_value() && !applicationList.name->isEmpty())
            listNames.append(*applicationList.name);
    }
    listNames.sort(Qt::CaseSensitive);
    updateText();
}

void ApplicationShortList::updateText()
{
    if(listNames.empty())
    {
        ui->text->setText("No applications selected.");
        return;
    }
         
    const int availableWidth = ui->text->contentsRect().width();
    const QFontMetrics metrics(ui->text->font());

    for (int omitted = 0; omitted < listNames.size(); ++omitted) {
        const int fitted = listNames.size() - omitted;

        QString text = listNames.mid(0, fitted).join(", ");

        if (omitted > 0)
        {
            text += ", ";
            text += QString("+%1").arg(omitted);
        }

        if (metrics.horizontalAdvance(text) <= availableWidth)
        {
            ui->text->setText(text);
            return;
        }
    }

    if(listNames.size() == 1)
        ui->text->setText("1 list");
    else
        ui->text->setText(QString("%1 lists").arg(listNames.size()));
}
