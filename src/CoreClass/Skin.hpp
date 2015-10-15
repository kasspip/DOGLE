#ifndef SKIN_HPP
# define SKIN_HPP

# include "DOGLE.hpp"
# include "IComponent.hpp"
# include <assimp/cimport.h>
# include <assimp/scene.h>
# include <assimp/postprocess.h>
# include <assimp/Importer.hpp>
# include <iterator>
#include <iostream>
#include <vector>

	class Skin : public IComponent
	{
		public:

			Skin(void);
			Skin(std::string obj);
			Skin(Skin const &src);
			~Skin(void);
		
			Skin &operator=(Skin const &rhs);
			
			std::string 	toString(void) const;
			void			Save(std::ofstream &file);
			bool			GetIsBind();
			void			SetIsBind(bool val);

			unsigned int	nb_vertices;
			GLfloat			*positions;
			GLfloat			*UVs;
			GLfloat			*normals;

			GLuint			positionsBind;
			GLuint			UVsBind;
			GLuint			normalsBind;

			GLuint			vao;

			int				texture_h;
			int				texture_w;
			unsigned char	*texture_data;
			std::string		texture_file;
			GLuint			textureBind;

			aiColor4D		diffuse;
			aiColor4D		specular;
			aiColor4D		ambient;

		private:

			GLfloat			*_Construct3DArray(aiVector3D *vec, unsigned int sz);
			GLfloat			*_Construct2DArray(aiVector3D *vec, unsigned int sz);
			GLfloat			*_CopyArray(GLfloat *vec, unsigned int sz);
			void			_flipTextureData(unsigned char *data, int w, int h);
			void			_flipYZAxis(GLfloat *data, unsigned int size);
			static std::string	_3Dobjects_path;
			static std::string	_images_path;
			std::string			_dae_file;
			bool				_isBind;
	};

	std::ostream	&operator<<(std::ostream &o, Skin const &rhs);

#endif
