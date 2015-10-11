#include "Skin.hpp"

// CONSTRUCTOR DESTRUCTOR //

std::string	Skin::_3Dobjects_path = std::string("resources/3D objects/");
std::string	Skin::_images_path = std::string("resources/images/");


Skin::Skin(std::string obj) : _dae_file(obj)
{
	Assimp::Importer	importer;
	const aiScene		*scene = importer.ReadFile((_3Dobjects_path + _dae_file).c_str(), aiProcess_Triangulate);

	if (!scene)
		throw DError() << msg("[Skin] " + _3Dobjects_path + obj + ": Invalid COLLADA file.");
	if (scene->mNumMeshes != 1)
		throw DError() << msg("[Skin] " + obj + ": Handle only one mesh.");
	if (scene->mNumMaterials != 1)
		throw DError() << msg("[Skin] " + obj + ": Handle only one material.");
	
	const aiMaterial* mat = scene->mMaterials[0];
	if (mat->GetTextureCount(aiTextureType_DIFFUSE) != 1)
		throw DError() << msg("[Skin] " + obj + ": Diffuse propertie has to be one texture.");
	
	const aiMesh*	mesh = scene->mMeshes[0];
	aiString		path;

	nb_vertices = mesh->mNumVertices;
	vertices = _Construct3DArray(mesh->mVertices, nb_vertices);
	normals = _Construct3DArray(mesh->mNormals, nb_vertices);
	textures = _Construct2DArray(mesh->mTextureCoords[0], nb_vertices);
	mat->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL);
	texture_file = _images_path + std::string(path.C_Str());
	if (!(texture_data = SOIL_load_image(texture_file.c_str(), &texture_w, &texture_h, 0, SOIL_LOAD_RGBA)))
		throw DError() << msg("[Skin] " + texture_file + ": SOIL load image return NULL.");
	mat->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	mat->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	importer.FreeScene();
}


Skin::Skin(Skin const & src)
{
	*this = src;
}

Skin::~Skin(void)
{
	SOIL_free_image_data(texture_data);
	delete [] vertices;
	delete [] normals;
	delete [] textures;
	std::cout << "destruct Skin" << std::endl;
}

GLfloat		*Skin::_Construct3DArray(aiVector3D *vec, unsigned int sz)
{
	GLfloat	*ret;

	ret = new GLfloat[sz * 3];
	for (unsigned int i = 0; i < sz; ++i)
	{
		ret[i * 3] = (GLfloat)vec[i].x;
		ret[i * 3 + 1] = (GLfloat)vec[i].y;
		ret[i * 3 + 2] = (GLfloat)vec[i].z;
	}
	return (ret);
}

GLfloat		*Skin::_Construct2DArray(aiVector3D *vec, unsigned int sz)
{
	GLfloat	*ret;

	ret = new GLfloat[sz * 2];
	for (unsigned int i = 0; i < sz; ++i)
	{
		ret[i * 2] = (GLfloat)vec[i].x;
		ret[i * 2 + 1] = (GLfloat)vec[i].y;
	}
	return (ret);
}

GLfloat		*Skin::_CopyArray(GLfloat *vec, unsigned int sz)
{
	GLfloat	*ret;

	ret = new GLfloat[sz];
	std::copy(vec, vec + sz, ret);
	return (ret);
}

Skin	&Skin::operator=(Skin const & rhs)
{
	_dae_file = rhs._dae_file;
	nb_vertices = rhs.nb_vertices;
	vertices = _CopyArray(rhs.vertices, nb_vertices * 3);
	normals = _CopyArray(rhs.normals, nb_vertices * 3);
	textures = _CopyArray(rhs.textures, nb_vertices * 2);
	texture_file = rhs.texture_file;
	if (!(texture_data = SOIL_load_image(texture_file.c_str(), &texture_w, &texture_h, 0, SOIL_LOAD_RGBA)))
		throw DError() << msg("[Skin] " + _images_path + ": SOIL load image return NULL.");
	diffuse = rhs.diffuse;
	specular = rhs.specular;
	ambient = rhs.ambient;
	return *this;
}

std::ostream	&operator<<(std::ostream & o, Skin const & rhs)
{
	o << rhs.toString();
	return o;
}

void		color_to_stream(std::stringstream &ss, const std::string nm, const aiColor4D &c)
{
	ss << "[Color] " << nm << " : r = " << c.r << " g = " << c.g << " b = " << c.b << " a = " << c.a << std::endl; 
}

std::string		Skin::toString(void) const
{
	std::stringstream ss;
	ss << "COLLADA file :" << _dae_file << "\n";
	ss << "Texture file :" << texture_file << "\n";
	ss << "Array vertices =\n";
	for (unsigned int i = 0; i < nb_vertices; ++i)
		ss << "v[" << i << "]\t" << vertices[i * 3] << "\t" << vertices[i * 3 + 1] << "\t" << vertices[i * 3 + 2] << "\n";
	ss << "Array normals =\n";
	for (unsigned int i = 0; i < nb_vertices; ++i)
		ss << "v[" << i << "]\t" << normals[i * 3] << "\t" << normals[i * 3 + 1] << "\t" << normals[i * 3 + 2] << "\n";
	ss << "Array textures =\n";
	for (unsigned int i = 0; i < nb_vertices; ++i)
		ss << "t[" << i << "]\t" << textures[i * 2] << "\t" << textures[i * 2 + 1] << "\n";
	color_to_stream(ss, "diffuse", diffuse);
	color_to_stream(ss, "specular", specular);
	color_to_stream(ss, "ambient", ambient);
	ss << "Texture : h = " << texture_h << " w = " << texture_w << std::endl;
	for (int i = 0; i <= texture_w * texture_h; ++i)
	{
		if (!(i % texture_w) && i) ss << std::endl;
		ss << (static_cast<unsigned int>(texture_data[i])) << " ";
	}
	return ss.str();
}

void			Skin::Save(std::ofstream &file)
{
	file << "\t\t\tSKIN : " << _dae_file <<std::endl;
}






