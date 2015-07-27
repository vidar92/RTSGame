#include "StdAfx.h"
#include "Terrain.h"
#include <Windows.h>
#include <glew.h>
#include <wglew.h>
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <SOIL.h>
#include <vector>

Terrain::Terrain(int w,int h)
{
	w++;
	h++;
	//zrób punkty ziemi
	for(int x=0;x<w;x++)
	{
		for(int y=0;y<h;y++)
		{
			sMapEnityPos temp = {64*x,0.0,64*y};
			Terrain::pMapVertices.push_back(temp);
		}
	}

	int c=1;
	int inc=1;
	//ustaw indices
	//for(int i=0;i<w-1;i++)
//	{
		for(int i=0;i<(w-1)*(h-1)+(w-2);i++)
		{
			float a=(float)c;
			float b=(float)(w);

			if(fmod(a,b)==0)
			{
				//inc=2;
				i+=1;
				c+=1;
			}

			Terrain::indices.push_back(i);
			Terrain::indices.push_back(i+inc);
			Terrain::indices.push_back(i+w+inc);


			Terrain::indices.push_back(i);
			Terrain::indices.push_back(i+w);
			Terrain::indices.push_back(i+w+inc);


			c++;

		}

		sTextureCoord tex1={0,1};
			Terrain::pMapTextureCoord.push_back(tex1);
			sTextureCoord tex2={0,0};
			Terrain::pMapTextureCoord.push_back(tex2);
			sTextureCoord tex3={1,1};
			Terrain::pMapTextureCoord.push_back(tex3);
			sTextureCoord tex4={1,0};
			Terrain::pMapTextureCoord.push_back(tex4);

			Terrain::pMapTextureCoord.push_back(tex1);
			
			Terrain::pMapTextureCoord.push_back(tex2);
			
			Terrain::pMapTextureCoord.push_back(tex3);
	
			Terrain::pMapTextureCoord.push_back(tex4);


			Terrain::pMapTextureCoord.push_back(tex4);



//	}

		

	LoadTExture();
}

void Terrain::LoadTExture()
{
	this->textureID = SOIL_load_OGL_texture
	(
		"brick.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );

	if( 0 == this->textureID )
	{
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

 
	//glBindTexture(GL_TEXTURE_2D,Terrain::textureID);

	glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void Terrain::Draw(int w,int h)
{
	float colors[] = { // Colors for the vertices (NEW)
      1.0f, 0.0f, 0.0f, 1.0f, // Red (NEW)
      0.0f, 1.0f, 0.0f, 1.0f, // Green (NEW)
      0.0f, 0.0f, 1.0f, 1.0f, // Blue (NEW)
	   0.0f, 1.0f, 1.0f, 1.0f,  // Blue (NEW)

	    1.0f, 0.0f, 0.0f, 1.0f, // Red (NEW)
      0.0f, 1.0f, 0.0f, 1.0f, // Green (NEW)
      0.0f, 0.0f, 1.0f, 1.0f, // Blue (NEW)
	   0.0f, 1.0f, 1.0f, 1.0f,  // Blue (NEW)

	      0.0f, 1.0f, 1.0f, 1.0f,  // Blue (NEW)
   };

	
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	/*for(int x=0;x<Terrain::indices.size();x+=3)
	{

			glBindTexture(GL_TEXTURE_2D, this->textureID);
			glBegin(GL_TRIANGLES);
				glNormal3f(0,1,0);

				glTexCoord2f(0,0);
				glVertex3f(Terrain::pMapVertices[Terrain::indices[x]].x,Terrain::pMapVertices[Terrain::indices[x]].y,Terrain::pMapVertices[Terrain::indices[x]].z);

				glTexCoord2f(1,0);
				glVertex3f(Terrain::pMapVertices[Terrain::indices[x+1]].x,Terrain::pMapVertices[Terrain::indices[x+1]].y,Terrain::pMapVertices[Terrain::indices[x+1]].z);

				glTexCoord2f(1,1);
				glVertex3f(Terrain::pMapVertices[Terrain::indices[x+2]].x,Terrain::pMapVertices[Terrain::indices[x+2]].y,Terrain::pMapVertices[Terrain::indices[x+2]].z);
			glEnd();

		//glBegin(GL_POINTS);
	//		glVertex3f(Terrain::pMapVertices[x].x,Terrain::pMapVertices[x].y,Terrain::pMapVertices[x].z);
	//	glEnd();
	}*/
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY); 
	glVertexPointer(3,GL_FLOAT,sizeof(sMapEnityPos),&(Terrain::pMapVertices[0]));
	glTexCoordPointer(2,GL_FLOAT,0,&(Terrain::pMapTextureCoord[0]));
	glColorPointer(4, GL_FLOAT, 0, colors);
	//glDrawArrays( GL_TRIANGLES, 0, Terrain::pMapVertices.size());
	glDrawElements(GL_TRIANGLES,Terrain::indices.size(),GL_UNSIGNED_INT,&(Terrain::indices[0]));
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
}

Terrain::~Terrain(void)
{
}
