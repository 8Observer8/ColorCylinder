/*
    The Color Cylinder Example

    Copyright (C) 2015  Enzhaev Ivan

    Email: 8observer8@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CYLINDER_H
#define CYLINDER_H

#include "LoaderOfCylinder.h"
#include <QOpenGLShaderProgram>

class Cylinder
{
public:
    Cylinder( QOpenGLShaderProgram *program, int vertexAttrLoc,
              int colorAttrLoc, int normalAttrLoc );
    ~Cylinder();

    void loadFromLoader( const LoaderOfCylinder *loader );

    void draw();

private:
    void draw( const std::vector<float> &vertices,
               const std::vector<float> &colors,
               const std::vector<float> &normals );

    std::vector<float> m_verticesOfTop;
    std::vector<float> m_colorsOfTop;
    std::vector<float> m_normalsOfTop;

    std::vector<float> m_verticesOfSide;
    std::vector<float> m_colorsOfSide;
    std::vector<float> m_normalsOfSide;

    std::vector<float> m_verticesOfBottom;
    std::vector<float> m_colorsOfBottom;
    std::vector<float> m_normalsOfBottom;

    QOpenGLShaderProgram *m_program;
    int m_vertexAttrLoc;
    int m_colorAttrLoc;
    int m_normalAttrLoc;
};

#endif // CYLINDER_H
