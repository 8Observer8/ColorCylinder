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

#include "LoaderOfCylinder.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

LoaderOfCylinder::LoaderOfCylinder( const QString &fileName ) :
    isSuccessfully( true )
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile( fileName.toStdString(),
                                             aiProcess_Triangulate );

    if ( scene == 0 )
    {
        std::cerr << "Error in 'LoaderOfCylinder::LoaderOfCylinder(...)': "
                     "'scene == 0' Unable to open the file" +
                     fileName.toStdString() << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE )
    {
        std::cerr << "Error in 'LoaderOfCylinder::LoaderOfCylinder(...)': "
                     "'scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE'" << std::endl;
        isSuccessfully = false;
        return;
    }

    if ( scene->mRootNode == 0 )
    {
        std::cerr << "Error in 'LoaderOfCylinder::LoaderOfCylinder(...)': "
                     "'scene->mRootNode == 0'" << std::endl;
        isSuccessfully = false;
        return;
    }

    init( scene );
}

LoaderOfCylinder::~LoaderOfCylinder()
{

}

void LoaderOfCylinder::init( const aiScene *scene )
{
    for ( unsigned int i = 0; i < scene->mRootNode->mNumChildren; ++i )
    {
        const aiNode *node = scene->mRootNode->mChildren[i];
        const aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];
        const aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        aiString name;
        material->Get( AI_MATKEY_NAME, name );

        if ( std::string( name.C_Str() ) == std::string( "TopMaterial" ) )
        {
            fillVertices( mesh, verticesOfTop );
            fillColors( mesh, material, colorsOfTop );
            fillNormals( mesh, normalsOfTop );
        }
        else if ( std::string( name.C_Str() ) == std::string( "SideMaterial" ) )
        {
            fillVertices( mesh, verticesOfSide );
            fillColors( mesh, material, colorsOfSide );
            fillNormals( mesh, normalsOfSide );
        }
        else if ( std::string( name.C_Str() ) == std::string( "BottomMaterial" ) )
        {
            fillVertices( mesh, verticesOfBottom );
            fillColors( mesh, material, colorsOfBottom );
            fillNormals( mesh, normalsOfBottom );
        }
    }
}

void LoaderOfCylinder::fillVertices( const aiMesh *mesh,
                   std::vector<float> &vertices )
{
    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        vertices.push_back( mesh->mVertices[i].x );
        vertices.push_back( mesh->mVertices[i].y );
        vertices.push_back( mesh->mVertices[i].z );
    }
}

void LoaderOfCylinder::fillColors( const aiMesh *mesh, const aiMaterial *material,
                 std::vector<float> &colors )
{
    aiColor4D color;
    aiGetMaterialColor( material, AI_MATKEY_COLOR_DIFFUSE, &color );

    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        colors.push_back( color.r );
        colors.push_back( color.g );
        colors.push_back( color.b );
    }
}

void LoaderOfCylinder::fillNormals( const aiMesh *mesh,
                                    std::vector<float> &normals )
{
    for ( unsigned int i = 0; i < mesh->mNumVertices; ++i )
    {
        normals.push_back( mesh->mNormals[i].x );
        normals.push_back( mesh->mNormals[i].y );
        normals.push_back( mesh->mNormals[i].z );
    }
}
