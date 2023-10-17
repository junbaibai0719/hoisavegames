#include "line.h"
#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

Line::Line()
{
    setFlag(QQuickItem::ItemHasContents, true);
    m_relativeX = 0;
    m_relativeY = 0;
}

QSGNode *Line::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;
    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setLineWidth(1);
        geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        auto *material = new QSGFlatColorMaterial;
        material->setColor(QColor(0, 0, 0));
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(2);
    }
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    vertices[0].set(0, 0);
    vertices[1].set(relativeX(), relativeY());
    node->markDirty(QSGNode::DirtyGeometry);
    setScenePos(mapToScene(position()));
    return node;
}



float Line::relativeX() const
{
    return m_relativeX;
}

void Line::setRelativeX(float newRelativeX)
{
    if (qFuzzyCompare(m_relativeX, newRelativeX)) {
        return;
    }
    m_relativeX = newRelativeX;
    emit relativeXChanged();
    update();
}

float Line::relativeY() const
{
    return m_relativeY;
}

void Line::setRelativeY(float newRelativeY)
{
    if (qFuzzyCompare(m_relativeY, newRelativeY)) {
        return;
    }
    m_relativeY = newRelativeY;
    emit relativeYChanged();
    update();
}

QPointF Line::scenePos() const
{
    return m_scenePos;
}

void Line::setScenePos(QPointF newScenePos)
{
    if (m_scenePos == newScenePos) {
        return;
    }
    m_scenePos = newScenePos;
    emit scenePosChanged();
}
