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

#include "Cylinder.h"
#include <iostream>

Cylinder::Cylinder( QOpenGLShaderProgram *program, int vertexAttrLoc,
                    int colorAttrLoc, int normalAttrLoc) :
    m_program( program ),
    m_vertexAttrLoc( vertexAttrLoc ),
    m_colorAttrLoc( colorAttrLoc ),
    m_normalAttrLoc( normalAttrLoc )
{

}

Cylinder::~Cylinder()
{

}

void Cylinder::loadFromLoader( const LoaderOfCylinder *loader )
{
    m_verticesOfTop = loader->verticesOfTop;
    m_colorsOfTop = loader->colorsOfTop;
    m_normalsOfTop = loader->normalsOfTop;

    m_verticesOfSide = loader->verticesOfSide;
    m_colorsOfSide = loader->colorsOfSide;
    m_normalsOfSide = loader->normalsOfSide;

    m_verticesOfBottom = loader->verticesOfBottom;
    m_colorsOfBottom = loader->colorsOfBottom;
    m_normalsOfBottom = loader->normalsOfBottom;
}

void Cylinder::draw()
{
    draw( m_verticesOfTop, m_colorsOfTop, m_normalsOfTop );
    draw( m_verticesOfSide, m_colorsOfSide, m_normalsOfSide );
    draw( m_verticesOfBottom, m_colorsOfBottom, m_normalsOfBottom );
}

void Cylinder::draw( const std::vector<float> &vertices,
                     const std::vector<float> &colors,
                     const std::vector<float> &normals)
{
    static bool isSuccessfully = true;

    if ( !isSuccessfully )
        return;

    if ( vertices.empty() )
    {
        std::cerr << "Error in 'void Cylinder::draw(...)': "
                     "vertices.empty() == true" << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( colors.empty() )
    {
        std::cerr << "Error in 'void Cylinder::draw(...)': "
                     "colors.empty() == true" << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( normals.empty() )
    {
        std::cerr << "Error in 'void Cylinder::draw(...)': "
                     "normals.empty() == true" << std::endl;
        isSuccessfully = false;
        return;
    }

    m_program->setAttributeArray( m_vertexAttrLoc, vertices.data(), 3 );
    m_program->setAttributeArray( m_colorAttrLoc, colors.data(), 3 );
    m_program->setAttributeArray( m_normalAttrLoc, normals.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttrLoc );
    m_program->enableAttributeArray( m_colorAttrLoc );
    m_program->enableAttributeArray( m_normalAttrLoc );

    glDrawArrays( GL_TRIANGLES, 0, vertices.size() / 3 );

    m_program->disableAttributeArray( m_vertexAttrLoc );
    m_program->disableAttributeArray( m_colorAttrLoc );
    m_program->disableAttributeArray( m_normalAttrLoc );
}

