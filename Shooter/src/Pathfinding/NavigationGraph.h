#pragma once
#include "raylib.h"
#include <vector>
#include "../Core/Camera.h"

class NavigationGraph {
private:
    std::vector<Vector2> nodes;
    float nodeSpacing = 32.0f;  // Distance between nodes, adjust as needed
    float m_minY = 0;
    float m_maxY = 0;

public:
    void Generate(float worldWidth, float minY, float maxY) {
        nodes.clear();

        m_minY = minY;
        m_maxY = maxY;

        // Generate nodes in the walkable area
        for (float x = 0; x < 2248; x += nodeSpacing) {
            for (float y = minY; y <= maxY; y += nodeSpacing) {
                nodes.push_back({ x, y });
            }
        }
    }

    void Draw(CameraController& camera) {
        Vector2 cameraOffset = camera.getCameraOffset();

        // Draw each node
        for (const auto& node : nodes) {
            // Adjust position based on camera
            Vector2 screenPos = {
                node.x - cameraOffset.x,
                node.y
            };

            // Only draw nodes that are on screen
            if (screenPos.x >= 0 && screenPos.x <= 2148) {
                DrawCircle(screenPos.x, screenPos.y, 2, RED);  // Small red dots for nodes

                // Draw connections to next node (horizontal)
                if (node.x + nodeSpacing < 2148) {
                    Vector2 nextNode = { screenPos.x + nodeSpacing, screenPos.y };
                    DrawLineV(screenPos, nextNode, BLUE);
                }

                // Draw connections to node below (vertical)
                if (node.y + nodeSpacing <= m_maxY) {
                    Vector2 nodeBelow = { screenPos.x, screenPos.y + nodeSpacing };
                    DrawLineV(screenPos, nodeBelow, BLUE);
                }
            }
        }
    }
};
