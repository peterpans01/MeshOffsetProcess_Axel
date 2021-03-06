// /////////////////////////////////////////////////////////////////
// Generated by axel-plugin wizard
// /////////////////////////////////////////////////////////////////

/* (C) MyCompany */


/* Put a short description of your plugin here */

/* MyCompany-contact@mycompany.com-http://www.mycompany.com */

#ifndef MYPLUGINDEFAULTDATADIALOG_H
#define MYPLUGINDEFAULTDATADIALOG_H

#include <axlGui/axlInspectorObjectFactory.h>

#include "MyPluginPluginExport.h"


class dtkAbstractData;

class MyPluginDefaultDataDialogPrivate;

class MYPLUGINPLUGIN_EXPORT MyPluginDefaultDataDialog : public axlInspectorObjectInterface
{
    Q_OBJECT
    
public:
    MyPluginDefaultDataDialog(QWidget *parent = 0);
    ~MyPluginDefaultDataDialog(void);
    
    QSize sizeHint(void) const;
    
    static bool registered(void);
    
signals:
    
    void colorChanged(QColor color,  dtkAbstractData *data);
    
    void dataChangedByShader(dtkAbstractData *data, QString isophoteShaderXml);
    void dataChangedByOpacity(dtkAbstractData *data, double opacity);
    
    void dataChangedByColor(dtkAbstractData *data, double red, double green, double blue);
    void dataChangedByGeometry(dtkAbstractData *data);
    
    void update(void);
    
public slots:
    void setData(dtkAbstractData *data);
    
    void onColorChanged(QColor color);
    void onOpacityChanged(int opacity);
    
    void openShader(void);
    void onShaderStateChanged(bool isShader);
    void onShaderChanged(QString);
    void onLineEditShaderChanged(QString);
    
private :
    void initComboBoxShaderValue(void);
    void initWidget(void);
    int initOpacityValue(void);
    QString initShaderValue(void);
    QColor initColorValue(void);
    
    MyPluginDefaultDataDialogPrivate *d;
};

axlInspectorObjectInterface *createMyPluginDefaultDataDialog(void);


#endif // MYPLUGINDEFAULTDATADIALOG_H

