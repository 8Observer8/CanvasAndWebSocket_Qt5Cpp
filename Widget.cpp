#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

#include "Widget.h"

Widget::Widget()
{
    setWindowTitle("QPainter, QWebSocket");
    setFixedSize(QSize(256, 256));

    connect(&m_webSocket, &QWebSocket::connected, this, &Widget::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Widget::onMessageReceived);

//    QUrl url("ws://localhost:3000");
    QUrl url("ws://canvas-and-websocket-js.herokuapp.com");
    m_webSocket.open(url);
}

void Widget::onConnected()
{
    m_connectionMessage = "Connection was completed";

    // Send a message to a server
    QJsonObject jsonObject;
    jsonObject["msg"] = "Hello, server!";
    QJsonDocument doc(jsonObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    m_webSocket.sendTextMessage(strJson);

    update();
}

void Widget::onMessageReceived(const QString &message)
{
    qDebug() << message; // Output: "{\"msg\":\"Hello, client!\"}"
    QJsonDocument doc(QJsonDocument::fromJson(message.toUtf8()));
    QJsonObject data = doc.object();
    m_outputMessage = data["msg"].toString(); // Output: "Hello, client!"

    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // White stone
    painter.setBrush(QBrush(QColor("#ffffff")));
    painter.drawEllipse( QRect( 0, 0, 32, 32 ) );

    // Black stone
    painter.setBrush(QBrush(QColor("#000000")));
    painter.drawEllipse( QRect( 0, 32, 32, 32 ) );

    // The game text
    QFont font = painter.font();
    font.setPixelSize(14);
    font.setFamily("Consolas");
    painter.setFont(font);
    painter.drawText(50, 50, "The Game");

    // Connection text
    painter.drawText(50, 100, m_connectionMessage);

    // Output text
    painter.drawText(50, 150, m_outputMessage);

    // Segment
    painter.drawLine(QPoint(32, 64), QPoint(196, 64));
}
