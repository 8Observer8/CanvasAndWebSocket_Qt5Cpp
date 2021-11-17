#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QPainter>
#include <QtWidgets/QWidget>
#include <QtWebSockets/QWebSocket>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();

private slots:
    void onConnected();
    void onMessageReceived(const QString &message);

private:
    void paintEvent(QPaintEvent *event) override;

    QWebSocket m_webSocket;
    QString m_connectionMessage = "Waiting for connection...";
    QString m_outputMessage;
};

#endif // WIDGET_H
