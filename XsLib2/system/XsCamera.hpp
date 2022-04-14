#undef near
#undef far
class XsCamera {
public:
	XsCamera() = default;
	vex3f pos = 0.f, rot = 0.f;
	vex2ui viewport = Xs.Sett.WindowSize;
	inline mat4 projectionMatrix() const { return glm::perspective(45.0f, (f32)viewport.x / (f32)viewport.y, 0.05f, 100.0f); };
	inline mat4 viewMatrix() const { return _viewMatrix; };
	inline mat4& viewMatrix() { return _viewMatrix; };
	operator str() const {
		str t;
		t += "[Pos     ]: "s + pos.str(", ", "\n");
		t += "[Rot     ]: "s + rot.str(", ", "\n");
		t += "[ViewPort]: "s + viewport.str(", ", "\n");
		return t;
	};
	friend std::ostream& operator<<(std::ostream& os, const XsCamera& v) { return os << (str)v; };
	void fps(const f32& _sensivity, const vex2f& _mouse_pos) {
		const auto& m_pos = _mouse_pos * _sensivity;
		const f32& _yaw = m_pos.x;
		const f32& _pitch = (m_pos.y > 89.9f) ? 89.9f : (m_pos.y < -89.9f) ? -89.9f : m_pos.y;
		glm::vec3 position = glm::normalize(glm::vec3(0, 1, 0));
		glm::vec3 t_rot = glm::vec3(0, 0, 0);
		t_rot.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		t_rot.y = -sin(glm::radians(_pitch));
		t_rot.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		glm::vec3 rott = glm::normalize(t_rot);
		glm::vec3 right = glm::normalize(glm::cross(rott, position));
		glm::vec3 up = glm::normalize(glm::cross(right, rott));
		_viewMatrix = glm::lookAt(position, position + rott, up) * glm::translate(glm::mat4(1.f), glm::vec3(-pos.x, -pos.y + 1, -pos.z));
		rot << t_rot;
	};
	void editor(const f32& sensivity = 0.3f) {
		static vex2f last_mouse_pos = 0.f;
		static bool mouse_press = false;
		if (Xs.Key.Pressed(Xs.Mouse.Right)) {
			if (Xs.Event.type == 8) {
				if (Xs.Event.mouseWheelScroll.delta == 1)
					Xs.Editor.Cam.Speed_v += 0.0001f;
				else if (Xs.Event.mouseWheelScroll.delta == -1)
					Xs.Editor.Cam.Speed_v -= 0.0001f;
				if (Xs.Editor.Cam.Speed_v < 0.0001f) Xs.Editor.Cam.Speed_v = 0.0001f;
			}
			if (Xs.Key.Pressed(Xs.Key.W) && !Xs.Key.Pressed(Xs.Key.Space))
				Xs.Editor.Cam.Speed += rot * (Xs.Editor.Cam.Speed_v);
			else if (Xs.Key.Pressed(Xs.Key.S) && !Xs.Key.Pressed(Xs.Key.Space))
				Xs.Editor.Cam.Speed -= rot * (Xs.Editor.Cam.Speed_v);
			const vex2f f_pos = Xs.Mouse.Pos() - last_mouse_pos;
			const vex2f sm_pos = Xs.Editor.Cam.Rot + f_pos;
			Xs.Editor.Cam.RotVel = (sm_pos - Xs.Editor.Cam.Rot) / 17.5;
			last_mouse_pos += Xs.Editor.Cam.RotVel;
		}
		else mouse_press = false;
		if (mouse_press == false) {
			last_mouse_pos = Xs.Mouse.Pos();
			mouse_press = true;
		};
		if (!Xs.Key.Pressed(Xs.Key.S) && !Xs.Key.Pressed(Xs.Key.W))
			Xs.Editor.Cam.Speed *= 0.95;
		if (Xs.Key.Pressed(Xs.Key.Space))
			Xs.Editor.Cam.Speed *= 0.75f;
		pos += Xs.Editor.Cam.Speed;
		Xs.Editor.Cam.RotVel *= 0.88;
		Xs.Editor.Cam.Rot += Xs.Editor.Cam.RotVel;
		fps(sensivity, Xs.Editor.Cam.Rot);
	};
	void use() {
		glScissor(0, 0, viewport.x, viewport.y);
		glViewport(0, 0, viewport.x, viewport.y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glm::mat4 _ftransform = projectionMatrix() * viewMatrix();
		glLoadMatrixf(&_ftransform[0][0]);
		glMatrixMode(GL_MODELVIEW);
	};
private:
	mat4 _viewMatrix = mat4(1.f);
};