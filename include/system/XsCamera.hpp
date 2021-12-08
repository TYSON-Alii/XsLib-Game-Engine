class XsCamera {
private:
	glm::mat4 _viewMatrix = glm::mat4(1.f);
public:
	inline XsCamera(const std::string& _name) { name = _name; };
	std::string name;
	vex3f pos = 0;
	vex3f rot = 0;
	inline glm::mat4 projectionMatrix() const;
	inline glm::mat4 viewMatrix() const { return _viewMatrix; };
	inline glm::mat4& viewMatrix() { return _viewMatrix; };
	friend std::ostream& operator<<(std::ostream& os, const XsCamera& v);
};
void XsFPSCamera(XsCamera& cam, vex2f _mouse_pos, float _sensivity) {
	float _yaw = _mouse_pos.x * _sensivity;
	float _pitch = (_mouse_pos.y * _sensivity > 89.9f) ? 89.9f : (_mouse_pos.y * _sensivity < -89.9f) ? -89.9f : (_mouse_pos.y * _sensivity);
	glm::vec3 position = glm::normalize(glm::vec3(0, 1, 0));
	glm::vec3 t_rot = glm::vec3(0, 0, 0);
	t_rot.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	t_rot.y = -sin(glm::radians(_pitch));
	t_rot.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	glm::vec3 rott = glm::normalize(t_rot);
	glm::vec3 right = glm::normalize(glm::cross(rott, position));
	glm::vec3 up = glm::normalize(glm::cross(right, rott));
	cam.rot.x = t_rot.x;
	cam.rot.y = t_rot.y;
	cam.rot.z = t_rot.z;
};
void XsEditorCamera(XsCamera& cam) {
	static vex2f last_mouse_pos = 0.f;
	static bool mouse_press = false;
	if (Xs.KeyPressed(Xs.Mouse.Button.Right)) {
		if (Xs.Event.type == 8) {
			if		(Xs.Event.mouseWheelScroll.delta == 1)	Xs.Editor.Cam.Speed_v += 0.0001f;
			else if (Xs.Event.mouseWheelScroll.delta == -1)	Xs.Editor.Cam.Speed_v -= 0.0001f;

			if (Xs.Editor.Cam.Speed_v < 0.0001f) Xs.Editor.Cam.Speed_v = 0.0001f;
		}
		if (Xs.KeyPressed(Xs.Key.W) && !Xs.KeyPressed(Xs.Key.Space))
			Xs.Editor.Cam.Speed += cam.rot * (Xs.Editor.Cam.Speed_v);
		else if (Xs.KeyPressed(Xs.Key.S) && !Xs.KeyPressed(Xs.Key.Space))
			Xs.Editor.Cam.Speed -= cam.rot * (Xs.Editor.Cam.Speed_v);
		const vex2f f_pos = Xs.Mouse.Pos() - last_mouse_pos;
		const vex2f sm_pos = Xs.Editor.Cam.Rot + f_pos;
		Xs.Editor.Cam.RotVel = (sm_pos - Xs.Editor.Cam.Rot) / 17.5;
		last_mouse_pos += Xs.Editor.Cam.RotVel;
	}
	else
		mouse_press = false;
	if (mouse_press == false) {
		last_mouse_pos = Xs.Mouse.Pos();
		mouse_press = true;
	};
	if (!Xs.KeyPressed(Xs.Key.S) && !Xs.KeyPressed(Xs.Key.W))
		Xs.Editor.Cam.Speed *= 0.95;
	if (Xs.KeyPressed(Xs.Key.Space))
		Xs.Editor.Cam.Speed *= 0.75f;
	cam.pos += Xs.Editor.Cam.Speed;
	Xs.Editor.Cam.RotVel *= 0.88;
	Xs.Editor.Cam.Rot += Xs.Editor.Cam.RotVel;
};