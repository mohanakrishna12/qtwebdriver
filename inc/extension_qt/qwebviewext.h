#ifndef QWEBVIEWEXT_H
#define QWEBVIEWEXT_H

#include <QtCore/QGlobalStatic>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWebKitWidgets/QWebView>
#else
#include <QtWebKit/QtWebKit>
#endif

class QWebViewExt : public QWebView
{
    Q_OBJECT
public:
    explicit QWebViewExt(QWidget *parent = 0);
    ~QWebViewExt();


protected:
    QWebView* createWindow(QWebPage::WebWindowType type);
    
};

#endif // QWEBVIEWEXT_H
