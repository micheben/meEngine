#include "PIL/meTypes.h"
using namespace meEngine;

meString meEngine::meToString(int val) { return std::to_wstring(val); };
meString meEngine::meToString(long val) { return std::to_wstring(val); };
meString meEngine::meToString(long long val) { return std::to_wstring(val); };
meString meEngine::meToString(unsigned val) { return std::to_wstring(val); };
meString meEngine::meToString(unsigned long val) { return std::to_wstring(val); };
meString meEngine::meToString(unsigned long long val) { return std::to_wstring(val); };
meString meEngine::meToString(float val) { return std::to_wstring(val); };
meString meEngine::meToString(double val) { return std::to_wstring(val); };