#include <chrono>
class XsChrono {
private:
	std::chrono::time_point<std::chrono::system_clock> _create = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> _start = std::chrono::system_clock::now(), _end = std::chrono::system_clock::now();
public:
	XsChrono() = default;
	const std::chrono::time_point<std::chrono::system_clock> getStartTime() { return _create; };
	float timeAfterCreation() { return (float)std::chrono::duration_cast<std::chrono::milliseconds>(_create - std::chrono::system_clock::now()).count() / 1000.f; };
	void restart() { _start = std::chrono::system_clock::now(); };
	void reset() {
		_create = std::chrono::system_clock::now();
		_start = std::chrono::system_clock::now();
	};
	bool froze = false;
	int getSeconds() {
		if (!froze)
			_end = std::chrono::system_clock::now();
		return (int)std::chrono::duration_cast<std::chrono::seconds>(_end - _start).count();
	};
	float getMilliSeconds() {
		if (!froze)
			_end = std::chrono::system_clock::now();
		return (float)std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count() / 1000.f;
	};
	double getMicroSeconds() {
		if (!froze)
			_end = std::chrono::system_clock::now();
		return (double)std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count() / 1000000.0;
	};
};
bool XsLimiter(XsChrono& v, float limit) {
	if (limit < v.getMilliSeconds()) {
		v.restart();
		return true;
	};
	return false;
};