#pragma once

class TestRenderable : public Renderable
{
public:
    int id;
    TestRenderable(int id) : id(id) {}
    void draw() {}
    const std::string unitName() const { return std::string(); } 
};
