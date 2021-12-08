XsVerts decltype(Xs)::LoadOBJ(const char* filename, XsEnum mode = Xs.Enum.Vertex) {
	const std::string filename_str = filename;
	XsVerts _vert;
	std::vector<vex3f> _vertex_positions;
	std::vector<vex2f> _vertex_texcoords;
	std::vector<vex3f> _vertex_normals;

	std::vector<GLint> _vertex_position_indicies;
	std::vector<GLint> _vertex_texcoord_indicies;
	std::vector<GLint> _vertex_normal_indicies;

	std::stringstream _ss;
	std::ifstream _in_file(filename_str);
	std::string _line = "";
	std::string _prefix = "";
	vex3f _temp_vec3;
	vex2f _temp_vec2;
	GLint _temp_glint = 0;

	if (!_in_file.is_open()) {
		std::cout << filename_str + " OBJ file Cannot Open.\n";
		Xs.Log << (filename_str + " OBJ file Cannot Open.\n").c_str();
		return _vert;
	}
	else {
		while (std::getline(_in_file, _line)) {
			_ss.clear();
			_ss.str(_line);
			_ss >> _prefix;

			if (_prefix == "v") {
				_ss >> _temp_vec3.x >> _temp_vec3.y >> _temp_vec3.z;
				_vertex_positions.push_back(_temp_vec3);
			}
			else if (_prefix == "vt") {
				_ss >> _temp_vec2.x >> _temp_vec2.y;
				_vertex_texcoords.push_back(_temp_vec2);
			}
			else if (_prefix == "vn") {
				_ss >> _temp_vec3.x >> _temp_vec3.y >> _temp_vec3.z;
				_vertex_normals.push_back(_temp_vec3);
			}
			else if (_prefix == "f") {
				size_t _counter = 0;
				while (_ss >> _temp_glint) {
					if (_counter == 0)
						_vertex_position_indicies.push_back(_temp_glint);
					else if (_counter == 1)
						_vertex_texcoord_indicies.push_back(_temp_glint);
					else if (_counter == 2)
						_vertex_normal_indicies.push_back(_temp_glint);

					if (_ss.peek() == '/') {
						++_counter;
						_ss.ignore(1, '/');
					}
					else if (_ss.peek() == ' ') {
						++_counter;
						_ss.ignore(1, ' ');
					}

					if (_counter > 2)
						_counter = 0;
				}
			}
		}
		_vert.clear();
		switch (mode) {
		case XsEnum::Vertex:
			_vert.resize(_vertex_position_indicies.size() * 3, 0);
			for (size_t i = 0; i < _vertex_position_indicies.size(); i++) {
				_vert[i * 3] = _vertex_positions[_vertex_position_indicies[i] - 1].x;
				_vert[i * 3 + 1] = _vertex_positions[_vertex_position_indicies[i] - 1].y;
				_vert[i * 3 + 2] = _vertex_positions[_vertex_position_indicies[i] - 1].z;
			}
			break;
		case XsEnum::VertexAndTexture:
			_vert.resize(_vertex_position_indicies.size() * 5, 0);
			for (size_t i = 0; i < _vertex_position_indicies.size(); i++) {
				_vert[i * 5] = _vertex_positions[_vertex_position_indicies[i] - 1].x;
				_vert[i * 5 + 1] = _vertex_positions[_vertex_position_indicies[i] - 1].y;
				_vert[i * 5 + 2] = _vertex_positions[_vertex_position_indicies[i] - 1].z;
				_vert[i * 5 + 3] = _vertex_texcoords[_vertex_texcoord_indicies[i] - 1].x;
				_vert[i * 5 + 4] = _vertex_texcoords[_vertex_texcoord_indicies[i] - 1].y;
			}
			break;
		case XsEnum::VertexAndNormal:
			_vert.resize(_vertex_position_indicies.size() * 6, 0);
			for (size_t i = 0; i < _vertex_position_indicies.size(); i++) {
				_vert[i * 6] = _vertex_positions[_vertex_position_indicies[i] - 1].x;
				_vert[i * 6 + 1] = _vertex_positions[_vertex_position_indicies[i] - 1].y;
				_vert[i * 6 + 2] = _vertex_positions[_vertex_position_indicies[i] - 1].z;
				_vert[i * 6 + 3] = _vertex_normals[_vertex_normal_indicies[i] - 1].x;
				_vert[i * 6 + 4] = _vertex_normals[_vertex_normal_indicies[i] - 1].y;
				_vert[i * 6 + 5] = _vertex_normals[_vertex_normal_indicies[i] - 1].z;
			}
			break;
		case XsEnum::All:
			_vert.resize(_vertex_position_indicies.size() * 8, 0);
			for (size_t i = 0; i < _vertex_position_indicies.size(); i++) {
				_vert[i * 8] = _vertex_positions[_vertex_position_indicies[i] - 1].x;
				_vert[i * 8 + 1] = _vertex_positions[_vertex_position_indicies[i] - 1].y;
				_vert[i * 8 + 2] = _vertex_positions[_vertex_position_indicies[i] - 1].z;
				_vert[i * 8 + 3] = _vertex_texcoords[_vertex_texcoord_indicies[i] - 1].x;
				_vert[i * 8 + 4] = _vertex_texcoords[_vertex_texcoord_indicies[i] - 1].y;
				_vert[i * 8 + 5] = _vertex_normals[_vertex_normal_indicies[i] - 1].x;
				_vert[i * 8 + 6] = _vertex_normals[_vertex_normal_indicies[i] - 1].y;
				_vert[i * 8 + 7] = _vertex_normals[_vertex_normal_indicies[i] - 1].z;
			}
			break;
		default:
			_vert.resize(_vertex_position_indicies.size() * 3, 0);
			for (size_t i = 0; i < _vertex_position_indicies.size(); i++) {
				_vert[i * 3] = _vertex_positions[_vertex_position_indicies[i] - 1].x;
				_vert[i * 3 + 1] = _vertex_positions[_vertex_position_indicies[i] - 1].y;
				_vert[i * 3 + 2] = _vertex_positions[_vertex_position_indicies[i] - 1].z;
			}
			break;
		}
	};
	return _vert;
};