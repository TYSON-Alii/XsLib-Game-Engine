#include <chrono>
class XsChrono {
private:
	std::chrono::time_point<std::chrono::system_clock> _create = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> _start = std::chrono::system_clock::now(), _end = std::chrono::system_clock::now();
public:
	XsChrono() = default;
	const std::chrono::time_point<std::chrono::system_clock> startTime() { return _create; };
	f32 timeAfterCreation() { return (f32)std::chrono::duration_cast<std::chrono::milliseconds>(_create - std::chrono::system_clock::now()).count() / 1000.f; };
	inline void restart() { _start = std::chrono::system_clock::now(); };
	inline void reset() { _start = _create = std::chrono::system_clock::now(); };
	bool froze = false;
	inline uint getSeconds() {
		if (!froze) _end = std::chrono::system_clock::now();
		return (uint)std::chrono::duration_cast<std::chrono::seconds>(_end - _start).count();
	};
	f32 getMilliSeconds() {
		if (!froze) _end = std::chrono::system_clock::now();
		return (f32)std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count() / 1000.f;
	};
	f64 getMicroSeconds() {
		if (!froze) _end = std::chrono::system_clock::now();
		return (f64)std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count() / 1000000.0;
	};
};
bool XsLimiter(XsChrono& v, f32 limit) {
	if (limit < v.getMilliSeconds()) {
		v.restart();
		return true;
	};
	return false;
};