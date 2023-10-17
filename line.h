#ifndef LINE_H
#define LINE_H

#include <QQuickItem>

class Line : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(float relativeX READ relativeX WRITE setRelativeX NOTIFY relativeXChanged FINAL)
    Q_PROPERTY(float relativeY READ relativeY WRITE setRelativeY NOTIFY relativeYChanged FINAL)
    Q_PROPERTY(QPointF scenePos READ scenePos WRITE setScenePos NOTIFY scenePosChanged FINAL)
public:
    Line();

    float relativeX() const;
    void setRelativeX(float newRelativeX);

    float relativeY() const;
    void setRelativeY(float newRelativeY);


    QPointF scenePos() const;
    void setScenePos(QPointF newScenePos);

signals:


    // QQuickItem interface
    void relativeXChanged();

    void relativeYChanged();

    void scenePosChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
private:
    float m_relativeX;
    float m_relativeY;
    QPointF m_scenePos;
};

#endif // LINE_H
